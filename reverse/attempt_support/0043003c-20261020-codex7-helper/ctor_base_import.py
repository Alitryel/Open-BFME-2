from pathlib import Path
exec(Path(__file__).with_name('ctor_visibility.py').read_text().split('with concurrent.futures.ThreadPoolExecutor')[0])
attrs=['inline','__forceinline','inline __declspec(noinline)']
def probe(bits):
 a,v=bits;k='baseimport_%d%d'%bits
 pre='namespace _STL { template <> __declspec(dllimport) '+attrs[a]+' _Vector_base<void *,allocator<void *> >::_Vector_base(const allocator<void *> &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a,0) {} }\n'
 if v:pre+='namespace _STL { template <> __declspec(dllimport) __forceinline vector<void *>::vector(const allocator<void *> &a) : _Vector_base<void *,allocator<void *> >(a) {} }\n'
 src=s.replace('// bfme link decl-only begin','// bfme link decl-only begin\n'+pre)
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-500:])
 out=dict(name=k,functions=[],other=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
  elif n.startswith(('??0?$_Vector_base','??0?$vector','??1?$allocator@PAX')):out['other'].append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return out
with concurrent.futures.ThreadPoolExecutor(max_workers=6) as ex:results=list(ex.map(probe,itertools.product(range(3),range(2))))
(D/'base-import-results.json').write_text(json.dumps(results,indent=2))
for r in results:print(json.dumps(r))
