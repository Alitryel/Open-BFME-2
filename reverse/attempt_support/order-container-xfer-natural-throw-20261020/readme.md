# Native exceptions in group-order map and deque transfers

This source repair replaces four manual CRT throw sequences with ordinary
`throw XferException(4, ...)` in three existing translation units:

- `Code/GameEngine/Source/GameLogic/AI/Rva00355770GroupOrderMaps.cpp`
- `Code/GameEngine/Source/GameLogic/AI/MoveToGroupOrderXfer.cpp`
- `Code/GameEngine/Source/GameClient/Gen00595870DequeXfer_Rva00586231.cpp`

The original and repaired sources use the same load guards, messages, iteration,
container operations, compiler flags, and STL configuration. The obsolete CRT
`/alternatename` in the MoveTo unit is removed. No container or payload identity
is inferred, and the established address-based names remain unchanged.

## Native type and source evidence

The four native throwing parents are `0x0035552A` (225 bytes), `0x0035568F`
(225 bytes), `0x0054755B` (241 bytes), and `0x00586231` (212 bytes). Each
constructs the tag-4 exception through RVA `0x0060C36E` and passes ThrowInfo VA
`0x00CFFD18` to the CRT throw routine at RVA `0x00629094`.

The native catchable-type graph names `.?AVXferException@@`, describes an
eight-byte object, and points to the established destructor at RVA `0x0002BD30`
and copy constructor at RVA `0x000588C5`. The class declaration retains the
`char *text; int tag;` layout. It declares the real constructor, copy constructor,
and destructor so the compiler emits the canonical exception metadata.

The pinned BFME1 reference `92f6bbe8` has an analogous natural tag-4 map-empty
guard in `Common/System/XferMapAsciiStringReal.cpp:124`. This supports the
serialization rule; it does not establish the unknown group-order or deque
payload identity. The direct native call and metadata evidence establishes the
exception identity. Relevant earlier attempts concern conversion and template
identity, not this natural-throw repair; see `native-packet.json`.

## Validation

Both normal scoped `./build.sh` gates pass all 12 existing rows, totaling
1,883 bytes, and all eight string references. Strict resolved body comparisons
also pass all 12 rows with no unresolved calls or masked fallback. All 12
exception-related relocations resolve to the native constructor, ThrowInfo,
and CRT throw targets. These rows have no owned EH tables; the EH verifier
reports no missing objects or differences.

All three compiler-emitted exception metadata graphs match the four native
sections each: ThrowInfo, catchable-type array, catchable type, and type
descriptor. External references identify the canonical destructor, copy
constructor, and `type_info` vtable. The independent review resolves every
metadata relocation before comparing the complete bytes.

The actual before/after linkage comparison uses the same published census
(`144ed0ccab`, 2026-10-20 15:34), compiler commands, and compiler environment.
It preserves the original objects before rebuilding and refreshes only an
in-memory index. The MoveTo unit is clean on both sides. GroupOrderMaps retains
its two existing COMDAT disagreements, and the deque unit retains its four
existing COMDAT blockers. Every blocker category is unchanged.

This is source and exception-identity repair. It adds no matched bytes, rows,
pins, shared headers, or linkage credit.

The evidence files contain native windows and prior attempts, source/object
hashes, strict body and exception relocation checks, metadata graphs, the EH
result, and the actual paired linkage results. The normal build logs and
effective compiler commands are retained in `build-receipt.json`.
