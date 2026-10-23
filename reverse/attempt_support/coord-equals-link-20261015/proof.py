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

OUT = ROOT / 'build/coord-equals-link-20261015'

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



def bindings(data):
    return {(s['name'],s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}

def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            n,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+n])
    return result

def assert_unreferenced(data,targets):
    syms={s['index']:s for s in lc._coff_symbols(data)}
    for target in targets:
        symbol=next(s for s in syms.values() if s['name']==target)
        for i in range(struct.unpack_from('<H',data,2)[0]):
            h=20+struct.unpack_from('<H',data,16)[0]+40*i
            if data[h:h+8].rstrip(b'\0').startswith(b'.debug'):continue
            start=struct.unpack_from('<I',data,h+24)[0];count=struct.unpack_from('<H',data,h+32)[0]
            for at in range(start,start+10*count,10):
                _,ref,_=struct.unpack_from('<IIH',data,at)
                assert syms[ref]['name']!=target and syms[ref]['section']!=symbol['section']



import copy
import link_check as ck
import data_check as dg
ctx=json.loads((OUT/'context-final.json').read_text());paths=ctx['paths'];name='?equals@Coord3D@@QBE_NABUCoord3DBase@@@Z'
index=ck.load_index();assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
truth=lc.RetailTruth(lc.ledger());proof={};objects={'before':[],'after':[]}
for i,s in enumerate(paths):
    folder=OUT/str(i);obj=build.obj_path((ROOT/s).resolve())
    assert build.compile_is_current((ROOT/s).resolve(),obj,strict=True)
    before=(folder/'before.obj').read_bytes();after=obj.read_bytes();(folder/'after.obj').write_bytes(after)
    saved=folder/'saved-before'/obj.name;saved.parent.mkdir(exist_ok=True);saved.write_bytes(before)
    objects['before'].append(saved);objects['after'].append(obj)
    old={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(before)}
    new={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(after)}
    removed=set(old)-set(new);retained=set(old)&set(new)
    update='?update@FiringTracker@@UAE?AW4UpdateSleepTime@@XZ'
    expected_removed={0:{name},1:set(),2:{update}}[i]
    assert removed==expected_removed,removed
    assert not set(new)-set(old)
    assert all(old[n]==new[n] for n in retained)
    os,ns=sections(before),sections(after)
    missing=list((os-ns).elements());added=list((ns-os).elements())
    assert not added,added
    assert len(missing)==(0 if i==1 else 1),missing
    if i==2:assert missing[0][3]==old[update][0].hex()
    if i==0:
        assert missing[0][3]==old[name][0].hex();assert_unreferenced(before,{name})
    assert directives(before)==directives(after)
    ob,nb=bindings(before),bindings(after)
    expected_bindings={(n,2,True,0) for n in expected_removed}
    if i==2:expected_bindings.add(('?reloadAllAmmo@Object@@QAEX_N@Z',2,False,0))
    assert ob-nb==expected_bindings,ob-nb
    assert nb-ob==({(update,2,False,0)} if i==2 else set()),nb-ob
    proof[s]={'retained_comdats':len(retained),'removed':sorted(removed),'other_nondebug_sections_and_relocations_identical':True,'external_bindings_removed':sorted(ob-nb),'external_bindings_added':sorted(nb-ob),'directives_identical':True,'before_sha256':hashlib.sha256(before).hexdigest(),'after_sha256':hashlib.sha256(after).hexdigest(),'strict_current':True}
old_inline={s['name']:(b,d,z) for s,b,_,d,z in lc._comdat_sections((OUT/'1/before.obj').read_bytes())}[name]
old_exclusive={s['name']:(b,d,z) for s,b,_,d,z in lc._comdat_sections((OUT/'0/before.obj').read_bytes())}[name]
assert old_inline==old_exclusive
proof['equals_twin']={'size':old_inline[2],'bytes':old_inline[0].hex(),'relocation_digest':old_inline[1]}
results={}
for phase in objects:
    local=copy.deepcopy(index);ck.refresh(local,objects[phase],truth)
    results[phase]={s:ck.check_object(o,local,truth,s) for s,o in zip(paths,objects[phase])}
for s in paths:
    expected=copy.deepcopy(results['before'][s])
    for key in expected:
        expected[key]=[row for row in expected[key] if (row if isinstance(row,str) else row[0]) not in {name,update}]
    assert expected==results['after'][s],(expected,results['after'][s])
assert not any(results['after'][paths[0]].values())
assert not any(results['after'][paths[1]].values())
original=dg.build.row_object;data={}
for phase in objects:
    saved=dict(zip(paths,objects[phase]));dg.build.row_object=lambda row:saved.get(row['source'],original(row))
    missing=[];facts=dg.object_facts(dg.source_rows(paths),missing);assert not missing,missing
    data[phase]={'facts':{s:[sorted(b),sorted(d)] for s,(b,d) in facts.items()},'findings':dg.findings(facts,dg.dl.load())}
dg.build.row_object=original
assert data['before']==data['after']
source_bytes=ck.source_bytes(set(paths))
result={'context':ctx,'objects':proof,'findings':results,'data':data,'legacy_predicted_linked_before':0,'legacy_predicted_linked_after':(source_bytes[paths[0]]+source_bytes[paths[1]]),'source_bytes_after':source_bytes,'new_authored_unique_bytes':0}
(OUT/'final-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'objects':proof,'findings':results,'legacy_linked_after':(source_bytes[paths[0]]+source_bytes[paths[1]]),'data_findings':len(data['after']['findings'])},indent=2))
