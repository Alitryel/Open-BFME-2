"""Bounded light/bird helper suppression proof; before snapshots remain in ignored build/."""
import hashlib, json, struct, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_census as lc, link_check as ck, data_check as dc
from unittest.mock import patch
BASE = Path('build/light-bird-math-link-20261015')
EVIDENCE = Path('reverse/attempt_support/light-bird-math-link-20261015')
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

sources = (EVIDENCE / 'sources.txt').read_text().splitlines()
trig = {'?sin@@YAMM@Z', '?cos@@YAMM@Z', '_sinf', '_cosf'}
ctor = '??0Matrix3D@@QAE@_N@Z'
excluded = [trig | {ctor}, trig, set(), trig]
meta = json.loads((EVIDENCE / 'index-meta.json').read_text())
assert sha(ck.INDEX.read_bytes()) == meta['sha256']
objects = [build.obj_path(build.ROOT / source) for source in sources]
before_objects = [BASE / 'before' / obj.name for obj in objects]
reports = []
for source, obj, before, removed in zip(sources, objects, before_objects, excluded):
    assert lc.object_current(build.ROOT / source, obj, allow_fresh=False)
    old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
    new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
    assert old.keys() - new.keys() == removed
    assert not new.keys() - old.keys()
    assert all(old[n] == new[n] for n in new)
    assert normalized(before, excluded=removed) == normalized(obj, excluded=(removed & trig)), source
    localized = {}
    for name in sorted(removed & trig):
        a = build.read_object_symbol_bytes(before, name, expected_size=17)
        b = build.read_object_symbol_bytes(obj, name, expected_size=17)
        assert a == b, (source, name, 'localized wrapper changed')
        localized[name] = {'bytes': len(b[0]), 'sha256': sha(b[0]), 'relocations': b[1]}
    # The normalization rejects incoming nondebug references to every excluded helper.
    def bindings(path):
        _, _, syms = build._object_layout(str(path), path.stat().st_mtime_ns, path.stat().st_size)
        return {(s['name'], s['storage'], s['section'] == 0, s['value'], s['type'])
                for s in syms if s.get('storage') in (2, 105) and s['name'] not in removed}
    assert bindings(before) == bindings(obj), source + ' binding difference'
    reports.append({'source': source, 'self_strict_current': True,
        'object_sha256': {'before': sha(before.read_bytes()), 'after': sha(obj.read_bytes())},
        'receipt_sha256': {'before': sha(before.with_suffix('.deps.json').read_bytes()),
                           'after': sha(obj.with_suffix('.deps.json').read_bytes())},
        'removed_external_comdat_copies': {n: old[n] for n in sorted(removed)},
        'localized_wrapper_bytes_and_relocations_unchanged': localized,
        'retained_comdats': len(new), 'all_retained_nondebug_sections_equal': True,
        'retained_external_and_weak_bindings_equal': True})
truth = lc.RetailTruth(lc.ledger())
paired = {}; indices = {}; selections = {}
for label, candidates in [('before', before_objects), ('after', objects)]:
    index = ck.load_index()
    ck.refresh(index, candidates, truth)
    indices[label] = index
    paired[label] = [ck.check_object(obj, index, truth, source=source)
                     for source, obj in zip(sources, candidates)]
    selections[label] = {}
    for name in sorted(trig | {ctor}):
        copies = sorted(index['comdat'][name])
        losses, rule = lc.keep_rule(copies)
        selections[label][name] = {'rule': rule, 'winners': [c for c in copies if not losses[c[0]]]}
for name in sorted(trig | {ctor}):
    before_sel = selections['before'][name]
    after_sel = selections['after'][name]
    assert before_sel['rule'] == after_sel['rule']
    assert before_sel['winners'][0] == after_sel['winners'][0], 'first kept provider changed'
    localized_ids = {indices['before']['objects'].index(obj.name)
                     for obj, names in zip(objects, excluded) if name in names}
    assert [c for c in before_sel['winners'] if c[0] not in localized_ids] == after_sel['winners'], name
for i, report in enumerate(reports):
    expected = {'?sin@@YAMM@Z', '?cos@@YAMM@Z'} | ({ctor} if i == 0 else set()) if i != 2 else set()
    assert {x[0] for x in paired['before'][i]['comdat']} == expected
    assert not any(paired['after'][i].values()), paired['after'][i]
    old_variants = ck.new_variants(before_objects[i], indices['before'], truth)
    new_variants = ck.new_variants(objects[i], indices['before'], truth)
    assert not new_variants, new_variants
    report['variant_findings'] = {'before': old_variants, 'after': new_variants}
rows = dc.source_rows(sources)
row_object = build.row_object
with patch.object(build, 'row_object', lambda row: BASE / 'before' / row_object(row).name):
    data_before = dc.object_facts(rows)
data_after = dc.object_facts(rows)
assert data_before == data_after, 'data-reference bindings changed'
findings = dc.findings(data_after, dc.dl.load())
assert not findings, findings
sizes = ck.source_bytes(set(sources))
linked = {label: sum(sizes[s] for s, f in zip(sources, checks) if not any(f.values()))
          for label, checks in paired.items()}
assert linked['after'] - linked['before'] == 1209, linked
assert sha(ck.INDEX.read_bytes()) == meta['sha256']
report = {'base_commit': (BASE / 'base.txt').read_text().strip(), 'index': meta,
    'objects': reports, 'paired_legacy_findings': paired, 'provider_selections': selections,
    'paired_legacy_local_linked_bytes': linked, 'legacy_gain_nonpadding_bytes': 1209,
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
    'data_bindings_unchanged': True, 'data_findings': findings}
(EVIDENCE / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS: thirteen competing external helper copies removed (twelve wrappers localized), retained sections/bindings/data and provider selection unchanged; strict-current objects; legacy local link gain 1209 nonpadding bytes; closed-strict gain unmeasured')
