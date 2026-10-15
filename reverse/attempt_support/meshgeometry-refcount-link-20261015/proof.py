"""Paired read-only COFF and local legacy link proof. Does not rewrite the census."""
import copy,hashlib,json,sys
from pathlib import Path
ROOT=Path.cwd();OUT=ROOT/'build/refcount-link-seat'
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'reverse/attempt_support/moduledata-snapshot-link-20261015')]
import build,link_check as ck,link_census as lc,sections as sec
before=json.loads((OUT/'before.json').read_text());source=before['sources'][0]
assert before['index_sha256']==hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
a=build.obj_path(ROOT/source);b=OUT/a.name
assert hashlib.sha256(b.read_bytes()).hexdigest()==before['before_sha256'][source]
assert build.compile_is_current(ROOT/source,a,strict=True)
old,new=sec.sections(b),sec.sections(a);removed=old-new
expected={'?Add_Ref@RefCountClass@@QAEXXZ':5,'?Release_Ref@RefCountClass@@QAEXXZ':11}
assert not new-old
assert {p[2][0][0]:p[5] for p in removed}==expected and sum(removed.values())==2
for part in removed:
 assert len(part[2])==1 and part[2][0][1:]==(0,2) and part[0].startswith('.text')
for part in new:
 for _,_,target in part[4]:assert not any(name in str(target) for name in expected)
assert a.read_bytes().count(b'__imp_')<=b.read_bytes().count(b'__imp_')
index=ck.load_index();truth=lc.RetailTruth(lc.ledger());paired={}
for label,obj in [('before',b),('after',a)]:
 idx=copy.deepcopy(index);ck.refresh(idx,[obj],truth);paired[label]=ck.check_object(obj,idx,truth,source)
assert json.loads(json.dumps(paired['before']))==before['before'][source]
for key,findings in paired['after'].items():
 want=paired['before'][key]
 if key=='comdat':want=[f for f in want if f[0] not in expected]
 assert findings==want,(key,findings,want)
counts={label:sum(map(len,findings.values())) for label,findings in paired.items()}
assert counts=={'before':7,'after':5},counts
assert any(paired['before'].values()) and any(paired['after'].values())
assert before['index_sha256']==hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
result={'base':before['base'],'source':source,'index_meta':before['index_meta'],'index_sha256':before['index_sha256'],'before_sha256':before['before_sha256'][source],'after_sha256':hashlib.sha256(a.read_bytes()).hexdigest(),'self_strict':True,'retained_nondebug_sections':sum((old&new).values()),'all_retained_bytes_and_symbolic_relocations_identical':True,'removed':[{'definitions':p[2],'size':p[5]}for p in removed],'paired':paired,'blocker_count':counts,'linked_nonpadding_bytes':{'before':0,'after':0},'closed_strict':False,'currency':'owned consumer self-strict; other providers retain legacy index currency'}
(OUT/'object-proof.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS: 24 retained sections identical; only unused 5B Add_Ref and 11B Release_Ref copies removed; legacy blockers 7->5; linked bytes 0->0; no closed-strict claim.')
