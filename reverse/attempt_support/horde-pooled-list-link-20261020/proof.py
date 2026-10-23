import hashlib,json,sys,shutil
from pathlib import Path
sys.path.insert(0,"tools")
import build, link_check as ck, link_census as lc
paths=["Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva00473212.cpp"]
base=Path("build/seat-horde"); olddir=base/"before";olddir.mkdir(exist_ok=True)
objects=[build.obj_path(build.ROOT/p)for p in paths]
old=[]
for i,obj in enumerate(objects):
 p=olddir/obj.name;shutil.copy2(base/("before.obj"if i==0 else f"before{i}.obj"),p);old.append(p)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
index_sha=sha(ck.INDEX);truth=lc.RetailTruth(lc.ledger());core=("unresolved","duplicates","comdat","addresses","selected")
paired={};changes={};sizes=ck.source_bytes(set(paths))
for phase,objs in [("before",old),("after",objects)]:
 x=ck.load_index();assert all(ck.in_census(x,o.name)for o in objs);ck.refresh(x,objs,truth)
 paired[phase]={p:{k:r[k]for k in core}for p,o in zip(paths,objs)for r in [ck.check_object(o,x,truth,source=p)]}
for p,a,b in zip(paths,old,objects):
 assert lc.object_current(build.ROOT/p,b,allow_fresh=False)
 aa={n:(h,z)for n,h,z in lc.comdat_bodies(a)};bb={n:(h,z)for n,h,z in lc.comdat_bodies(b)}
 changed=[n for n in aa.keys()&bb.keys()if aa[n]!=bb[n]]
 assert len(changed)==1 and changed[0].startswith("?_M_create_node@?$list@PAVObject") and bb.keys()<=aa.keys(),(p,changed,bb.keys()-aa.keys())
 changes[p]={"before_sha256":sha(a),"after_sha256":sha(b),"changed_factory":{n:{"before":aa[n],"after":bb[n]}for n in changed},"removed_comdats":sorted(aa.keys()-bb.keys()),"other_retained_comdat_bytes_and_relocations_identical":len(bb)-len(changed)}
gains={phase:sum(sizes[p]for p,r in results.items()if not any(r[k]for k in core))for phase,results in paired.items()}
assert gains=={"before":0,"after":1412},gains
assert sha(ck.INDEX)==index_sha
report={"index_sha256":index_sha,"measurement":ck.load_index()["meta"],"paired_legacy_link_bytes":gains,"paired_link":paired,"changes":changes,"self_strict_rows":1,"closed_strict_gain_unmeasured":True}
out=Path("reverse/attempt_support/horde-pooled-list-link-20261020");out.mkdir(exist_ok=True)
(out/"proof.json").write_text(json.dumps(report,indent=2)+"\n")
print("PASS paired legacy +1412 B, identical retained COMDAT bodies except pooled node factory and relocations, 1 self-strict rows")
