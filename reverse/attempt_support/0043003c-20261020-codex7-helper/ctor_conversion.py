from pathlib import Path
exec(Path(__file__).with_name('ctor_visibility.py').read_text().split('with concurrent.futures.ThreadPoolExecutor')[0])
def converted(bits):
 c,a,kind=bits;k='conversion_v%d_a%d_k%d'%bits
 extra='#define _STLP_NO_TEMPLATE_CONVERSIONS\n' if kind==0 else '#define _STLP_NO_MEMBER_TEMPLATE_CLASSES\n'
 src=s.replace('#include <hash_map>',extra+'#include <hash_map>')
 src=src.replace('// bfme link decl-only begin','// bfme link decl-only begin\nnamespace _STL {\n'+ctors[c]+'\n'+allocs[a]+'\n}\n')
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-500:])
 out=dict(name=k,functions=[],other=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
  else:out['other'].append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return dict(name=k,bodies=[(x['size'],len(x['diffs'])) for x in out['functions']],other=out['other'])
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:results=list(ex.map(converted,itertools.product(range(3),range(4),range(2))))
(D/'conversion-results.json').write_text(json.dumps(results,indent=2))
from collections import defaultdict
g=defaultdict(list)
for r in results:g[str(r.get('bodies',r.get('error'))) ].append(r['name'])
for k,v in g.items():print(k,','.join(v))
