"""Compare one unused COMDAT removal against the saved strict before object."""
import collections
import copy
import hashlib
import json
import struct
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
import link_check as ck
import link_census as lc
OUT = Path('build/terrain-data-getter-link-20261015')
ctx = json.loads((OUT / 'context.json').read_text())
source = ctx['source']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(ck.INDEX) == ctx['index_sha256']
obj = build.obj_path(build.ROOT / source)
before = OUT / 'before' / obj.name
assert sha(before) == ctx['before_object_sha256']
assert lc.object_current(build.ROOT / source, obj, allow_fresh=False)
removed = '?getDataPtr@WorldHeightMap@@QAEPAEXZ'

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
            body = tuple(symbols[t[0]]['name'] for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            assert s['name'] != removed
            if s['storage'] in (2, 105):
                label = ('external', s['name'])
            else:
                assert s['section'] > 0
                tn, tf, tz, tb, _, _ = raw[s['section'] - 1]
                label = ('local', tn, tf, tz, tb.hex() if tb is not None else None, s['value'])
            refs.append((where, kind, label))
        result[(name, flags, size, body, tuple(refs))] += 1
    return result

def bindings(data):
    return {(s['name'], s['storage'], s['section'] > 0,
             s['value'] if s['section'] <= 0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2, 105)}

def comdats(data):
    return {s['name']: (body, digest, size)
            for s, body, rel, digest, size in lc._comdat_sections(data)}

old_data, new_data = before.read_bytes(), obj.read_bytes()
old, new = comdats(old_data), comdats(new_data)
assert old.keys() - new.keys() == {removed}
assert not new.keys() - old.keys()
assert all(old[n] == new[n] for n in new)
assert old[removed][0].hex() == '8b4124c3'
os, ns = sections(old_data), sections(new_data)
dropped = list((os - ns).elements())
assert not ns - os
assert len(dropped) == 1 and dropped[0][3] == old[removed][0].hex()
assert bindings(old_data) - bindings(new_data) == {(removed, 2, True, 0)}
assert not bindings(new_data) - bindings(old_data)
assert lc._weak_externals(old_data) == lc._weak_externals(new_data)
index = ck.load_index()
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase, candidate in [('before', before), ('after', obj)]:
    local = copy.deepcopy(index)
    ck.refresh(local, [candidate], truth)
    results[phase] = ck.check_object(candidate, local, truth, source=source)
old_findings = [r for r in results['before']['comdat'] if r[0] == removed]
assert len(old_findings) == 1
expected = copy.deepcopy(results['before'])
expected['comdat'].remove(old_findings[0])
assert expected == results['after']
assert len(results['after']['unresolved']) == 1
assert not ck.new_variants(obj, index, truth)
assert sha(ck.INDEX) == ctx['index_sha256']
report = dict(context=ctx, before_object_sha256=sha(before), after_object_sha256=sha(obj),
              after_source_sha256=sha(Path(source)),
              before_receipt_sha256=sha(before.with_suffix('.deps.json')),
              after_receipt_sha256=sha(obj.with_suffix('.deps.json')),
              removed_comdat=dict(name=removed, bytes=old[removed][0].hex(), size=old[removed][2]),
              retained_comdats={n:dict(size=v[2], relocation_digest=v[1]) for n,v in new.items()},
              retained_nondebug_sections_bytes_symbolic_relocations_and_bindings_identical=True,
              removed_getter_incoming_nondebug_relocations=0,
              new_imports_aliases_pins_and_weak_externals=0,
              after_strict_receipt_current=True, results=results,
              authored_cpp_gain=0, local_legacy_linked_before=0,local_legacy_linked_after=0,
              self_strict_executable_placement_unmeasured=True, closed_strict_unmeasured=True)
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('Paired proof: one unused 4-byte getter removed, all retained nondebug sections/relocations/bindings unchanged; findings 2 -> 1; legacy linked bytes 0 -> 0.')
