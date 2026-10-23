"""Recheck the bounded link repair using the preserved build/ snapshots."""
import hashlib
import json
import shutil
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, "tools")
import build
import link_census as lc
import link_check

BASE = Path("build/path-node-getters-link-20261015")
REMOVED = {"?getNext@PathNode@@QBEPAV1@XZ", "?bfme_get_layer@PathNode@@QBE?AW4PathfindLayerEnum@@XZ"}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def normalized(obj, excluded):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    removed = [s for s in symbols if s["name"] in excluded and s["section"] > 0]
    assert {s["name"] for s in removed} == excluded
    omitted = {s["section"] for s in removed}
    leaders = {}
    for symbol in symbols:
        if symbol.get("storage") == 2 and symbol["section"] > 0:
            leaders.setdefault(symbol["section"], []).append(symbol["name"])

    def body(n):
        section = sections[n - 1]
        pointer = section["raw_pointer"]
        return data[pointer:pointer + section["raw_size"]] if pointer else b""

    def referent(i):
        symbol = symbols[i]
        n = symbol["section"]
        assert n not in omitted, "removed helper has an incoming nondebug relocation"
        if symbol["storage"] in (2, 105):
            return symbol["name"], symbol["storage"], symbol["value"]
        return ("local", symbol["value"], symbol["storage"], symbol["type"],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (), sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section["name"].startswith(".debug") or n in omitted:
            continue
        raw = body(n)
        if section["name"] == ".sxdata":
            raw = repr([referent(struct.unpack_from("<I", raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        relocs = []
        for j in range(section["reloc_count"]):
            at, symbol, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section["name"], section["characteristics"], section["raw_size"],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    return Counter(found)


paths = (BASE / 'sources.txt').read_text().splitlines()
objects = [build.obj_path(build.ROOT / p) for p in paths]
assert all(lc.object_current(build.ROOT / p, o, allow_fresh=False) for p, o in zip(paths, objects))
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256']
truth = lc.RetailTruth(lc.ledger())
proof = {}
for i, (p, obj) in enumerate(zip(paths, objects)):
    before = BASE / 'before' / obj.name
    old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
    new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
    expected = REMOVED if i == 0 else set()
    assert set(old) - set(new) == expected
    assert not set(new) - set(old)
    assert all(old[n] == new[n] for n in new)
    assert normalized(before, expected) == normalized(obj, set())
    bf, af = lc.object_facts(before, truth), lc.object_facts(obj, truth)
    assert all(set(bf[j]) == set(af[j]) for j in (1, 2, 3))
    proof[p] = {'strict_current': True, 'before_sha256': sha(before.read_bytes()),
                'after_sha256': sha(obj.read_bytes()), 'retained_comdats': len(new),
                'removed': {n: old[n] for n in expected},
                'remaining_nondebug_sections_flags_bindings_and_relocations_identical': True,
                'strong_undefined_weak_sets_identical': True}
    shutil.copy2(obj, BASE / ('after%d.obj' % i))
    shutil.copy2(obj.with_suffix('.deps.json'), BASE / ('receipt-after%d.json' % i))
assert (BASE/'before'/objects[1].name).read_bytes() == objects[1].read_bytes()
paired = {}
for label in ('before', 'after'):
    index = link_check.load_index()
    objs = [BASE/'before'/o.name for o in objects] if label == 'before' else objects
    link_check.refresh(index, objs, truth)
    paired[label] = {p: link_check.check_object(o, index, truth, p) for p,o in zip(paths, objs)}
for p in paths[:1]:
    b, a = paired['before'][p], paired['after'][p]
    assert ('?getNext@PathNode@@QBEPAV1@XZ', 'first', None) in b['comdat'], b
    assert a == {k: ([x for x in v if x[0] not in REMOVED] if k=='comdat' else v) for k,v in b.items()}
assert paired['before'][paths[1]] == paired['after'][paths[1]]
assert not any(paired['after'][paths[0]].values())
source_bytes = link_check.source_bytes(set(paths))
linked = {phase: sum(source_bytes[p] for p in paths if not any(paired[phase][p].values())) for phase in paired}
index = link_check.load_index()
family = {n: [(index['objects'][i], d, v) for i,d,v in index['comdat'].get(n, [])] for n in REMOVED}
report = {'base_commit':(BASE/'base.txt').read_text().strip(), 'index':meta,
          'objects':proof, 'family_before':family, 'witness_digest_size':new.get('?getNext@PathNode@@QBEPAV1@XZ'),
          'paired_findings':paired, 'source_bytes':source_bytes,
          'legacy_predicted_linked_bytes':linked, 'new_authored_cpp_bytes':0,
          'closed_strict_gain_claimed':False}
(BASE/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'paired_findings':paired,'source_bytes':source_bytes,'legacy_predicted_linked_bytes':linked},indent=2))
