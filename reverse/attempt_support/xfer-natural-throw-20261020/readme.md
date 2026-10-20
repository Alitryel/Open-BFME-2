# Natural XferException throws in three save/load units

GhostObject::xfer, LocomotorSet::DoXfer and Weapon::xfer now use ordinary `throw XferException(tag, 0)` instead of manually constructing a two-field struct with `bfmeFormatText`, passing it and an opaque ThrowInfo global to `_CxxThrowException`, and asserting unreachable. The declarations name the existing constructor, copy constructor and destructor. Error tags remain 5 for missing referenced objects/templates and 4 for a nonempty locomotor load destination. The change does not alter the surrounding save/load logic, STL declarations, compiler flags, registered classes, pins, function ranges or verifier rules.

The lead was Open-BFME-1 revision `4483e88da1c2f3b9a273f779baac7458bd8bb891`, `game/GameEngine/Source/GameLogic/Object/GhostObject_xfer.cpp`, which uses a natural XferException throw. BFME2's existing `W3DGhostObjectScene.cpp` and `Common/System/XferException.cpp` independently establish the same declaration/provider family. The committed BFME1 build input remains `92f6bbe8`; this repair was built on BFME2 `413ecd9e` plus the unrelated text-entry repair.

`throw-evidence.json` records the emitted constructor, ThrowInfo and runtime-throw relocations against native callsites in all three parent bodies. Native ThrowInfo at VA 0x00CFFD18 names the 8-byte class `.?AVXferException@@`, destructor VA 0x0042BD30 and copy constructor VA 0x004588C5. The varargs constructor calls resolve to VA 0x00A0C36E and runtime throws to VA 0x00A29094. These are the established providers, not new invented aliases. `metadata-graph.json` additionally follows the compiler-generated ThrowInfo, catchable-type array, catchable type and type descriptor: all four reachable data sections in each object are byte-equal to retail after masking their relocation fields, and the native targets of those fields are preserved in the evidence.

Verification:

- Each source passed the normal scoped byte/reference gate both before and after the repair. The six existing rows total 1,191 claimed bytes: GhostObject 154; LocomotorSet 413 plus its 10-byte handler; Weapon 579 plus its 25-byte unwind and 10-byte handler.
- `eh_verify.py` reports the two parent EH graphs EXACT, zero failures/baselines/missing objects. GhostObject has no local EH frame on either side. The Weapon unwind row's old `$L5624` ledger label remains correctly identified through its parent EH graph despite compiler label renumbering. See `eh.json`.
- `link_check.py` against the published census dated 2026-10-20 12:21 at `5366c4f808` reports all three files LINKS: GhostObject 154, LocomotorSet 423 and Weapon 589 current linked bytes (its metric excludes some 0xCC bytes). The index reports LocomotorSet as 0 at census time, but an explicit temporary restore/build/linkcheck of this checkout's original source also produced LINKS 423. Therefore there is **zero measured link gain** from this repair.
- Independent review confirmed the native exception class/provider identities and unchanged error behavior. The ordinary staged hook remains mandatory before commit.

This is a source-quality repair of already matched bodies, with **zero newly recovered bytes**. It is a bounded three-file batch, not a claim that all manual exception bridges in the repository have been replaced.

Agent: Codex (runtime model not exposed).
