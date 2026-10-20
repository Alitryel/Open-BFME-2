import sys,subprocess,json,concurrent.futures,itertools
from pathlib import Path
sys.path.insert(0,str(Path('tools').resolve()));import build
from locate import object_functions
HERE=Path(__file__).resolve().parent
D=Path('build/selection43003c-prereqs-reproduce').resolve();D.mkdir(parents=True,exist_ok=True)
base=(HERE/'constructor-input.cpp.txt').read_text();a=base.index('// bfme link decl-only begin');b=base.index('typedef _STL::pair');s=base[:a]+base[b:]
# Keep only the reference algorithm and selectively suppress complete, already-provider-backed classes.
cs=['vector<void *>','_Vector_base<void *,allocator<void *> >','allocator<void *>','_STLP_alloc_proxy<void **,void *,allocator<void *> >']
def one(bits):
 k='ext_'+''.join(map(str,bits));decl='namespace _STL {\n'+''.join('extern template class '+c+';\n' for c,x in zip(cs,bits) if x)+'}\n';ss=s.replace('typedef _STL::pair',decl+'typedef _STL::pair',1)
 p=D/(k+'.cpp');p.write_text(ss);o=p.with_suffix('.obj');cmd,env=build.compiler_command(p,o);env['WINEDEBUG']='-all';r=subprocess.run(cmd,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);p.with_suffix('.compile.log').write_bytes(r.stdout)
 if r.returncode:return dict(name=k,error=r.stdout.decode(errors='replace')[-900:])
 out=dict(name=k,functions=[])
 for n,b,rel in object_functions(o):
  if n.startswith(('??0?$hashtable@','?_M_initialize_buckets')):
   rva,size=(0x42ffc0,64) if n.startswith('??0') else (0x148ddf,59);t=build.read_target_bytes(rva,size);holes={x for off,_,_ in rel for x in range(off,off+4)};diff=[hex(i) for i,(a,z) in enumerate(zip(b,t)) if a!=z and i not in holes];out['functions'].append(dict(name=n,size=len(b),diffs=diff,relocs=rel))
  elif n.startswith(('??1?$allocator@PAX','??0?$_Vector_base@PAX','??0?$vector@PAX','?end@?$vector@PAX','?insert@?$vector@PAX','??1?$_STLP_alloc_proxy@PAPAX')):out.setdefault('other',[]).append([n,len(b)])
 p.with_suffix('.proof.json').write_text(json.dumps(out,indent=2));return dict(name=k,bodies=[(x['size'],len(x['diffs'])) for x in out['functions']],other=out.get('other',[]))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
 for r in ex.map(one,itertools.product(range(2),repeat=4)):print(json.dumps(r),flush=True)
