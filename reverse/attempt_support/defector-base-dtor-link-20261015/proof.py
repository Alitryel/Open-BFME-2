"""Bounded paired link preview against an immutable census; no census writes."""
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
import link_check as ck
OUT = ROOT / 'build/defector-base-dtor-link-20261015'
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


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

names = ['DefectorSpecialPower', 'SpecialPowerModuleDataDtor',
         'CashHackSpecialPowerModuleDataDtor', 'TaintSpecialPowerModuleDataDtor']
sources = ['Code/GameEngine/Source/GameLogic/Object/SpecialPower/' + n + '.cpp' for n in names]
objects = [build.obj_path(ROOT / s) for s in sources]
meta = json.loads((OUT / 'index-meta.json').read_text())
assert sha(ck.INDEX) == meta['sha256']
for source, obj in zip(sources, objects):
    assert build.compile_is_current(ROOT / source, obj, strict=True), source
before_obj = OUT / 'before' / objects[0].name
before, after = before_obj.read_bytes(), objects[0].read_bytes()
removed = {'??1SpecialPowerModuleData@@UAE@XZ', '??1BehaviorModuleData@@UAE@XZ',
           '??1ModuleData@@UAE@XZ'}
def comdats(data):
    return {s['name']: (body, digest, size)
            for s, body, _, digest, size in lc._comdat_sections(data)}
a, b = comdats(before), comdats(after)
assert a.keys() - b.keys() == removed
assert not b.keys() - a.keys()
assert all(a[n] == b[n] for n in b)
old_sections, new_sections = sections(before), sections(after)
lost = list((old_sections - new_sections).elements())
gained = list((new_sections - old_sections).elements())
# Only the three deleted destructor bodies, their EH companion sections and
# the deleted destructor's SafeSEH handler disappear. Everything else is exact.
assert len(lost) == 6 and len(gained) == 1
text = [s for s in lost if s[0] == '.text']
assert collections.Counter(s[3] for s in text) == collections.Counter(a[n][0].hex() for n in removed)
assert [(s[0], s[2]) for s in lost if s[0] not in ('.text', '.sxdata')] == [('.text$x', 18), ('.xdata$x', 36)]
old_seh = next(s for s in lost if s[0] == '.sxdata')
new_seh = gained[0]
handler = '__ehhandler$??1SpecialPowerModuleData@@UAE@XZ'
assert new_seh[0] == '.sxdata' and old_seh[1] == new_seh[1]
assert old_seh[2] - new_seh[2] == 4
assert tuple(n for n in old_seh[3] if n != handler) == new_seh[3]
assert old_seh[4] == new_seh[4] == ()
# Verify the include was actually resolved; a missing /I would silently compile.
receipt = json.loads(objects[0].with_suffix('.deps.json').read_text())
shim = 'reference/open-bfme-1/inputs/reference/shims/specialpowermoduledata/GameLogic/Module/SpecialPowerModule.h'
assert shim in receipt['deps']
truth = lc.RetailTruth(lc.ledger())
results = {}
for phase in ('before', 'after'):
    local = ck.load_index()
    current = [before_obj if phase == 'before' else objects[0], *objects[1:]]
    ck.refresh(local, current, truth)
    results[phase] = {s: ck.check_object(o, local, truth, source=s) for s, o in zip(sources, current)}
results = json.loads(json.dumps(results))
base = '??1SpecialPowerModuleData@@UAE@XZ'
expected = json.loads(json.dumps(results['before']))
for source in sources:
    row = expected[source]
    row['duplicates'] = [n for n in row['duplicates'] if n != base]
    row['comdat'] = [r for r in row['comdat'] if r[0] != base]
    row['selected'] = [n for n in row['selected'] if n != base]
expected[sources[0]]['unresolved'] = [n for n in expected[sources[0]]['unresolved']
                                    if n not in ('??1AudioEventRTS@@UAE@XZ', '??1Snapshot@@QAE@XZ')]
for source in sources:
    for key in expected[source]:
        assert sorted(expected[source][key]) == sorted(results['after'][source][key]), (source, key)
for source in sources[2:]:
    assert not any(results['after'][source].values())
assert sum(len(v) for v in results['before'][sources[0]].values()) == 14
assert sum(len(v) for v in results['after'][sources[0]].values()) == 9
counts = ck.source_bytes(set(sources))
assert counts[sources[2]] + counts[sources[3]] == 132
assert sha(ck.INDEX) == meta['sha256']
report = dict(index=meta, self_strict_current=True, closed_strict_gain_unmeasured=True,
              legacy_predicted_linked_bytes_delta=132, authored_cpp_bytes_delta=0,
              sources={s:dict(object_sha256=sha(o), matched_bytes=counts[s]) for s,o in zip(sources,objects)},
              before_object_sha256=sha(before_obj), retained_comdats_exact=len(b),
              removed_comdats={n:dict(size=a[n][2], digest=a[n][1]) for n in sorted(removed)},
              removed_sections=lost, added_sections=gained, actual_header=shim, results=results)
(OUT / 'proof.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS: 3 obsolete destructor copies and their EH removed; retained sections exact; 9 findings removed across 4 strict-current witnesses; legacy +132 bytes, closed-strict unmeasured.')
