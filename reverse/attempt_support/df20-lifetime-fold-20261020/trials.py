from pathlib import Path
import os,sys,re,subprocess,json,concurrent.futures,itertools
sys.path.insert(0,'tools')
import build
root=Path.cwd(); scratch=root/'build/df20-seat-20261020'
# Recreate baseline.cpp from this commit's parent bank before rerunning.
bank=(scratch/'baseline.cpp').read_text(); symbol=bank.splitlines()[0][3:]
alloc=(root/'vendor/stlport/stl/_alloc.h').read_text()
proxy='''
#define _STLP_alloc_proxy _DiagVendorProxy
#include <stl/_alloc.h>
#undef _STLP_alloc_proxy
namespace _STL {
template<class Value,class T,class Alloc>
class _STLP_alloc_proxy:public Alloc {
public:
 Value _M_data;
 _STLP_alloc_proxy(const Alloc&a,Value p):Alloc(a),_M_data(p) {}
 ~_STLP_alloc_proxy() EXCEPTION { if (sizeof(T)==0) free(_M_data); }
};
}
'''
def run(spec):
 label,src=spec
 p=scratch/(label+'.cpp');p.write_text(src)
 env={**os.environ,'BFME_OBJSTORE':'off'}
 proc=subprocess.run([sys.executable,'tools/align_diff.py',str(p.relative_to(root)),symbol,'0xdf20','2610'],capture_output=True,text=True,env=env)
 p.with_suffix('.align.txt').write_text(proc.stdout+proc.stderr)
 r={'label':label,'exit':proc.returncode}
 for key,pat in [('size',r'ours (\d+) B'),('memory',r'^\s+(\d+)\s+memory\s'),('register',r'^\s+(\d+)\s+register\s'),('structural',r'== structural regions: (\d+)')]:
  m=re.search(pat,proc.stdout,re.M);r[key]=int(m[1]) if m else None
 if r['size']:
  raw,rels=build.read_object_symbol_bytes(build.obj_path(p),symbol,code_only=True)
  names=[n for o,t,n in rels if t==build.REL32]
  r['whole']=sum(n.startswith('??1?$basic_string@G') for n in names)
  r['base']=sum(n.startswith('??1?$_String_base@G') for n in names)
  r['free']=sum('free@' in n or n=='_free' for n in names)
  r['locale']=sum(n.startswith('??1locale@') for n in names)
 print(json.dumps(r),flush=True)
 return r
if __name__=='__main__':
 specs=[]
 for location,nothrow,opaque,locinline in itertools.product(['allocator','proxy'],[False,True],[False,True],[False,True]):
  # This is a new nested-lifetime hypothesis. Earlier work added only a proxy
  # destructor and had no inline/nonthrowing cross-factor matrix.
  label=f'nest-{location}-nt{int(nothrow)}-op{int(opaque)}-li{int(locinline)}'
  src=bank
  if location=='allocator':
   d=scratch/label/'stl';d.mkdir(parents=True,exist_ok=True)
   replacement='~allocator() '+('_STLP_NOTHROW ' if nothrow else '')+'{ if (sizeof(_Tp)==0) free(this); }'
   assert alloc.count('~allocator() _STLP_NOTHROW {}')==1
   (d/'_alloc.h').write_text(alloc.replace('~allocator() _STLP_NOTHROW {}',replacement))
   src=src.replace('// cl:','// cl: /I'+str(d.parent.relative_to(root)),1)
  else:
   src=src.replace('#define private public',proxy.replace('EXCEPTION','throw()' if nothrow else '')+'\n#define private public',1)
  if not opaque:src=src.replace('template <> _String_base<wchar_t, allocator<wchar_t> >::~_String_base();','')
  if locinline:src=src.replace('locale::~locale()','inline locale::~locale()')
  specs.append((label,src))
 # Different compiler builds have never been tried on this bank.
 for profile,opaque,locinline in itertools.product(['vc71-sp1','vc71-ddk-4035'],[False,True],[False,True]):
  src=bank.replace('// stlport','// compiler: '+profile+'\n// stlport',1)
  if not opaque:src=src.replace('template <> _String_base<wchar_t, allocator<wchar_t> >::~_String_base();','')
  if locinline:src=src.replace('locale::~locale()','inline locale::~locale()')
  specs.append((f'compiler-{profile}-op{int(opaque)}-li{int(locinline)}',src))
 with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:results=list(pool.map(run,specs))
 (scratch/'results.json').write_text(json.dumps(results,indent=2)+'\n')
