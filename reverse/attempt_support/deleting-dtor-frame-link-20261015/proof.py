"""Paired local link evidence; original objects/receipts stay under build/."""
import hashlib
import json
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, 'tools')
import build
import hatch_counters
import link_census as lc
import link_check

BASE = Path('build/w3dview-frame-link-20261015')
OUT = Path('reverse/attempt_support/deleting-dtor-frame-link-20261015')
UNITS = [
    ('', 'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewAggregateDtor.cpp',
     'Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB09.cpp',
     '??_GRva008BD5E@@UAEPAXI@Z'),
    ('baseupgrade', 'Code/GameEngine/Source/GameLogic/Object/Upgrade/BaseUpgradeModuleDataCtor.cpp',
     'Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-67c0.cpp',
     '??_GBaseUpgradeModuleData@@UAEPAXI@Z'),
    ('riderchange', 'Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainModuleDataCtor.cpp',
     'Code/GameEngine/Source/GameLogic/Object/Contain/ContainModuleDeletingDtors.cpp',
     '??_GRiderChangeContainModuleData@@UAEPAXI@Z'),
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def normalized_except_helper(obj, helper):
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    leaders = {}
    omitted = set()
    for symbol in symbols:
        if symbol.get('storage') == 2 and symbol['section'] > 0:
            leaders.setdefault(symbol['section'], []).append(symbol['name'])
            if symbol['name'] == helper:
                omitted.add(symbol['section'])
    assert len(omitted) == 1

    def body(n):
        section = sections[n - 1]
        pointer = section['raw_pointer']
        return data[pointer:pointer + section['raw_size']] if pointer else b''

    def referent(i):
        symbol = symbols[i]
        n = symbol['section']
        if symbol['storage'] in (2, 105):
            return symbol['name'], symbol['storage'], symbol['value']
        return ('local', symbol['value'], symbol['storage'], symbol['type'],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (),
                sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section['name'].startswith('.debug') or n in omitted:
            continue
        raw = body(n)
        if section['name'] == '.sxdata':
            raw = repr([referent(struct.unpack_from('<I', raw, j)[0])
                        for j in range(0, len(raw), 4)]).encode()
        relocs = []
        for j in range(section['reloc_count']):
            at, symbol, kind = struct.unpack_from('<IIH', data, section['reloc_pointer'] + 10 * j)
            relocs.append((at, kind, referent(symbol)))
        found.append(repr((section['name'], section['characteristics'], section['raw_size'],
                           sha(raw), relocs, sorted(leaders.get(n, ())))))
    external = Counter((s['name'], s['storage'], s['value'], s['type'],
                        s['section'] > 0, s['section'] == 0)
                       for s in symbols if s.get('storage') in (2, 105))
    return Counter(found), external


meta = json.loads((BASE / 'before.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['index_sha256']
truth = lc.RetailTruth(lc.ledger())
objects = [build.obj_path(build.ROOT / source) for _, source, _, _ in UNITS]
old_objects = [BASE / tag / 'before' / obj.name for (tag, _, _, _), obj in zip(UNITS, objects)]
peer_objects = [build.obj_path(build.ROOT / peer) for _, _, peer, _ in UNITS]
assert all(lc.object_current(build.ROOT / source, obj, allow_fresh=False)
           for (_, source, _, _), obj in zip(UNITS, objects))
assert all(lc.object_current(build.ROOT / peer, obj, allow_fresh=False)
           for (_, _, peer, _), obj in zip(UNITS, peer_objects))

changes = []
for (tag, source, peer, helper), old, new, provider in zip(UNITS, old_objects, objects, peer_objects):
    before = json.loads((BASE / tag / 'before.json').read_text())
    assert normalized_except_helper(old, helper) == normalized_except_helper(new, helper)
    old_bodies = {n: (d, z) for n, d, z in lc.comdat_bodies(old)}
    new_bodies = {n: (d, z) for n, d, z in lc.comdat_bodies(new)}
    assert old_bodies.keys() == new_bodies.keys()
    assert [n for n in old_bodies if old_bodies[n] != new_bodies[n]] == [helper]
    old_bytes, old_refs = build.read_object_symbol_bytes(old, helper)
    new_bytes, new_refs = build.read_object_symbol_bytes(new, helper)
    assert len(old_bytes) == 31 and len(new_bytes) == 28
    assert (new_bytes, new_refs) == build.read_object_symbol_bytes(provider, helper)
    hatches = sorted(hatch_counters.scan(source, Path(source).read_text()).items())
    assert json.loads(json.dumps(hatches)) == before['hatches']
    changes.append({'source': source, 'provider': peer, 'helper': helper,
                    'before_object_sha256': sha(old.read_bytes()),
                    'after_object_sha256': sha(new.read_bytes()),
                    'all_other_nondebug_sections_and_external_bindings_unchanged': True,
                    'all_other_comdat_bodies_unchanged': len(old_bodies) - 1,
                    'before_helper_hex': old_bytes.hex(' '), 'before_relocations': old_refs,
                    'after_helper_hex': new_bytes.hex(' '), 'after_relocations': new_refs,
                    'after_whole_helper_and_relocations_equal_verified_provider': True,
                    'hatch_counts_unchanged': hatches})

paired = {}
for label, candidates in [('before', old_objects), ('after', objects)]:
    index = link_check.load_index()
    link_check.refresh(index, candidates + peer_objects, truth)
    paired[label] = {}
    for (_, source, peer, helper), obj, provider in zip(UNITS, candidates, peer_objects):
        paired[label][source] = link_check.check_object(obj, index, truth, source=source)
        paired[label][peer] = link_check.check_object(provider, index, truth, source=peer)
        if label == 'before':
            assert paired[label][source]['comdat'] == [(helper, 'retail', 'wrong')]
        else:
            assert not any(paired[label][source].values())
            assert not link_check.new_variants(obj, index, truth)
    if label == 'after':
        for source, findings in paired[label].items():
            for kind, values in findings.items():
                assert set(map(str, values)) <= set(map(str, paired['before'][source][kind]))

byte_counts = link_check.source_bytes(set(paired['before']))
gain = sum(byte_counts[s] for s in byte_counts
           if any(paired['before'][s].values()) and not any(paired['after'][s].values()))
report = {'base_commit': meta['head'], 'index': meta['meta'],
          'index_sha256': meta['index_sha256'], 'changes': changes,
          'paired_same_index_findings': paired, 'existing_byte_counts': byte_counts,
          'legacy_local_preview_gain': gain, 'new_authored_cpp_bytes': 0,
          'closed_strict_gain_claimed': False, 'full_link_cycle_run': False}
(OUT / 'object-proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS: three 31B wrappers become verified 28B twins; all other sections unchanged; legacy local +%dB' % gain)
