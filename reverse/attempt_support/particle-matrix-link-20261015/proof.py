import collections,copy,hashlib,json,shutil,struct,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/particle-matrix-link-20261015'
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
assert build.compile_is_current(ROOT/source,obj,strict=True)
shutil.copy2(obj,OUT/'after.obj');shutil.copy2(obj.with_suffix('.deps.json'),OUT/'after.deps.json')
before=(OUT/'before.obj').read_bytes();after=obj.read_bytes()
removed='??AMatrix3@@QBEABVVector3@@H@Z'
added={'??AMatrix3@@QAEAAVVector3@@H@Z','??AVector3@@QAEAAMH@Z'}
old={s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(before)}
new={s['name']:(body,refs,digest,size) for s,body,refs,digest,size in lc._comdat_sections(after)}
assert old.keys()-new.keys()=={removed}
assert new.keys()-old.keys()==added
assert all((old[n][0],old[n][2],old[n][3])==(new[n][0],new[n][2],new[n][3]) for n in old.keys()&new.keys())
os,ns=sections(before),sections(after)
removed_sections=list((os-ns).elements());added_sections=list((ns-os).elements())
assert old[removed][:3]==new['??AMatrix3@@QAEAAVVector3@@H@Z'][:3]
assert not removed_sections and len(added_sections)==1
assert added_sections[0][3]==new['??AVector3@@QAEAAMH@Z'][0].hex()
assert directives(before)==directives(after)
ob,nb=bindings(before),bindings(after)
assert ob-nb=={(removed,2,True,0)},ob-nb
assert nb-ob=={(n,2,True,0) for n in added},nb-ob
assert_unreferenced(before,[removed]);assert_unreferenced(after,added)
providers={}
for name in sorted(added):
    copies=index['comdat'][name]
    assert {d for p,d,v in copies}=={new[name][2]}
    assert all(v in (None,'retail') for p,d,v in copies)
    providers[name]={'size':new[name][3],'bytes':new[name][0].hex(),'relocations':new[name][1],'digest':new[name][2], 'census_copies':len(copies),'census_verdicts':sorted({str(v) for p,d,v in copies}),'first_census_object':index['objects'][copies[0][0]]}
folder=OUT/'saved-before';folder.mkdir(exist_ok=True)
bobj=folder/obj.name;shutil.copy2(OUT/'before.obj',bobj)
results={}
for phase,current in [('before',bobj),('after',obj)]:
    local=copy.deepcopy(index);ck.refresh(local,[current],truth)
    results[phase]=ck.check_object(current,local,truth,source)
assert sum(map(len,results['before'].values()))==1,results['before']
assert results['before']['comdat'][0][0]==removed
assert not any(results['after'].values()),results['after']
proof={'context':ctx,'results':results,'retained_comdats_identical':len(old.keys()&new.keys()),'removed':{'name':removed,'size':old[removed][3],'bytes':old[removed][0].hex(),'digest':old[removed][2]},'compatible_added_accessors':providers,'sections_bindings_directives_identical_except_described_accessor_changes':True,'no_nondebug_relocations_to_changed_accessors':True,'consumer_strict_current':True,'legacy_linked_before':0,'legacy_linked_after':1816,'closed_strict_claim':False,'before_object_sha256':hashlib.sha256(before).hexdigest(),'after_object_sha256':hashlib.sha256(after).hexdigest(),'before_receipt_sha256':hashlib.sha256((OUT/'before.deps.json').read_bytes()).hexdigest(),'after_receipt_sha256':hashlib.sha256((OUT/'after.deps.json').read_bytes()).hexdigest()}
(OUT/'proof.json').write_text(json.dumps(proof,indent=2,default=lambda v:v.hex() if isinstance(v,bytes) else str(v))+'\n')
print(json.dumps({k:proof[k] for k in ['retained_comdats_identical','legacy_linked_before','legacy_linked_after','results']},indent=2))
