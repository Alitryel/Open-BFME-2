# ICoord2D component-constructor header adoption

Base `7360cb439a`, on upstream `7de0e86f1c`, 2026-10-26. The picker claimed
class ICoord2D and served ThrowingNewHelpers.cpp. Its frozen-file check passes;
all 31 existing rows pass before the change.

## Evidence and interface

Retail exports `??0ICoord2D@@QAE@HH@Z` at RVA `0x0007E523`. The existing
18-byte owner in WWMath/icoord.cpp stores the two integer arguments into the
eight-byte receiver at offsets 0 and 4. The matched 374-byte constructor at
`0x005CF07E..0x005CF1F4` calls that owner to construct its temporary pair.
Its private ICoord2D declaration already exposes precisely this constructor.

The shared header supplies the same layout but previously omitted that
constructor. The contract now records its export, owner and declaration.
Generating the header from that evidence exposes the declaration when
`ICOORD2D_VIEW_COMPONENT_CTOR` is selected. The existing project constructor
views for Coord2D, Coord3D and ICoord3D establish this approach to preserving
the compiler's construction/ABI distinction. Ordinary header users retain
the existing aggregate definition. No constructor implementation is added.

The consumer selects the mode, includes the canonical header where its
private definition stood, and undefines the selector. The mode must be chosen
before the first direct or indirect ICoord2D.h include. The selected type lasts
for the entire TU; undef does not restore aggregate semantics. This is a
prerequisite for later TU composition: a constructed temporary and a POD
by-value/aggregate view cannot simply be mixed in the same unit.

## Verification and scope

- Before editing, the supported gate-cost command verifies all 251 existing
  dependent sources in 139 seconds, with no failing chunk.
- The changed consumer, the existing component-constructor owner and the
  existing POD-returning screen-position unit pass 51/51 rows. The consumer
  retains all 31 rows and all eight EXACT EH graphs.
- Independent before/current COFF comparison, reproduced locally, finds the
  same external symbols and all 58 non-debug sections, 2,547 bytes and 201
  relocation targets unchanged. Local compiler-label renumbering is resolved
  by section/value/type/storage. Unrowed COMDATs and exception data are included.
- `header_adopt_lane.py accept --class ICoord2D` accepts the complete consumer
  and retires exactly its one header-queue row. The shared-header edit remains
  subject to the normal dependent-source commit gate.
- Five aggregate-initializing dependent files were reserved during analysis,
  then released unchanged. No global constructor migration was attempted.

No ledger range, pin, alias, data binding or class layout changes. The other
ICoord2D queue items retain their constructor, default-initialization or
missing-method prerequisites. There is no C++ coverage, linked-byte or complete
TU-composition claim.

Local receipts under `build/codex-cleanup-20261025/`:
`iteration26-before-build.log`, `iteration26-ctor-mode-build.log`,
`iteration26-header-accept.log`, `iteration26-eh.log`,
`iteration26-coff-parity.log`, and the normal `iteration26-commit.log`.
