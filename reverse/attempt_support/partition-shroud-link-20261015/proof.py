"""Object identity and conflict-removal proof, not a LINK closure measurement."""
import hashlib
import json
import shutil
import struct
import sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check
import hatch_counters

BASE = Path('build/partition-shroud-link-20261015')
OUT = Path('reverse/attempt_support/partition-shroud-link-20261015')
SOURCES = [
    'Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp',
    'Code/GameEngine/Source/Common/PartitionDataShroudStatus.cpp',
    'Code/GameEngine/Source/GameLogic/Object/ObjectGetShroudStatusForPlayer.cpp',
]
METHOD = '?getShroudedStatus@PartitionData@@QAE?AW4ObjectShroudStatus@@H@Z'
UNUSED = '?getUpdatedSinceLastReset@PartitionManager@@QBE_NXZ'
OLD_CELL = '?getShroudStatusForPlayer@PartitionCell@@QBE?AW4CellShroudStatus@@H@Z'
NEW_CELL = '?getShroudStatusForPlayer@PartitionDataShroudCellView@@QBE?AW4CellShroudStatus@@H@Z'

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
            leaders.setdefault(symbol["section"], []).append(aliases.get(symbol["name"], symbol["name"]))

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


objects = [build.obj_path(build.ROOT / p) for p in SOURCES]
before = [BASE / 'before' / o.name for o in objects]
assert all(lc.object_current(build.ROOT / p, o, allow_fresh=False)
           for p, o in zip(SOURCES, objects))
index = link_check.load_index()
meta = dict(index['meta'])
meta['sha256'] = sha(link_check.INDEX.read_bytes())
assert meta['sha256'] == json.loads((BASE/'index-meta.json').read_text())['sha256']
truth = lc.RetailTruth(lc.ledger())

# No provider is appended to the census. Its unknown order prevents a
# defensible LINK result, even though this bounded set proves the conflict.
assert not link_check.in_census(index, objects[1].name)
assert all(link_check.in_census(index, objects[i].name) for i in (0, 2))
assert normalized(before[0], excluded=[METHOD, UNUSED]) == normalized(objects[0])
assert normalized(before[1], aliases={OLD_CELL: NEW_CELL}) == normalized(objects[1])
assert normalized(before[2]) == normalized(objects[2])

old_bodies = [{n: (d, z) for n, d, z in lc.comdat_bodies(o)} for o in before]
new_bodies = [{n: (d, z) for n, d, z in lc.comdat_bodies(o)} for o in objects]
assert old_bodies[0].keys() - new_bodies[0].keys() == {METHOD, UNUSED}
assert not new_bodies[0].keys() - old_bodies[0].keys()
assert all(old_bodies[0][n] == new_bodies[0][n] for n in new_bodies[0])
assert old_bodies[1][METHOD] == new_bodies[1][METHOD]
assert old_bodies[1][OLD_CELL] == new_bodies[1][NEW_CELL]
assert old_bodies[2] == new_bodies[2]
raw, refs = build.read_object_symbol_bytes(objects[1], METHOD)
assert len(raw) == 392 and not refs
assert (METHOD, new_bodies[1][METHOD][0], 392, 'retail') in lc.object_facts(objects[1], truth)[0]
assert build.read_object_symbol_bytes(before[0], METHOD)[0] != raw

# Check defined-name conflicts between the two strictly current owners,
# independently of missing census placement. This is not a closed LINK.
def names(obj):
    copies, strong, _, _ = lc.object_facts(obj, truth)
    return set(strong) | {n for n, _, _, _ in copies}
conflicts_before = names(before[0]) & names(before[1])
conflicts_after = names(objects[0]) & names(objects[1])
assert conflicts_before == {METHOD, OLD_CELL}
assert conflicts_after == set()

paired = {}
for label, candidates in [('before', before), ('after', objects)]:
    idx = link_check.load_index()
    link_check.refresh(idx, [candidates[0], candidates[2]], truth)
    paired[label] = {SOURCES[i]: link_check.check_object(candidates[i], idx, truth, source=SOURCES[i])
                     for i in (0, 2)}
assert METHOD in paired['before'][SOURCES[2]]['selected']
assert paired['after'][SOURCES[2]] == {
    'unresolved': [METHOD], 'duplicates': [], 'comdat': [], 'addresses': [], 'selected': []}
for field in ['duplicates', 'addresses', 'unresolved']:
    assert paired['before'][SOURCES[0]][field] == paired['after'][SOURCES[0]][field]
assert set(paired['before'][SOURCES[0]]['selected']) - set(paired['after'][SOURCES[0]]['selected']) == {METHOD}
assert [x for x in paired['before'][SOURCES[0]]['comdat'] if x[0] != METHOD] == paired['after'][SOURCES[0]]['comdat']
assert not link_check.new_variants(objects[0], idx, truth,
    previous={n: {d} for n, (d, _) in old_bodies[0].items()})
assert not link_check.new_variants(objects[1], idx, truth)

report = {
    'base_commit': (BASE/'base.txt').read_text().strip(),
    'index': meta,
    'sources': SOURCES,
    'strict_current_receipts': SOURCES,
    'removed_nonretail_body_size': old_bodies[0][METHOD][1],
    'removed_unused_accessor_size': old_bodies[0][UNUSED][1],
    'retail_provider_size': len(raw),
    'retail_provider_sha256': sha(raw),
    'retail_provider_relocations': refs,
    'retained_legacy_comdats_unchanged': len(new_bodies[0]),
    'normalized_nondebug_sections_unchanged_except_removed_bodies_and_cell_view_name': True,
    'direct_owner_name_conflicts_before': sorted(conflicts_before),
    'direct_owner_name_conflicts_after': sorted(conflicts_after),
    'paired_census_findings': paired,
    'retail_provider_absent_from_census': True,
    'legacy_linked_byte_gain_claimed': 0,
    'closed_strict_gain_claimed': False,
    'new_authored_cpp_bytes': 0,
    'object_hashes': {p: {'before': sha(b.read_bytes()), 'after': sha(o.read_bytes())}
                      for p, b, o in zip(SOURCES, before, objects)},
}
hatches = {}
for source in SOURCES[:2]:
    old = hatch_counters.scan(source, (BASE/'before'/Path(source).name).read_text())
    new = hatch_counters.scan(source, Path(source).read_text())
    assert not new - old
    hatches[source] = {'before': sum(old.values()), 'after': sum(new.values()),
                       'removed': [list(k) + [n] for k, n in (old - new).items()]}
report['hatches'] = hatches
for o in objects:
    shutil.copy2(o, BASE / ('after-' + o.name))
    shutil.copy2(o.with_suffix('.deps.json'), BASE / ('after-' + o.with_suffix('.deps.json').name))
(OUT/'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS: two direct owner conflicts -> zero; 455B wrong body and unused 4B accessor removed; all retained sections and 392B retail provider unchanged. No LINK gain claimed.')
