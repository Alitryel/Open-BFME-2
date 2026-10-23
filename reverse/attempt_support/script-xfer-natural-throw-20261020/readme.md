# Natural XferException throws in five ScriptEngine transfer helpers

This source repair replaces the manual `bfmeFormatText` / `_CxxThrowException`
bridge and `__assume(0)` with ordinary C++ throws in five existing units:

- `Rva00206923XferList.cpp`: 0x00206923, 205 bytes.
- `Rva002081C7Xfer.cpp`: 0x002081C7, 240 bytes, and its existing 10-byte handler at 0x0076C96C.
- `Rva002070F7Xfer.cpp`: 0x002070F7, 89 bytes.
- `Rva00208081Xfer.cpp`: 0x00208081, 89 bytes.
- `Rva00209A09Xfer.cpp`: 0x00209A09, 89 bytes.

All files are under `Code/GameEngine/Source/GameLogic/ScriptEngine/`.
The list loaders retain tag 4 and `"List must be empty on load"`. The three
fixed-array helpers retain tag 0, a null format, and the check that the
transferred count equals 20. The surrounding transfer operations, loops,
STL declarations, exception macros, and compiler flags are unchanged.

The declaration matches the existing BFME2
`Common/System/XferException.cpp` provider family. The pinned BFME1
`92f6bbe8` source `game/GameEngine/Source/GameLogic/ScriptEngine/XferListAsciiStringUINT.cpp`
and its sibling list helpers independently use natural `throw XferException`.
The earlier GhostObject/LocomotorSet/Weapon repair established the same
exception metadata family. These are existing provider identities; no pin,
alias, shared header, function range, or gate was changed.

`throw-evidence.json` records all 15 emitted exception relocations against
the native callsites. Every constructor resolves to VA 0x00A0C36E, every
ThrowInfo reference to VA 0x00CFFD18, and every runtime throw to VA 0x00A29094.
`metadata-graph.json` follows each object's ThrowInfo, catchable-type array,
catchable type, and type descriptor. All 20 reachable sections match native
bytes outside their relocation fields. Their references retain the native
8-byte `.?AVXferException@@` class, destructor VA 0x0042BD30, copy constructor
VA 0x004588C5, and type-info vtable VA 0x00C7C730.

The normal scoped `build.sh` gate passes before and after: six existing rows,
722 bytes, and four string references. `eh.json` reports the list helper's
exception graph EXACT with no baselines or missing objects. The other four
parents have no local EH graph. Source hashes and unchanged effective flags
are retained in `throw-evidence.json`.

Four units link cleanly against the published census at `5366c4f808`.
`Rva002081C7Xfer.cpp` has an existing conflicting incidental `list::insert`
COMDAT. `paired-link.json` compares the original source at `5578111f`,
compiled into a private object with the same effective flags, against the
repaired object. The original parent and handler are also byte-exact, and
both objects have exactly the same single link blocker. This comparison
did not temporarily replace production source or inject a private object
into the shared cache.

This repairs already matched source: zero newly recovered bytes and no
link gain claimed. Independent review confirmed the unchanged native
failure conditions and exception semantics. `independent-review.json`
records a separate read of the five objects, resolving all metadata
relocations before comparing their full bytes with retail. The ordinary
commit hook remains required.

Agent: Codex (runtime model not exposed). Verification and repair batch:
approximately 6 minutes, measured from the initial scoped gate.
