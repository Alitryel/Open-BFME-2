"""Paired current-object and bounded legacy-link evidence for the render counter."""
import collections, copy, hashlib, json, shutil, struct, sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build, link_check as ck, link_census as lc
OUT=ROOT/'build/smudge-counter-owner-link-20261015'
COUNTER='?g_bfmeVal991@@3HA'
OLD_CALL='?bfmeSet991@BfmeB991@@QAEXH@Z'
NEW_CALL='?render@W3DSmudgeManager@@QAEXAAVRenderInfoClass@@@Z'
CONSUMER='Code/GameEngine/Source/Common/BfmeConv991.cpp'
PROVIDER='Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFXParticleSystem.cpp'
def identity(name): return NEW_CALL if name==OLD_CALL else name
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
            body = tuple(identity(symbols[t[0]]['name']) for t in struct.iter_unpack('<I', body))
        else:
            body = body.hex() if body is not None else None
        refs = []
        for at in range(reloc, reloc + nr * 10, 10):
            where, target, kind = struct.unpack_from('<IIH', data, at)
            s = symbols[target]
            if s['storage'] in (2, 105):
                label = ('external', identity(s['name']))
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
    return {(identity(s['name']),s['storage'],s['section']>0,s['value'] if s['section']<=0 else 0)
            for s in lc._coff_symbols(data) if s['storage'] in (2,105)}

def directives(data):
    result=[]
    for i in range(struct.unpack_from('<H',data,2)[0]):
        h=20+struct.unpack_from('<H',data,16)[0]+40*i
        if data[h:h+8].rstrip(b'\0')==b'.drectve':
            n,at=struct.unpack_from('<II',data,h+16);result.append(data[at:at+n])
    return result


paths=json.loads((OUT/'sources.json').read_text())
ctx=json.loads((OUT/'context.json').read_text())
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
index=ck.load_index();truth=lc.RetailTruth(lc.ledger());rank=ck.link_rank(lc.ledger())
objects={};proof={}
for source in paths:
 obj=build.obj_path(ROOT/source);old=OUT/'before'/obj.name
 assert build.compile_is_current(ROOT/source,obj,strict=True),source
 a,b=old.read_bytes(),obj.read_bytes();sa,sb=sections(a),sections(b);ba,bb=bindings(a),bindings(b)
 if source==PROVIDER:
  extra=sb-sa
  assert not sa-sb,(source,list((sa-sb).elements()))
  assert sum(extra.values())==1,list(extra.elements())
  sec=list(extra.elements())[0]
  assert sec[0]=='.bss' and sec[2]==4 and sec[3] in (None,'00000000') and sec[4]==(),sec
  assert bb-ba=={(COUNTER,2,True,0)} and ba-bb=={(COUNTER,2,False,0)},(ba-bb,bb-ba)
 elif source==CONSUMER:
  assert sa==sb and ba==bb,source
 else:
  assert a==b,source
 assert directives(a)==directives(b),source
 ca={s['name']:(body,digest,size) for s,body,relocs,digest,size in lc._comdat_sections(a)}
 cb={s['name']:(body,digest,size) for s,body,relocs,digest,size in lc._comdat_sections(b)}
 if source!=CONSUMER:assert ca==cb,(source,ca.keys()^cb.keys())
 else:assert ca.keys()==cb.keys() and all(ca[n][0]==cb[n][0] and ca[n][2]==cb[n][2] for n in ca),source
 previous={}
 for name,digest,_,verdict in lc.object_facts(old,truth)[0]:previous.setdefault(name,set()).add(digest)
 assert not ck.new_variants(obj,index,truth,previous,rank),source
 proof[source]={'strict_receipt_current':True,'source_sha256':hashlib.sha256((ROOT/source).read_bytes()).hexdigest(),
 'object_before_sha256':hashlib.sha256(a).hexdigest(),'object_after_sha256':hashlib.sha256(b).hexdigest(),
 'retained_comdat_bodies_equal':len(ca),'call_binding_renamed':source==CONSUMER,'only_change_four_byte_zero_owner':source==PROVIDER,'consumer_object_identical':a==b}
 objects[source]=(old,obj)
 after=OUT/'after';after.mkdir(exist_ok=True)
 shutil.copy2(obj,after/obj.name);shutil.copy2(obj.with_suffix('.deps.json'),after/obj.with_suffix('.deps.json').name)
results={}
for phase,n in [('before',0),('after',1)]:
 local=copy.deepcopy(index);ck.refresh(local,[objects[s][n] for s in paths],truth)
 results[phase]={s:ck.check_object(objects[s][n],local,truth,s) for s in paths}
sizes=ck.source_bytes(set(paths));gain=0
for source in paths:
 before,after=results['before'][source],results['after'][source];expected=copy.deepcopy(before)
 if source in (PROVIDER,CONSUMER):
  assert COUNTER in expected['unresolved'],(source,before)
  expected['unresolved'].remove(COUNTER)
 if source==CONSUMER:
  assert OLD_CALL in expected['unresolved'],before
  expected['unresolved'].remove(OLD_CALL)
 assert expected==after,(source,before,after)
 if any(before.values()) and not any(after.values()):gain+=sizes.get(source,0)
 print(source,sum(map(len,before.values())),'->',sum(map(len,after.values())),'findings')
report={'context':ctx,'index_meta':index['meta'],'objects':proof,'paired_results':results,
'removed_unresolved_findings':3,'legacy_linked_bytes_gain':gain,'new_authored_cpp_bytes':0,
'self_strict_gain_claimed':False,'closed_strict_gain_claimed':False,'existing_bytes_affected':sizes}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print('PASS: three missing bindings repaired; legacy LINKED gain',gain)
