import collections
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/link_check.py').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
import build
import link_census as lc

OUT = ROOT / 'build/unsigned-max-cohort-link-20261014'

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

context = json.loads((OUT / 'context.json').read_text())
context['proof'] = {}
removed_name = '??$max@I@_STL@@YAABIABI0@Z'
for i, source in enumerate(context['paths']):
    before = (OUT / f'before-{i}.obj').read_bytes()
    obj = build.obj_path((ROOT / source).resolve())
    after = obj.read_bytes()
    (OUT / f'after-{i}.obj').write_bytes(after)
    old = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(before)}
    new = {s['name']: (body, digest, size) for s, body, _, digest, size in lc._comdat_sections(after)}
    if i == 2:
        assert before == after, 'canonical provider changed'
        assert build.compile_is_current((ROOT / source).resolve(), obj, strict=True)
        context['proof'][source] = {'whole_object_identical': True, 'strict_receipt_current': True, 'sha256': hashlib.sha256(after).hexdigest()}
        print(source, 'canonical provider whole object identical')
        continue
    removed = old.keys() - new.keys()
    retained = old.keys() & new.keys()
    assert removed == {removed_name}, (source, removed)
    assert not new.keys() - old.keys(), (source, new.keys() - old.keys())
    changed = [n for n in retained if old[n] != new[n]]
    assert not changed, (source, changed)
    def bindings(data):
        return {(s['name'], s['storage'], s['section'] > 0,
                 s['value'] if s['section'] <= 0 else 0)
                for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}
    ob, nb = bindings(before), bindings(after)
    assert ob - nb == {(removed_name, 2, True, 0)}, (source, ob - nb)
    assert not nb - ob, (source, nb - ob)
    os, ns = sections(before), sections(after)
    removed_sections = list((os - ns).elements())
    added_sections = list((ns - os).elements())
    assert len(removed_sections) == 1 and len(added_sections) == 1, (source, removed_sections, added_sections)
    local_name = '?max@_STL@@YAABIABI0@Z'
    helpers = [s for s in lc._coff_symbols(after) if s['name'] == local_name]
    assert len(helpers) == 1 and helpers[0]['storage'] == 3 and helpers[0]['section'] > 0, helpers
    helper = helpers[0]
    count = struct.unpack_from('<H', after, 2)[0]
    optional = struct.unpack_from('<H', after, 16)[0]
    helper_header = 20 + optional + (helper['section'] - 1) * 40
    helper_size, helper_pointer = struct.unpack_from('<II', after, helper_header + 16)
    helper_body = after[helper_pointer:helper_pointer + helper_size]
    assert added_sections[0][3] == helper_body.hex() and not added_sections[0][4]
    # No caller relocation targets either the former external template or
    # the private comparison helper; the matched callers retain inline work.
    for data, name in [(before, removed_name), (after, local_name)]:
        symbols = {s['index']: s for s in lc._coff_symbols(data)}
        target = next(s for s in symbols.values() if s['name'] == name)
        nsections = struct.unpack_from('<H', data, 2)[0]
        opt = struct.unpack_from('<H', data, 16)[0]
        for section in range(nsections):
            h = 20 + opt + section * 40
            section_name = data[h:h + 8].rstrip(b'\0')
            if section_name.startswith(b'.debug'):
                continue
            reloc = struct.unpack_from('<I', data, h + 24)[0]
            nr = struct.unpack_from('<H', data, h + 32)[0]
            for at in range(reloc, reloc + nr * 10, 10):
                _, ref, _ = struct.unpack_from('<IIH', data, at)
                assert symbols[ref]['name'] != name
                assert symbols[ref]['section'] != target['section'], (source, name, symbols[ref])
    assert removed_sections[0][3] == old[removed_name][0].hex()
    def directives(data):
        count = struct.unpack_from('<H', data, 2)[0]
        optional = struct.unpack_from('<H', data, 16)[0]
        result = []
        for at in range(count):
            h = 20 + optional + 40 * at
            if data[h:h+8].rstrip(b'\0') == b'.drectve':
                size, pointer = struct.unpack_from('<II', data, h+16)
                result.append(data[pointer:pointer+size])
        return result
    assert directives(before) == directives(after)
    assert build.compile_is_current((ROOT / source).resolve(), obj, strict=True)
    context['proof'][source] = {
        'retained_comdats_identical': sorted(retained),
        'removed': {n:{'bytes':old[n][0].hex(),'relocation_digest':old[n][1],'size':old[n][2]} for n in removed},
        'bindings_removed':sorted(ob-nb),'bindings_added':sorted(nb-ob),
        'private_helper':{'name':local_name,'storage':3,'bytes':helper_body.hex(),'size':helper_size,'nondebug_call_relocations':0},
        'directives_identical':True,'other_sections_identical':True,'strict_receipt_current':True,
        'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),
        'sha256_before':hashlib.sha256(before).hexdigest(), 'sha256_after':hashlib.sha256(after).hexdigest()}
    print(source, len(retained), 'retained COMDATs identical; external max replaced by unreferenced private helper')
assert hashlib.sha256((ROOT / 'build/link_census/link_index.pkl').read_bytes()).hexdigest() == context['index_sha256']
(OUT / 'object-proof.json').write_text(json.dumps(context, indent=2) + '\n')
