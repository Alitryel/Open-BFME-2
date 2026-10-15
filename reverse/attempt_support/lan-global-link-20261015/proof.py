"""Run from repository root; genuine baseline objects live only in build/."""
import collections
import copy
import hashlib
import json
import shutil
import struct
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_check as ck
import link_census as lc

OUT = ROOT / 'build/lan-global-link-20261015'
context = json.loads((OUT / 'context.json').read_text())
source = context['source']
old_name, new_name = context['old_symbol'], context['new_symbol']
current = build.obj_path((ROOT / source).resolve())
before = (OUT / 'before.obj').read_bytes()
after = current.read_bytes()
assert build.compile_is_current((ROOT / source).resolve(), current, strict=True)
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == context['index_sha256']

def sections(data, rename=False):
    symbols = {s['index']: s for s in lc._coff_symbols(data)}
    result = collections.Counter()
    changed = 0
    for i in range(struct.unpack_from('<H', data, 2)[0]):
        h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
        name = data[h:h + 8].rstrip(b'\0').decode('latin1')
        if name.startswith('.debug'):
            continue
        size, pointer, reloc = struct.unpack_from('<III', data, h + 16)
        nr = struct.unpack_from('<H', data, h + 32)[0]
        flags = struct.unpack_from('<I', data, h + 36)[0]
        body = data[pointer:pointer + size] if pointer else b''
        if name == '.sxdata':
            body = repr([symbols[x[0]]['name'] for x in struct.iter_unpack('<I', body)]).encode()
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            label = s['name']
            if rename and label == old_name:
                assert kind == 6  # IMAGE_REL_I386_DIR32
                label = new_name
                changed += 1
            refs.append((where, kind, label, s['section'], s['value'], s['storage']))
        result[(name, flags, size, body.hex(), tuple(refs))] += 1
    return result, changed

old_sections, changed = sections(before, True)
new_sections, _ = sections(after)
assert changed > 0
assert old_sections == new_sections
def bindings(data, rename=False):
    return {(new_name if rename and s['name'] == old_name else s['name'],
             s['section'], s['value'], s['storage'])
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
assert bindings(before, True) == bindings(after)

index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
saved = OUT / 'saved-before' / current.name
saved.parent.mkdir(exist_ok=True)
shutil.copy2(OUT / 'before.obj', saved)
results = {}
for phase, obj in [('before', saved), ('after', current)]:
    local = copy.deepcopy(index)
    ck.refresh(local, [obj], truth)
    results[phase] = ck.check_object(obj, local, truth, source)
expected = copy.deepcopy(results['before'])
assert expected['unresolved'] == [old_name]
expected['unresolved'] = []
assert expected == results['after']
assert new_name in index['strong'] or new_name in index['common']
context.update({'results': results, 'dir32_rebindings': changed,
                'nondebug_sections_identical_after_rebinding': True,
                'external_bindings_identical_after_rebinding': True,
                'strict_consumer_receipt_current': True,
                'before_sha256': hashlib.sha256(before).hexdigest(),
                'after_sha256': hashlib.sha256(after).hexdigest(),
                'legacy_linked_bytes_before': 0, 'legacy_linked_bytes_after': 0})
(OUT / 'proof.json').write_text(json.dumps(context, indent=2) + '\n')
print(f'{changed} DIR32 rebindings; all nondebug sections unchanged; unresolved 1 -> 0')
