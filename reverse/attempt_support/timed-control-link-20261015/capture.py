import sys,json,hashlib,shutil,subprocess
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_check as ck,link_census as lc
out=Path('build/timed-control-link-20261015')
sources=['Code/GameEngine/Source/Common/GameEngineControl.cpp','Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineCallbacks.cpp']
index=ck.load_index(); truth=lc.RetailTruth(lc.ledger()); objects=[]
for source in sources:
    obj=build.obj_path(build.ROOT/source)
    assert build.compile_is_current(build.ROOT/source,obj,strict=True)
    objects.append(obj)
    for path in (obj,obj.with_suffix('.deps.json')): shutil.copy2(path,out/'before'/path.name)
    shutil.copy2(source,out/'before'/Path(source).name)
ck.refresh(index,objects,truth)
results={s:ck.check_object(o,index,truth,source=s) for s,o in zip(sources,objects)}
context={'base':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),'sources':sources,'index_sha256':hashlib.sha256(ck.INDEX.read_bytes()).hexdigest(),'index_meta':index['meta'],'before':results}
(out/'context.json').write_text(json.dumps(context,indent=2)+'\n')
for s,o in zip(sources,objects):
    ck.report(s,o,results[s],index,ck.source_bytes({s})[s])
