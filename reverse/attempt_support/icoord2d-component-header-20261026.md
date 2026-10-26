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

## Completed gate and second whole-file adoption

Commit `a37e665064` passed the normal dependent-source gate on the final
header: 252 sources, 1,927 function rows, 25 data rows, two STLport folds,
536 literals plus 61 empty-string references, 778 float references and
229 imports. Converged-data enforcement found no second names or unjudged
rows across that scope. The separately repeated changed-consumer check
passes 31/31 rows and eight EXACT EH graphs; it is not added to the totals.

The same class claim covers
StrategicInGameUIPlanningPhaseBuildingSelectionCtor.cpp. Its whole file has
17 matched rows, including the 496-byte selection constructor at 0x005CE5B3
and ControlBar::populateCommand at 0x0053D355 (1,790 bytes). Both construct
two-integer temporaries through the same native 0x0007E523 owner. Replacing
the identical private declaration with the component-constructor header
selection preserves both calls. The only earlier include is
LivingWorldObservers.h, which does not include a coordinate header; the
selection therefore precedes every ICoord2D include in the TU.

Before and after normal builds pass all 17 rows. Both EH graphs are EXACT,
the frozen-file check passes, and `header_adopt_lane.py accept` retires this
file's one queue row. Independent COFF review, reproduced locally, preserves
all 121 non-debug sections, 5,162 bytes, 214 relocations and 205 external
symbols. Fourteen local-label references are renumbered but retain their
physical targets; external names are not normalized.
No source move or constructor implementation is added.
The two component-constructor consumers now share the canonical declaration;
the remaining seven ICoord2D queue items need separate default-constructor,
base or method evidence.

Local receipts: `iteration27-before-build.log`, `iteration27-after-build.log`,
`iteration27-accept.log`, `iteration27-eh.log`, `iteration27-coff-parity.log`,
and `iteration27-commit.log`.

## Publication qualification after rebase

The second normal commit gate passes all 17 rows and both EH graphs. Its
shadow identity check reports two divergent TemplateCountKey allocator
COMDATs (`_STLP_alloc_proxy::allocate` and `allocator::allocate`) outside the
register. Complete before/after object parity above includes those unchanged
definitions and their relocation targets. They remain a separate provider
prerequisite; header acceptance is not a claim that this unit links cleanly.

The series is rebased onto upstream `5e6511da79`; the two header commits are
now `e548acf0d1` and `32da969550`. No upstream source or header overlaps the
series' edited paths. Ledger integrity passes with 98,273 function rows,
15,683 symbols and 2,218 data rows. The new official census at `47e030bafc`
(2026-10-26 08:28) records LINKING 7,370,962 and LINKED 7,614,012 bytes.
These upstream measurements do not measure this PR. Fresh progress against
master retains C++ exact 7,984,346 (+0) and BYTE-MATCHED 100%.

The complete pending path audit was repeated for
`5e6511da79..32da969550`: all seven absorbed INI paths, their basenames and
stems were searched together across tracked consumers. The 73 occurrences
in 32 files are source comments, prior attempt evidence, historical census
rows, documentation, or the independent BFME 1 reference. No active tool,
hook, configuration, source include or current ownership registry depends
on a removed donor. `iteration27-path-audit.log` retains the complete hits.
No path changes follow this audit in the publication batch.

Two historical streak-data retirements now duplicate upstream `462ffdd1f8`;
the rebase preserves its register and removes that credit from this PR.
Net against current master: fourteen header rows, six identity keys,
nineteen hatch occurrences and five Microsoft-header queue rows retired;
three verified data rows added. No net data-debt key retirement remains.
