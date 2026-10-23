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

OUT = ROOT / 'build/ascii-from-unicode-link-20261015'

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
source, provider, geometry = ctx['paths']
objects = [build.obj_path(ROOT / s) for s in ctx['paths']]
for s, obj in zip(ctx['paths'], objects):
    assert build.compile_is_current(ROOT / s, obj, strict=True), s
assert objects[1].read_bytes() == (OUT / 'before-1.obj').read_bytes()
comparisons = {}
for number in (0, 2):
    before = (OUT / ('before-%d.obj' % number)).read_bytes()
    after = objects[number].read_bytes()
    removed = {'??0?$StringBase@D@@AAE@XZ'}
    def comdats(data):
        return {s['name']: (body, digest, size)
                for s, body, _, digest, size in lc._comdat_sections(data)}
    a, b = comdats(before), comdats(after)
    assert a.keys() - b.keys() == removed
    assert not b.keys() - a.keys()
    assert all(a[n] == b[n] for n in b)
    assert not sections(after) - sections(before)
    dropped = list((sections(before) - sections(after)).elements())
    assert len(dropped) == 1
    assert dropped[0][3] == a[next(iter(removed))][0].hex()
    def bindings(data):
        return {(s['name'], s['storage'], s['section'] > 0,
                 s['value'] if s['section'] <= 0 else 0)
                for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
    ab, bb = bindings(before), bindings(after)
    assert ab - bb == {(n, 2, True, 0) for n in removed}
    assert not bb - ab
    # No retained nondebug code or data references the discarded wrapper.
    syms = {s['index']: s for s in lc._coff_symbols(before)}
    ctor_sections = {s['section'] for s in syms.values() if s['name'] in removed}
    directives = []
    for data in (before, after):
        ds = []
        for i in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
            name = data[h:h+8].rstrip(b'\0')
            if name == b'.drectve':
                size, at = struct.unpack_from('<II', data, h+16)
                ds.append(data[at:at+size])
            if data is not before or name.startswith(b'.debug') or i+1 in ctor_sections:
                continue
            at = struct.unpack_from('<I', data, h+24)[0]
            nr = struct.unpack_from('<H', data, h+32)[0]
            for j in range(at, at+nr*10, 10):
                _, target, _ = struct.unpack_from('<IIH', data, j)
                assert syms[target]['name'] not in removed
                assert syms[target]['section'] not in ctor_sections
        directives.append(ds)
    assert directives[0] == directives[1]
    comparisons[ctx['paths'][number]] = {'retained_comdats':len(b), 'removed_comdat':{n:[d.hex(),h,z] for n,(d,h,z) in a.items() if n in removed}}
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    if phase == 'before':
        d = OUT / 'saved-before'; d.mkdir(exist_ok=True)
        current = []
        for i, obj in enumerate(objects):
            saved = d / obj.name
            shutil.copy2(OUT / ('before-%d.obj' % i), saved)
            current.append(saved)
    else:
        current = objects
    ck.refresh(local, current, truth)
    results[phase] = {s: ck.check_object(obj, local, truth, s)
                      for s, obj in zip(ctx['paths'], current)}
for caller in (source, geometry):
    assert {r[0] for r in results['before'][caller]['comdat']} & removed == removed
    expected = copy.deepcopy(results['before'][caller])
    expected['comdat'] = [r for r in expected['comdat'] if r[0] not in removed]
    expected['selected'] = [r for r in expected['selected'] if (r if isinstance(r, str) else r[0]) not in removed]
    assert expected == results['after'][caller]
assert not any(results['after'][source].values())
assert sum(map(len,results['before'][geometry].values())) == 6
assert sum(map(len,results['after'][geometry].values())) == 5
assert results['before'][provider] == results['after'][provider]
report = {**ctx, 'results':results, 'comparisons':comparisons,
          'objects':{str(obj.relative_to(ROOT)):hashlib.sha256(obj.read_bytes()).hexdigest() for obj in objects},
          'before_objects':[hashlib.sha256((OUT/('before-%d.obj'%i)).read_bytes()).hexdigest() for i in range(len(objects))]}
print(json.dumps(report,indent=2))
