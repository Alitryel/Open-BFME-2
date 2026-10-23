from pathlib import Path
import subprocess,re
s=Path('reverse/attempts/0x0024877a.cpp').read_text();base=subprocess.check_output(['git','show','eb8b155e6d'],text=True)
patch=s[s.index('diff --git'):s.rindex('#endif')].splitlines(True)
chunks=[];cur=None
for line in patch:
 if line.startswith('@@'):
  if cur:chunks.append(cur)
  cur=[]
 elif cur is not None and line[:1] in [' ','+','-']:cur.append(line)
if cur:chunks.append(cur)
for chunk in chunks:
 before=''.join(x[1:] for x in chunk if x[0] in ' -');after=''.join(x[1:] for x in chunk if x[0] in ' +')
 assert base.count(before)==1,(base.count(before),before[:80]);base=base.replace(before,after,1)
base='// ?rva0024877A@GameLogic@@QAE_NXZ\n'+base
Path('build/crack-g/game_refresh.cpp').write_text(base)
print('reconstructed',len(base))
