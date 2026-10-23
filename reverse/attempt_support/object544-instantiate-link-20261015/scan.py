import sys,json,hashlib,time
from pathlib import Path
sys.path.insert(0,'tools');import build,link_check as ck
base=Path('build/object544-instantiate-link-20261015');sole=set(json.loads((base/'sole-symbols.json').read_text()));assert all('BfmeObject544' in s for s in sole)
index=ck.load_index();measured=set(index['digests'].values());seen=set();covered=set();hits={};relevant={};count=0;started=time.time()
paths=list(Path('.git/bfme-objstore').rglob('*.obj'))+list(Path('build/match').glob('*.obj'))
for p in paths:
 d=p.read_bytes();h=hashlib.sha256(d).hexdigest()
 if h in measured:covered.add(h)
 if h in seen:continue
 seen.add(h);count+=1
 if b'BfmeObject544' not in d:continue
 sy=build.read_object_symbols(d)
 missing=sorted({s['name'] for s in sy if s.get('storage')==2 and s['section']==0 and s['value']==0}&sole)
 relevant[str(p)]={'sha256':h,'measured':h in measured}
 if missing:hits[str(p)]=missing
report={'removed_sole_provider_names':len(sole),'unique_objects_examined':count,'snapshot_object_hashes_covered':len(covered),'snapshot_object_hashes_unavailable':len(measured-covered),'relevant_objects':relevant,'external_consumers':hits,'seconds':round(time.time()-started,2)}
(base/'consumer-scan.json').write_text(json.dumps(report,indent=2)+'\n');print({k:v for k,v in report.items() if k!='relevant_objects'});assert not hits
