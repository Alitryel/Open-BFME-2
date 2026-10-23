import hashlib,json,struct,sys,copy
from pathlib import Path
sys.path.insert(0,"tools")
import build,link_check as ck,link_census as lc,data_check as dc,data_ledger as dl
def sections(path,names):
 data=path.read_bytes();syms=lc._coff_symbols(data);byid={z['index']:z for z in syms};count=struct.unpack_from('<H',data,2)[0];optional=struct.unpack_from('<H',data,16)[0];result=[]
 for i in range(count):
  h=20+optional+i*40;label=data[h:h+8].rstrip(b'\0').decode('latin1');size,p,relp=struct.unpack_from('<III',data,h+16);nr=struct.unpack_from('<H',data,h+32)[0];flags=struct.unpack_from('<I',data,h+36)[0]
  if label.startswith('.debug'):continue
  rel=[]
  for at in range(relp,relp+nr*10,10):
   off,target,typ=struct.unpack_from('<IIH',data,at);z=byid[target];rel.append((off,typ,names.get(z['name'],z['name']),z['value'],z['storage']))
  owners=sorted(names.get(z['name'],z['name']) for z in syms if z['storage']==lc.EXTERNAL and z['section']==i+1)
  result.append((label,size,flags,hashlib.sha256(data[p:p+size] if p else b'').hexdigest(),owners,rel))
 return result
root=Path('build/army-entry-max-link-20261014')
a=json.loads((root/'before.json').read_text());b=json.loads((root/'after.json').read_text())
s=(root/'sources.txt').read_text().strip();aa=a['sources'][s];bb=b['sources'][s]
oldname='??$max@I@_STL@@YAABIABI0@Z';newname='?max@_STL@@YAABIABI0@Z'
ac={x['name']:x for x in aa['copies']};bc={x['name']:x for x in bb['copies']}
assert ac.keys()-bc.keys()=={oldname};assert not bc.keys()-ac.keys()
def clean(c):return c['body'],c['size'],c['digest'],[(o,t,{k:v for k,v in r.items() if k not in ('section','index')}) for o,t,r in c['relocations']]
for n in bc:assert clean(ac[n])==clean(bc[n]),n
assert aa['facts_tail']==bb['facts_tail'];assert aa['strict_current'] and bb['strict_current']
obj=build.obj_path(Path(s).resolve());historical=root/'historical';historical.mkdir(exist_ok=True);old=historical/obj.name
old.write_bytes((root/('before-'+Path(s).stem+'.obj')).read_bytes())
def full_sections(path):
 data=path.read_bytes();syms=lc._coff_symbols(data);byid={z['index']:z for z in syms};n=struct.unpack_from('<H',data,2)[0];optional=struct.unpack_from('<H',data,16)[0]
 labels={}
 for z in syms:
  if z['storage']==3 and z['section']>0 and z['name'].startswith('$'):
   h=20+optional+(z['section']-1)*40;label=data[h:h+8].rstrip(b'\0').decode('latin1');size,p=struct.unpack_from('<II',data,h+16)
   labels[z['name']]='local:'+label+':'+hashlib.sha256(data[p:p+size] if p else b'').hexdigest()+':'+str(z['value'])
 base=sections(path,labels)
 records=[];helpers=[]
 for i in range(n):
  h=20+optional+i*40;label=data[h:h+8].rstrip(b'\0').decode('latin1')
  if label.startswith('.debug'):continue
  size,p,relp=struct.unpack_from('<III',data,h+16);nr=struct.unpack_from('<H',data,h+32)[0]
  names=[z['name'] for z in syms if z['section']==i+1 and z['storage'] in (lc.EXTERNAL,3) and z['value']==0]
  if oldname in names or newname in names:
   assert label=='.text' and nr==0
   helpers.append(dict(names=names,body=data[p:p+size].hex(),size=size,relocations=nr))
   continue
  record=next(z for z in base if z[0]==label and z[1]==size and z[3]==hashlib.sha256(data[p:p+size] if p else b'').hexdigest() and z[4]==sorted(x['name'] for x in syms if x['storage']==lc.EXTERNAL and x['section']==i+1))
  records.append(record)
 incoming=[]
 for i in range(n):
  h=20+optional+i*40;label=data[h:h+8].rstrip(b'\0').decode('latin1')
  if label.startswith('.debug'):continue
  relp=struct.unpack_from('<I',data,h+24)[0];nr=struct.unpack_from('<H',data,h+32)[0]
  for at in range(relp,relp+nr*10,10):
   off,target,typ=struct.unpack_from('<IIH',data,at)
   if byid[target]['name'] in (oldname,newname):incoming.append((label,off,typ))
 return sorted(records,key=repr),helpers,incoming
