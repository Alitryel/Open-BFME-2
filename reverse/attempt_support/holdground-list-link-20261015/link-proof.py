import copy, json, sys, shutil, hashlib
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import build,link_check as ck,link_census as lc
OUT=ROOT/'build/holdground-list-link-20261015'
ctx=json.loads((OUT/'context.json').read_text());index=ck.load_index();truth=lc.RetailTruth(lc.ledger());results={}
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()==ctx['index_sha256']
for phase in ['before','after']:
    local=copy.deepcopy(index);objects=[]
    for i,s in enumerate(ctx['paths']):
        current=build.obj_path(ROOT/s)
        if phase=='before':
            folder=OUT/str(i)/'saved-before';folder.mkdir(exist_ok=True);obj=folder/current.name;shutil.copy2(OUT/str(i)/'before.obj',obj)
        else:obj=current
        objects.append(obj)
    ck.refresh(local,objects,truth)
    results[phase]={s:ck.check_object(obj,local,truth,s) for s,obj in zip(ctx['paths'],objects)}
for s,size in zip(ctx['paths'],ctx['row_bytes']):
    before=results['before'][s];after=results['after'][s]
    old=[row for row in before['comdat'] if row[0] in set(ctx['removed_names'])];assert len(old)==len(ctx['removed_names']),before
    expected=copy.deepcopy(before)
    for row in old:expected['comdat'].remove(row)
    assert expected==after,(before,after)
    print(s,'findings',sum(map(len,before.values())),'->',sum(map(len,after.values())),'legacy LINKED 0 ->',size)
(OUT/'link-proof.json').write_text(json.dumps({'context':ctx,'index_meta':index['meta'],'results':results,'legacy_linked_before':0,'legacy_linked_after':sum(ctx['row_bytes'])},indent=2)+'\n')
