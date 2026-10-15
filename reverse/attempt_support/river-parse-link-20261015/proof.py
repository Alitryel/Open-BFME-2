"""Paired same-index proof; baseline snapshots remain under ignored build/.

Section normalization follows horde-damage-link-20261015/proof.py.
"""
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

BASE = Path('build/river-parse-link-20261015')
SOURCE = 'Code/GameEngine/Source/GameLogic/Map/RiverAreasDataChunkParserParse.cpp'
PEERS = ['Code/GameEngine/Source/Common/Rva0030C1FCOwnerCtor.cpp',
         'Code/GameEngine/Source/Common/Rva00030830GameFree.cpp']
HELPER = '??1Rva005388AB@@QAE@XZ'
PARENT = '?parse@RiverAreasDataChunkParser@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z'
OLD = '?free@_STL@@YAXPAX@Z'
NEW = '?Rva00030830GameFree@@YAXPAX@Z'

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

obj = build.obj_path(build.ROOT / SOURCE)
before = BASE / 'before' / obj.name
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256']
assert lc.object_current(build.ROOT / SOURCE, obj, allow_fresh=False)
peer_objects = [build.obj_path(build.ROOT / p) for p in PEERS]
assert all(lc.object_current(build.ROOT / p, o, allow_fresh=False)
           for p, o in zip(PEERS, peer_objects))
old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert old.keys() == new.keys()
assert {n for n in old if old[n] != new[n]} == {HELPER, PARENT}
assert normalized(before, aliases={OLD: NEW}) == normalized(obj)
raw_before, refs_before = build.read_object_symbol_bytes(before, HELPER)
raw_after, refs_after = build.read_object_symbol_bytes(obj, HELPER)
assert raw_before == raw_after
assert refs_after == [(at, kind, NEW if name == OLD else name)
                       for at, kind, name in refs_before]
assert len(refs_after) == 1 and refs_after[0][2] == NEW
truth = lc.RetailTruth(lc.ledger())
paired, selection, peers = {}, {}, {}
for label, candidate in [('before', before), ('after', obj)]:
    index = link_check.load_index()
    link_check.refresh(index, [candidate] + peer_objects, truth)
    paired[label] = link_check.check_object(candidate, index, truth, source=SOURCE)
    peers[label] = {p: link_check.check_object(o, index, truth, source=p)
                    for p, o in zip(PEERS, peer_objects)}
    copies = sorted(index['comdat'][HELPER])
    first = copies[0]
    selection[label] = {'source_object': index['objects'][first[0]],
                         'digest': first[1], 'retail_verdict': first[2],
                         'indexed_copies': len(copies),
                         'distinct_digests': len({c[1] for c in copies})}
assert len(paired['before']['comdat']) == 1
assert paired['before']['comdat'][0][0] == HELPER
assert all(not v for k, v in paired['before'].items() if k != 'comdat')
assert not any(paired['after'].values())
assert peers['before'] == peers['after']
assert not any(peers['after'][PEERS[1]].values())
assert selection['before']['source_object'] == selection['after']['source_object']
assert selection['before']['digest'] == selection['after']['digest']
assert selection['before']['distinct_digests'] == 2
assert selection['after']['distinct_digests'] == 1
assert not link_check.new_variants(obj, index, truth)
report = {
    'base_commit': (BASE/'base.txt').read_text().strip(), 'index': meta,
    'source': SOURCE, 'strict_current_receipts': [SOURCE] + PEERS,
    'object_before_sha256': sha(before.read_bytes()),
    'object_after_sha256': sha(obj.read_bytes()),
    'changed_comdats': [HELPER, PARENT], 'helper_bytes': raw_after.hex(),
    'old_relocations': refs_before, 'new_relocations': refs_after,
    'all_nondebug_sections_identical_after_only_allocator_name_substitution': True,
    'unchanged_other_comdat_bodies': len(new) - 2,
    'helper_selected_provider': selection, 'paired_findings': paired,
    'peer_findings_unchanged': peers,
    'peer_object_hashes': {p: sha(o.read_bytes()) for p, o in zip(PEERS, peer_objects)},
    'legacy_linked_bytes_before': 0,
    'legacy_linked_bytes_after': link_check.source_bytes({SOURCE})[SOURCE],
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
shutil.copy2(obj, BASE/'object-after.obj')
shutil.copy2(obj.with_suffix('.deps.json'), BASE/'receipt-after.json')
out = Path('reverse/attempt_support/river-parse-link-20261015/object-proof.json')
out.write_text(json.dumps(report, indent=2)+'\n')
print('PASS: only allocator relocation spelling changes; COMDAT family 2 -> 1 variants; peers unchanged; LEGACY +%d linked bytes' % report['legacy_linked_bytes_after'])
