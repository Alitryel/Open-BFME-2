import copy, hashlib, json, sys, subprocess
from pathlib import Path
sys.path.insert(0, 'tools')
import build, link_check as ck, link_census as lc
out = Path('build/link-stlport-factory-20261018')
sources = json.loads((out/'sources.json').read_text())
providers = ['Code/Libraries/Source/WWVegas/WWLib/stlport_wide_filebuf.cpp',
             'Code/Libraries/Source/WWVegas/WWLib/stlport_wide_filebuf_allocate.cpp']
truth = lc.RetailTruth(lc.ledger()); index = ck.load_index()
proof = {'base': subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),
         'index_meta':index['meta'], 'index_sha256':hashlib.sha256(ck.INDEX.read_bytes()).hexdigest(),
         'scope':'paired legacy preview with identical current providers; self-strict receipts separately; no closed-strict claim',
         'sources':{}, 'providers':{}}
findings = {}
for mode in ['before','after']:
    objs = [out/build.obj_path(p).name if mode=='before' else build.obj_path(p) for p in sources]
    objs += [build.obj_path(p) for p in providers]
    state = copy.deepcopy(index); ck.refresh(state, objs, truth)
    findings[mode] = {p: ck.check_object(o,state,truth,p) for p,o in zip(sources+providers,objs)}
for p in providers:
    assert findings['before'][p] == findings['after'][p]
    proof['providers'][p] = findings['after'][p]
for p in sources:
    old = out/build.obj_path(p).name; new = build.obj_path(p)
    before = {n:(d,z,v) for n,d,z,v in lc.object_facts(old,truth)[0]}
    after = {n:(d,z,v) for n,d,z,v in lc.object_facts(new,truth)[0]}
    changed = [n for n in before.keys() & after.keys() if before[n] != after[n]]
    assert not changed, changed
    b = {k:v for k,v in findings['before'][p].items() if k!='unreferenced_differs'}
    a = {k:v for k,v in findings['after'][p].items() if k!='unreferenced_differs'}
    assert not any(a.values()), (p,a)
    proof['sources'][p] = {'before':b,'after':a,
        'removed':sorted(before.keys()-after.keys()), 'added':sorted(after.keys()-before.keys()),
        'retained_comdats_unchanged':len(before.keys() & after.keys()),
        'before_object_sha256':hashlib.sha256(old.read_bytes()).hexdigest(),
        'after_object_sha256':hashlib.sha256(new.read_bytes()).hexdigest()}
assert any(proof['sources'][sources[0]]['before'].values())
proof['newly_linked_existing_unit_bytes'] = ck.source_bytes({sources[0]})[sources[0]]
proof['new_alias_bytes'] = 4
proof['unique_cpp_bytes_added'] = 0
assert proof['newly_linked_existing_unit_bytes']==4139
(out/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
print('Paired legacy: +4139 existing unit bytes linked; 4-byte alias adds zero unique C++ bytes; retained COMDATs/providers unchanged')
