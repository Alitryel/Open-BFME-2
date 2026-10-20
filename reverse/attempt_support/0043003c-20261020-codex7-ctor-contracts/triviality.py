from pathlib import Path
exec(Path(__file__).with_name('common.py').read_text())
D=Path('build/selection43003c-allocator-triviality').resolve();D.mkdir(exist_ok=True)
h=Path('vendor/stlport/stl/_alloc.h').read_text()
for mask in range(1,8):
 d=D/('headers%d'%mask)/'stl';d.mkdir(parents=True,exist_ok=True)
 x=h
 if mask&1:x=x.replace('  ~allocator() _STLP_NOTHROW {}','')
 if mask&2:x=x.replace('  allocator(const allocator<_Tp>&) _STLP_NOTHROW {}','')
 if mask&4:x=x.replace('  allocator() _STLP_NOTHROW {}','')
 (d/'_alloc.h').write_text(x)
def one(args):
 mask,hidden,eh=args;k='m%d_h%d_e%d'%args
 decl='namespace _STL { template <> '+('_Vector_base<void *,allocator<void *> >::_Vector_base' if hidden==0 else 'vector<void *>::vector')+'(const allocator<void *> &); }\n'
 src=s.replace('// bfme link decl-only begin',decl+'// bfme link decl-only begin').replace('/Ireference/shims/bfmealloc','/I'+str((D/('headers%d'%mask)).relative_to(Path.cwd()))+' /Ireference/shims/bfmealloc')
 if eh:src=src.replace('/EHsc','/GX')
 p=D/(k+'.cpp');p.write_text(src);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';cmd.insert(2,'-showIncludes');r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-1000:])
 out=dict(name=k,functions=[],other=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)}
   out['functions'].append(dict(name=n,size=len(b),diffs=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes],relocs=rel))
  elif n.startswith(('??0?$_Vector_base','??0?$vector','??1?$allocator@PAX')):out['other'].append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return out
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:results=list(ex.map(one,itertools.product(range(1,8),range(2),range(2))))
(D/'results.json').write_text(json.dumps(results,indent=2))
for r in results:print(r['name'],r.get('error') or [(x['size'],len(x['diffs'])) for x in r['functions']])
