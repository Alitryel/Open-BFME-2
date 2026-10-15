"""Compare shadow diagnostics using saved originals and current objects."""
import json, sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed, code_identity_gate as gate, data_check as dc
OUT=ROOT/'build/font-cache-owner-link-20261015'
paths=json.loads((OUT/'sources.json').read_text())
original=allowed.row_object;data_original=dc.build.row_object
saved={s:OUT/'before'/original({'source':s}).name for s in paths}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    findings,mode,seconds,rows,refs=gate.check(paths,[])
    allowed.row_object=original
    dc.build.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else data_original(row)
    unread=[]
    facts=dc.object_facts(dc.source_rows(paths),unread)
    assert not unread,unread
    data_findings=dc.findings(facts,dc.dl.load())
    dc.build.row_object=data_original
    results[phase]={'identity':findings,'mode':mode,'rows':rows,'data':data_findings}
old=set(results['before']['identity']);new=set(results['after']['identity'])
assert new <= old, sorted(new-old)
added=set(results['after']['data'])-set(results['before']['data'])
expected={(s,'wrong-name','?BfmeFontCharsCache@@3V?$SimpleDynVecClass@PAVFontCharsClass@@@@A','0x009E2084') for s in paths[:-1]}
assert added==expected,added
assert set(results['before']['data']) <= set(results['after']['data'])
results['added_stale_ledger_diagnostics']=sorted(added)
results['removed_identity_diagnostics']=sorted(old-new)
print('Shadow identity:',len(old),'->',len(new),'findings; data:',len(results['before']['data']),'->',len(results['after']['data']))
print('Only new data findings: three references to the byte-verified data_rows owner, which the generated data_ledger still names as the old undefined scalar.')
(OUT/'diagnostic-proof.json').write_text(json.dumps(results,indent=2)+'\n')
