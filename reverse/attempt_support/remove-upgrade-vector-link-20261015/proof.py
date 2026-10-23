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

OUT = ROOT / 'build/remove-upgrade-link-20261015'

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



import copy, shutil
import link_check as ck
ctx=json.loads((OUT/'context.json').read_text());source=ctx['source'];obj=build.obj_path(ROOT/source)
a=(OUT/'before.obj').read_bytes();b=obj.read_bytes()
old={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(a)}
new={s['name']:(body,digest,size) for s,body,_,digest,size in lc._comdat_sections(b)}
removed=set(old)-set(new);retained=set(old)&set(new)
assert len(removed)==19 and not set(new)-set(old)
assert all(old[n]==new[n] for n in retained)
sa,sb=sections(a),sections(b)
old_sx=next(s for s in sa if s[0]=='.sxdata');new_sx=next(s for s in sb if s[0]=='.sxdata')
overflow=next(n for n in removed if n.startswith('?_M_insert_overflow'))
handler='__ehhandler$'+overflow
assert new_sx[3]==tuple(n for n in old_sx[3] if n!=handler)
assert old_sx[2]-new_sx[2]==4
sa.pop(old_sx);sb.pop(new_sx)
assert not sb-sa
assert sum((sa-sb).values())==21
deleted=list((sa-sb).elements())
assert collections.Counter(s[3] for s in deleted if s[0]=='.text')==collections.Counter(old[n][0].hex() for n in removed)
assert collections.Counter(s[0] for s in deleted)=={'.text':19,'.text$x':1,'.xdata$x':1}
syms={s['index']:s for s in lc._coff_symbols(a)}
removed_sections={s['section'] for s in syms.values() if s['name'] in removed or s['name']==handler}
def relocation_refs(section):
 h=20+struct.unpack_from('<H',a,16)[0]+40*(section-1)
 at=struct.unpack_from('<I',a,h+24)[0];nr=struct.unpack_from('<H',a,h+32)[0]
 return [syms[struct.unpack_from('<IIH',a,at+i*10)[1]] for i in range(nr)]
handler_section=next(s['section'] for s in syms.values() if s['name']==handler)
funcinfo=next(s for s in relocation_refs(handler_section) if s['section']>0)
removed_sections.add(funcinfo['section']);assert len(removed_sections)==21
# No retained section points into the removed dependency/EH subtree except
# the unchanged main-function call to the shared push_back symbol.
for section in range(1,struct.unpack_from('<H',a,2)[0]+1):
 h=20+struct.unpack_from('<H',a,16)[0]+40*(section-1);name=a[h:h+8].rstrip(b'\0')
 if section in removed_sections or name.startswith(b'.debug') or name==b'.sxdata':continue
 for ref in relocation_refs(section):
  if ref['section'] in removed_sections:assert ref['name'].startswith('?push_back@?$vector@W4ScienceType'),ref

push='?push_back@?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@QAEXABW4ScienceType@@@Z'
assert bindings(a)-bindings(b)=={(n,2,True,0) for n in removed}|{('?allocate@?$allocator@D@_STL@@SAPADIPBX@Z',2,False,0),('__CxxThrowException@8',2,False,0)}
assert bindings(b)-bindings(a)=={(push,2,False,0)}
assert directives(a)==directives(b)
assert build.compile_is_current(ROOT/source,obj,strict=True)
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
index=ck.load_index();truth=lc.RetailTruth(lc.ledger());rank=ck.link_rank(lc.ledger())
previous={}
for n,d,_,v in lc.object_facts(OUT/'before.obj',truth)[0]:previous.setdefault(n,set()).add(d)
assert not ck.new_variants(obj,index,truth,previous,rank)
# Both phases use current, byte-verified provider witnesses; only the consumer changes.
providers=['Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp','Code/GameEngine/Source/Common/RTS/Player.cpp']
provider_objects=[];provider_receipts={}
for s in providers:
 p=build.obj_path(ROOT/s);assert build.compile_is_current(ROOT/s,p,strict=True),s
 provider_objects.append(p)
 provider_receipts[s]={'object_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'source_sha256':hashlib.sha256((ROOT/s).read_bytes()).hexdigest(),'strict_receipt_current':True}
saved=OUT/'before'/obj.name;saved.parent.mkdir(exist_ok=True);saved.write_bytes(a)
results={};winners={}
for phase,o in [('before',saved),('after',obj)]:
 local=copy.deepcopy(index);ck.refresh(local,[o]+provider_objects,truth)
 results[phase]={s:ck.check_object(p,local,truth,s) for s,p in [(source,o)]+list(zip(providers,provider_objects))}
 winners[phase]={}
 for n in removed:
  copies=sorted(local['comdat'].get(n,[]));loses,rule=lc.keep_rule(copies)
  kept=[(local['objects'][i],d,v) for i,d,v in copies if not loses[i]]
  assert kept,n
  winners[phase][n]=kept[0]
assert winners['before']==winners['after']
before=results['before'][source];after=results['after'][source]
assert len(before['comdat'])==5 and not any(after.values()),(before,after)
for s in providers:assert results['before'][s]==results['after'][s],s
# main/other retained sections keep identical relocations, so removal only
# redirects resolution of push_back from a redundant definition to its owner.
report={'context':ctx,'retained_comdats_identical':len(retained),'removed':{n:{'bytes':old[n][0].hex(),'digest':old[n][1],'size':old[n][2]} for n in sorted(removed)},'removed_non_debug_sections':21,'safeseh_removed_only_overflow_handler':True,'retained_relocation_into_removed_subtree_only_push_back':True,'other_non_debug_sections_and_directives_identical':True,'external_binding_added':push,'no_new_variants':True,'strict_consumer_receipt_current':True,'provider_witnesses':provider_receipts,'paired_results':results,'selected_winners_unchanged':winners['after'],'consumer_before_sha256':hashlib.sha256(a).hexdigest(),'consumer_after_sha256':hashlib.sha256(b).hexdigest(),'legacy_linked_gain':528,'new_authored_cpp_bytes':0,'self_strict_link_gain_claimed':False,'closed_strict_link_gain_claimed':False}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
shutil.copy2(obj,OUT/'after.obj');shutil.copy2(obj.with_suffix('.deps.json'),OUT/'after.deps.json')
print('PASS:',len(retained),'retained COMDATs identical; 19 redundant copies removed; all selected winners unchanged; findings 5 -> 0; legacy linked +528 bytes')
