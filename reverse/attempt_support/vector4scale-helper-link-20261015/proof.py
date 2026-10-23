import collections,copy,hashlib,json,shutil,struct,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/vector4scale-helper-link-20261015'
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


ctx=json.loads((OUT/'context.json').read_text())
index=ck.load_index();truth=lc.RetailTruth(lc.ledger())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
source=ctx['source'];obj=build.obj_path(ROOT/source)
provider='Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.cpp'
pobj=build.obj_path(ROOT/provider)
assert build.compile_is_current(ROOT/source,obj,strict=True)
assert build.compile_is_current(ROOT/provider,pobj,strict=True)
shutil.copy2(obj,OUT/'after.obj');shutil.copy2(obj.with_suffix('.deps.json'),OUT/'after.deps.json')
before=(OUT/'before.obj').read_bytes();after=obj.read_bytes()
name='??D@YA?AVVector4@@ABV0@M@Z'
old={s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(before)}
new={s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(after)}
assert old.keys()-new.keys()=={name},old.keys()-new.keys()
assert not new.keys()-old.keys()
assert all((old[n][0],old[n][2],old[n][3])==(new[n][0],new[n][2],new[n][3]) for n in new)
os,ns=sections(before),sections(after)
removed_sections=list((os-ns).elements());added_sections=list((ns-os).elements())
assert len(removed_sections)==1 and not added_sections,(removed_sections,added_sections)
assert removed_sections[0][3]==old[name][0].hex()
assert directives(before)==directives(after)
ob,nb=bindings(before),bindings(after)
assert ob-nb=={(name,2,True,0)},ob-nb
assert not nb-ob,nb-ob
assert_unreferenced(before,[name])
folder=OUT/'saved-before';folder.mkdir(exist_ok=True)
bobj=folder/obj.name;shutil.copy2(OUT/'before.obj',bobj)
results={}
for phase,current in [('before',bobj),('after',obj)]:
    local=copy.deepcopy(index)
    ck.refresh(local,[current,pobj],truth)
    results[phase]={source:ck.check_object(current,local,truth,source),provider:ck.check_object(pobj,local,truth,provider)}
assert len(results['before'][source]['comdat'])==1,results['before'][source]
assert results['before'][source]['comdat'][0][0]==name
assert sum(map(len,results['before'][source].values()))==1
assert not any(results['after'][source].values()),results['after'][source]
assert results['before'][provider]==results['after'][provider]
providers=[]
for s,body,refs,digest,size in lc._comdat_sections(pobj.read_bytes()):
    if s['name']==name:providers.append({'size':size,'bytes':body.hex(),'relocations':refs,'digest':digest,'verdict':next(v for n,d,sz,v in lc.object_facts(pobj,truth)[0] if n==name)})
proof={'context':ctx,'index_meta':index['meta'],'results':results,'retained_comdats_identical':len(new),'removed':{'name':name,'size':old[name][3],'bytes':old[name][0].hex(),'relocations':old[name][1],'digest':old[name][2]},'provider':providers,'other_sections_bindings_and_directives_identical':True,'no_nondebug_caller_relocations_to_removed_body':True,'consumer_and_provider_strict_current':True,'legacy_linked_before':0,'legacy_linked_after':69,'closed_strict_claim':False,'before_object_sha256':hashlib.sha256(before).hexdigest(),'after_object_sha256':hashlib.sha256(after).hexdigest()}
(OUT/'proof.json').write_text(json.dumps(proof,indent=2,default=lambda v:v.hex() if isinstance(v,bytes) else str(v))+'\n')
print(json.dumps({k:proof[k] for k in ['retained_comdats_identical','legacy_linked_before','legacy_linked_after','results']},indent=2))
