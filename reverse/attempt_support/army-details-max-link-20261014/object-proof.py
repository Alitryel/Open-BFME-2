import hashlib,json,pickle,shutil,struct,sys
from collections import Counter
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_census as lc
OUT=Path('build/link-seat-20261014b')
OLD='??$max@I@_STL@@YAABIABI0@Z';NEW='?max@_STL@@YAABIABI0@Z'
def sha(b):return hashlib.sha256(b).hexdigest()
def normalized(obj,excluded):
 stat=obj.stat();data,sections,symbols=build._object_layout(str(obj),stat.st_mtime_ns,stat.st_size)
 removed=[s for s in symbols if s['name']==excluded and s['section']>0]
 assert len(removed)==1
 omitted=removed[0]['section'];leaders={}
 for s in symbols:
  if s.get('storage')==2 and s['section']>0:leaders.setdefault(s['section'],[]).append(s['name'])
 def body(n):
  s=sections[n-1];p=s['raw_pointer'];return data[p:p+s['raw_size']] if p else b''
 def referent(i):
  s=symbols[i];n=s['section']
  assert n!=omitted,'helper has an incoming non-debug relocation'
  if s['storage'] in (2,105):return (s['name'],s['storage'],s['value'])
  return ('local',s['value'],s['storage'],s['type'],tuple(sorted(leaders.get(n,()))) if n>0 else (),sha(body(n)) if n>0 else None)
 found=[]
 for n,s in enumerate(sections,1):
  if s['name'].startswith('.debug') or n==omitted:continue
  raw=body(n)
  if s['name']=='.sxdata':raw=repr([referent(struct.unpack_from('<I',raw,j)[0]) for j in range(0,len(raw),4)]).encode()
  rel=[]
  for j in range(s['reloc_count']):
   at,sym,kind=struct.unpack_from('<IIH',data,s['reloc_pointer']+10*j);rel.append((at,kind,referent(sym)))
  found.append(repr((s['name'],s['characteristics'],s['raw_size'],sha(raw),rel,sorted(leaders.get(n,())))))
 helper=sections[omitted-1];assert helper['reloc_count']==0
 return Counter(found),{'storage':removed[0]['storage'],'size':helper['raw_size'],'bytes':body(omitted).hex()}
def main(source,prefix):
 before=OUT/(prefix+'object-before.obj');after=build.obj_path(build.ROOT/source)
 assert lc.object_current(build.ROOT/source,after,allow_fresh=False)
 index=Path('build/link_census/link_index.pkl').read_bytes();assert sha(index)==(OUT/'index-sha.txt').read_text()
 old={n:(d,s) for n,d,s in lc.comdat_bodies(before)};new={n:(d,s) for n,d,s in lc.comdat_bodies(after)}
 assert set(old)-set(new)=={OLD} and not(set(new)-set(old))
 assert all(old[n]==new[n] for n in new)
 b,hb=normalized(before,OLD);a,ha=normalized(after,NEW)
 assert b==a,('changed section records',list((b-a).items())[:3],list((a-b).items())[:3])
 assert hb=={'storage':2,'size':16,'bytes':'8b4424048b108b4c24083b110f42c1c3'}
 assert ha=={'storage':3,'size':8,'bytes':'8b113b100f43c1c3'}
 truth=lc.RetailTruth(lc.ledger());bf=lc.object_facts(before,truth);af=lc.object_facts(after,truth)
 assert bf[1:]==af[1:],'strong/undefined/weak bindings changed'
 shutil.copy2(after,OUT/(prefix+'object-after.obj'));shutil.copy2(after.with_suffix('.deps.json'),OUT/(prefix+'receipt-after.json'))
 report={'source':source,'base':(OUT/'base.txt').read_text().strip(),'index_meta':pickle.loads(index)['meta'],'index_sha256':sha(index),'object_before_sha256':sha(before.read_bytes()),'object_after_sha256':sha(after.read_bytes()),'strict_current_receipt':True,'retained_external_comdats':len(new),'all_retained_external_comdat_bytes_extents_relocations_equal':True,'all_other_nondebug_sections_and_relocations_equal':True,'strong_undefined_weak_bindings_equal':True,'old_helper':hb,'new_helper':ha,'helper_nondebug_incoming_relocations':0,'new_authored_cpp_bytes':0,'closed_strict_gain_claimed':False}
 (OUT/(prefix+'object-proof.json')).write_text(json.dumps(report,indent=2)+'\n')
 print('PASS',source,len(new),'retained COMDATs unchanged; only unreferenced unsigned max emitter replaced')
if __name__=='__main__': main(sys.argv[1],sys.argv[2] if len(sys.argv)>2 else '')
