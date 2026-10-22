# OpenContainModuleData link repair, 2026-10-22

Base a8aae3b818; published index 08160bc2c9 (2026-10-22 17:08).
Same-cause follow-up to moduledata-link-20261022.md. No donor inputs, shared
headers, pins, destructor identities or verifier rules changed.

Target game.dat table VA C43658 has 31 slots, matching BfmeModuleData.h except
slot 8 returns true (RVA 50B5C6). Slot 0 is OpenContain's 465221 deleter; slots
1/2/3 are B3FD0/65212/47A69C, slot 14 is B69A1, slots 16..29 are D43D0,
slot 30 is 50B5C6; other slots are 47A699. The constructor's four-slot private
Snapshot view supplied three undefined callbacks and a truncated competing
table. Adopt the existing shared interface, preserving that slot-8 override,
the 0x98-byte layout and native Snapshot teardown in constructor EH/destructor.
The intermediate class hierarchy remains unrecovered.

The remaining losing COMDAT is list<BfmePod32>::~list. Its whole 5-byte retail
body is already rowed at 207F08 in W3DModelDrawParticleBones.cpp. A declaration
specialization binds this unit to that owner instead of emitting another copy;
normal byte and full EH gates prove the parent's cleanup bindings unchanged.

The real constructor object emits the complete exact 28-byte deleting
destructor at 465221. Move its existing row there with add_match
--replace-existing and remove only OpenContain's generation class/constructor
from FamilyDeletingDtors_muse-8fbc.cpp. Its other two rowed destructors remain.

Paired legacy link_check on all three units, same index:

| Unit | Before | After |
| --- | ---: | ---: |
| OpenContainModuleDataConstructor | 0 B | 290 B |
| Rva00465124BaseDtor | 143 B | 143 B |
| FamilyDeletingDtors_muse-8fbc | 84 B | 56 B |
| Total | 227 B | 489 B |

Gain: **262 B**, all three units clean. The 28-byte row move contributes no net
gain. This is a legacy prediction; no closed-strict gain is claimed.
--prepare-current passes 20/20 rows, prepares strict reusable receipts and
leaves census/index/status untouched. Normal gates verify 13 renumbered local
labels through parent EH evidence, one float literal and all imports/strings.
find_declared_unmatched passes; data_check has zero shadow/converged findings.

Reference review: BFME1 remains at verified pointer
37c3022de1ab944c7ffe536440d637dc8199091c. Its game/GameEngine/Include/Common/Module.h
has a different, smaller virtual interface and cannot supply BFME2's table.
Use target evidence and the already established BFME2 header. The upstream
pointer update remains owned by another seat; no freshness stamp was changed.

The further Snapshot-shaped ActivateModuleSpecialPower and CastleBehavior data
constructors already link in current inputs (63/458 B), so no repair was made.
