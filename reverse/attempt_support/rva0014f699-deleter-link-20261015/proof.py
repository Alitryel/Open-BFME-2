"""Paired local proof; requires ignored before objects in build/rva0014f699-deleter-link-20261015."""
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
OUT = Path('build/rva0014f699-deleter-link-20261015')
ctx = json.loads((OUT / 'context.json').read_text())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(ck.INDEX) == ctx['index_sha256']
index = ck.load_index()
ctx['index_meta'] = index['meta']
paths = ctx['paths']
objects = [build.obj_path(build.ROOT / p) for p in paths]
before = [OUT / ('before-%d.obj' % i) for i in range(2)]
for p, obj in zip(paths, objects):
    assert lc.object_current(build.ROOT / p, obj, allow_fresh=False), p
assert objects[1].read_bytes() == before[1].read_bytes()
def comdats(path):
    return {s['name']: (b.hex() if b is not None else None, d, z,
                        [(at, kind, r['name'], r['storage']) for at, kind, r in rel])
            for s, b, rel, d, z in lc._comdat_sections(path.read_bytes())}
a, b = comdats(before[0]), comdats(objects[0])
removed = {'??1Rva0014F699@@UAE@XZ', '??1Rva00BC6F24Base@@UAE@XZ',
           '??1?$RefCountPtr@VTextureClass@@@@QAE@XZ',
           '?bfmeAnchorRva0014F699Dtor@@YAXPAVRva0014F699@@@Z'}
ctor = '??0Rva0014F699@@QAE@PAUEmitVtableTag@@@Z'
retained = {'??_GRva0014F699@@UAEPAXI@Z', '??_7Rva0014F699@@6B@'}
assert a.keys() - b.keys() == removed
assert b.keys() - a.keys() == {ctor}
assert a.keys() & b.keys() == retained
assert all(a[n] == b[n] for n in retained)
assert b[ctor][0] == '8bc1c70000000000c20400'
assert b[ctor][3] == [(4, 6, '??_7Rva0014F699@@6B@', 2)]
# Every nondebug after section belongs to a verified retained COMDAT, the
# explicit constructor above, or the unchanged runtime-library directives.
def section_facts(path):
    data = path.read_bytes()
    syms = lc._coff_symbols(data)
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    out = []
    for i in range(count):
        at = 20 + optional + 40*i
        name = data[at:at+8].rstrip(b'\0').decode('latin1')
        if name.startswith('.debug'):
            continue
        size, pointer = struct.unpack_from('<II', data, at+16)
        body = data[pointer:pointer+size].hex() if pointer else None
        leaders = sorted(s['name'] for s in syms if s['storage'] == 2 and s['section'] == i+1)
        out.append((name, size, body, leaders))
    return out
old_sections, new_sections = section_facts(before[0]), section_facts(objects[0])
assert len(new_sections) == 4
assert [s for s in old_sections if s[0] == '.drectve'] == [s for s in new_sections if s[0] == '.drectve']
assert {s[3][0] for s in new_sections if s[3]} == retained | {ctor}
assert lc._weak_externals(before[0].read_bytes()) == lc._weak_externals(objects[0].read_bytes())
truth = lc.RetailTruth(lc.ledger())
results = {}
for label, candidates in [('before', before), ('after', objects)]:
    local = copy.deepcopy(index)
    if label == 'before':
        saved = OUT / 'saved-before'; saved.mkdir(exist_ok=True)
        current = []
        for obj, old in zip(objects, candidates):
            target = saved / obj.name
            shutil.copy2(old, target); current.append(target)
    else:
        current = candidates
    ck.refresh(local, current, truth)
    results[label] = {p: ck.check_object(o, local, truth, source=p) for p, o in zip(paths, current)}
assert {r[0] for r in results['before'][paths[0]]['comdat']} == {'??1Rva0014F699@@UAE@XZ'}
expected = copy.deepcopy(results['before'][paths[0]])
expected['comdat'] = []
assert expected == results['after'][paths[0]]
assert not any(results['after'][paths[0]].values())
assert results['before'][paths[1]] == results['after'][paths[1]]
assert not any(results['after'][paths[1]].values())
assert not ck.new_variants(objects[0], index, truth)
assert sha(ck.INDEX) == ctx['index_sha256']
report = dict(context=ctx, results=results, removed_comdats={n:a[n] for n in sorted(removed)},
              retained_comdats={n:b[n] for n in sorted(retained)}, synthetic_constructor={ctor:b[ctor]},
              nondebug_sections_after=new_sections, provider_byte_identical=True,
              objects=[dict(source=p,before_sha256=sha(o),after_sha256=sha(n),
                            source_sha256=sha(Path(p)),strict_receipt_current=True)
                       for p,o,n in zip(paths,before,objects)],
              local_legacy_linked_bytes_before=189,local_legacy_linked_bytes_after=217,
              local_legacy_gain=28,authored_cpp_bytes_gain=0,
              self_strict_executable_placement_unmeasured=True,closed_strict_unmeasured=True)
print(json.dumps(report, indent=2))
