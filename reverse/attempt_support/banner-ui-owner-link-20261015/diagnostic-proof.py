"""Compare shadow diagnostics against original/current COFF and data ledgers."""
import json, subprocess, sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed, code_identity_gate as gate, data_check as dc
OUT=ROOT/'build/banner-ui-owner-link-20261015'
paths=json.loads((OUT/'sources.json').read_text())
ctx=json.loads((OUT/'context.json').read_text())
old_ledger=OUT/'before-data-ledger.csv'
old_ledger.write_bytes(subprocess.check_output(['git','show',ctx['base']+':reverse/data_ledger.csv']))
original=allowed.row_object;data_original=dc.build.row_object
saved={s:OUT/'before'/original({'source':s}).name for s in paths}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    try:
        findings,mode,seconds,rows,refs=gate.check(paths,[])
    finally:
        allowed.row_object=original
    dc.build.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else data_original(row)
    try:
        unread=[]
        facts=dc.object_facts(dc.source_rows(paths),unread)
        assert not unread,unread
        ledger=dc.dl.load(old_ledger) if phase=='before' else dc.dl.load()
        data_findings=dc.findings(facts,ledger)
    finally:
        dc.build.row_object=data_original
    results[phase]={'identity':findings,'mode':mode,'rows':rows,'data':data_findings}
old=set(results['before']['identity']);new=set(results['after']['identity'])
assert new <= old, sorted(new-old)
before=set(results['before']['data']);after=set(results['after']['data'])
expected={('Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/BannerUI.cpp','wrong-name','?g_00DFE32C@@3PAVRva00217194BannerUI@@A','0x009FE32C')}
assert before-after==expected,(before-after)
assert not after-before,after-before
results['removed_data_diagnostics']=sorted(before-after)
results['removed_identity_diagnostics']=sorted(old-new)
print('Shadow identity:',len(old),'->',len(new),'findings; data:',len(before),'->',len(after))
print('Only removed data finding: obsolete parser-view name at 0x009FE32C; all four remaining findings pre-exist.')
(OUT/'diagnostic-proof.json').write_text(json.dumps(results,indent=2)+'\n')
