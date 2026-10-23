import copy, json, sys, shutil, hashlib
from pathlib import Path
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/horde-iterator-link-20261015'
ctx=json.loads((OUT/'context.json').read_text());index=ck.load_index();truth=lc.RetailTruth(lc.ledger());results={}
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
s=ctx['paths'][0]; current=build.obj_path(ROOT/s)
for phase in ['before','after']:
 local=copy.deepcopy(index)
 if phase=='before':
  folder=OUT/'saved-before';folder.mkdir(exist_ok=True);obj=folder/current.name;shutil.copy2(OUT/'before.obj',obj)
 else:obj=current
 ck.refresh(local,[obj],truth)
 results[phase]=ck.check_object(obj,local,truth,s)
before=results['before'];after=results['after']
old=[row for row in before['comdat'] if row[0] in set(ctx['removed_names'])];assert len(old)==2, before
expected=copy.deepcopy(before)
for row in old:expected['comdat'].remove(row)
assert expected==after,(before,after)
print('findings',sum(map(len,before.values())),'->',sum(map(len,after.values())),'legacy local LINKED 0 ->',index['bytes'][s])
(OUT/'link-proof.json').write_text(json.dumps({'measurement':ctx,'results':results,'legacy_preview_bytes':index['bytes'][s]},indent=2)+'\n')
