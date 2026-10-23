import sys,json,hashlib,shutil,subprocess
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
out=Path('build/payload-ctor-home-link-20261015')
sources=['Code/GameEngine/Source/Common/Rva002C00E0ObjCtor.cpp','Code/GameEngine/Source/Common/Rva005CBB0AWrap.cpp']
name='??0Rva002C00E0Obj@@QAE@PBH@Z'
index=ck.load_index(); truth=lc.RetailTruth(lc.ledger()); objects=[]
for i,source in enumerate(sources):
 obj=build.obj_path(build.ROOT/source)
 assert build.compile_is_current(build.ROOT/source,obj,strict=True)
 objects.append(obj); snap=out/str(i);snap.mkdir(exist_ok=True)
 shutil.copy2(obj,snap/obj.name)
 shutil.copy2(obj.with_suffix('.deps.json'),snap/'before.deps.json')
 shutil.copy2(source,snap/'before.cpp')
row=next(r for r in lc.ledger() if r['name']==name)
ck.refresh(index,objects,truth)
results={s:ck.check_object(o,index,truth,None) for s,o in zip(sources,objects)}
ctx={'base':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),'sources':sources,'row':row,'index_sha256':hashlib.sha256(ck.INDEX.read_bytes()).hexdigest(),'index_meta':index['meta'],'before':results}
(out/'context.json').write_text(json.dumps(ctx,indent=2)+'\n')
for s,o in zip(sources,objects):ck.report(s,o,results[s],index,ck.source_bytes({s})[s])
