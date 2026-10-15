import json, sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed, code_identity_gate as gate, data_check as dc
OUT=ROOT/'build/tactic-clamp-link-20261015'
paths=json.loads((OUT/'context.json').read_text())['paths']
original=allowed.row_object;data_original=dc.build.row_object
saved={s:OUT/str(i)/'saved-before'/original({'source':s}).name for i,s in enumerate(paths)}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    findings,mode,seconds,rows,refs=gate.check(paths,[])
    allowed.row_object=original
    dc.build.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else data_original(row)
    data_findings=dc.findings(dc.object_facts(dc.source_rows(paths)),dc.dl.load())
    dc.build.row_object=data_original
    results[phase]={'identity':findings,'mode':mode,'rows':rows,'data':data_findings}
assert results['before']['data']==results['after']['data'], results
assert set(results['after']['identity']) <= set(results['before']['identity']), results
results['removed_raw_label_identity_diagnostics']=sorted(set(results['before']['identity'])-set(results['after']['identity']))
print('Data findings unchanged; identity diagnostics do not grow:',len(results['before']['identity']),'identity,',len(results['before']['data']),'data')
(OUT/'diagnostic-proof.json').write_text(json.dumps(results,indent=2)+'\n')
