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

OUT = ROOT / 'build/lw-unicode-link-20261015'

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
import subprocess
import link_check as ck

ctx = json.loads((OUT / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
source = ctx['paths'][0]
predicate = ctx['paths'][1]
paths = [source, predicate]
objects = [build.obj_path(ROOT / s) for s in paths]
for s, obj in zip(paths, objects):
    assert build.compile_is_current(ROOT / s, obj, strict=True), s
before = [(OUT / ('before-%d.obj' % i)).read_bytes() for i in range(2)]
after = [obj.read_bytes() for obj in objects]

def comdats(data):
    return {s['name']: (body.hex(), digest, size,
                       [(at, kind, target['name']) for at, kind, target in refs])
            for s, body, refs, digest, size in lc._comdat_sections(data)}

originals = [comdats(data) for data in before]
a = originals[0] | originals[1]
assert not originals[0].keys() & originals[1].keys()
b, c = [comdats(data) for data in after]
assert not b.keys() & c.keys()
assert a.keys() == b.keys() | c.keys()
changed = {n for n in a if a[n] != (b | c)[n]}
expected = {'??0UnicodeString@@QAE@ABV0@@Z', '??YUnicodeString@@QAEAAV0@ABV0@@Z'}
assert changed == expected
moved = set(c) - set(originals[1])
assert len(moved) == 3
assert all(a[n] == c[n] for n in c)
added = sections(after[0]) + sections(after[1]) - (sections(before[0]) + sections(before[1]))
removed = (sections(before[0]) + sections(before[1])) - sections(after[0]) - sections(after[1])
assert sum(added.values()) == sum(removed.values()) == 2
assert {r[3] for r in added} == {b[n][0] for n in expected}
assert {r[3] for r in removed} == {a[n][0] for n in expected}

def directives(data):
    result = []
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
        if data[h:h+8].rstrip(b'\0') == b'.drectve':
            size, at = struct.unpack_from('<II', data, h+16)
            result.append(data[at:at+size].decode('latin1'))
    return result

before_directives = set(' '.join(d for data in before for d in directives(data)).split())
after_directives = set(' '.join(d for data in after for d in directives(data)).split())
assert before_directives == after_directives
assert set(' '.join(directives(before[0])).split()) == set(' '.join(directives(after[0])).split())

def bindings(data):
    return {(s['name'], s['storage'], s['section'] > 0,
             s['value'] if s['section'] <= 0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}

ab = bindings(before[0]) | bindings(before[1])
bb = bindings(after[0]) | bindings(after[1])
assert ab - bb == {('?Check@Rva0059E647Entry@@QAE_NH@Z', 2, False, 0)}
assert not bb - ab
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
saved_dir = OUT / 'saved-before'
saved_dir.mkdir(exist_ok=True)
saved = []
for i, obj in enumerate(objects):
    dest = saved_dir / obj.name
    shutil.copy2(OUT / ('before-%d.obj' % i), dest)
    saved.append(dest)
for phase, inputs, names in [('before', saved, paths), ('after', objects, paths)]:
    local = copy.deepcopy(index)
    ck.refresh(local, inputs, truth)
    results[phase] = {s: ck.check_object(obj, local, truth, s)
                      for s, obj in zip(names, inputs)}
assert {r[0] for r in results['before'][source]['comdat']} == expected
assert not any(results['before'][source][k] for k in results['before'][source] if k != 'comdat')
assert not any(results['before'][predicate].values())
assert all(not any(r.values()) for r in results['after'].values())
report = {**ctx, 'after_paths': paths, 'results': results,
          'retained_comdats': len(a) - len(expected),
          'moved_comdats': sorted(moved),
          'directives': {'before': [directives(d) for d in before], 'after': [directives(d) for d in after]},
          'changed_comdats': {n: {'before': a[n], 'after': b[n]} for n in sorted(expected)},
          'objects': {str(obj.relative_to(ROOT)): hashlib.sha256(obj.read_bytes()).hexdigest()
                      for obj in objects},
          'before_objects': [hashlib.sha256(d).hexdigest() for d in before],
          'source_hashes': {s: hashlib.sha256((ROOT / s).read_bytes()).hexdigest() for s in paths}}
print(json.dumps(report, indent=2))
