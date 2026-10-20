import sys,json,subprocess,concurrent.futures
from pathlib import Path
sys.path.insert(0,str(Path('tools').resolve()));import build
from locate import object_functions
HERE=Path(__file__).resolve().parent
D=Path('build/selection43003c-prereqs-reproduce').resolve();D.mkdir(parents=True,exist_ok=True)
vs={}
for vec in (0,1):
 s=(D/('fac_1%d3.cpp'%vec)).read_text()
 for nt in ('_STLP_NOTHROW','__declspec(nothrow)'):
  a=s.replace('template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &);', 'template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &) _STLP_NOTHROW;' if nt=='_STLP_NOTHROW' else 'template <> __declspec(nothrow) _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &);')
  vs['nt_%d_%d'%(vec,nt=='_STLP_NOTHROW')]=a
def one(k):
 p=D/(k+'.cpp');p.write_text(vs[k]);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-1000:])
 out=dict(name=k,functions=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)};diff=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes];out['functions'].append(dict(name=n,size=len(b),diffs=diff,relocs=rel))
  elif n.startswith(('??1?$allocator@PAX','??0?$_Vector_base@PAX','??0?$vector@PAX','?end@?$vector@PAX','?insert@?$vector@PAX','??1?$_STLP_alloc_proxy@PAPAX')):out.setdefault('other',[]).append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return dict(name=k,bodies=[(x['size'],len(x['diffs'])) for x in out['functions']],other=out.get('other',[]))
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as ex:
 for r in ex.map(one,vs):print(json.dumps(r))
