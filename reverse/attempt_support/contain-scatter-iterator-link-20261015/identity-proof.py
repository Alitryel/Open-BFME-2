import json,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed,code_identity_gate as gate
OUT=ROOT/'build/contain-scatter-iterator-link-20261015'
paths=json.loads((OUT/'context.json').read_text())['paths'];original=allowed.row_object
saved={s:OUT/str(i)/'saved-before'/original({'source':s}).name for i,s in enumerate(paths)}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    findings,mode,seconds,rows,refs=gate.check(paths,[])
    results[phase]={'findings':findings,'mode':mode,'rows':rows}
assert results['before']==results['after'],results
print('identical identity-shadow findings',len(results['after']['findings']))
(OUT/'identity-proof.json').write_text(json.dumps(results,indent=2)+'\n')
