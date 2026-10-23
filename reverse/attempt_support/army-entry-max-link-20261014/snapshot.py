import hashlib,json,pickle,shutil,subprocess,sys
from pathlib import Path
sys.path.insert(0,'tools')
import build,link_census as lc,link_check as ck
root=Path('build/army-entry-max-link-20261014'); sources=(root/'sources.txt').read_text().splitlines(); stage=sys.argv[1]
truth=lc.RetailTruth(lc.ledger()); index=ck.load_index(); saved={}; objs=[]
for name in sources:
 source=(build.ROOT/name).resolve(); obj=build.obj_path(source); data=obj.read_bytes(); key=source.stem
 assert lc.object_current(source,obj,allow_fresh=False),name
 copies=[dict(name=s['name'],body=b.hex(),relocations=r,digest=d,size=n,verdict=truth.verdict(s,b,r,d,n)) for s,b,r,d,n in lc._comdat_sections(data)]
 saved[name]=dict(source_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),object_sha256=hashlib.sha256(data).hexdigest(),copies=copies,facts_tail=lc.object_facts(obj,truth)[1:],strict_current=True)
 shutil.copy2(source,root/(stage+'-'+key+'.cpp')); shutil.copy2(obj,root/(stage+'-'+key+'.obj'));shutil.copy2(obj.with_suffix('.deps.json'),root/(stage+'-'+key+'.deps.json'));objs.append(obj)
ck.refresh(index,objs,truth)
preview={s:ck.check_object(o,index,truth,s) for s,o in zip(sources,objs)}
result=dict(base=subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),index_meta=index['meta'],index_sha256=hashlib.sha256(ck.INDEX.read_bytes()).hexdigest(),sources=saved,preview=preview)
(root/(stage+'.json')).write_text(json.dumps(result,indent=2,default=lambda x:x.hex() if isinstance(x,bytes) else str(x))+'\n');print(json.dumps(preview,indent=2))
