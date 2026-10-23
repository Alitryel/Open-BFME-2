"""Paired link evidence; requires this session's ignored before snapshots."""
import copy,csv,hashlib,json,struct,sys
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
OUT=Path('build/online-rank-link-20261015')
ctx=json.loads((OUT/'context.json').read_text())
rename={'?g_Va00E02548@@3HA':'?BfmeOnlineLadderRank1v1@@3HA','?g_Va00E0254C@@3HA':'?BfmeOnlineLadderRank2v2@@3HA'}
addresses=dict(zip(rename.values(),[0xA02548,0xA0254C]))
def norm(n):return rename.get(n,n)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def externals(data):
 return {(norm(s['name']),s['section']>0,s['storage']) for s in lc._coff_symbols(data) if s['storage'] in (2,105)}
def sections(data):
 symbols=lc._coff_symbols(data);by_index={s['index']:s for s in symbols}
 table=20+struct.unpack_from('<H',data,16)[0];identities={};ordinals={};result={}
 for i in range(struct.unpack_from('<H',data,2)[0]):
  h=table+40*i;label=data[h:h+8].rstrip(b'\0').decode()
  owners=tuple(sorted(norm(s['name']) for s in symbols if s['section']==i+1 and s['storage']==2 and norm(s['name']) not in addresses))
  base=(label,owners);ordinal=ordinals.get(base,0);ordinals[base]=ordinal+1;identities[i+1]=base+(ordinal,)
 def target(s):return norm(s['name']) if s['storage'] in (2,105) else (identities.get(s['section']),s['value'])
 for i,key in identities.items():
  if key[0].startswith('.debug'):continue
  h=table+40*(i-1);size,at,reloc=struct.unpack_from('<III',data,h+16)
  nr=struct.unpack_from('<H',data,h+32)[0];flags=struct.unpack_from('<I',data,h+36)[0]
  body=data[at:at+size].hex() if at else None
  if key[0]=='.sxdata':body=[target(by_index[x[0]]) for x in struct.iter_unpack('<I',data[at:at+size])]
  refs=[(where,kind,target(by_index[t])) for where,t,kind in struct.iter_unpack('<IIH',data[reloc:reloc+10*nr])]
  result[key]=(flags,size,body,refs)
 return result
assert sha(ck.INDEX)==ctx['index_sha256']
objects=[build.obj_path(Path(s).resolve()) for s in ctx['sources']]
comparison={}
for i,(source,obj) in enumerate(zip(ctx['sources'],objects)):
 assert build.compile_is_current(Path(source).resolve(),obj,strict=True)
 old=OUT/'before'/obj.name
 assert sha(old)==ctx['hashes'][source]['object']
 a,b=old.read_bytes(),obj.read_bytes();x,y=sections(a),sections(b)
 assert not x.keys()-y.keys()
 changed=[k for k in x if x[k]!=y[k]]
 if i==0:
  assert len(changed)==1 and changed[0][0]=='.bss'
  k=changed[0];assert x[k][1]==4 and y[k][1]==12
  assert x[k][0]==y[k][0] and x[k][2:]==y[k][2:]==(None,[])
  olddefs={s['name']:s['value'] for s in lc._coff_symbols(a) if s['section']>0 and s['storage']==2}
  newdefs={s['name']:s['value'] for s in lc._coff_symbols(b) if s['section']>0 and s['storage']==2}
  assert all(newdefs[n]==v for n,v in olddefs.items())
  assert {n:newdefs[n] for n in addresses}==dict(zip(addresses,[4,8]))
 else:assert not changed
 added=sorted(y.keys()-x.keys())
 ea,eb=externals(a),externals(b)
 if i==0:
  assert ea-eb=={(n,False,2) for n in rename.values()}
  assert eb-ea=={(n,True,2) for n in rename.values()}
  assert not added
  for k in added:
   flags,size,body,refs=y[k]
   assert k[0]=='.bss' and size==4 and body is None and refs==[],(k,y[k])
 else:assert ea==eb and not added
 comparison[source]={'unchanged_nondebug_sections':len(x)-len(changed),'bss_extension_bytes':8 if i==0 else 0,'added_zero_data_sections':[[k,y[k]] for k in added], 'after_source_sha256':sha(Path(source)),'after_object_sha256':sha(obj),'after_receipt_sha256':sha(obj.with_suffix('.deps.json'))}
index=ck.load_index();truth=lc.RetailTruth(lc.ledger());results={}
for phase in ('before','after'):
 local=copy.deepcopy(index)
 objs=[OUT/'before'/o.name for o in objects] if phase=='before' else objects
 ck.refresh(local,objs,truth)
 results[phase]={s:ck.check_object(o,local,truth,s) for s,o in zip(ctx['sources'],objs)}
assert json.loads(json.dumps(results['before']))==ctx['before']
for s in ctx['sources']:
 before,after=results['before'][s],results['after'][s]
 assert set(after['unresolved'])==set(before['unresolved'])-set(rename)
 assert all(before[k]==after[k] for k in before if k!='unresolved')
# Verify each matched retail instruction referring to these cells, not just source names.
consumers=[]
for row in csv.DictReader(open('reverse/functions.csv')):
 if row['source'] not in ctx['sources'] or row['status']!='matched':continue
 obj=objects[ctx['sources'].index(row['source'])]
 try:body,refs=build.read_object_symbol_bytes(obj,build.ledger_object_symbol(row),int(row['target_size']),code_only=True)
 except ValueError:continue # EH label rows are separately verified by the byte/EH gates.
 size=int(row['target_size']);refs=[r for r in refs if r[2] in addresses and r[0]<size]
 if not refs:continue
 native=build.read_target_bytes(int(row['target_rva'],16),size);sites=[]
 for offset,kind,name in refs:
  assert kind==6
  value=struct.unpack_from('<I',native,offset)[0]
  assert value==0x400000+addresses[name]
  sites.append({'offset':offset,'name':name,'target_va':hex(value),'window':native[max(0,offset-3):offset+7].hex()})
 consumers.append({'name':row['name'],'rva':row['target_rva'],'size':size,'source':row['source'],'native_sha256':hashlib.sha256(native).hexdigest(),'sites':sites})
assert {c['source'] for c in consumers}==set(ctx['sources'])
assert all(build.read_target_bytes(r,4)==bytes(4) for r in addresses.values())
report={'context':ctx,'normalized_names':rename,'comparison':comparison,'results':results,'native_consumers':consumers,'new_owned_data_bytes':8,'new_authored_code_bytes':0,'legacy_linked_delta':0,'self_strict_link_gain':'not measured','closed_strict_link_gain':'not measured'}
(OUT/'proof.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'findings':{phase:{s:{k:len(v) for k,v in findings.items()} for s,findings in items.items()} for phase,items in results.items()},'consumers':len(consumers),'sites':sum(len(c['sites']) for c in consumers),'sections':comparison},indent=2))
