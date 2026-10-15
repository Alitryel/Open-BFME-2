import json,sys
from pathlib import Path
ROOT=Path.cwd();sys.path.insert(0,str(ROOT/'tools'))
import allowed_symbols as allowed,code_identity_gate as gate
OUT=ROOT/'build/client-iterator-link-20261015'
paths=json.loads((OUT/'context.json').read_text())['paths'];original=allowed.row_object
saved={s:OUT/str(i)/'saved-before'/original({'source':s}).name for i,s in enumerate(paths)}
assert all(p.exists() for p in saved.values())
results={}
for phase in ['before','after']:
    allowed.row_object=lambda row: saved[row['source']] if phase=='before' and row['source'] in saved else original(row)
    findings,mode,seconds,rows,refs=gate.check(paths,[])
    results[phase]={'findings':findings,'mode':mode,'rows':rows}
old=set(results['before']['findings']);new=set(results['after']['findings'])
assert not old-new,old-new
expected={
'binding: Code/GameEngine/Source/GameClient/Drawable/PickAndPlayUnitVoiceResponse.cpp | uw_007913f8 | ??1AsciiString@@QAE@XZ | 0x004DA2EA | divergent',
'binding: Code/GameEngine/Source/GameClient/Drawable/PickAndPlayUnitVoiceResponse.cpp | uw_00791421 | ??1AsciiString@@QAE@XZ | 0x004D95CE | divergent',
'binding: Code/GameEngine/Source/GameClient/Drawable/PickAndPlayUnitVoiceResponse.cpp | uw_00791429 | ??1AsciiString@@QAE@XZ | 0x00239BAB | divergent'}
assert new-old==expected,new-old
# This records the unmodified shadow gate, including its stale-label findings.
# object-proof proves every nondebug section/binding unchanged apart from the
# unused helpers; the ordinary byte gate and eh_verify resolve funclets by EH.
results['added_raw_label_shadow_findings']=sorted(new-old)
print(len(old),'existing shadow findings unchanged;',len(new-old),'added raw-label findings; see EH/object proof')
(OUT/'identity-proof.json').write_text(json.dumps(results,indent=2)+'\n')
