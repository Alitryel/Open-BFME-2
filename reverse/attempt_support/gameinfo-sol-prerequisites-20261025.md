# GameInfo consolidation prerequisites, 2026-10-25

Seat: yasinschroeder-codexb. Scope: GameNetwork, GameEngineDevice and Libraries.

## Player-name donor unblocked

The prior GameNetwork Luna handoff records C2365 duplicate SlotState enumerators
for GameSlotIsPlayerAscii.cpp. Current scoped planner, plan and unchanged dry-run
reproduced it. The donor now names its enum SlotState so composition selects one
existing declaration. The seed and donor share the target field view: state at
+0x04, UnicodeString at +0x30, separate AsciiString at +0x1A8. text30 is the
existing offset spelling from GameSlotCtor.cpp; no semantic identity is inferred.
The donor no longer supplies an unrelated reset-only virtual class view.
No symbols, pins, ledger names, canonical headers or protected registers change.

`./build.sh GameInfo.cpp GameSlotIsPlayerAscii.cpp` passes 11/11 existing rows;
`find_declared_unmatched.py` passes both (the seed's existing absent-from-retail
anchor remains). The normal merge dry-run now accepts exactly the seed and
GameSlotIsPlayerAscii.cpp, whereas before it accepted no pair. This is a verified
consolidation prerequisite, +0 recovered C++ bytes. The compatible fragment is
left for the mechanical seat's next normal merge, not manually moved.

Other unchanged GameInfo blockers: setSlot requires a compatible GameInfo/slot
view; closeOpenSlots requires reconciliation of the virtual interface and state
fields; setMapSize hits duplicate STL iterator operators. Mixed and protected
files were not touched. Raw local trial logs: build/gameinfo-sol-dry.json and
build/gameinfo-sol-after-dry.txt; these are scratch, not publication receipts.

The outgoing range before this prerequisite contains only the prior HTree
handoff commit d4da232e30; there are no pending source path changes to audit.
No files are removed by this prerequisite. All original EA paths are retained.
Normal hooks remain required. File/RVA claims stay held until confirmed push;
then release file:Code/GameEngine/Source/GameNetwork/GameInfo.cpp,
file:Code/GameEngine/Source/GameNetwork/GameSlotIsPlayerAscii.cpp and 0x003FFEF5.
