import copy,json,sys,shutil,hashlib
from pathlib import Path
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/special-power-iterator-link-20261015'
ctx=json.loads((OUT/'context.json').read_text());index=ck.load_index();truth=lc.RetailTruth(lc.ledger());results={}
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
for phase in ['before','after']:
 local=copy.deepcopy(index);objects=[]
 for i,s in enumerate(ctx['paths']):
  current=build.obj_path(ROOT/s)
  if phase=='before':
   folder=OUT/'saved-before';folder.mkdir(exist_ok=True);obj=folder/current.name;shutil.copy2(OUT/'before.obj',obj)
  else:obj=current
  objects.append(obj)
 ck.refresh(local,objects,truth)
 results[phase]={s:ck.check_object(obj,local,truth,s) for s,obj in zip(ctx['paths'],objects)}
for s in ctx['paths']:
 before=results['before'][s];after=results['after'][s]
 old=[row for row in before['comdat'] if row[0] in {'??9_List_iterator_base@_STL@@QBE_NABU01@@Z'}];assert len(old)==1
 expected=copy.deepcopy(before);[expected['comdat'].remove(row) for row in old];assert expected==after,(s,before,after)
 print(s, 'findings',sum(map(len,before.values())),'->',sum(map(len,after.values())),'legacy local LINKED remains 0')
(OUT/'final-link-proof.json').write_text(json.dumps({'measurement':ctx,'results':results},indent=2)+'\n')
