import sys,pathlib,json,hashlib
sys.path.insert(0,'tools');import build,link_census,link_check
B=pathlib.Path('build/apt-registry-link-20261014');paths=(B/'sources.txt').read_text().splitlines();truth=link_census.RetailTruth(link_census.ledger());result={}
for phase in ('before','after'):
 idx=link_check.load_index();objects=[(B/'objects'/build.obj_path(pathlib.Path.cwd()/s).name if phase=='before' else build.obj_path(pathlib.Path.cwd()/s)) for s in paths[:-1]]
 assert all(o.name in idx['objects'] for o in objects)
 assert build.obj_path(pathlib.Path.cwd()/paths[-1]).name not in idx['objects']
 link_check.refresh(idx,objects,truth)
 result[phase]={s:link_check.check_object(o,idx,truth,s) for s,o in zip(paths[:-1],objects)}
for s in paths[:-1]:
 b,a=result['before'][s],result['after'][s]
 assert '?rva002D2C34@Rva002D2C34@@QAEXXZ' not in a['unresolved'],s
print(json.dumps(result,indent=2))
sizes=link_check.source_bytes(set(paths[:-1]));summary={p:dict(clean=sum(not any(v.values()) for v in rs.values()),linked_bytes=sum(sizes[s] for s,v in rs.items() if not any(v.values()))) for p,rs in result.items()}
assert json.loads((B/'index-meta.json').read_text())['sha256']==hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest()
(B/'link-proof.json').write_text(json.dumps(dict(index=idx['meta'],index_sha256=hashlib.sha256(link_check.INDEX.read_bytes()).hexdigest(),results=result,paired_legacy=summary,unpreviewable_provider=paths[-1],closed_strict_gain_claimed=False,new_authored_bytes=0),indent=2)+'\n')
print('SUMMARY',json.dumps(summary))
