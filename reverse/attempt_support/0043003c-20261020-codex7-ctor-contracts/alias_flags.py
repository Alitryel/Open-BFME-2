from pathlib import Path
exec(Path(__file__).with_name('common.py').read_text())
D=Path('build/selection43003c-ctor-alias-flags').resolve();D.mkdir(exist_ok=True)
def one(args):
 hidden,mask,ob,eh=args;k='h%d_m%d_ob%d_e%d'%args
 decl='namespace _STL { template <> '+('_Vector_base<void *,allocator<void *> >::_Vector_base' if hidden==0 else 'vector<void *>::vector')+'(const allocator<void *> &); }\n'
 flags=' /Ob%d'%ob+(' /Oa' if mask&1 else '')+(' /Ow' if mask&2 else '')+(' /Og-' if mask&4 else '')
 src=s.replace('// bfme link decl-only begin',decl+'// bfme link decl-only begin').replace('/Ireference/shims/bfmealloc','/Ireference/shims/bfmealloc'+flags)
 if eh:src=src.replace('/EHsc','/GX')
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-1000:])
 out=dict(name=k,functions=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return out
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
 results=[]
 for r in ex.map(one,itertools.product(range(2),range(8),range(3),range(2))):
  results.append(r)
  if len(results)%24==0:print('finished',len(results),flush=True)
(D/'results.json').write_text(json.dumps(results,indent=2))
from collections import Counter
print(Counter(str([(x['size'],len(x['diffs'])) for x in r.get('functions',[])]) if 'error' not in r else r['error'][-100:] for r in results))
for r in results:
 if any(x['size']==64 for x in r.get('functions',[])):print(r['name'],[(x['size'],len(x['diffs'])) for x in r['functions']])
