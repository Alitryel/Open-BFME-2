import sys,subprocess,json,concurrent.futures,itertools
from pathlib import Path
sys.path.insert(0,str(Path('tools').resolve()));import build
from locate import object_functions
HERE=Path(__file__).resolve().parent
D=Path('build/selection43003c-prereqs-reproduce').resolve();D.mkdir(parents=True,exist_ok=True)
s=(HERE/'constructor-input.cpp.txt').read_text()
s=s.replace('template <> void **vector<void*>::end();','template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }')
s=s.replace('template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &);','template <> __declspec(dllimport) __forceinline void vector<void *, allocator<void *> >::insert(void **p, unsigned int n, void *const &x) { _M_fill_insert(p,n,x); }')
allocs=['','template <> allocator<void *>::~allocator();','template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {}','template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() _STLP_NOTHROW {}']
def one(v):
 base,vec,alloc=v;k='fac_%d%d%d'%v;pre='namespace _STL {\n'
 if base:pre+='template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &);\n'
 pre+=allocs[alloc]+'\n}\n';ss=s.replace('// bfme link decl-only begin','// bfme link decl-only begin\n'+pre)
 if vec:ss=ss.replace('typedef _STL::pair','namespace _STL { template <> __declspec(dllimport) __forceinline vector<void *>::vector(const allocator<void *> &a) : _Vector_base<void *,allocator<void *> >(a) {} }\ntypedef _STL::pair',1)
 p=D/(k+'.cpp');p.write_text(ss);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-1000:])
 out=dict(name=k,functions=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59)
   t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)};diff=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes]
   out['functions'].append(dict(name=n,size=len(b),diffs=diff,relocs=rel))
  elif n.startswith(('??1?$allocator@PAX','??0?$_Vector_base@PAX','??0?$vector@PAX','?end@?$vector@PAX','?insert@?$vector@PAX','??1?$_STLP_alloc_proxy@PAPAX')):out.setdefault('other',[]).append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return dict(name=k,bodies=[(x['size'],len(x['diffs'])) for x in out['functions']],other=out.get('other',[]))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
 for r in ex.map(one,itertools.product(range(2),range(2),range(4))):print(json.dumps(r),flush=True)
