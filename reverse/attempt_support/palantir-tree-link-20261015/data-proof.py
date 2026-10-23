import json,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import data_check as gate
OUT=ROOT/'build/palantir-tree-link-20261015'
paths=json.loads((OUT/'context.json').read_text())['paths'];original=gate.build.row_object
saved={s:OUT/'saved-before'/original({'source':s}).name for i,s in enumerate(paths)}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    gate.build.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    unread=[];facts=gate.object_facts(gate.source_rows(paths),unread)
    assert not unread,unread
    results[phase]={'facts':{s:[sorted(b),sorted(d)] for s,(b,d) in facts.items()},'findings':gate.findings(facts,gate.dl.load())}
assert results['before']==results['after'],results
print('data facts and findings identical; findings',len(results['after']['findings']))
(OUT/'data-proof.json').write_text(json.dumps(results,indent=2)+'\n')
