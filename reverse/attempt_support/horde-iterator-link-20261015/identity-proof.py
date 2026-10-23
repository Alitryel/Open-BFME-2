import json, sys
from pathlib import Path
ROOT=Path.cwd()
sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed
import code_identity_gate as gate
OUT=ROOT/'build/horde-iterator-link-20261015'
s=json.loads((OUT/'context.json').read_text())['paths'][0]
original=allowed.row_object
before=OUT/'saved-before'/original({'source':s}).name
assert before.exists()
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: before if phase=='before' and row['source']==s else original(row)
    findings,mode,seconds,rows,refs=gate.check([s],[])
    results[phase]={'findings':findings,'mode':mode,'rows':rows}
assert results['before']==results['after'], results
assert len(results['after']['findings'])==4, results
print(json.dumps(results,indent=2))
(OUT/'identity-proof.json').write_text(json.dumps(results,indent=2)+'\n')
