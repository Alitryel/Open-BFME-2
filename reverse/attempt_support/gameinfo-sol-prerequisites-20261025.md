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

## setSlot donor unblocked

After the virtual-interface repair, setSlot rejected the seed's GameSlot
because its body still used word04/flag08/flag09. Its private declarations now
match the seed, the body uses the seed's existing m_state/m_isAccepted/m_hasMap
spellings, and GameInfo has friend access to those fields. The external rowed
rva002DBAB9 assignment declaration is retained. There is no generated wrapper
or new function, and the by-value object remains 0x1AC bytes with the same
rowed destructor cleanup.

`./build.sh` passes 15/15 rows across the four participating sources, frozen-file
checks pass, and build/gameinfo-sol-setslot-dry.txt accepts seed, setSlot,
closeOpenSlots and the ASCII player donor together. Only setMapSize remains a
compile rejection among the current eligible donors. This is another standalone
prerequisite; no fragments have been absorbed yet. Pending path-change audit
remains empty. Retain file:Code/GameEngine/Source/GameNetwork/GameInfo_setSlot.cpp
and 0x003FFDFA through publication as well.

## setMapSize/getMaxPlayers donor unblocked

The duplicate iterator != definition is now in its own identical namespace
block in the seed and donor, so the normal composer deduplicates it without a
tooling change. The participating GameInfo declaration combines the existing
verified +0x40 map name, +0x44 CRC and +0x48 size with the seed's earlier fields.
Slot 13 uses the existing donor's getLocalSlotNum signature. No vtable entries
are inserted. The donor's isHuman inline uses the seed's exact same definition;
the pre-existing hasMap accesses retain their target +0x09 offset.

`./build.sh` passes **18/18 existing ledger rows** across all five eligible
sources. Declared-unmatched and whitespace checks pass. The normal dry-run
build/gameinfo-sol-mapsize-dry.txt accepts GameInfo.cpp plus **all four**
remaining eligible donors, with an empty rejected dictionary. These are eight
additional existing rows (including three EH handlers), 723 retail bytes, ready
for the next mechanical merge. This repair itself removes no source files and
adds zero recovered bytes. Mixed/protected files remain untouched.

All four private-view/compile prerequisites recorded by the prior Luna handoff
are now cleared for this eligible subset. The mechanical seat should rerun the
current scoped planner and --plan, then use tu_skeleton.py --merge normally.
No handwritten merge or preparation patch is needed. This seat leaves the
compatible donors intact for that pass.

The audit of origin/master..HEAD and these staged edits contains no source-path
changes. Current names, EA path strings, ledgers and protected registers are
unchanged. Additional pending claims are
file:Code/GameEngine/Source/GameNetwork/GameInfoSetMapSize.cpp, 0x00400F5A and
0x0040203C. Release all five file scopes and the five body RVAs listed in this
handoff only after the runner confirms publication; settle landed rows through
claims.py release --landed.

The latest origin/master fetch also includes another seat's Device changes;
the double-dot inventory shows those differences, but the merge-base outgoing
inventory and explicit local commit list confirm this batch has no path moves.
The staged map-size prerequisite also changes declarations only. No changed
path consumer requires repair. AGENTS.md has no incoming change.
