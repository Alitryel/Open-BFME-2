from pathlib import Path
import sys,re,json,difflib,time
ROOT=Path.cwd(); sys.path.insert(0,str(ROOT/'tools'))
import permute,build
class Lab:
 def __init__(self,rva,size,symbol=None,source=None,label='main'):
  self.rva=f'0x{int(rva,16):08x}'; self.path=Path(source or f'reverse/attempts/{self.rva}.cpp'); self.base=self.path.read_text(encoding='latin1'); self.symbol=symbol or re.match(r'//\s*(\S+)',self.base).group(1); self.size=size
  self.dir=ROOT/'build/crack-g'/self.rva/label; self.dir.mkdir(parents=True,exist_ok=True)
  self.scorer=permute.Scorer(self.rva,self.symbol,size,self.dir);self.best=-1.; self.records=[];self.start=time.monotonic()
  self.test('baseline',self.base)
 def test(self,name,text):
  score,exact=self.scorer.score(text); rawlen=None
  if score>=0:
   obj=self.dir/f't{self.scorer.trials%4}.obj'
   try: raw,rels=build.read_object_symbol_bytes(obj,self.symbol,self.size);rawlen=len(raw)
   except Exception:pass
  rec=dict(name=name,score=score,exact=exact,size=rawlen,unresolved=self.scorer.unresolved)
  self.records.append(rec)
  if score>self.best:
   self.best=score; self.besttext=text; self.bestrec=rec
   (self.dir/'best.cpp').write_text(text,encoding='latin1')
   if self.scorer.last:
    compiled,target=self.scorer.last
    a=permute._instructions(target);b=permute._instructions(compiled)
    diff='\n'.join(difflib.unified_diff([str(x) for x in a],[str(x) for x in b],fromfile='retail',tofile='compiled',n=4))
    (self.dir/'best.diff').write_text(diff)
   print(self.rva,rec,flush=True)
  (self.dir/'results.json').write_text(json.dumps(self.records,indent=2))
  return rec
 def done(self):
  print('DONE',self.rva,'trials',len(self.records),'best',self.bestrec,'seconds',round(time.monotonic()-self.start),flush=True)
