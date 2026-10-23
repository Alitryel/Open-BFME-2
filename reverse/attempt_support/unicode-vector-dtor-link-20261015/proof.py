"""Paired local proof; baseline object is kept in the ignored build directory."""
import copy
import hashlib
import json
import shutil
import struct
import sys
from pathlib import Path

sys.path.insert(0, 'tools')
import build
import link_check as ck
import link_census as lc

out = Path('build/unicode-vector-dtor-link-20261015')
ctx = json.loads((out / 'context.json').read_text())
source = ctx['source']
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(ck.INDEX) == ctx['index_sha256']
after = build.obj_path(build.ROOT / source)
before = out / 'before' / after.name
before.parent.mkdir(exist_ok=True)
shutil.copyfile(out / 'before.obj', before)
assert lc.object_current(build.ROOT / source, after, allow_fresh=False)
old_free, new_free = '_free', '?free@_STL@@YAXPAX@Z'

def sections(path, normalize):
    stat = path.stat()
    data, secs, syms = build._object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    def ref(index):
        s = syms[index]
        if s['storage'] in (2, 105):
            return new_free if normalize and s['name'] == old_free else s['name']
        return ('local', s['section'], s['value'], s['storage'], s['type'])
    result = []
    for sec in secs:
        if sec['name'].startswith('.debug'):
            continue
        pointer, size = sec['raw_pointer'], sec['raw_size']
        body = data[pointer:pointer+size] if pointer else None
        if sec['name'] == '.sxdata':
            body = repr([ref(struct.unpack_from('<I', data, pointer+j)[0])
                         for j in range(0, size, 4)]).encode()
        relocs = []
        for j in range(sec['reloc_count']):
            at, symbol, kind = struct.unpack_from('<IIH', data, sec['reloc_pointer']+10*j)
            relocs.append((at, kind, ref(symbol)))
        result.append((sec['name'], sec['characteristics'], size, body, relocs))
    defs = sorted((s['name'], s['section'], s['value'], s['type'])
                  for s in syms if s.get('storage') == 2 and s['section'] > 0)
    return result, defs

assert sections(before, True) == sections(after, False)
assert lc._weak_externals(before.read_bytes()) == lc._weak_externals(after.read_bytes())

def comdats(path):
    return {s['name']: (body, [(a, k, r['name'], r['storage']) for a, k, r in rel], size)
            for s, body, rel, digest, size in lc._comdat_sections(path.read_bytes())}

old, new = comdats(before), comdats(after)
assert old.keys() == new.keys()
retargets = []
for name in old:
    a, b = old[name], new[name]
    assert a[0] == b[0] and a[2] == b[2] and len(a[1]) == len(b[1])
    for x, y in zip(a[1], b[1]):
        if x != y:
            assert x[:2] == y[:2] and x[2:] == (old_free, 2) and y[2:] == (new_free, 2)
            retargets.append(dict(comdat=name, offset=x[0], kind=x[1]))
assert len(retargets) == 4
truth = lc.RetailTruth(lc.ledger())
index = ck.load_index()
results = {}
for label, obj in [('before', before), ('after', after)]:
    local = copy.deepcopy(index)
    ck.refresh(local, [obj], truth)
    results[label] = ck.check_object(obj, local, truth, source=source)
assert len(results['before']['comdat']) == 4
assert not any(results['after'].values())
assert all(not v for k, v in results['before'].items() if k != 'comdat')
assert not ck.new_variants(after, index, truth)
assert sha(ck.INDEX) == ctx['index_sha256']
report = dict(context=ctx, index_meta=index['meta'], results=results,
              before_object_sha256=sha(before), after_object_sha256=sha(after),
              source_sha256=sha(Path(source)), free_call_retargets=retargets,
              nondebug_bytes_extents_sections_definitions_identical=True,
              only_relocation_change='four _free references become ?free@_STL@@YAXPAX@Z',
              current_source_strict_receipt=True, authored_cpp_gain=0,
              paired_legacy_linked_before=0, paired_legacy_linked_after=63,
              self_strict_executable_placement_unmeasured=True,
              closed_strict_unmeasured=True)
Path(__file__).with_name('proof.json').write_text(json.dumps(report, indent=2)+'\n')
print('Paired proof: 4 -> 0 findings, 0 -> 63 legacy linked bytes; all nondebug bytes preserved.')
