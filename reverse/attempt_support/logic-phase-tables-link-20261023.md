Logic-phase parser data ownership, 2026-10-23
===========================================

At parent cf4b43fd8c, Rva003F86F9Ctor.cpp's 237 unique matched bytes
fail legacy link prediction only on g_logicTurnPhaseNames and
g_logicTurnPhaseFields. No other source defines either name. Their original
identifiers remain unproven; preserve the existing descriptive names.

Target evidence is the two DIR32 operands of the matched 3F90E4 parser:
the scanIndexList call pushes VA C6CC10 and initFromINI pushes C374EC.
C6CC10 contains exactly seven string pointers (Planning, MoveArmies,
ResolveBattles, FakePhaseOne, PlanRetreats, RetreatArmies, Complete), then
null; the first string follows at C6CC30. C374EC contains the 16-byte Session
entry, callback VA 7F907B, zero user data and offset, followed by a complete
16-byte null entry ending C3750C. The callback is the existing row
LivingWorldTutorial::LogicTurn::ParseINI in Rva003F8F2BParse.cpp. Its row
proves the two accessed cdecl arguments, not an original four-argument
declaration; the table retains the INI dispatcher's standard callback type.
No donor names or layouts are promoted from a byte placement.

Define both complete arrays and own each 32-byte range in data_rows.csv.
The field table's former scalar declaration becomes an array. This changes
its COFF type to the actual array type without adding a second data owner.
The declarations also renumber the existing compiler cleanup label from
$L5001 to $L5043. add_match --replace-existing rebinds the same 8-byte
funclet after eh_verify proves its parent's whole EH graph EXACT.

Acceptance: build.sh verifies 3/3 code rows, both data rows, literals and
imports. prepare-current supplies strict reusable receipts for the edited
unit; frozen-file and converged-data checks pass. eh_verify is EXACT 1/1.
With the same published index (2026-10-23 19:41, d4fa46f19a), the edited
unit changes from 0 to 237 linked bytes. Including its unchanged callback
owner yields 445 linked bytes (237 + 208). These are bounded current-object
legacy previews; no closed-strict, actual link-cycle or executable claim.

Scratch evidence: build/logicphase-{before,after,byte,prepare,eh}-seat.log
and build/logicphase-add-seat.log. No other unit references the two names;
the cause sweep is complete for these tables.
