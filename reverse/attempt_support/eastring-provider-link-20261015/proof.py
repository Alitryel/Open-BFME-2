"""Same-index provider binding proof; saved baseline stays in ignored build/."""
import hashlib
import json
import struct
import sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check as ck
import data_check as dc
from unittest.mock import patch
BASE = Path('build/eastring-provider-link-20261015')
SOURCE = 'Code/Libraries/Source/Apt/string/EAString.cpp'
PROVIDER = 'Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp'
CANONICAL = 'Code/Libraries/Source/EA/Apt/AptString/EAStringCRefCount.cpp'
OLD = '?rva0089E2B0@Rva0089EFE0@@QAEHPBD0@Z'
NEW = '?rva006D47F0@EAStringC@@QAEHPBD0@Z'
PARENT = '?method@Rva0089EFE0@@QAEHD@Z'
ASSIGN = '??4EAStringC@@QAEAAV0@ABV0@@Z'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, excluded=(), aliases=None):
    aliases = aliases or {}
    excluded = set(excluded)
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
            return aliases.get(symbol["name"], symbol["name"]), symbol["storage"], symbol["value"]
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

objects = {s: build.obj_path(build.ROOT / s) for s in (SOURCE, PROVIDER, CANONICAL)}
before = {s: BASE / 'before' / objects[s].name for s in (SOURCE, PROVIDER)}
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(ck.INDEX.read_bytes()) == meta['sha256']
assert all(lc.object_current(build.ROOT / s, o, allow_fresh=False) for s, o in objects.items())
assert normalized(before[SOURCE], aliases={OLD: NEW}) == normalized(objects[SOURCE])
assert normalized(before[PROVIDER], excluded={ASSIGN}) == normalized(objects[PROVIDER])
retained = {}
for s in (SOURCE, PROVIDER):
    old = {n: (d, z) for n, d, z in lc.comdat_bodies(before[s])}
    new = {n: (d, z) for n, d, z in lc.comdat_bodies(objects[s])}
    assert old.keys() - new.keys() == ({ASSIGN} if s == PROVIDER else set())
    assert not new.keys() - old.keys()
    changed = {n for n in new if old[n] != new[n]}
    assert changed == ({PARENT} if s == SOURCE else set())
    retained[s] = len(new)
    if s == PROVIDER:
        removed_assignment = {'bytes': old[ASSIGN][1], 'comdat_digest': old[ASSIGN][0]}
assert build.read_object_symbol_bytes(before[PROVIDER], ASSIGN) == build.read_object_symbol_bytes(objects[CANONICAL], ASSIGN)
raw_before, refs_before = build.read_object_symbol_bytes(before[SOURCE], PARENT)
raw_after, refs_after = build.read_object_symbol_bytes(objects[SOURCE], PARENT)
assert raw_before == raw_after and len(raw_after) == 35
assert refs_after == [(at, kind, NEW if name == OLD else name) for at, kind, name in refs_before]
assert [r for r in refs_before if r[2] == OLD] == [(27, 20, OLD)]
truth = lc.RetailTruth(lc.ledger())
paired = {}
for label in ('before', 'after'):
    index = ck.load_index()
    cohort = {s: before[s] if label == 'before' and s in before else o for s, o in objects.items()}
    assert all(ck.in_census(index, o.name) for o in cohort.values())
    ck.refresh(index, list(cohort.values()), truth)
    paired[label] = {s: ck.check_object(o, index, truth, source=s) for s, o in cohort.items()}
assert OLD in paired['before'][SOURCE]['unresolved']
assert all(not any(f.values()) for f in paired['after'].values())
assert all(not ck.new_variants(o, index, truth) for o in objects.values())
data_rows = dc.source_rows(list(objects))
row_object = build.row_object
with patch.object(build, 'row_object', lambda row: before.get(row['source'], row_object(row))):
    data_before = dc.findings(dc.object_facts(data_rows), dc.dl.load())
data_after = dc.findings(dc.object_facts(data_rows), dc.dl.load())
assert data_before == data_after
byte_counts = ck.source_bytes(set(objects))
linked = {phase: sum(byte_counts[s] for s, f in results.items() if not any(f.values()))
          for phase, results in paired.items()}
report = {
 'base_commit': (BASE / 'base.txt').read_text().strip(), 'index': meta,
 'strict_current_receipts': list(objects),
 'before_objects_sha256': {s: sha(o.read_bytes()) for s, o in before.items()},
 'after_objects_sha256': {s: sha(o.read_bytes()) for s, o in objects.items()},
 'wrapper_bytes': len(raw_after), 'wrapper_bytes_sha256': sha(raw_after),
 'old_relocation': [r for r in refs_before if r[2] == OLD],
 'new_relocation': [r for r in refs_after if r[2] == NEW],
 'consumer_nondebug_sections_identical_modulo_callee_name': True,
 'provider_nondebug_sections_identical_except_removed_external_assignment': True,
 'retained_comdats': retained, 'removed_assignment': removed_assignment,
 'paired_findings': paired, 'unchanged_data_findings': data_after,
 'current_ledger_authored_bytes_by_source': byte_counts,
 'same_index_local_linked_bytes': linked,
 'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
Path('reverse/attempt_support/eastring-provider-link-20261015/proof.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({'paired_findings': paired, 'local_linked_bytes': linked, 'removed_assignment': removed_assignment}, indent=2))
