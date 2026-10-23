import sys,json,hashlib,copy
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_census,link_check
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
root=Path('build/orientation-getter-link-20261015')
paths=(root/'sources.txt').read_text().splitlines()
getters=['?getOrientation@Object@@QBEMXZ']
index=link_check.load_index();rows=link_census.ledger();truth=link_census.RetailTruth(rows)
objects=[build.obj_path(build.ROOT/s) for s in paths];olds=[root/'before'/p.name for p in objects]
trials={}
for phase,ps in [('before',olds),('after',objects)]:
 trial=copy.deepcopy(index);link_check.refresh(trial,ps,truth);trials[phase]=trial
result={'measurement':json.loads((root/'measurement.json').read_text()),'consumers':[]}
def facts(p):
 return {sym['name']:{'body':body.hex() if body is not None else None,'digest':digest,'size':size} for sym,body,relocs,digest,size in link_census._comdat_sections(p.read_bytes())}
for source,obj,old in zip(paths,objects,olds):
 a,b=facts(old),facts(obj);expected=getters
 removed=sorted(set(a)-set(b));added=sorted(set(b)-set(a));changed=[n for n in a.keys()&b.keys() if a[n]!=b[n]]
 assert removed==sorted(expected),(source,removed)
 assert not added,(source,added)
 assert not changed,(source,changed)
 assert [sorted(v) for v in link_census.object_facts(old,truth)[1:]]==[sorted(v) for v in link_census.object_facts(obj,truth)[1:]],source
 assert build.compile_is_current(build.ROOT/source,obj,strict=True),source
 entry={'source':source,'source_sha256_before':hashlib.sha256((root/'before'/Path(source).name).read_bytes()).hexdigest(),'source_sha256_after':hashlib.sha256(Path(source).read_bytes()).hexdigest(),'object_sha256_before':hashlib.sha256(old.read_bytes()).hexdigest(),'object_sha256_after':hashlib.sha256(obj.read_bytes()).hexdigest(),'strict_current_after':True,'removed_comdats':{n:a[n] for n in expected},'retained_comdat_count':len(b),'retained_byte_and_relocation_digests':{n:v['digest'] for n,v in sorted(b.items())},'unchanged_strong_undefined_weak_symbols':True}
 for phase,p in [('before',old),('after',obj)]:entry[phase+'_findings']=link_check.check_object(p,trials[phase],truth,source)
 before,after=entry['before_findings'],entry['after_findings']
 assert all(any(v[0]==n for v in before['comdat']) for n in expected),before
 assert after['comdat']==[v for v in before['comdat'] if v[0] not in expected],after
 for k in before:
  if k!='comdat':assert before[k]==after[k],(source,k)
 print(source,sum(map(len,before.values())),'->',sum(map(len,after.values())),len(b),'retained COMDATs unchanged')
 result['consumers'].append(entry)
result['index_unchanged']=hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()==result['measurement']['index_sha256'];assert result['index_unchanged']
result['other_census_copies']={name:[{'object':index['objects'][i],'digest':d,'retail_verdict':v} for i,d,v in index['comdat'][name] if index['objects'][i] not in {p.name for p in objects}] for name in getters}
(root/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
# Retain complete owner rows plus direct target reads; names/layout origins remain donor/inferred as documented by each original row.
reads=[]
for row in rows:
 if row['source'] not in paths or row['name'].startswith(('$','__ehhandler')):continue
 rv=int(row['target_rva'],0);sz=int(row['target_size'],0);raw=build.read_target_bytes(rv,sz)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,rv));hits=[]
 for i,inst in enumerate(ins):
  if '0x1c0' in inst.op_str:
   hits.append([{'rva':hex(v.address),'bytes':v.bytes.hex(),'instruction':v.mnemonic+' '+v.op_str} for v in ins[max(0,i-3):i+4]])
 reads.append({'row':row,'retail_sha256':hashlib.sha256(raw).hexdigest(),'orientation_field_access_contexts':hits})
(root/'target-reads.json').write_text(json.dumps(reads,indent=2)+'\n')
