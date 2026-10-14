from pathlib import Path
import subprocess,sys,json,re
# CLI: RVA lab-directory minutes note. The selected diagnostic source is banked
# only as partial; no match row or coverage assertion is made.
rva,folder,minutes,note=sys.argv[1:5];rva=f'0x{int(rva,16):08x}';p=Path(folder);s=(p/'best.cpp').read_text(encoding='latin1');sym=re.match(r'//\s*(\S+)',s).group(1)
results=json.loads((p/'results.json').read_text());best=max(results,key=lambda x:x['score']);size=None
for line in Path('reverse/re_attempts.log').open():
 f=line.rstrip('\n').split('\t')
 if len(f)>4:
  try:
   if int(f[1],16)==int(rva,16):size=int(f[2])
  except:pass
if size is None:raise RuntimeError('size missing')
msg=f'Crack-g wave5: {note} Measured full compiled extent {best["size"]}/{size} B; fitness {best["score"]:.9f}, unresolved={best["unresolved"]}. No Code/pin/ledger claim. t={minutes} model=GPT-6'
subprocess.run([sys.executable,'tools/re_log.py','record',sym,rva,str(size),'partial',msg,'--stash',str(p/'best.cpp'),'--score',str(best['score'])],check=True)
f=Path('build/crack-g/attempted.json');data=json.loads(f.read_text()) if f.exists() else {};data[rva]=dict(symbol=sym,size=size,score=best['score'],compiled_size=best['size'],note=note,lab=str(p),trials=len(results));f.write_text(json.dumps(data,indent=2))
