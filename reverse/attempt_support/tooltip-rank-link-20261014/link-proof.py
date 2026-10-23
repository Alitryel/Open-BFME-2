import sys, pathlib, json, hashlib
sys.path.insert(0,'tools')
import build, link_census, link_check
base=pathlib.Path('build/tooltip-rank-link-20261014')
paths=(base/'sources.txt').read_text().splitlines()
truth=link_census.RetailTruth(link_census.ledger())
results={}
for label in ['before','after']:
 index=link_check.load_index()
 objects=[(base/'objects'/build.obj_path(pathlib.Path.cwd()/s).name if label=='before' else build.obj_path(pathlib.Path.cwd()/s)) for s in paths]
 link_check.refresh(index,objects,truth)
 results[label]={s:link_check.check_object(o,index,truth,s) for s,o in zip(paths,objects)}
for s in paths:
 b,a=results['before'][s],results['after'][s]
 for k in b:
  if s!=paths[-1] and k=='unresolved':
   assert set(b[k])-set(a[k])=={'?g_Va00E05FCC@@3IA','?g_Va00E06000@@3IA'}
   assert not set(a[k])-set(b[k])
  else: assert b[k]==a[k],(s,k)
assert json.loads((base/'index-meta.json').read_text())['sha256']==hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()
sizes=link_check.source_bytes(set(paths))
summary={phase:{'clean':sum(not any(v.values()) for v in findings.values()),'linked_bytes':sum(sizes.get(s,0) for s,v in findings.items() if not any(v.values()))} for phase,findings in results.items()}
assert summary['after']['clean']==summary['before']['clean']+1
assert summary['after']['linked_bytes']==summary['before']['linked_bytes']+sizes[paths[0]]
(base/'link-delta.json').write_text(json.dumps({'findings':results,'paired_same_index_legacy':summary,'self_strict_objects':True,'closed_strict_gain_claimed':False,'new_authored_bytes':0},indent=2)+'\n')
print(json.dumps(summary,indent=2))
print('Same-index paired preview: exactly two unresolved rank-table data bindings removed from the tooltip; every other finding unchanged.')
