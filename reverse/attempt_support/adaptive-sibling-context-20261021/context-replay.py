from pathlib import Path
import subprocess,sys,re,json
out=Path('build/resume-eh-local/turn64-adaptive-context');out.mkdir(exist_ok=True)
base=Path('reverse/attempt_support/adaptive-sibling-context-20261021/prior-bank.cpp.txt').read_text()
base=re.sub(r'template void AdaptiveDeltaMotionChannelClass::(?:getframe|decompress)<[14]>\([^;]+;','',base)
decl={
 'D1':'template void AdaptiveDeltaMotionChannelClass::decompress<1>(uint32,float *,uint32,float *);',
 'D4':'template void AdaptiveDeltaMotionChannelClass::decompress<4>(uint32,float *,uint32,float *);',
 'G1':'template void AdaptiveDeltaMotionChannelClass::getframe<1>(uint32,AdaptiveDeltaCacheStruct<1> &);',
 'G4':'template void AdaptiveDeltaMotionChannelClass::getframe<4>(uint32,AdaptiveDeltaCacheStruct<4> &);'}
orders=[['G4','D1'],['D4'],['D1','D4'],['G1','D4'],['D1','G4'],['G4','D1'],['G1','D1','D4','G4'],['G4','D4','D1','G1']]
orders=list(dict.fromkeys(tuple(o) for o in orders))
sym='??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z';results=[]
for order in orders:
 key='_'.join(order);p=out/(key+'.cpp');p.write_bytes((base+'\n'+'\n'.join(decl[x] for x in order)+'\n').encode())
 r=subprocess.run([sys.executable,'tools/explain_mismatch.py',sym,'--rva','0x0018F9C0','--size','222','--source',p.as_posix()],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 p.with_suffix('.txt').write_bytes(r.stdout.encode());d={'variant':key,'exit':r.returncode,'summary':[x for x in r.stdout.splitlines() if x.startswith(('compiled symbol size:','classification:','first diff:','unresolved:'))]}
 if r.returncode:d['tail']=r.stdout[-900:]
 results.append(d);print(d,flush=True)
 (out/'results.json').write_bytes((json.dumps(results,indent=2)+'\n').encode())
