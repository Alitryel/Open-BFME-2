#!/usr/bin/env python3
"""Diagnostic only; run from the BFME2 root with SOURCE.cpp [--resolve]."""
import sys,subprocess,re,json,difflib
from pathlib import Path
sys.path.insert(0,str(Path.cwd()/'tools'))
import build,capstone
ROOT=Path.cwd(); DIR=ROOT/'build/render2d-second-opinion'; DIR.mkdir(parents=True,exist_ok=True); NAME='?Render@Render2DClass@@QAEXXZ'
def instructions(blob,relocs=()):
 blob=bytearray(blob)
 for off,typ,name in relocs:
  if typ==6 and name!='__except_list' and off+4<=len(blob):blob[off:off+4]=(0x400000).to_bytes(4,'little')
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 rs={x[0] for x in relocs}; out=[]
 for i in md.disasm(blob,0):
  op=i.op_str
  if i.mnemonic.startswith('j') or i.mnemonic=='call' and not '[' in op:op='TARGET'
  else:
   op=re.sub(r'0x[0-9a-f]+',lambda m:'ABS' if int(m[0],16)>=0x400000 else m[0],op)
   if any(i.address<=r<i.address+i.size for r in rs):
    op=re.sub(r'\[0\]', '[ABS]',op)
    if op=='0':op='ABS'
  op=op.replace('fs:[ABS]','fs:[0]')
  out.append((i.address,i.mnemonic,op,i.size))
 return out
T=build.read_target_bytes(0x11a040,7476); TI=instructions(T)
def measure(src):
 dest=DIR/src.stem; obj=dest.with_suffix('.obj'); cmd,env=build.compiler_command(src,obj)
 p=subprocess.run(cmd,cwd=ROOT,env=env,capture_output=True,text=True) if not ('--rescore' in sys.argv and obj.exists()) else None
 if p is not None and p.returncode:
  dest.with_suffix('.log').write_text(p.stdout+p.stderr);return {'name':src.stem,'error':(p.stdout+p.stderr)[-450:]}
 data,rels=build.read_object_symbol_bytes(obj,NAME,code_only=True)
 data=data.rstrip(b'\xcc'); A=instructions(data,rels)
 # Normalize reloc immediate push/call for both sides.
 sm=difflib.SequenceMatcher(None,[(x[1],x[2]) for x in TI],[(x[1],x[2]) for x in A],autojunk=False)
 counts=[0,0,0,0]; diffs=[]
 for tag,i,j,k,l in sm.get_opcodes():
  if tag=='equal':continue
  loc=TI[min(i,len(TI)-1)][0]; reg=0 if loc<0x5d0 else 1 if loc<0x7e0 else 2 if loc<0x16d1 else 3
  counts[reg]+=max(j-i,l-k)
  diffs.append({'retail':TI[i:j],'ours':A[k:l]})
 # Terminator B sites recognizable from following store after absolute load.
 sites=[]
 for off,ty,n in sorted(rels):
  if 'm_NullChar@StringClass' not in n:continue
  i=next(i for i,x in enumerate(A) if x[0]<=off<x[0]+x[3])
  sites.append((hex(A[i][0]),'N' if A[i-1][1]=='call' else 'B'))

 result={'name':src.stem,'size':len(data),'counts':counts,'nd':sum(counts),'sites':sites}
 dest.with_suffix('.json').write_text(json.dumps({'result':result,'diffs':diffs},indent=1));dest.with_suffix('.bin').write_bytes(data)
 return result
if __name__=='__main__':
 src=Path(sys.argv[1]).resolve()
 result=measure(src)
 if '--resolve' in sys.argv and 'error' not in result:
  from variant_search import fitness
  row={'name':NAME,'target_rva':'0x0011A040','target_size':'7476',
       'source':str(src.relative_to(ROOT)), 'notes':''}
  r=build.compile_function(row,build.load_symbol_map(),(DIR/src.stem).with_suffix('.obj'))
  result.update(fitness=fitness(r['bytes'],r['target']),
                unresolved=r['unresolved'],masked=r['masked'],
                dir32_note='compile_function copies retail DIR32 values at compiled offsets; fitness is position-sensitive, not aligned data-identity proof')
 print(json.dumps(result))
