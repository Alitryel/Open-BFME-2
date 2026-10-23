from pathlib import Path
exec(Path(__file__).with_name('common.py').read_text())
cs=['_Vector_base<void *,allocator<void *> >','vector<void *>','_STLP_alloc_proxy<void **,void *,allocator<void *> >']
styles=['extern template class __declspec(dllimport) ','template class __declspec(dllimport) ']
def one(args):
 style,mask=args;k='s%d_m%d'%args
 decl='namespace _STL {\n'+''.join(styles[style]+c+';\n' for i,c in enumerate(cs) if mask&(1<<i))+'}\n'
 src=s.replace('// bfme link decl-only begin',decl+'// bfme link decl-only begin')
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-1500:])
 out=dict(name=k,functions=[],other=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
  elif n.startswith(('??0?$_Vector_base','??0?$vector','??1?$allocator@PAX','??0?$_STLP_alloc_proxy')):out['other'].append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return out
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:results=list(ex.map(one,itertools.product(range(2),range(1,8))))
(D/'results.json').write_text(json.dumps(results,indent=2))
for r in results:
 print(r['name'],r.get('error') or {'functions':[(x['size'],x['diffs'],x['relocs']) for x in r['functions']],'other':r['other']})
