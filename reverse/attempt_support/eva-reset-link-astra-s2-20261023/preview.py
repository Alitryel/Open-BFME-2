import sys,json
from pathlib import Path
sys.path.insert(0,str(Path("tools").resolve()))
import build,link_check,link_census
source="Code/GameEngine/Source/GameClient/Eva.cpp"
retired="Code/GameEngine/Source/GameClient/EvaRva001DF42D.cpp"
rows=link_census.ledger()
assert not Path(retired).exists()
assert not any(r["source"]==retired for r in rows)
index=link_check.load_index()
before={s:index["blockers"].get(s,{}) for s in (source,retired)}
obj=build.obj_path(Path(source).resolve())
gone=build.obj_path(Path(retired).resolve())
truth=link_census.RetailTruth(rows)
# Standard updater operation, restricted to the one actually deleted unit.
# This is an in-memory preview; no published index/census/status is written.
link_check.forget(index,[gone.name])
link_check.refresh(index,[obj],truth)
result=link_check.check_object(obj,index,truth,source)
count=link_check.source_bytes({source})[source]
linked=link_check.report(source,obj,result,index,count)
Path("build/s2-eva/preview.json").write_text(json.dumps({"index":index["meta"],"retired_source":retired,"retired_object":gone.name,"before":before,"result":result,"linked":linked,"owned_bytes":count},default=str,indent=2)+"\n")
print("Scoped preview; retired source absent from disk and current ledger; linked bytes:",count if linked else 0)
raise SystemExit(0 if linked else 1)
