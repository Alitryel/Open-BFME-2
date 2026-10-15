"""Paired same-index proof; baseline object/receipt are retained under build/.

Run from the repository root after preparing the current source receipt.
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
import hatch_counters
import link_census as lc
import link_check

BASE = Path('build/button-base-link-20261015')
SOURCE = 'Code/GameEngine/Source/Common/Rva005E92F7Dtor.cpp'
PEERS = ['Code/GameEngine/Source/Common/' + name + '.cpp' for name in (
    'Rva005E91A9Dtor', 'Rva005F589ECtor', 'Rva005F5C77Ctor',
    'Rva005F5F2BCtor', 'Rva005CC3C0Permuted')]
OLD = 'Rva005F5C77Base0'
NEW = 'Rva005E92F7RecordBase'
HELPER = '??1' + OLD + '@@UAE@XZ'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def normalized(obj, rename=False):
    def name(s):
        return s.replace(OLD, NEW) if rename else s

    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    leaders = {}
    for symbol in symbols:
        if symbol.get('storage') == 2 and symbol['section'] > 0:
            leaders.setdefault(symbol['section'], []).append(name(symbol['name']))

    def body(n):
        section = sections[n - 1]
        pointer = section['raw_pointer']
        return data[pointer:pointer + section['raw_size']] if pointer else b''

    def referent(i):
        symbol = symbols[i]
        n = symbol['section']
        if symbol['storage'] in (2, 105):
            return name(symbol['name']), symbol['storage'], symbol['value']
        return ('local', symbol['value'], symbol['storage'], symbol['type'],
                tuple(sorted(leaders.get(n, ()))) if n > 0 else (),
                sha(body(n)) if n > 0 else None)

    found = []
    for n, section in enumerate(sections, 1):
        if section['name'].startswith('.debug'):
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
    externals = Counter((name(s['name']), s['storage'], s['value'], s['type'],
                         s['section'] > 0, s['section'] == 0)
                        for s in symbols if s.get('storage') in (2, 105))
    return Counter(found), externals

obj = build.obj_path(build.ROOT / SOURCE)
before = BASE / 'before' / obj.name
meta = json.loads((BASE / 'index-meta.json').read_text())
assert sha(link_check.INDEX.read_bytes()) == meta['sha256']
assert lc.object_current(build.ROOT / SOURCE, obj, allow_fresh=False)
assert normalized(before, rename=True) == normalized(obj)
old = {n: (d, z) for n, d, z in lc.comdat_bodies(before)}
new = {n: (d, z) for n, d, z in lc.comdat_bodies(obj)}
assert {n.replace(OLD, NEW) for n in old} == new.keys()
renamed = sorted(n for n in old if OLD in n)
changed = sorted(n for n in old if OLD not in n and old[n] != new[n])
assert len(renamed) == 5
assert changed == ['??0Rva005E92F7@@QAE@IPAX@Z', '??1Rva005E92F7@@UAE@XZ']
for old_name in old:
    new_name = old_name.replace(OLD, NEW)
    old_bytes, old_refs = build.read_object_symbol_bytes(before, old_name)
    new_bytes, new_refs = build.read_object_symbol_bytes(obj, new_name)
    assert old_bytes == new_bytes, old_name
    assert new_refs == [(at, kind, name.replace(OLD, NEW)) for at, kind, name in old_refs], old_name
truth = lc.RetailTruth(lc.ledger())
peer_objects = [build.obj_path(build.ROOT / p) for p in PEERS]
assert all(o.exists() for o in peer_objects)
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
assert paired['before']['comdat'] == [(HELPER, 'first', None)]
assert all(not v for k, v in paired['before'].items() if k != 'comdat')
assert not any(paired['after'].values())
assert peers['before'] == peers['after']
assert selection['before']['source_object'] == selection['after']['source_object']
assert selection['before']['digest'] == selection['after']['digest']
assert selection['before']['distinct_digests'] == 3
assert selection['after']['distinct_digests'] == 2
assert not link_check.new_variants(obj, index, truth)
hatches = sorted((key, count) for key, count in hatch_counters.scan(SOURCE, Path(SOURCE).read_text()).items())
assert json.loads(json.dumps(hatches)) == json.loads((BASE / 'hatches-before.json').read_text())
report = {
    'base_commit': (BASE / 'base.txt').read_text().strip(), 'index': meta,
    'source': SOURCE, 'strict_current_receipts': [SOURCE],
    'object_before_sha256': sha(before.read_bytes()),
    'object_after_sha256': sha(obj.read_bytes()),
    'renamed_comdats': renamed, 'changed_retained_comdat_relocation_names': changed,
    'all_nondebug_sections_and_external_symbols_equal_after_private_class_rename': True,
    'every_comdat_raw_body_unchanged': True,
    'unchanged_other_comdat_bodies': len(old) - len(renamed) - len(changed),
    'old_family_selected_provider': selection, 'paired_findings': paired,
    'peer_findings_unchanged': peers,
    'peer_object_hashes': {p: sha(o.read_bytes()) for p, o in zip(PEERS, peer_objects)},
    'peer_receipts_not_claimed_strict': True, 'hatch_counts_unchanged': hatches,
    'legacy_linked_bytes_before': 0,
    'legacy_linked_bytes_after': link_check.source_bytes({SOURCE})[SOURCE],
    'new_authored_cpp_bytes': 0, 'closed_strict_gain_claimed': False,
}
shutil.copy2(obj, BASE / 'object-after.obj')
shutil.copy2(obj.with_suffix('.deps.json'), BASE / 'receipt-after.json')
out = Path('reverse/attempt_support/button-base-link-20261015/object-proof.json')
out.write_text(json.dumps(report, indent=2) + '\n')
print('PASS: only private class name changes; old family 3 -> 2 variants; peers unchanged; LEGACY +%d linked bytes' % report['legacy_linked_bytes_after'])
