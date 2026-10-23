import sys,subprocess,json,itertools,concurrent.futures
from pathlib import Path
sys.path.insert(0,str(Path('tools').resolve()));import build
from locate import object_functions
D=Path('build/selection43003c-vector-visibility').resolve();D.mkdir(parents=True,exist_ok=True)
s=Path('reverse/attempt_support/0043003c-20261020-codex7-prereqs/constructor-input.cpp.txt').read_text()
s=s.replace('template <> void **vector<void*>::end();','template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }')
s=s.replace('template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &);','template <> __declspec(dllimport) __forceinline void vector<void *, allocator<void *> >::insert(void **p, unsigned int n, void *const &x) { _M_fill_insert(p,n,x); }')
allocs=['','template <> allocator<void *>::~allocator();','template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {}','template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() _STLP_NOTHROW {}']
ctors=['template <> vector<void *>::vector(const allocator<void *> &);','template <> __declspec(nothrow) vector<void *>::vector(const allocator<void *> &);','template <> vector<void *>::vector(const allocator<void *> &) _STLP_NOTHROW;']
def one(bits):
 c,a,eh=bits;k='v%d_a%d_e%d'%bits
 src=s.replace('// bfme link decl-only begin','// bfme link decl-only begin\nnamespace _STL {\n'+ctors[c]+'\n'+allocs[a]+'\n}\n')
 if eh:src=src.replace('/EHsc','/GX')
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-500:])
 out=dict(name=k,functions=[],other=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59)
   t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
  else:out['other'].append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2))
 return dict(name=k,bodies=[(x['size'],len(x['diffs'])) for x in out['functions']],other=out['other'])
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
 results=list(ex.map(one,itertools.product(range(3),range(4),range(2))))
(D/'results.json').write_text(json.dumps(results,indent=2))
for x in results:print(json.dumps(x),flush=True)
