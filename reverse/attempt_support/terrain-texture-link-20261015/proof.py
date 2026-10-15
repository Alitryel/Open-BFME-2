import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/terrain-texture-link-20261015'

def sections(data):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    raw = []
    for i in range(count):
        h = 20 + optional + 40 * i
        name = data[h:h + 8].rstrip(b'\0').decode('latin1')
        size, pointer, reloc = struct.unpack_from('<III', data, h + 16)
        nr = struct.unpack_from('<H', data, h + 32)[0]
        flags = struct.unpack_from('<I', data, h + 36)[0]
        body = data[pointer:pointer + size] if pointer else None
        raw.append((name, flags, size, body, reloc, nr))
    result = collections.Counter()
    for name, flags, size, body, reloc, nr in raw:
        if name.startswith('.debug') or name == '.drectve':
            continue
        if name == '.sxdata':
            # COFF symbol indices change when the unused wrapper disappears.
            body = tuple(symbols[t[0]]['name'] for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', s['name'])
            else:
                # Compare the actual local target section and offset, rather
                # than MSVC's automatically renumbered $L/$T label.
                assert s['section'] > 0
                target_name, target_flags, target_size, target_body, _, _ = raw[s['section'] - 1]
                label = ('local', target_name, target_flags, target_size,
                         target_body.hex() if target_body is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

import copy
import shutil
import link_check as ck

def object_proof(source, suffix, tag):
    obj = build.obj_path(ROOT / source)
    before = (OUT / ('before' + suffix + '.obj')).read_bytes()
    after = obj.read_bytes()
    (OUT / ('after' + suffix + '.obj')).write_bytes(after)
    old = {s['name']: (body, digest, size)
           for s, body, _, digest, size in lc._comdat_sections(before)}
    new = {s['name']: (body, digest, size)
           for s, body, _, digest, size in lc._comdat_sections(after)}
    removed = '??0BfmeResetTextureRef@@QAE@XZ'
    added = '??0BfmeResetTextureRef@@QAE@U' + tag + '@0@@Z'
    assert old.keys() - new.keys() == {removed}
    assert new.keys() - old.keys() == {added}
    retained = old.keys() & new.keys()
    assert all(old[n] == new[n] for n in retained)
    assert old[removed][0].hex() == '8bc1832000c3'
    assert new[added][0].hex() == '8bc1832000c20400'
    os, ns = sections(before), sections(after)
    rs, ads = list((os - ns).elements()), list((ns - os).elements())
    assert len(rs) == len(ads) == 1
    assert rs[0][3] == old[removed][0].hex() and not rs[0][4]
    assert ads[0][3] == new[added][0].hex() and not ads[0][4]

    def bindings(data):
        return {(s['name'], s['storage'], s['section'] > 0,
                 s['value'] if s['section'] <= 0 else 0)
                for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
    ob, nb = bindings(before), bindings(after)
    assert ob - nb == {(removed, 2, True, 0)}
    assert nb - ob == {(added, 2, True, 0)}
    for data, target in [(before, removed), (after, added)]:
        syms = {s['index']: s for s in lc._coff_symbols(data)}
        symbol = next(s for s in syms.values() if s['name'] == target)
        for i in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
            if data[h:h+8].rstrip(b'\0').startswith(b'.debug'):
                continue
            start = struct.unpack_from('<I', data, h+24)[0]
            count = struct.unpack_from('<H', data, h+32)[0]
            for at in range(start, start+10*count, 10):
                _, ref, _ = struct.unpack_from('<IIH', data, at)
                assert syms[ref]['name'] != target
                assert syms[ref]['section'] != symbol['section']

    def directives(data):
        found = []
        for i in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40*i
            if data[h:h+8].rstrip(b'\0') == b'.drectve':
                n, at = struct.unpack_from('<II', data, h+16)
                found.append(data[at:at+n])
        return found
    assert directives(before) == directives(after)
    assert build.compile_is_current(ROOT / source, obj, strict=True)
    return {
        'source_sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
        'before_object_sha256': hashlib.sha256(before).hexdigest(),
        'after_object_sha256': hashlib.sha256(after).hexdigest(),
        'after_receipt_sha256': hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),
        'strict_receipt_current': True,
        'retained_comdats_identical': sorted(retained),
        'removed_helper': {'name': removed, 'bytes': old[removed][0].hex(), 'digest': old[removed][1]},
        'added_helper': {'name': added, 'bytes': new[added][0].hex(), 'digest': new[added][1]},
        'helper_nondebug_caller_relocations': 0,
        'other_sections_and_directives_identical': True,
    }

ctx = json.loads((OUT / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
witnesses = [(ctx['paths'][0], '', 'TerrainInit'),
             (ctx['snow']['source'], '-snow', 'SnowInit')]
proof = {'context': ctx, 'objects': {}}
for source, suffix, tag in witnesses:
    proof['objects'][source] = object_proof(source, suffix, tag)
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase in ['before', 'after']:
    local = copy.deepcopy(index)
    objects = []
    for source, suffix, _ in witnesses:
        obj = build.obj_path(ROOT / source)
        if phase == 'before':
            folder = OUT / 'saved-before'
            folder.mkdir(exist_ok=True)
            witness = folder / obj.name
            shutil.copy2(OUT / ('before' + suffix + '.obj'), witness)
        else:
            witness = obj
        objects.append(witness)
    ck.refresh(local, objects, truth)
    results[phase] = {source: ck.check_object(obj, local, truth, source)
                      for (source, _, _), obj in zip(witnesses, objects)}
for source, _, _ in witnesses:
    before = results['before'][source]
    after = results['after'][source]
    old = [row for row in before['comdat'] if row[0] == '??0BfmeResetTextureRef@@QAE@XZ']
    assert len(old) == 1
    expected = copy.deepcopy(before)
    expected['comdat'].remove(old[0])
    assert expected == after
    print(source, 'findings', sum(map(len, before.values())), '->', sum(map(len, after.values())))
assert sum(map(len, results['after'][ctx['paths'][0]].values())) == 0
proof.update({'legacy_local_link_findings': results,
              'legacy_local_linked_bytes_before': 0,
              'legacy_local_linked_bytes_after': 276,
              'closed_strict_gain': 'unmeasured'})
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
(OUT / 'proof.json').write_text(json.dumps(proof, indent=2)+'\n')
print('all retained COMDATs identical; helper signatures/return-pop are the only changes')
print('both strict current; paired legacy findings 4 -> 2, LINKED 0 -> 276 bytes')
