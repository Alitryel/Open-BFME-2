"""Bounded object/link proof; baseline snapshots remain under ignored build/."""
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

BASE = Path('build/horde-damage-link-20261015')
SOURCE = 'Code/GameEngine/Source/GameLogic/Object/Damage/HordeTransportContainDamageCallback.cpp'
HELPER = '??$_Construct@HH@_STL@@YAXPAHABH@Z'
LOCAL = '?_Construct@_STL@@YAXPAHABH@Z'

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

obj = build.obj_path(build.ROOT / SOURCE)
before = BASE / 'before' / obj.name
assert lc.object_current(build.ROOT / SOURCE, obj, allow_fresh=False)
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256']
old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert set(old) - set(new) == {HELPER}
assert not set(new) - set(old)
assert all(old[n] == new[n] for n in new)
# The comparison also refuses any incoming nondebug relocation to the removed
# body; every retained section's bytes, flags, leaders and symbolic relocs agree.
local_body, local_relocs = build.read_object_symbol_bytes(obj, LOCAL, 9)
assert local_body.hex() == '85c074048b098908c3' and not local_relocs
assert normalized(before, {HELPER}) == normalized(obj, {LOCAL})
truth = lc.RetailTruth(lc.ledger())
paired = {}
selection = {}
for label, candidate in [('before', before), ('after', obj)]:
    index = link_check.load_index()
    link_check.refresh(index, [candidate], truth)
    paired[label] = link_check.check_object(candidate, index, truth, source=SOURCE)
    copies = sorted(index['comdat'].get(HELPER, []))
    first = copies[0]
    selection[label] = {'source_object': index['objects'][first[0]],
                        'digest': first[1], 'retail_verdict': first[2],
                        'indexed_copies': len(copies)}
assert paired['before']['comdat'] == [(HELPER, 'retail', 'wrong')]
assert all(not v for k, v in paired['before'].items() if k != 'comdat')
assert not any(paired['after'].values())
assert selection['before']['source_object'] == selection['after']['source_object']
assert selection['before']['digest'] == selection['after']['digest']
assert not link_check.new_variants(obj, index, truth)
report = {
    'base_commit': (BASE/'base.txt').read_text().strip(), 'index': meta,
    'source': SOURCE, 'strict_current_receipt': True,
    'object_before_sha256': sha(before.read_bytes()),
    'object_after_sha256': sha(obj.read_bytes()),
    'removed_comdat': {'name': HELPER, 'digest_size': old[HELPER]},
    'new_private_unreferenced_helper': {'name': LOCAL, 'bytes': local_body.hex(),
                                        'relocations': local_relocs},
    'unchanged_other_comdat_bodies': len(new),
    'all_retained_nondebug_sections_and_relocations_equal': True,
    'removed_helper_nondebug_incoming_relocations': 0,
    'helper_selected_provider': selection,
    'paired_findings': paired,
    'legacy_linked_bytes_before': 0,
    'legacy_linked_bytes_after': link_check.source_bytes({SOURCE})[SOURCE],
    'new_authored_cpp_bytes': 0,
    'closed_strict_gain_claimed': False,
}
shutil.copy2(obj, BASE/'object-after.obj')
shutil.copy2(obj.with_suffix('.deps.json'), BASE/'receipt-after.json')
out = Path('reverse/attempt_support/horde-damage-link-20261015/object-proof.json')
out.write_text(json.dumps(report, indent=2)+'\n')
print('PASS: unreferenced 17-byte external helper replaced by private 9-byte helper; all other sections/relocations equal; LEGACY +%d linked bytes' % report['legacy_linked_bytes_after'])
