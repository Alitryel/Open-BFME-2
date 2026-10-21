from pathlib import Path
import subprocess,sys,json
out=Path('build/resume-eh-local/turn64-adaptive-state');out.mkdir(exist_ok=True)
base=Path('build/resume-eh-local/turn64-adaptive-context/G4_D1.cpp').read_text()
start=base.index('\tunsigned char *base = (unsigned char *) Data;');end=base.index('\tif (frame_idx >= NumFrames)',start)
old=base[start:end]
views={
'constructed':'''struct AdaptiveDecodeStart {
 float *values; uint32 frame;
 __forceinline AdaptiveDecodeStart(uint32 sourceFrame,float *source,uint32 *header) {
  if(source) {values=source;frame=sourceFrame;} else {values=(float *)header;frame=0;}
 }
};
''',
'copied':'''struct AdaptiveDecodeStart {
 float *values; uint32 frame;
 __forceinline AdaptiveDecodeStart(uint32 sourceFrame,float *source,uint32 *header) {
  if(source) {values=source;frame=sourceFrame;} else {values=(float *)header;frame=0;}
 }
 __forceinline AdaptiveDecodeStart(const AdaptiveDecodeStart &s) : values(s.values),frame(s.frame) {}
};
''',
'returned':'''struct AdaptiveDecodeStart { float *values; uint32 frame; };
static __forceinline AdaptiveDecodeStart adaptiveDecodeStart(uint32 sourceFrame,float *source,uint32 *header) {
 AdaptiveDecodeStart result;
 if(source) {result.values=source;result.frame=sourceFrame;} else {result.values=(float *)header;result.frame=0;}
 return result;
}
'''}
results=[];sym='??$decompress@$03@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z'
for key,view in views.items():
 state='AdaptiveDecodeStart state(src_idx,srcdata,Data);' if key!='returned' else 'AdaptiveDecodeStart state=adaptiveDecodeStart(src_idx,srcdata,Data);'
 new='\t'+state+'\n\tunsigned char *base=(unsigned char *)Data;\n\tfloat *src=state.values;\n\tuint32 start=state.frame;\n'
 s=base.replace(old,new)
 pos=s.index('template <int N>\nvoid AdaptiveDeltaMotionChannelClass::decompress')
 s=s[:pos]+view+s[pos:]
 p=out/(key+'.cpp');p.write_bytes(s.encode())
 r=subprocess.run([sys.executable,'tools/explain_mismatch.py',sym,'--rva','0x0018F9C0','--size','222','--source',p.as_posix()],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
 p.with_suffix('.txt').write_bytes(r.stdout.encode());d={'variant':key,'exit':r.returncode,'summary':[x for x in r.stdout.splitlines() if x.startswith(('compiled symbol size:','classification:','first diff:','unresolved:'))]}
 if r.returncode:d['tail']=r.stdout[-900:]
 results.append(d);print(d,flush=True)
 (out/'results.json').write_bytes((json.dumps(results,indent=2)+'\n').encode())
