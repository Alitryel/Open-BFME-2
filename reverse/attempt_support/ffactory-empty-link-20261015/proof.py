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

OUT = ROOT / 'build/ffactory-empty-link-20261015'

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
        if name.startswith('.debug'):
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
source = ctx['source']
obj = build.obj_path(ROOT / source)
assert build.compile_is_current(ROOT / source, obj, strict=True)
before = (OUT / 'before.obj').read_bytes()
after = obj.read_bytes()
name = '?Is_Empty@StringClass@@QBE_NXZ'
a = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(before)}
b = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(after)}
assert a.keys() - b.keys() == {name}
assert not b.keys() - a.keys()
assert all(a[n] == b[n] for n in b)
removed = list((sections(before) - sections(after)).elements())
added = list((sections(after) - sections(before)).elements())
assert not added
assert len(removed) == 1
assert removed[0][0] == '.text'
assert removed[0][3] == a[name][0].hex()
assert not any(s['name'] == name for s in lc._coff_symbols(after))
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
paired = {}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    current = obj
    if phase == 'before':
        saved = OUT / 'saved-before' / obj.name
        saved.parent.mkdir(exist_ok=True)
        shutil.copy2(OUT / 'before.obj', saved)
        current = saved
    ck.refresh(local, [current], truth)
    paired[phase] = ck.check_object(current, local, truth, source)
assert json.loads(json.dumps(paired['before'])) == json.loads((OUT / 'before.json').read_text())
assert paired['before']['selected'] == [name]
assert paired['before']['comdat'] == [
    (name, 'retail', 'wrong'), ('??_GFileFactoryClass@@UAEPAXI@Z', 'retail', 'wrong')]
assert paired['after']['comdat'] == [('??_GFileFactoryClass@@UAEPAXI@Z', 'retail', 'wrong')]
assert all(not v for k, v in paired['after'].items() if k != 'comdat')
report = {
    'context': {**ctx, 'measurement': index['meta']},
    'source': source,
    'object': str(obj.relative_to(ROOT)),
    'strict_after_receipt_current': True,
    'strict_before_preparation': 'link_check --prepare-current succeeded before snapshot (33/33)',
    'removed_comdat': {'name': name, 'body': a[name][0].hex(), 'bytes': a[name][2]},
    'every_other_comdat_unchanged': True,
    'all_other_nondebug_sections_and_relocations_unchanged': True,
    'before_object_sha256': hashlib.sha256(before).hexdigest(),
    'after_object_sha256': hashlib.sha256(after).hexdigest(),
    'before_source_sha256': hashlib.sha256((OUT / 'before.cpp').read_bytes()).hexdigest(),
    'after_source_sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
    'before_receipt_sha256': hashlib.sha256((OUT / 'before.deps.json').read_bytes()).hexdigest(),
    'after_receipt_sha256': hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),
    'paired_legacy_results': paired,
    'paired_legacy_total_findings': {'before': 3, 'after': 1},
    'local_legacy_linked_bytes': {'before': 0, 'after': 0, 'gain': 0},
    'new_authored_cpp_bytes': 0,
    'closed_strict': 'not measured; other providers in runner index are historical',
}
assert build.compile_is_current(ROOT / source, obj, strict=True)
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Only removed section: unused Is_Empty COMDAT. All other code/data/relocations identical.')
print('Paired legacy findings 3 -> 1; no linked-byte or closed-strict gain claimed.')

