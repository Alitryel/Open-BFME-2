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

OUT = ROOT / 'build/genbase-destructor-link-20261015'

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
objects = [build.obj_path(ROOT / s) for s in paths]
name = '??1GenBase009EB7D0@@UAE@XZ'
reset = '?bfmeResetUB@BfmeThingUB@@QAEXXZ'
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
report = {'context': ctx, 'objects': {}, 'paired_results': {}}
for source, stem, obj in zip(paths, ('ctor', 'dtor'), objects):
    assert build.compile_is_current(ROOT / source, obj, strict=True)
    before, after = (OUT / (stem + '.obj')).read_bytes(), obj.read_bytes()
    a = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(before)}
    b = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(after)}
    assert a.keys() == b.keys()
    changed = {n for n in a if a[n] != b[n]}
    if stem == 'ctor':
        assert changed == {name}
        assert a[name][0] == bytes.fromhex('c3')
        assert b[name][0] == bytes.fromhex('e900000000')
        old = list((sections(before) - sections(after)).elements())
        new = list((sections(after) - sections(before)).elements())
        assert len(old) == len(new) == 1
        assert old[0][0] == new[0][0] == '.text'
        assert old[0][3] == 'c3' and new[0][3] == 'e900000000'
        assert new[0][4] == ((1, 20, ('external', reset)),)
    else:
        assert not changed and before == after
    report['objects'][source] = {
        'strict_receipt_current': True,
        'changed_comdats': sorted(changed),
        'all_other_nondebug_sections_and_relocations_identical': True,
        'before_object_sha256': hashlib.sha256(before).hexdigest(),
        'after_object_sha256': hashlib.sha256(after).hexdigest(),
        'before_source_sha256': hashlib.sha256((OUT / (stem + '.cpp')).read_bytes()).hexdigest(),
        'after_source_sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
        'before_receipt_sha256': hashlib.sha256((OUT / (stem + '.deps.json')).read_bytes()).hexdigest(),
        'after_receipt_sha256': hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest()}
    if stem == 'ctor':
        # The constructor's first EH action reloads the completed base from
        # EBP-10 and tail-jumps to the destructor COMDAT; it is unchanged.
        data = after
        syms = {s['index']: s for s in lc._coff_symbols(data)}
        for i in range(struct.unpack_from('<H', data, 2)[0]):
            h = 20 + struct.unpack_from('<H', data, 16)[0] + 40 * i
            if data[h:h + 8] != b'.text$x\0':
                continue
            size, at, reloc = struct.unpack_from('<III', data, h + 16)
            assert data[at:at+8] == bytes.fromhex('8b4df0e900000000')
            nr = struct.unpack_from('<H', data, h + 32)[0]
            refs = [struct.unpack_from('<IIH', data, r) for r in range(reloc, reloc+nr*10, 10)]
            assert any(where == 4 and kind == 20 and syms[target]['name'] == name for where, target, kind in refs)
            report['constructor_eh_action'] = {'code': '8b4df0e900000000', 'target': name}
        assert 'constructor_eh_action' in report
# Target evidence: both complete parent unwind tables destroy their base
# through 135E35, whose entire body tail-jumps to the named reset worker.
image, image_sections = build.exe_image()
def retail(rva, size):
    at = build.rva_to_file_offset(image_sections, rva)
    return image[at:at+size]
assert retail(0x135e35, 1) == b'\xe9'
assert 0x135e35 + 5 + struct.unpack('<i', retail(0x135e36, 4))[0] == 0x61ed80
for handler, action in ((0x765aba, 0x765a86), (0x765b51, 0x765b12)):
    info = struct.unpack_from('<I', retail(handler, 10), 1)[0] - 0x400000
    magic, count, table = struct.unpack('<III', retail(info, 12))
    assert magic == 0x19930520
    state, first = struct.unpack('<II', retail(table - 0x400000, 8))
    assert state == 0xffffffff and first - 0x400000 == action
    assert retail(action, 4) == bytes.fromhex('8b4df0e9')
    assert action + 8 + struct.unpack('<i', retail(action+4, 4))[0] == 0x135e35
report['retail_evidence'] = {'ctor_first_unwind_action': '0x765A86 -> 0x135E35',
    'dtor_first_unwind_action': '0x765B12 -> 0x135E35',
    'complete_wrapper': '0x135E35: JMP 0x61ED80', 'new_pin': False}
for phase in ('before', 'after'):
    local = copy.deepcopy(index)
    if phase == 'before':
        d = OUT / 'saved-before'
        d.mkdir(exist_ok=True)
        current = []
        for stem, obj in zip(('ctor', 'dtor'), objects):
            saved = d / obj.name
            shutil.copy2(OUT / (stem + '.obj'), saved)
            current.append(saved)
    else:
        current = objects
    ck.refresh(local, current, truth)
    report['paired_results'][phase] = {s: ck.check_object(o, local, truth, s) for s, o in zip(paths, current)}
assert not any(report['paired_results']['before'][paths[0]].values())
assert report['paired_results']['before'][paths[1]]['comdat'] == [(name, 'first', None)]
for source in paths:
    assert not any(report['paired_results']['after'][source].values())
size = ck.source_bytes(set(paths))
report['local_legacy_linked_bytes'] = {'before': size[paths[0]], 'after': sum(size.values()),
                                     'gain': size[paths[1]]}
report['new_authored_cpp_bytes'] = 0
report['closed_strict'] = 'not measured; runner index contains historical other providers'
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('Byte-current paired legacy findings: 1 -> 0; eligible matched bytes +', size[paths[1]])
print('Only changed COMDAT: empty base destructor now tail-jumps to the retail reset worker.')
