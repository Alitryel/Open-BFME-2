# ODS debug-output ownership and compiler repair

Two units now predict link cleanly: `DebugIOOds_Create.cpp` (111 non-padding
retail bytes) and `Rva0088FAA0DebugIOOdsDestructor.cpp` (168). Paired legacy-index
prediction across eight self-strict providers increases 4,664 -> 4,943 B,
**+279 B**, with all other provider results preserved. This is not a
closed-strict or full-link measurement; the frozen index is 3f413ed3ff,
2026-10-20 18:52. `measurements.json` records both objects, blockers and hashes.

The native base deleting destructor 0x3F340 is the existing 31-byte frameless
body. Derived ctor 0x3F380, destructor 0x3F460, deleting wrapper 0x3F430 and
factory 0x3F3D0 require their frame pointers. Removing /Oy- globally was tested
and rejected: it changes their code and EH graphs. The existing
`DebugIONetPipeDestructorThunk.cpp` repair supplies the applicable compiler
boundary: compile the base normally, then disable frame omission for the derived
class and its bodies. The scoped pragma addresses this demonstrated codegen
conflict; no naked body, byte emission, alias or pin was introduced.

The ODS constructor is an inline header definition in the donor. The row owner
now emits it as a COMDAT, retained through an explicitly non-retail anchor, as
its factory does already. The owner's shortened Write(int)/Execute(void) view
is reconciled with the donor interface used by the factory and rowed Write
provider. Write binds to the actual provider instead of an empty local method.
The donor was reviewed at BFME1 4483e88da1c2f3b9a273f779baac7458bd8bb891,
`inputs/reference/.../debug/internal_io.h`. Original source identities and slot
signatures come from that donor plus the existing named factory/Write rows;
compiler settings and ABI are independently verified against BFME2's bodies.

Checks: touched byte gate 10/10, all eight providers self-strict 41/41 before
and after, 41 literals + one empty string and 32 named imports verified.
Compiler-local funclet labels are associated through the exact parent EH data.
The net factory/constructor remain blocked by their unresolved named destructor
and incomplete base view; the trial edit to the net factory was restored.
