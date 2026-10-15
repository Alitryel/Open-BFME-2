"""Run at the repository root, retaining this session's build witnesses."""
import copy
import hashlib
import json
import shutil
import struct
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import build
import link_census as lc
import link_check as ck

OUT = Path('build/display-name-tables-link-20261015')
ctx = json.loads((OUT / 'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == ctx['index_sha256']
paths = ctx['paths']
objects = [build.obj_path(Path(p).resolve()) for p in paths]
for p, obj in zip(paths, objects):
    assert build.compile_is_current(Path(p).resolve(), obj, strict=True)

before = (OUT / 'before-0.obj').read_bytes()
after = objects[0].read_bytes()
def comdats(data):
    return {s['name']: (body.hex(), digest, size)
            for s, body, _, digest, size in lc._comdat_sections(data)}
a, b = comdats(before), comdats(after)
assert not a.keys() - b.keys()
assert all(a[n] == b[n] for n in a)
added = sorted(b.keys() - a.keys())
assert len(added) == 10 and all(n.startswith('??_C@') for n in added)
def externals(data):
    return {(s['name'], s['section'] > 0, s['storage'])
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
old, new = externals(before), externals(after)
names = {'?TheAnimDebugModeNames@@3PAPBDA', '?TheWeaponStatusNames@@3PAPBDA'}
assert old - new == {(n, False, 2) for n in names}
assert new - old == {(n, True, 2) for n in names} | {(n, True, 2) for n in added}
def nondebug_sections(data):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    result = []
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
        name = data[h:h+8].rstrip(b'\0')
        if name.startswith(b'.debug'):
            continue
        size, at, reloc = struct.unpack_from('<III', data, h+16)
        nr = struct.unpack_from('<H', data, h+32)[0]
        flags = struct.unpack_from('<I', data, h+36)[0]
        body = data[at:at+size] if at else None
        if name == b'.sxdata':
            body = tuple(symbols[x[0]]['name'] for x in struct.iter_unpack('<I', body))
        refs = tuple((where, kind, symbols[target]['name'])
                     for where, target, kind in struct.iter_unpack('<IIH', data[reloc:reloc+10*nr]))
        result.append((name, flags, size, body, refs))
    return result
for i, obj in enumerate(objects[1:], 1):
    previous = (OUT / ('before-%d.obj' % i)).read_bytes()
    # Rebuilding a strict receipt may alter COFF timestamps/debug records.
    assert comdats(obj.read_bytes()) == comdats(previous)
    assert nondebug_sections(obj.read_bytes()) == nondebug_sections(previous)

index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    current = objects
    if phase == 'before':
        d = OUT / 'saved-before'
        d.mkdir(exist_ok=True)
        current = []
        for i, obj in enumerate(objects):
            saved = d / obj.name
            shutil.copy2(OUT / ('before-%d.obj' % i), saved)
            current.append(saved)
    ck.refresh(local, current, truth)
    results[phase] = {p: ck.check_object(o, local, truth, p)
                      for p, o in zip(paths, current)}
assert results['before'] == ctx['before']
assert set(results['before'][paths[0]]['unresolved']) == names
assert not any(results['after'][paths[0]].values())
for p in paths[1:]:
    assert results['before'][p] == results['after'][p]
    assert not any(results['after'][p].values())

tables = []
for va, size in ((0xDB3BB4, 16), (0xDBC7AC, 32)):
    raw = build.read_target_bytes(va - 0x400000, size)
    pointers = [x[0] for x in struct.iter_unpack('<I', raw)]
    assert pointers[-1] == 0 and all(pointers[:-1])
    tables.append({'va': hex(va), 'size': size, 'retail_pointers': pointers,
                   'strings': [build.read_target_bytes(p - 0x400000, 64).split(b'\0')[0].decode()
                               for p in pointers[:-1]]})
sizes = ck.source_bytes(set(paths))
def linked(phase):
    return sum(sizes[p] for p in paths if not any(results[phase][p].values()))
report = {'context': ctx, 'results': results,
          'retained_comdats_identical': len(a), 'added_string_comdats': added,
          'only_new_external_definitions': sorted(names), 'tables': tables,
          'comparison_units_all_nondebug_sections_identical': True,
          'linked_legacy_before': linked('before'), 'linked_legacy_after': linked('after'),
          'legacy_linked_delta': linked('after') - linked('before'),
          'strict_current_objects': {p: {'object_sha256': hashlib.sha256(o.read_bytes()).hexdigest(),
                                        'receipt_sha256': hashlib.sha256(o.with_suffix('.deps.json').read_bytes()).hexdigest(),
                                        'source_sha256': hashlib.sha256(Path(p).read_bytes()).hexdigest()}
                                     for p, o in zip(paths, objects)}}
assert report['legacy_linked_delta'] == 3019
Path('reverse/attempt_support/display-name-tables-link-20261015/proof.json').write_text(
    json.dumps(report, indent=2) + '\n')
print('64 existing COMDATs unchanged; two verified table definitions; paired legacy LINKED +3019 bytes')
