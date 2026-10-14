import re,csv,json,subprocess,collections,datetime
from pathlib import Path
root=Path.cwd(); out=root/'build/crack-g'; latest={}
for n,line in enumerate(Path('reverse/re_attempts.log').open(),1):
 p=line.rstrip('\n').split('\t')
 if len(p)<5: continue
 try: r=int(p[1],16); size=int(p[2])
 except ValueError: continue
 latest[r]=dict(rva=f'0x{r:08X}',symbol=p[0],size=size,status=p[3],evidence=p[4],line=n)
candidates=set()
for r,d in latest.items():
 scores=re.findall(r'score=([\d.]+)',d['evidence'])
 bank=Path(f'reverse/attempts/0x{r:08x}.cpp')
 if not scores and bank.exists(): scores=re.findall(r'score=([\d.]+)',bank.read_text(errors='replace')[:1000])[:1]
 d['score']=float(scores[-1]) if scores else 0
 d['bank']=str(bank) if bank.exists() else ''
 d['deps']=[int(x,16) for group in re.findall(r'blocked-on=((?:0x[\da-fA-F]+[, ]?)+)',d['evidence']) for x in re.findall(r'0x[\da-fA-F]+',group)]
 if d['score']>=.95 or d['deps']: candidates.add(r); candidates.update(d['deps'])
# Explicit raw-bank call references are additional leads, separate from log fan-in.
# Only address-named callees avoid ambiguous common method names.
for caller,d in latest.items():
 if not d['bank']: continue
 body=Path(d['bank']).read_text(errors='replace')
 found=set(int(x,16) for x in re.findall(r'(?:->|\.)\s*(?:rva|Rva)([0-9A-Fa-f]{8})\s*\(',body))
 d['bank_deps']=sorted(x for x in found if x!=caller and x in latest)
 if d['bank_deps']: candidates.add(caller); candidates.update(d['bank_deps'])
# Narrow ledger lookup for relevant graph nodes and bank names, no full ledger load.
patterns=out/'rvas.patterns'; patterns.write_text('\n'.join(f',0x{r:08X},' for r in candidates)+'\n')
rows=subprocess.run(['rg','-i','-F','-f',str(patterns),'reverse/functions.csv'],capture_output=True,text=True).stdout
matched={}
for row in csv.reader(rows.splitlines()):
 if len(row)<7: continue
 r=int(row[2],16)
 if row[5]=='matched' and not row[4].startswith(('Code/gen_','Code/masm_dumps/')) and not re.search(r'(^|[; ])gen-',row[6]): matched[r]=row
claims={}
for l in (out/'claims.txt').read_text().splitlines():
 p=l.split()
 if p and p[0].startswith('0x') and p[1]!='crack-g-20261014': claims[int(p[0],16)]=p[1]
graph=collections.defaultdict(set)
for r,d in latest.items():
 if r in matched: continue
 for dep in set(d['deps']+d.get('bank_deps',[])): graph[dep].add(r)
def descendants(r):
 seen=set(); pending=list(graph[r])
 while pending:
  x=pending.pop()
  if x==r or x in seen or x in matched: continue
  seen.add(x); pending.extend(graph[x])
 return seen
rank=[]
for r in candidates:
 if r in matched or r in claims: continue
 d=latest.get(r,dict(rva=f'0x{r:08X}',symbol='unlogged provider',size=0,status='',evidence='',line=0,score=0,bank='',deps=[])).copy()
 ds=descendants(r); d['dependents']=[f'0x{x:08X}' for x in sorted(ds)]; d['dependent_bytes']=sum(latest[x]['size'] for x in ds)
 d['priority']=d['dependent_bytes']+(d['size']*d['score'] if d['score']>=.95 else 0)
 if d['priority']>0: rank.append(d)
rank.sort(key=lambda d:(-d['priority'],d['rva']))
(out/'ranking.json').write_text(json.dumps(rank,indent=2))
lines=['# Crack-g wave 5 ranking','',f"UTC {datetime.datetime.now(datetime.timezone.utc).isoformat()}; current master base `{subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip()}`.",'','Priority = unique transitive latest-per-RVA blocked-on consumer bytes + size × score for banks >= .95 (latest log score, bank header fallback). Real matched providers and live foreign claims excluded. Generated placeholders are unmatched. Explicit blocked-on edges are the reproducible fan-in; address-named callee invocations in current banks add provisional consumer edges, audited during cracking. Potential bytes are not verified gain. No census or verification runner.','', '| Rank | RVA / symbol | Own B | Potential dependent B | Score | Priority | Evidence |','|---|---|---:|---:|---:|---:|---|']
for i,d in enumerate(rank[:60],1):
 if i==26: lines+=['','## Continuation leads 26–60','','| Rank | RVA / symbol | Own B | Potential dependent B | Score | Priority | Evidence |','|---|---|---:|---:|---:|---:|---|']
 ev=d['evidence'].replace('|','/')
 lines.append(f"| {i} | `{d['rva']}` `{d['symbol']}` | {d['size']} | {d['dependent_bytes']} ({', '.join(d['dependents'])}) | {d['score']:.6f} | {d['priority']:.1f} | log:{d['line']} {ev} |")
Path.home().joinpath('crack-seats/g.rank.md').open('a').write('\n\n## Bank-callee audit refresh\n\n'+'\n'.join(lines)+'\n')
for i,d in enumerate(rank[:70],1):print(i,d['rva'],d['size'],d['dependent_bytes'],round(d['score'],6),d['symbol'][:90])
print('EXCLUDED FOREIGN',len(claims),'MATCHED',len(matched),'CANDIDATES',len(rank))
