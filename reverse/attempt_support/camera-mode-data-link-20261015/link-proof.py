import sys, pathlib, json, hashlib
sys.path.insert(0,'tools')
import build, link_census, link_check
base=pathlib.Path('build/camera-mode-data-link-20261015')
paths=(base/'sources.txt').read_text().splitlines()
truth=link_census.RetailTruth(link_census.ledger())
results={}
for label in ['before','after']:
 index=link_check.load_index()
 objects=[(base/'objects'/build.obj_path(pathlib.Path.cwd()/s).name if label=='before' else build.obj_path(pathlib.Path.cwd()/s)) for s in paths]
 link_check.refresh(index,objects,truth)
 results[label]={s:link_check.check_object(o,index,truth,s) for s,o in zip(paths,objects)}
for s in paths:
 assert results['before'][s]==results['after'][s],s
assert json.loads((base/'index-meta.json').read_text())['sha256']==hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()
(base/'link-delta.json').write_text(json.dumps(results,indent=2)+'\n')
print('Same-index paired legacy preview: all findings unchanged. Camera remains locally link-clean; no closed-strict gain asserted.')
