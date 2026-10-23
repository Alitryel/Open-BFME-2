"""Same-index local predicate repair proof; saved before objects stay in ignored build/.

Section normalization helper reused from eastring-provider-link-20261015/proof.py.
"""
import hashlib
import json
import struct
import sys
from collections import Counter
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check as ck
import data_check as dc
BASE = Path('build/apt-text-predicate-link-20261015')
EVIDENCE = Path('reverse/attempt_support/apt-text-predicate-link-20261015')
OLD = '?rva006E02B0@BfmeAptValue006DCD20@@QBE_NXZ'
NEW = '?rva006E02B0@BfmeAptValue006DCD20@@QBEHXZ'
HELPER = '?isTextInst@AptCIH@@QBE_NXZ'

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

baseline = json.loads((BASE / 'baseline.json').read_text())
assert sha(ck.INDEX.read_bytes()) == baseline['index_sha256']
sources = baseline['sources']
objects = {s: build.obj_path(build.ROOT / s) for s in sources}
before = {s: BASE / 'before' / o.name for s, o in objects.items()}
assert all(lc.object_current(build.ROOT / s, o, allow_fresh=False) for s, o in objects.items())
parents = {sources[0]: '?rva006ff980@@YAXPAVAptValue@@AAVEAStringC@@H@Z',
           sources[1]: '?getVariable@AptActionInterpreter@@QAEPAVAptValue@@PAV2@0PBVEAStringC@@HHH@Z'}
retained, calls = {}, {}
for source in sources:
    excluded = {HELPER} if source == sources[0] else set()
    assert normalized(before[source], excluded=excluded, aliases={OLD: NEW}) == normalized(objects[source])
    old = {n: (d, z) for n, d, z in lc.comdat_bodies(before[source])}
    new = {n: (d, z) for n, d, z in lc.comdat_bodies(objects[source])}
    assert old.keys() - new.keys() == excluded
    assert not new.keys() - old.keys()
    assert {n for n in new if old[n] != new[n]} == ({parents[source]} if source in parents else set())
    retained[source] = len(new)
    if source in parents:
        raw_old, refs_old = build.read_object_symbol_bytes(before[source], parents[source])
        raw_new, refs_new = build.read_object_symbol_bytes(objects[source], parents[source])
        assert raw_old == raw_new
        assert refs_new == [(at, kind, NEW if name == OLD else name) for at, kind, name in refs_old]
        changed = [r for r in refs_old if r[2] == OLD]
        assert len(changed) == (2 if source == sources[0] else 1)
        calls[source] = {'bytes': len(raw_new), 'sha256': sha(raw_new), 'old_relocations': changed,
                         'new_relocations': [r for r in refs_new if r[2] == NEW]}
assert build.read_object_symbol_bytes(before[sources[0]], HELPER) == (b'\xe9\x00\x00\x00\x00', [(1, 20, OLD)])
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase in ('before', 'after'):
    index = ck.load_index()
    cohort = before if phase == 'before' else objects
    assert all(ck.in_census(index, o.name) for o in cohort.values())
    ck.refresh(index, list(cohort.values()), truth)
    paired[phase] = {s: ck.check_object(o, index, truth, source=s) for s, o in cohort.items()}
assert json.loads(json.dumps(paired['before'])) == baseline['paired_before']
expected = json.loads(json.dumps(paired['before']))
for source in sources[:2]:
    expected[source]['unresolved'].remove(OLD)
expected[sources[0]]['comdat'] = []
assert paired['after'] == expected
assert not any(paired['after'][sources[0]].values())
assert all(not ck.new_variants(o, index, truth) for o in objects.values())
rows = dc.source_rows(sources)
row_object = build.row_object
with patch.object(build, 'row_object', lambda row: before.get(row['source'], row_object(row))):
    data_before = dc.findings(dc.object_facts(rows), dc.dl.load())
data_after = dc.findings(dc.object_facts(rows), dc.dl.load())
assert data_before == data_after
counts = ck.source_bytes(set(sources))
linked = {phase: sum(counts.get(s, 0) for s, f in result.items() if not any(f.values()))
          for phase, result in paired.items()}
report = {
    'base_commit': baseline['base'], 'index_meta': baseline['index_meta'],
    'index_sha256': baseline['index_sha256'], 'strict_current_receipts': sources,
    'before_objects_sha256': {s: sha(o.read_bytes()) for s, o in before.items()},
    'after_objects_sha256': {s: sha(o.read_bytes()) for s, o in objects.items()},
    'whole_nondebug_sections_unchanged_modulo_callee_name_and_omitted_adapter': True,
    'retained_comdats': retained, 'calls': calls, 'removed_adapter_bytes': 5,
    'paired_findings': paired, 'unchanged_data_findings': data_after,
    'current_ledger_bytes_by_source': counts, 'same_index_local_linked_bytes': linked,
    'new_authored_bytes': 0, 'closed_strict_gain_claimed': False,
    'known_preview_limit': 'Matched AptValue.cpp findChild provider is absent from this legacy index; not appended or excused.'
}
(EVIDENCE / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({'paired_findings': paired, 'local_linked_bytes': linked, 'calls': calls}, indent=2))
