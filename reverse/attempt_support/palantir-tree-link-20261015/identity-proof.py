import json,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed,code_identity_gate as gate
OUT=ROOT/'build/palantir-tree-link-20261015'
paths=json.loads((OUT/'context.json').read_text())['paths'];original=allowed.row_object
saved={s:OUT/'saved-before'/original({'source':s}).name for i,s in enumerate(paths)}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    findings,mode,seconds,rows,refs=gate.check(paths,[])
    results[phase]={'findings':findings,'mode':mode,'rows':rows}
assert results['before']['mode']==results['after']['mode']=='shadow'
assert results['before']['rows']==results['after']['rows']==73
# Preserve the raw shadow result: this gate reads the stale ledger label,
# whereas build.sh resolves renumbered funclets through the verified EH graph.
expected = ('binding: Code/GameEngine/Source/GameClient/GUI/Palantir/'
            'AptPalantirConstructor.cpp | $L7591 | ??1Rva002D394B@@QAE@XZ | '
            '0x002D3B30 | wrong')
assert set(results['after']['findings']) - set(results['before']['findings']) == {expected}, results
assert set(results['before']['findings']) <= set(results['after']['findings']), results
byte_log=(OUT/'byte-after.txt').read_text()
assert 'verified parent EH data places $L7591 at 0x007776E5' in byte_log
assert all(v[0]=='EXACT' for v in json.loads((OUT/'eh-after.json').read_text()).values())
results['renumbered_label_evidence'] = {
 'ledger_label':'$L7591', 'ledger_rva':'0x00777776',
 'actual_label_rva':'0x007776E5',
 'source':'byte-after.txt and eh-after.json; object-proof.json proves all other sections/relocations identical',
 'shadow_diagnostic_not_a_real_binding_change':True}

results['new_findings']=sorted(set(results['after']['findings'])-set(results['before']['findings']))
results['absent_after']=sorted(set(results['before']['findings'])-set(results['after']['findings']))
print('identity shadow: before',len(results['before']['findings']),'after',len(results['after']['findings']),'new',len(results['new_findings']))
(OUT/'identity-proof.json').write_text(json.dumps(results,indent=2)+'\n')
