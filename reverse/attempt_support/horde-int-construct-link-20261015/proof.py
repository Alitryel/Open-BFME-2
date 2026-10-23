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

OUT = ROOT / 'build/horde-int-construct-link-20261015'

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
source, provider = ctx['paths']
objects = [build.obj_path(ROOT / s) for s in ctx['paths']]
for s, obj in zip(ctx['paths'], objects):
    assert build.compile_is_current(ROOT / s, obj, strict=True)
before = (OUT / 'before-0.obj').read_bytes()
after = objects[0].read_bytes()
assert objects[1].read_bytes() == (OUT / 'before-1.obj').read_bytes()
removed = {'??$_Construct@HH@_STL@@YAXPAHABH@Z'}

def comdats(data):
    return {s['name']: (body, digest, size)
            for s, body, _, digest, size in lc._comdat_sections(data)}

a, b = comdats(before), comdats(after)
assert a.keys() - b.keys() == removed
assert not b.keys() - a.keys()
assert all(a[n] == b[n] for n in b)
old = list((sections(before) - sections(after)).elements())
new = list((sections(after) - sections(before)).elements())
assert len(old) == len(new) == 1
assert new[0][:4] == ('.text', old[0][1], 9, '85c074048b098908c3')
assert not new[0][4]
assert old[0][3] == a[next(iter(removed))][0].hex()

def bindings(data):
    return {(s['name'], s['storage'], s['section'] > 0,
             s['value'] if s['section'] <= 0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}

ab, bb = bindings(before), bindings(after)
assert ab - bb == {(n, 2, True, 0) for n in removed}
assert not bb - ab
after_symbols = {s['index']: s for s in lc._coff_symbols(after)}
local_helpers = [s for s in after_symbols.values() if s['name'] == '?_Construct@_STL@@YAXPAHABH@Z']
assert len(local_helpers) == 1 and local_helpers[0]['storage'] == 3
local_section = local_helpers[0]['section']
for i in range(struct.unpack_from('<H', after, 2)[0]):
    h = 20 + struct.unpack_from('<H', after, 16)[0] + 40 * i
    if after[h:h+8].startswith(b'.debug'):
        continue
    at = struct.unpack_from('<I', after, h+24)[0]
    nr = struct.unpack_from('<H', after, h+32)[0]
    for j in range(at, at+nr*10, 10):
        _, target, _ = struct.unpack_from('<IIH', after, j)
        assert after_symbols[target]['section'] != local_section
symbols = {s['index']: s for s in lc._coff_symbols(before)}
ctor_sections = {s['section'] for s in symbols.values() if s['name'] in removed}
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
            sym = symbols[target]
            assert sym['name'] not in removed and sym['section'] not in ctor_sections
    directives.append(ds)
assert directives[0] == directives[1]

index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    if phase == 'before':
        d = OUT / 'saved-before'
        d.mkdir(exist_ok=True)
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
assert {r[0] for r in results['before'][source]['comdat']} == removed
assert not any(results['after'][source].values())
expected = copy.deepcopy(results['before'][source])
expected['comdat'] = []
assert expected == results['after'][source]
assert results['before'][provider] == results['after'][provider]
# Provider findings are reported, without claiming dependency closure.
report = {
    'context': ctx, 'results': results,
    'retained_comdats_identical': len(b),
    'removed_comdats': {n: {'bytes': a[n][0].hex(), 'relocation_digest': a[n][1],
                            'size': a[n][2]} for n in removed},
    'all_other_nondebug_sections_identical': True,
    'local_unreferenced_helper': {'bytes': new[0][3], 'size': new[0][2], 'storage_class': 3, 'nondebug_references': 0},
    'link_directives_identical': True, 'nondebug_constructor_relocations': 0,
    'only_bindings_removed': sorted(removed), 'provider_object_unchanged': True,
    'strict_receipts_current': True,
    'after_receipt_sha256': [hashlib.sha256(o.with_suffix('.deps.json').read_bytes()).hexdigest()
                             for o in objects],
    'object_sha256': {'before': hashlib.sha256(before).hexdigest(),
                      'after': hashlib.sha256(after).hexdigest()},
    'source_sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
    'consumer_legacy_linked_bytes_before': 0,
    'consumer_legacy_linked_bytes_after': ck.source_bytes({source})[source],
}
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Retained COMDATs identical:', len(b), '; consumer findings 1 -> 0; local legacy bytes 0 ->',
      report['consumer_legacy_linked_bytes_after'], '; verified provider unchanged')
