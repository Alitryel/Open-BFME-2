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

OUT = ROOT / 'build/list-transfer-link-20261015'

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
objects = [build.obj_path(ROOT / s) for s in ctx['paths']]
truth = lc.RetailTruth(lc.ledger())
name = '??9_List_iterator_base@_STL@@QBE_NABU01@@Z'
removed = {name}
summary = {}

def comdats(data):
    return {s['name']: (body, digest, size)
            for s, body, _, digest, size in lc._comdat_sections(data)}

def bindings(data):
    return {(s['name'], s['storage'], s['section'] > 0,
             s['value'] if s['section'] <= 0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}

def directives(data):
    found = []
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        at = 20 + struct.unpack_from('<H', data, 16)[0] + i * 40
        if data[at:at+8].rstrip(b'\0') == b'.drectve':
            size, p = struct.unpack_from('<II', data, at+16)
            found.append(data[p:p+size])
    return found

for i, (s, obj) in enumerate(zip(ctx['paths'], objects)):
    assert build.compile_is_current(ROOT / s, obj, strict=True), s
    before = (OUT / ('before-%d.obj' % i)).read_bytes()
    after = obj.read_bytes()
    a, b = comdats(before), comdats(after)
    if i == len(objects) - 1:
        assert before == after
        native = [(h, z, truth.verdict(sym, body, rel, h, z))
                  for sym, body, rel, h, z in lc._comdat_sections(after)
                  if sym['name'] == name]
        assert len(native) == 1 and native[0][1:] == (22, 'retail')
        summary[s] = {'unchanged': True, 'provider': native}
        continue
    assert a.keys() - b.keys() == removed, s
    assert not b.keys() - a.keys(), s
    assert all(a[n] == b[n] for n in b), s
    added = list((sections(after) - sections(before)).elements())
    # MSVC retains unused internal copies even with forceinline. They have no
    # nondebug references and cannot participate in external COMDAT selection.
    local_body = '8b0033c93b020f95c18ac1c3'
    assert added and all(row[:4] == ('.text', 1611665440, 12, local_body)
                         and row[4] == () for row in added), s
    after_symbols = {sym['index']: sym for sym in lc._coff_symbols(after)}
    typed = [sym for sym in after_symbols.values()
             if sym['name'].startswith('??$?9') and '_List_iterator' in sym['name']]
    assert len(typed) == len(added) and all(sym['storage'] == 3 for sym in typed), s
    local_sections = {sym['section'] for sym in typed}
    for k in range(struct.unpack_from('<H', after, 2)[0]):
        at = 20 + struct.unpack_from('<H', after, 16)[0] + k*40
        secname = after[at:at+8].rstrip(b'\0')
        if secname.startswith(b'.debug'):
            continue
        rel = struct.unpack_from('<I', after, at+24)[0]
        nr = struct.unpack_from('<H', after, at+32)[0]
        for off in range(rel, rel+nr*10, 10):
            target = struct.unpack_from('<I', after, off+4)[0]
            assert after_symbols[target]['section'] not in local_sections, s
    dropped = list((sections(before) - sections(after)).elements())
    assert len(dropped) == 1 and dropped[0][3] == a[name][0].hex(), s
    assert bindings(before) - bindings(after) == {(name, 2, True, 0)}, s
    assert not bindings(after) - bindings(before), s
    assert directives(before) == directives(after), s
    # Retained nondebug sections cannot refer to the removed definition.
    syms = {sym['index']:sym for sym in lc._coff_symbols(before)}
    discarded = {sym['section'] for sym in syms.values() if sym['name'] == name}
    for k in range(struct.unpack_from('<H', before, 2)[0]):
        at = 20 + struct.unpack_from('<H', before, 16)[0] + k*40
        secname = before[at:at+8].rstrip(b'\0')
        if secname.startswith(b'.debug') or k+1 in discarded:
            continue
        rel = struct.unpack_from('<I', before, at+24)[0]
        nr = struct.unpack_from('<H', before, at+32)[0]
        for off in range(rel,rel+nr*10,10):
            target = struct.unpack_from('<I',before,off+4)[0]
            assert syms[target]['name'] != name and syms[target]['section'] not in discarded, s
    summary[s] = {'retained_comdats':len(b), 'unreferenced_internal_comparators':len(added), 'internal_comparator_hex':local_body,
                  'removed':{'name':name,'hex':a[name][0].hex(),'digest':a[name][1],'size':a[name][2]}}

index = ck.load_index()
results = {}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    if phase == 'before':
        saved = OUT / 'saved-before'; saved.mkdir(exist_ok=True)
        current = []
        for i, obj in enumerate(objects):
            old = saved / obj.name
            shutil.copy2(OUT / ('before-%d.obj' % i), old)
            current.append(old)
    else:
        current = objects
    ck.refresh(local, current, truth)
    results[phase] = {s: ck.check_object(obj, local, truth, s)
                      for s,obj in zip(ctx['paths'],current)}
for s in ctx['paths'][:-1]:
    expected = copy.deepcopy(results['before'][s])
    old = expected['comdat']
    expected['comdat'] = [r for r in old if r[0] != name]
    assert len(old) - len(expected['comdat']) == 1, s
    assert expected == results['after'][s], s
provider = ctx['paths'][-1]
assert results['before'][provider] == results['after'][provider]
report = {**ctx,'objects':summary,'results':results,
          'before_objects':[hashlib.sha256((OUT/('before-%d.obj'%i)).read_bytes()).hexdigest() for i in range(len(objects))],
          'after_objects':[hashlib.sha256(obj.read_bytes()).hexdigest() for obj in objects]}
print(json.dumps(report,indent=2))
