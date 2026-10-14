import sys,pathlib,json,hashlib,struct,shutil,csv
sys.path.insert(0,'tools')
import build,link_census,link_check
B=pathlib.Path('build/apt-registry-link-20261014'); ROOT=pathlib.Path.cwd(); paths=(B/'sources.txt').read_text().splitlines()
OLD='?rva002D2C34@Rva002D2C34@@QAEXXZ'; NEW='??0Rva005248D0@@QAE@XZ'
def sections(data):
 syms={s['index']:s for s in link_census._coff_symbols(data)}; out=[]
 for i in range(struct.unpack_from('<H',data,2)[0]):
  h=20+struct.unpack_from('<H',data,16)[0]+i*40; name=data[h:h+8].rstrip(b'\0').decode('latin1')
  if name.startswith('.debug'):continue
  size,ptr,rptr=struct.unpack_from('<III',data,h+16); nr=struct.unpack_from('<H',data,h+32)[0]; rel=[]
  for at in range(rptr,rptr+nr*10,10):
   off,idx,kind=struct.unpack_from('<IIH',data,at); s=syms[idx]; n=s['name']
   if s['storage']==3 and s['section']>0 and n.startswith(('$L','$T')):n='<compiler-local>'
   rel.append([off,kind,n,s['storage'],s['section'],s['value']])
  out.append(dict(name=name,size=size,flags=struct.unpack_from('<I',data,h+36)[0],body=data[ptr:ptr+size].hex() if ptr else None,relocs=rel))
 return out
if sys.argv[1]=='before':
 (B/'objects').mkdir(exist_ok=True);(B/'source').mkdir(exist_ok=True)
 for p in paths:
  obj=build.obj_path(ROOT/p); assert link_census.object_current(ROOT/p,obj,allow_fresh=False)
  shutil.copy2(obj,B/'objects'/obj.name);shutil.copy2(obj.with_suffix('.deps.json'),B/'objects'/obj.with_suffix('.deps.json').name)
  shutil.copy2(p,B/'source'/obj.with_suffix('.cpp').name)
 idx=link_check.load_index();(B/'index-meta.json').write_text(json.dumps(dict(meta=idx['meta'],sha256=hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()),indent=2)+'\n')
 print('snapshotted',len(paths))
else:
 rows={p:[] for p in paths}
 with open('reverse/functions.csv',newline='') as f:
  for r in csv.DictReader(f):
   if r['source'] in rows and r['status']=='matched':rows[r['source']].append(r)
 proof=[]
 for p in paths:
  obj=build.obj_path(ROOT/p); old=B/'objects'/obj.name; before=old.read_bytes();after=obj.read_bytes(); a,b=sections(before),sections(after)
  import object_facts as facts
  ca,oa,ea=facts.facts(old);cb,ob,eb=facts.facts(obj)
  removed=set(ca)-set(cb)
  assert not set(cb)-set(ca),p
  assert removed in (set(),{NEW}),p
  for name in removed:
   assert ca[name]['size'] in (12,17) and len(ca[name]['relocations'])==1 and ca[name]['relocations'][0][1:]==(20,OLD,0,2),(p,ca[name])
  for name in cb:
   aa={k:v for k,v in ca[name].items() if k!='digest'};bb={k:v for k,v in cb[name].items() if k!='digest'}
   aa['relocations']=[(o,k,NEW if n==OLD else n,v,st) for o,k,n,v,st in aa['relocations']]
   assert aa==bb,(p,name)
  assert oa==ob,p+' ordinary sections changed'
  assert facts.directives(old)==facts.directives(obj),p
  expected=sorted((NEW if n==OLD else n,v,False if n==NEW and removed else defined,st) for n,v,defined,st in ea if not (n==OLD and removed))
  assert expected==eb,(p,'external bindings')
  edges=[]
  for r in rows[p]:
   if build.ledger_object_symbol(r).startswith('$L'):continue
   n=int(r['target_size'],0); body,rel=build.read_object_symbol_bytes(old,build.ledger_object_symbol(r),n)
   for off,kind,name in rel:
    if name!=OLD:continue
    assert kind==0x14,(kind,p)
    target=build.read_target_bytes(int(r['target_rva'],16),n); actual=(int(r['target_rva'],16)+off+4+struct.unpack_from('<i',target,off)[0])&0xffffffff
    assert actual==0x2d2c34,(p,hex(actual))
    _,rr=build.read_object_symbol_bytes(obj,build.ledger_object_symbol(r),n);assert (off,kind,NEW) in rr
    edges.append(dict(caller=r['name'],rva=r['target_rva'],offset=off,native_destination=hex(actual)))
  if p!=paths[-1] and not p.endswith('AptRowListCallbacks.cpp'):assert edges,p
  assert link_census.object_current(ROOT/p,obj,allow_fresh=False),p
  proof.append(dict(source=p,before_sha256=hashlib.sha256(before).hexdigest(),after_sha256=hashlib.sha256(after).hexdigest(),strict_receipt_sha256=hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),native_edges=edges,removed_forwarder={name:ca[name] for name in removed},retained_comdats=len(cb),nondebug_sections_unchanged_except_constructor_relocation=True,self_strict_current=True))
 assert proof[-1]['before_sha256']==proof[-1]['after_sha256']
 assert json.loads((B/'index-meta.json').read_text())['sha256']==hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()
 (B/'object-proof.json').write_text(json.dumps(dict(old=OLD,new=NEW,provider_unchanged=True,objects=proof),indent=2)+'\n');print('proved',len(proof),'objects',sum(len(p['native_edges']) for p in proof),'native edges')
