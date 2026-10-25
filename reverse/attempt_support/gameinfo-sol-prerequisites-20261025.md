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

## closeOpenSlots donor unblocked

The next normal trial reproduced the private-view selection failure: selecting
closeOpenSlots' GameInfo discarded the seed's preorder fields and methods.
The seed and this donor now use the existing donor's slot-17 virtual interface,
with the seed's leading padding reduced by its real vptr size so the verified
+0x08 mask, +0x10/+0x11 flags and +0x18 slot array do not move. GameSlot's
already-rowed virtual destructor replaces the seed's raw vptr field, retaining
its +0x04 state and 0x1AC-byte size. External constructor/copy-constructor,
isOccupied, getSlot and setSlot declarations come from the rowed donor. The
connection record initializes the same dword/word pair; padding is unwritten.
These are target ABI facts from the existing rowed sources, not donor layout
claims. No bodies move, and no pin, name or protected register changes.

`./build.sh` passes all 13 ledger rows across GameInfo.cpp,
GameInfoCloseOpenSlots.cpp and GameSlotIsPlayerAscii.cpp. Frozen-file checks pass.
The normal dry-run now accepts all three together, recorded in
build/gameinfo-sol-close-dry.txt. setSlot still rejects its private field names;
setMapSize still rejects the duplicate STL iterator operator. No merge is
applied; this adds another compatible fragment for the mechanical seat.

The complete outgoing range still has no path moves or removed sources, so
there are no changed path consumers to audit. Also retain
file:Code/GameEngine/Source/GameNetwork/GameInfoCloseOpenSlots.cpp and
0x003FFE51 until publication, alongside the earlier claims above.
