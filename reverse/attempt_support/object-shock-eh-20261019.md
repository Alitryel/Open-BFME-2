# Shockwave exception-body ownership, 2026-10-19

The whole owner is Code/GameEngine/Source/GameLogic/Object/ObjectShockRva00296065.cpp. Its matched 1447-byte Object::rva00296065 at 0x00296065 owns the sound-record temporary, copied sound reference and 136-byte audio event. Its preexisting source identifies the queued entry contract, native Object.cpp string, WorldBuilder CC92C0 and the Zero Hour attemptDamage shockwave section. This change does not add an original method-name claim or change the parent implementation.

Native FuncInfo at 0x0091BA20 has four states: state0 -> action0x0077466D and -1; state1 -> action0x00774686 and 0; state2 -> action0x00774686 and -1; state3 -> action0x0077468E and 2. Parent prologue installs handler0x00774699. The complete native EH graph agrees with the object's associative EH data, including every relocation.

| Body | Size | Compiler label | Native behavior |
| --- | ---: | --- | --- |
| 0x0077466D | 25 | $L3833 | Test bit0 at EBP-14; if set clear it and tail-call 0x004C9F38 on EBP-28; otherwise return. |
| 0x00774686 | 8 | $L3837 | Tail-call 0x0010F149 on EBP+8. |
| 0x0077468E | 11 | $L3840 | Tail-call 0x002D9A43 on EBP-D4. |
| 0x00774699 | 10 | __ehhandler$?rva00296065@Object@@QAEXPAURva00297612Entry@@@Z | Load native FuncInfo and tail-jump to CxxFrameHandler at0x00629182. |

The RET at0x00774685 is an internal branch target within the first25-byte body, not another recovery. Only actual unwind-map action entries and the native handler are claimed. The8/11-byte actions replace anonymous generator harness rows; the25-byte action and10-byte handler were unclaimed when selected. During verification another contributor published the handler. The publication rebase preserves that upstream row and removes this batch's duplicate; final unique C++ exact gain against current master is25 bytes.

The parent and all newly ledgered bodies must pass the regular whole-file build and exact EH verification. No pin, alias, inline assembly, generated source edit or verifier change is used. Raw native unwind/disassembly evidence is in ignored build/next-batch-oct19c/shock-eh-native.txt; raw object location inventory is four-file-eh.json. Model: gpt-6.1-sol.

The final link preview exposed an existing helper-name collision: this unit's setCondition writes the bit unconditionally, whereas BezierProjectileBehaviorUpdate.cpp and GettingBuiltBehaviorCompletion.cpp emit a guarded helper under that name. The shockwave caller already performs the guard. Renaming its private helper to setShockConditionUnchecked preserves all five exact rows and the complete parent EH graph, while the normal --new-variants check no longer refuses the competing COMDAT. The published census predates this unit, so this is a verified conflict repair, not a claim that a fresh census has proved the whole unit links.
