"""Recover the retail FieldParse tables (name, parse function, user data, offset rows in .rdata/.data)
from game.dat and attribute each to the functions.csv rows that reference it.

Usage: python3 tools/fieldparse_tables.py [out.tsv]   (default reverse/fieldparse_tables.tsv)
Not gate code; a naming aid. Offsets are relative to the object the table parses into.
"""
import struct,sys,json,bisect
d=open(str(__import__('pathlib').Path(__file__).resolve().parents[1]/'baselines/bfme2/workshop-vanilla-1.06/files/game.dat'),'rb').read()
pe=struct.unpack_from('<I',d,0x3c)[0]; ns=struct.unpack_from('<H',d,pe+6)[0]; osz=struct.unpack_from('<H',d,pe+20)[0]
base=struct.unpack_from('<I',d,pe+24+28)[0]
secs=[]
for i in range(ns):
    o=pe+24+osz+40*i; n=d[o:o+8].rstrip(b'\0').decode(); vs,va,rs,ro=struct.unpack_from('<IIII',d,o+8); secs.append((n,va,max(vs,rs),ro,rs))
def v2o(v):
    r=v-base
    for n,va,vs,ro,rs in secs:
        if va<=r<va+rs: return ro+r-va,n
    return None,None
text=[s for s in secs if s[0]=='.text'][0]
def istext(v): r=v-base; return text[1]<=r<text[1]+text[2]
def cstr(v):
    o,n=v2o(v)
    if o is None: return None
    e=d.find(b'\0',o,o+80)
    if e<=o: return None
    s=d[o:e]
    if not all(32<c<127 for c in s): return None
    return s.decode()
tables=[]
for n,va,vs,ro,rs in secs:
    if n not in('.rdata','.data'): continue
    o=ro
    while o<ro+rs-16:
        run=[]; p=o
        while p<ro+rs-16:
            a,f,u,off=struct.unpack_from('<IIII',d,p)
            s=cstr(a) if a else None
            if s and istext(f) and off<0x4000 and s[:1].isalpha():
                run.append((s,f-base,u,off)); p+=16
            else: break
        if len(run)>=3:
            tva=base+va+(o-ro)
            tables.append({'va':tva-base,'rows':run}); o=p
        else: o+=4


import csv,bisect,collections
osz=struct.unpack_from('<H',d,pe+20)[0]; o=pe+24+osz
va,ro,rs=struct.unpack_from('<I',d,o+12)[0],struct.unpack_from('<I',d,o+20)[0],struct.unpack_from('<I',d,o+16)[0]
assert d[o:o+5]==b'.text'
T=tables
want={base+t['va']:t for t in T}
refs=collections.defaultdict(list)
tx=d[ro:ro+rs]
for tv in want:
    b=struct.pack('<I',tv); i=tx.find(b)
    while i>=0: refs[tv].append(va+i); i=tx.find(b,i+1)
rows=[]
for r in csv.reader(open('reverse/functions.csv',encoding='utf-8',errors='replace')):
    try: rows.append((int(r[2],16),int(r[3]),r[0],r[4],r[5]))
    except: pass
rows.sort(); starts=[r[0] for r in rows]
out=[]
for tv,t in want.items():
    owners=[]
    for x in refs[tv]:
        k=bisect.bisect_right(starts,x)-1
        if k>=0 and rows[k][0]<=x<rows[k][0]+rows[k][1]: owners.append(rows[k][2])
    t['owners']=owners; t['refs']=[hex(x) for x in refs[tv]]

out=sys.argv[1] if len(sys.argv)>1 else 'reverse/fieldparse_tables.tsv'
with open(out,'w',encoding='utf-8',newline='\n') as w:
    w.write('table_rva\towners\tfield\tparse_rva\tuser_data\toffset\n')
    for t in tables:
        for name,f,u,off in t['rows']:
            w.write('0x%08X\t%s\t%s\t0x%08X\t0x%X\t0x%X\n'%(t['va'],' '.join(sorted(set(t['owners']))),name,f,u,off))
print(len(tables),'tables',sum(len(t['rows']) for t in tables),'rows')
