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

OUT = ROOT / 'build/apt-invoke-owner-link-20261015'

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
ctx=json.loads((OUT/'context.json').read_text())
paths=(OUT/'sources.txt').read_text().splitlines()
name='?Rva0021639AInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABH@Z'
index=ck.load_index();assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
truth=lc.RetailTruth(lc.ledger());proof={};objects={'before':[],'after':[]};twins=[]
for i,s in enumerate(paths):
    obj=build.obj_path((ROOT/s).resolve());old=OUT/'before'/obj.name
    assert lc.object_current((ROOT/s).resolve(),obj,allow_fresh=False)
    before=old.read_bytes();after=obj.read_bytes()
    objects['before'].append(old);objects['after'].append(obj)
    oldparts={x['name']:(body,digest,size) for x,body,_,digest,size in lc._comdat_sections(before)}
    newparts={x['name']:(body,digest,size) for x,body,_,digest,size in lc._comdat_sections(after)}
    twins.append(oldparts[name]);assert twins[0]==twins[-1]
    removed=set(oldparts)-set(newparts);retained=set(oldparts)&set(newparts)
    assert removed==({name} if i==0 else set()),removed
    assert not set(newparts)-set(oldparts)
    assert all(oldparts[n]==newparts[n] for n in retained)
    os,ns=sections(before),sections(after)
    missing=list((os-ns).elements());added=list((ns-os).elements())
    print(s,'removed sections',len(missing),'added sections',len(added))
    print('bindings removed',bindings(before)-bindings(after),'added',bindings(after)-bindings(before))
    if i==0:
        assert len(added)==1 and added[0][0]=='.sxdata'
        sx=next(x for x in missing if x[0]=='.sxdata')
        assert tuple(x for x in sx[3] if x!='__ehhandler$'+name)==added[0][3]
        assert sx[:2]==added[0][:2] and sx[2]==added[0][2]+4
        assert sx[4]==added[0][4]==()
        assert_unreferenced(before,{name})
        assert len(missing)==4
        assert sorted((x[0],x[2]) for x in missing if x[0]!='.sxdata')==[('.text',149),('.text$x',26),('.xdata$x',44)]
        assert next(x for x in missing if x[0]=='.text')[3]==oldparts[name][0].hex()
        assert bindings(before)-bindings(after)=={(name,2,True,0)}
        assert not bindings(after)-bindings(before)
    else:assert not added and not missing
    if i==1:
        a,b=bytearray(before),bytearray(after);a[4:8]=b[4:8]=b'\0'*4
        assert a==b
    assert directives(before)==directives(after)
    proof[s]={'retained_comdats':len(retained),'removed':sorted(removed),'removed_nondebug_sections':[{'section':x[0],'size':x[2],'body':x[3],'relocations':x[4]} for x in missing],'external_bindings_removed':sorted(bindings(before)-bindings(after)),'external_bindings_added':sorted(bindings(after)-bindings(before)),'directives_identical':True,'before_sha256':hashlib.sha256(before).hexdigest(),'after_sha256':hashlib.sha256(after).hexdigest(),'strict_current':True,'before_receipt_sha256':hashlib.sha256((OUT/'before'/obj.with_suffix('.deps.json').name).read_bytes()).hexdigest(),'after_receipt_sha256':hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest()}
results={}
for phase in objects:
    local=copy.deepcopy(index);ck.refresh(local,objects[phase],truth)
    results[phase]={s:ck.check_object(o,local,truth,s) for s,o in zip(paths,objects[phase])}
    if phase=='after':
        import pickle
        with (OUT/'preview-index.pkl').open('wb') as f:pickle.dump(local,f,pickle.HIGHEST_PROTOCOL)
for s in paths:
    expected=copy.deepcopy(results['before'][s]);expected['duplicates'].remove(name)
    assert expected==results['after'][s],(expected,results['after'][s])
assert not any(results['after'][paths[0]].values())
source_bytes=ck.source_bytes(set(paths));before_bytes=dict(source_bytes);before_bytes[paths[0]]+=149;before_bytes[paths[1]]-=149
linked={p:sum((before_bytes if p=='before' else source_bytes)[s] for s,v in results[p].items() if not any(v.values())) for p in results}
import data_check as dg
original=dg.build.row_object;data={}
for phase in objects:
    saved=dict(zip(paths,objects[phase]));dg.build.row_object=lambda row:saved.get(row['source'],original(row))
    missing=[];facts=dg.object_facts(dg.source_rows(paths),missing);assert not missing,missing
    data[phase]={'facts':{s:[sorted(b),sorted(d)] for s,(b,d) in facts.items()},'findings':dg.findings(facts,dg.dl.load())}
dg.build.row_object=original
assert data['before']==data['after']
result={'data':data,'context':ctx,'objects':proof,'identical_149_byte_twin':{'size':twins[0][2],'bytes':twins[0][0].hex(),'relocation_digest':twins[0][1]},'paired_legacy_findings':results,'before_matched_bytes':before_bytes,'after_matched_bytes':source_bytes,'legacy_predicted_linked_bytes':linked,'new_authored_unique_bytes':0,'closed_strict_gain_claimed':False}
Path('reverse/attempt_support/apt-invoke-owner-link-20261015/proof.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps({'findings':results,'legacy_linked_bytes':linked},indent=2))
