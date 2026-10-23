import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/vector3-filler-link-20261015'

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

ctx = json.loads((OUT / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
paths = ctx['paths']
stems = ['before']
objects = [build.obj_path(ROOT / s) for s in paths]
removed = '??0Vector3@@QAE@ABV0@@Z'
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
report = {'context': ctx, 'objects': {}, 'paired_results': {}}
for source, stem, obj in zip(paths, stems, objects):
    assert build.compile_is_current(ROOT / source, obj, strict=True)
    before, after = (OUT / (stem + '.obj')).read_bytes(), obj.read_bytes()
    a = {s['name']: (body, digest, size)
         for s, body, _, digest, size in lc._comdat_sections(before)}
    b = {s['name']: (body, digest, size)
         for s, body, _, digest, size in lc._comdat_sections(after)}
    assert a.keys() - b.keys() == {removed}
    assert not b.keys() - a.keys()
    assert all(a[n] == b[n] for n in b)
    old = list((sections(before) - sections(after)).elements())
    assert len(old) == 1 and not sections(after) - sections(before)
    assert old[0][0] == '.text' and old[0][3] == '8bc1c20400'
    assert not old[0][4]
    def bindings(data):
        return {(s['name'], s['storage'], s['section'] > 0,
                 s['value'] if s['section'] <= 0 else 0)
                for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
    assert bindings(before) - bindings(after) == {(removed, 2, True, 0)}
    assert not bindings(after) - bindings(before)
    syms = {s['index']: s for s in lc._coff_symbols(before)}
    removed_sections = {s['section'] for s in syms.values() if s['name'] == removed}
    directives = []
    for data in (before, after):
        ds = []
        for i in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
            name = data[h:h + 8].rstrip(b'\0')
            if name == b'.drectve':
                size, at = struct.unpack_from('<II', data, h + 16)
                ds.append(data[at:at + size])
            if data is not before or name.startswith(b'.debug'):
                continue
            at = struct.unpack_from('<I', data, h + 24)[0]
            nr = struct.unpack_from('<H', data, h + 32)[0]
            for j in range(at, at + nr * 10, 10):
                _, target, _ = struct.unpack_from('<IIH', data, j)
                sym = syms[target]
                assert sym['name'] != removed and sym['section'] not in removed_sections
        directives.append(ds)
    assert directives[0] == directives[1]
    report['objects'][source] = {
        'retained_comdats_identical': len(b), 'all_other_nondebug_sections_identical': True,
        'removed_comdat': {'name': removed, 'bytes': a[removed][0].hex(),
                           'relocation_digest': a[removed][1], 'size': a[removed][2]},
        'nondebug_references_to_removed_constructor': 0, 'link_directives_identical': True,
        'only_external_binding_removed': removed, 'strict_receipt_current': True,
        'before_object_sha256': hashlib.sha256(before).hexdigest(),
        'after_object_sha256': hashlib.sha256(after).hexdigest(),
        'before_receipt_sha256': hashlib.sha256((OUT / (stem + '.deps.json')).read_bytes()).hexdigest(),
        'after_receipt_sha256': hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),
        'before_source_sha256': hashlib.sha256((OUT / (stem + '.cpp')).read_bytes()).hexdigest(),
        'after_source_sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest()}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    if phase == 'before':
        d = OUT / 'saved-before'
        d.mkdir(exist_ok=True)
        current = []
        for stem, obj in zip(stems, objects):
            saved = d / obj.name
            shutil.copy2(OUT / (stem + '.obj'), saved)
            current.append(saved)
    else:
        current = objects
    ck.refresh(local, current, truth)
    report['paired_results'][phase] = {s: ck.check_object(o, local, truth, s)
                                       for s, o in zip(paths, current)}
for source in paths:
    old, new = (report['paired_results'][p][source] for p in ('before', 'after'))
    assert {r[0] for r in old['comdat']} == {removed}
    assert not new['comdat']
    expected = copy.deepcopy(old)
    expected['comdat'] = []
    assert expected == new
assert not any(report['paired_results']['after'][paths[0]].values())
report['local_legacy_linked_bytes'] = {'before': 0, 'after': ck.source_bytes({paths[0]})[paths[0]]}
report['new_authored_cpp_bytes'] = 0
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('All retained code/data/relocations identical; removed one unused 5-byte copy-constructor COMDAT.')
print('Paired legacy findings 1 -> 0; linked bytes 0 ->', report['local_legacy_linked_bytes']['after'])
