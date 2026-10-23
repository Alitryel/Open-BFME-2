import sys, pathlib, json, struct, hashlib, csv, shutil
sys.path.insert(0,'tools')
import build, link_census, link_check
BASE=pathlib.Path('build/frame-rate-cohort-link-20261015'); ROOT=pathlib.Path.cwd()
paths=(BASE/'sources.txt').read_text().splitlines()
renames={n:('?BfmeLogicFramesPerSecond@@3HA',0xDBA4E4) for n in ['?g_Va00DBA4E4@@3HA','?g_00DBA4E4@@3HA']}
def sections(data):
 symbols={s['index']:s for s in link_census._coff_symbols(data)}
 count=struct.unpack_from('<H',data,2)[0]; optional=struct.unpack_from('<H',data,16)[0]
 out=[]
 for i in range(count):
  h=20+optional+i*40; section_name=data[h:h+8].rstrip(b'\0').decode('latin1')
  if section_name.startswith('.debug') : continue
  size,ptr,rptr=struct.unpack_from('<III',data,h+16); nr=struct.unpack_from('<H',data,h+32)[0]; flags=struct.unpack_from('<I',data,h+36)[0]
  rr=[]
  for at in range(rptr,rptr+nr*10,10):
   where,target,kind=struct.unpack_from('<IIH',data,at); s=symbols[target]
   name=s['name']
   if s['storage']==3 and s['section']>0 and name.startswith(('$L','$T')): name='<compiler-local>'
   rr.append([where,kind,name,s['storage'],s['section'],s['value']])
  out.append(dict(index=i+1,name=section_name,size=size,flags=flags,body=(data[ptr:ptr+size].hex() if ptr else None),relocs=rr))
 return out
if sys.argv[1]=='before':
 (BASE/'objects').mkdir(exist_ok=True)
 for source in paths:
  obj=build.obj_path(ROOT/source); shutil.copy2(obj,BASE/'objects'/obj.name); shutil.copy2(obj.with_suffix('.deps.json'),BASE/'objects'/obj.with_suffix('.deps.json').name)
  assert link_census.object_current(ROOT/source,obj,allow_fresh=False),source
 idx=link_check.load_index()
 (BASE/'index-meta.json').write_text(json.dumps({'meta':idx['meta'],'sha256':hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()},indent=2)+'\n')
 print('snapshotted',len(paths),'self-strict objects')
else:
 rows={s:[] for s in paths}
 with open('reverse/functions.csv',newline='') as f:
  for r in csv.DictReader(f):
   if r['source'] in rows and r['status']=='matched': rows[r['source']].append(r)
 proof=[]
 for source in paths:
  obj=build.obj_path(ROOT/source); before=(BASE/'objects'/obj.name).read_bytes(); after=obj.read_bytes(); a,b=sections(before),sections(after)
  assert len(a)==len(b),source
  for sa,sb in zip(a,b):
   assert {k:v for k,v in sa.items() if k!='relocs'}=={k:v for k,v in sb.items() if k!='relocs'},source
   expected=[[o,k,renames[n][0] if n in renames else n,st,se,v] for o,k,n,st,se,v in sa['relocs']]
   assert expected==sb['relocs'],(source,sa['name'])
  defs=lambda data: sorted((s['name'],s['section'],s['storage'],s['value']) for s in link_census._coff_symbols(data) if s['storage']==2 and s['section']>0)
  assert defs(before)==defs(after),source
  externals=lambda data: sorted((renames.get(t['name'],(t['name'],None))[0],t['section'],t['storage'],t['value']) for t in link_census._coff_symbols(data) if t['storage']==2)
  assert externals(before)==externals(after),source+' external symbols changed'
  edges=[]
  for r in rows[source]:
   if r['name'].startswith('$L'): continue
   size=int(r['target_size'],0); body,rr=build.read_object_symbol_bytes(BASE/'objects'/obj.name,build.ledger_object_symbol(r),size)
   for off,kind,name in rr:
    if name not in renames: continue
    new,dest=renames[name]; assert kind==6 and off<size
    target=build.read_target_bytes(int(r['target_rva'],16),size)
    actual=struct.unpack_from('<I',target,off)[0]
    assert dest==actual,(name,hex(actual))
    final,relocs=build.read_object_symbol_bytes(obj,build.ledger_object_symbol(r),size)
    assert (off,kind,new) in relocs,(source,new)
    edges.append(dict(caller=r['name'],rva=r['target_rva'],offset=off,old_name=name,new_name=new,native_destination=hex(actual)))
  if source!=paths[-1]: assert edges,source
  assert link_census.object_current(ROOT/source,obj,allow_fresh=False),source
  assert not set(renames)&{s['name'] for s in link_census._coff_symbols(after)},source
  proof.append(dict(source=source,before_sha256=hashlib.sha256(before).hexdigest(),sha256=hashlib.sha256(after).hexdigest(),before_receipt_sha256=hashlib.sha256((BASE/'objects'/obj.with_suffix('.deps.json').name).read_bytes()).hexdigest(),after_receipt_sha256=hashlib.sha256(obj.with_suffix('.deps.json').read_bytes()).hexdigest(),comdat_count=len(list(link_census.comdat_bodies(obj))),section_bytes_flags_extents_and_external_definitions_unchanged=True,only_data_relocation_names_changed=True,self_strict_current=True,native_edges=edges))
 provider=build.obj_path(ROOT/paths[-1]); syms=link_census._coff_symbols(provider.read_bytes())
 for name in {p[0] for p in renames.values()}: assert any(s['name']==name and s['section']>0 for s in syms),name
 assert json.loads((BASE/'index-meta.json').read_text())['sha256']==hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()
 result=dict(census_sha256=hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest(),provider_body_unchanged=True,objects=proof)
 (BASE/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
 print('proved',len(paths),'self-strict objects;',sum(len(p['native_edges']) for p in proof),'retail data references; provider unchanged')
