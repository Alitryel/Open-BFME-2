import sys,hashlib,json,shutil,struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3];sys.path.insert(0,str(ROOT/'tools'))
import build,link_census as lc,link_check as ck
OUT=ROOT/'build/stringrecord-destructor-link-20261014'
SOURCES=(OUT/'sources.txt').read_text().splitlines();OLD='??1BfmeStringRecord000B9534@@QAE@XZ'
def sha(b):return hashlib.sha256(b).hexdigest()
def comdats(obj):
 return {s['name']:(body,[(a,k,r['name'],r.get('content')) for a,k,r in rel],digest,size) for s,body,rel,digest,size in lc._comdat_sections(obj.read_bytes())}
def normalized(obj,remove):
 stat=obj.stat();data,sections,symbols=build._object_layout(str(obj),stat.st_mtime_ns,stat.st_size)
 dropped={s['section'] for s in symbols if remove and s['name']==OLD and s['section']>0}
 symoff=struct.unpack_from('<I',data,8)[0]
 parents={}
 for n,s in enumerate(symbols):
  if s.get('storage')==3 and s.get('aux') and s['section']>0:
   aux=data[symoff+(n+1)*18:symoff+(n+2)*18]
   if aux[14]==5:parents[s['section']]=struct.unpack_from('<h',aux,12)[0]
 while any(p in dropped and c not in dropped for c,p in parents.items()):
  dropped.update(c for c,p in parents.items() if p in dropped)
 sxdata={}
 for i,s in enumerate(sections,1):
  if s['name']=='.sxdata':
   entries=[struct.unpack_from('<I',data,s['raw_pointer']+j)[0] for j in range(0,s['raw_size'],4)]
   sxdata[i]=[n for n in entries if symbols[n]['section'] not in dropped]
   if not sxdata[i]:dropped.add(i)
 kept=[i for i,s in enumerate(sections,1) if i not in dropped and not s['name'].startswith('.debug')]
 kept.sort(key=lambda i: (sections[i-1]['name']=='.sxdata',sections[i-1]['name'],tuple(sorted(s['name'] for s in symbols if s.get('storage')==2 and s['section']==i))))
 mapped={i:j for j,i in enumerate(kept,1)}
 def ref(index):
  s=symbols[index]
  if s['storage'] in (2,105):return OLD if remove and s['name']=='??1AsciiString@@QAE@XZ' else s['name']
  return ('local',mapped.get(s['section'],s['section']),s['value'],s['storage'],s['type'])
 found=[]
 for i in kept:
  sec=sections[i-1];ptr,size=sec['raw_pointer'],sec['raw_size'];body=data[ptr:ptr+size] if ptr else None
  if sec['name']=='.sxdata' and body is not None:body=repr([ref(n) for n in sxdata[i]]).encode();size=4*len(sxdata[i])
  rel=[]
  for j in range(sec['reloc_count']):
   where,symbol,kind=struct.unpack_from('<IIH',data,sec['reloc_pointer']+10*j);rel.append((where,kind,ref(symbol)))
  found.append((sec['name'],sec['characteristics'],size,body,rel))
 defs=sorted((s['name'],mapped[s['section']],s['value'],s['type']) for s in symbols if s.get('storage')==2 and s['section'] in mapped)
 return found,defs
truth=lc.RetailTruth(lc.ledger());proof=[];before_objects=[];after_objects=[]
for i,s in enumerate(SOURCES):
 after=build.obj_path(ROOT/s);assert lc.object_current(ROOT/s,after,allow_fresh=False)
 before_dir=OUT/'before';before_dir.mkdir(exist_ok=True);before=before_dir/after.name;shutil.copyfile(OUT/f'before-{i}.obj',before)
 before_objects.append(before);after_objects.append(after)
 old,new=comdats(before),comdats(after)
 if i in (1,2):
  removed=old.pop(OLD);assert set(old)==set(new)
  retargeted=[]
  for name in old:
   a,b=old[name],new[name];assert a[0]==b[0] and a[3]==b[3]
   if a!=b:
    assert i==1 and len(a[1])==len(b[1])
    for x,y in zip(a[1],b[1]):
     if x!=y:
      assert x[:2]==y[:2] and x[2]=='??1AsciiString@@QAE@XZ' and y[2]==OLD and x[3]==y[3]
      retargeted.append({'comdat':name,'offset':x[0],'kind':x[1],'before':x[2],'after':y[2]})
  assert len(retargeted)==(6 if i==1 else 0)
  assert normalized(before,True)==normalized(after,False),'nondebug change'
 else:
  removed=None;retargeted=[];assert old==new;assert normalized(before,False)==normalized(after,False)
 bf,af=lc.object_facts(before,truth),lc.object_facts(after,truth)
 assert bf[1]==af[1] and bf[3]==af[3]
 added=set(af[2])-set(bf[2]);assert added<=({OLD} if i in (1,2) else set()),'unexpected new undefined reference'
 shutil.copyfile(after,OUT/f'after-{i}.obj');shutil.copyfile(after.with_suffix('.deps.json'),OUT/f'after-{i}.deps.json')
 proof.append({'source':s,'before_sha256':sha(before.read_bytes()),'after_sha256':sha(after.read_bytes()),'retained_comdat_count':len(new),'all_retained_comdat_bytes_and_extents_identical':True,'cleanup_call_retargets':retargeted,'all_other_comdat_relocations_and_referent_contents_identical':True,'retained_nondebug_sections_and_external_definitions_identical_after_section_reorder_and_cleanup_retarget_normalization':True,'strong_weak_bindings_identical':True,'undefined_removed':sorted(set(bf[2])-set(af[2])),'undefined_added':sorted(added),'removed_helper':None if removed is None else {'name':OLD,'size':removed[3],'digest':removed[2]}})
idx_bytes=ck.INDEX.read_bytes();assert sha(idx_bytes)==(OUT/'index-sha.txt').read_text()
previews={}
for phase,objects in [('before',before_objects),('after',after_objects)]:
 idx=ck.load_index();ck.refresh(idx,objects,truth);rows=[]
 for s,o in zip(SOURCES,objects):
  r=ck.check_object(o,idx,truth,s);clean=not any(r.values());rows.append({'source':s,'clean':clean,'findings':r,'linked_bytes':ck.source_bytes({s}).get(s,0) if clean else 0})
 previews[phase]={'clean':sum(r['clean'] for r in rows),'linked_bytes':sum(r['linked_bytes'] for r in rows),'rows':rows}
assert previews['after']['clean']==previews['before']['clean']+1
assert previews['after']['rows'][2]['clean'] and not previews['before']['rows'][2]['clean']
assert previews['after']['linked_bytes']==previews['before']['linked_bytes']+28
assert sha(ck.INDEX.read_bytes())==sha(idx_bytes)
report={'index_meta':ck.load_index()['meta'],'index_sha256':sha(idx_bytes),'objects':proof,'paired_same_index_legacy_preview':previews,'self_strict_current':True,'closed_strict_gain_claimed':False,'new_authored_bytes':0}
(OUT/'object-proof.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(previews,indent=2))