ss0,hh0,in0=full_sections(old);ss1,hh1,in1=full_sections(obj)

if ss0!=ss1:
 from collections import Counter
 print('ONLY BEFORE',list((Counter(map(repr,ss0))-Counter(map(repr,ss1))).elements()))
 print('ONLY AFTER',list((Counter(map(repr,ss1))-Counter(map(repr,ss0))).elements()))
assert ss0==ss1;assert len(hh0)==len(hh1)==1;assert not in0 and not in1
assert hh0[0]['body']==ac[oldname]['body'] and hh0[0]['size']==16
assert hh1[0]['body']=='8b113b100f43c1c3'
truth=lc.RetailTruth(lc.ledger());index=ck.load_index()
assert a['index_sha256']==b['index_sha256']==hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
provider='Code/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_init.cpp';po=build.obj_path(Path(provider).resolve())
assert lc.object_current(Path(provider).resolve(),po,allow_fresh=False)
pc=[(z,body,rs,digest,size) for z,body,rs,digest,size in lc._comdat_sections(po.read_bytes()) if z['name']==oldname]
assert len(pc)==1 and pc[0][4]==17 and truth.verdict(*pc[0])=='retail'
ck.refresh(index,[old,po],truth);before={s:ck.check_object(old,index,truth,s),provider:ck.check_object(po,index,truth,provider)}
ck.refresh(index,[obj],truth);after={s:ck.check_object(obj,index,truth,s),provider:ck.check_object(po,index,truth,provider)}
assert before[provider]==after[provider]
for k in before[s]:
 expected=[n for n in before[s][k] if n[0]!=oldname] if k=='comdat' else before[s][k]
 assert expected==after[s][k],k
assert len(before[s]['comdat'])-len(after[s]['comdat'])==1
original=build.row_object;rows=dc.source_rows([s]);facts={};findings={}
try:
 for phase,path in [('before',old),('after',obj)]:
  build.row_object=lambda row:path
  unread=[];facts[phase]=dc.object_facts(rows,unread);assert not unread
  findings[phase]=dc.findings(facts[phase],dl.load())
finally:build.row_object=original
assert facts['before']==facts['after'];assert findings['before']==findings['after']
proof=dict(base=a['base'],measurement=a['index_meta'],index_sha256=a['index_sha256'],mode='strict byte receipts; paired legacy link preview; no closed-strict gain',source=s,retained_identical_comdats=len(bc),retained={n:dict(size=bc[n]['size'],digest=bc[n]['digest']) for n in sorted(bc)},nondebug_sections_unchanged=len(ss0),old_helper=hh0,new_helper=hh1,helpers_have_no_incoming_or_outgoing_relocations=True,external_bindings_unchanged_except_removed_definition=True,data_findings=findings['after'],strict_before=aa['strict_current'],strict_after=bb['strict_current'],before_source_sha256=aa['source_sha256'],after_source_sha256=bb['source_sha256'],before_object_sha256=aa['object_sha256'],after_object_sha256=bb['object_sha256'],provider=dict(source=provider,source_sha256=hashlib.sha256(Path(provider).read_bytes()).hexdigest(),object_sha256=hashlib.sha256(po.read_bytes()).hexdigest(),strict_current=True,max_body=pc[0][1].hex(),max_size=pc[0][4],max_digest=pc[0][3],verdict='retail'),paired_legacy_findings=dict(before=before,after=after),legacy_linked_byte_gain=0)
(root/'object-proof.json').write_text(json.dumps(proof,indent=2,default=str)+'\n')
print('retained COMDATs',len(bc),'unchanged nondebug sections',len(ss0),'findings',sum(map(len,before[s].values())),'->',sum(map(len,after[s].values())))
