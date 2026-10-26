# ICoord2D empty-constructor header adoption

Base `88917daf20`, on upstream `d831bc2403`, 2026-10-26, under the existing
ICoord2D class claim. ButtonFlashTransitionUpdate.cpp was read in full;
its frozen-file check and three existing rows pass before editing.

## Evidence and change

Retail exports `??0ICoord2D@@QAE@XZ` at RVA `0x0047A6A9`; its existing
three-byte matched owner is W3DPushButtonImageDrawVertical.cpp. Direct
native-byte inspection reads `8B C1 C3`: return the receiver without
initializing either coordinate. The button-transition source already
defines that same empty inline constructor in its private two-integer view.
The existing default canonical view is an aggregate, which changes VC7's
expression/code-generation treatment in this consumer.

The class contract now records the native owner and exposes `ICoord2D() {}`
only when `ICOORD2D_VIEW_DEFAULT_CTOR` is selected. The supported generator
produces the header. The ordinary aggregate view and existing component-
constructor declaration remain unchanged. This is an opt-in compiler view;
it does not establish that constructed and aggregate views can be freely
combined in one translation unit.

The complete button-transition source replaces its private declaration
with the mode and canonical include. This is its first header include;
IRegion2D.h follows it and sees the same constructed coordinate type.
Undefining the selector afterward does not undo the selected type. The
mode must precede every direct or indirect ICoord2D.h inclusion in a TU.

## Verification

Whole-file byte verification preserves update at `0x0035E387` (636 bytes),
three-piece image drawing at `0x0035E6A1` (733 bytes), and draw at
`0x0035EA05` (909 bytes), including their existing table extents. All 3/3
rows, 2,278 bytes, pass. Complete COFF comparison retains 13 non-debug
sections, 2,413 bytes, 93 relocations and every external symbol without
normalizing any external spelling. The source has no EH graphs. The
frozen-file check passes after adoption. Owning header acceptance removes
exactly one header-queue row. The shared-header change is also subject to
the normal dependent-source commit gate.

Ordinary preview against index `47e030bafc` reports LINKS, retaining 2,274
authored nonpadding bytes. This differs from the 2,278 ledger-extent total
by padding; neither figure is an incremental gain or a fresh census.

No function range, class layout, pin, alias or data binding changes.
The existing Microsoft TRUE/FALSE definitions remain a separate queued
item to drain next. Five ICoord2D header items remain. No linked-byte,
ownership, C++ exact-byte or runtime gain is claimed.

Local receipts under `build/codex-cleanup-20261025/`:
`iteration30-before-build.log`, `iteration30-after-build.log`,
`iteration30-accept.log`, `iteration30-link-preview.log`, and the normal
`iteration30-commit.log`. The before object is retained for independent
COFF review.

## Completed shared gate and boolean cleanup

Commit `44c05332d2` passes the normal dependent gate over 255 sources:
1,955 functions, 25 data rows, two STLport folds, 536 literals plus 61
empty references, 778 float references and 229 imports. Converged-data
enforcement reports zero second names and zero unjudged rows. The hook's
separate changed-source repeat is not added to those totals.

The next whole-file change removes the local TRUE/FALSE definitions and
uses C++ `true`/`false` at all 24 boolean arguments and assignments. No
Windows header is needed for these language literals. Normal verification
retains all three rows; the complete 13-section/2,413-byte/93-relocation
COFF comparison and every external symbol are unchanged. Frozen check
passes. The owning Microsoft-header scan reports clean and its scoped
refresh removes exactly the one row for these two macros, preserving all
unrelated queue bytes. Receipts: `iteration31-build.log` and the normal
`iteration31-commit.log`; no remaining queued header or MS-header item
belongs to this file.

## Horizontal slider

On `c1eb8755a4`, GadgetHorizontalSlider.cpp adopts the existing default-
constructor mode in its first include. The whole file was read; its
private constructor had the same empty body and no base or extra fields.
The two callbacks retain their native boundaries `0x00321B50..0x00321E5C`
and `0x00321E5C..0x00322167`: 2/2 rows, 1,559 bytes. Complete comparison
retains all six non-debug sections, 1,615 bytes, 66 relocations and external
names; no external normalization is used. There are no EH graphs. Frozen
check passes, and normal header acceptance retires this file's only queued
item. No header or provider changes are needed in this commit. Four ICoord2D
header items remain. Receipts: `iteration32-before-build.log`,
`iteration32-after-build.log`, `iteration32-accept.log`, and the normal
`iteration32-commit.log`.

## Control-bar rendering

On `88adf8a14b`, the complete W3DControlBar.cpp adopts the same empty-
constructor mode. Its earlier AsciiString/StringBase and Coord3D includes
do not include ICoord2D; the selection precedes its first coordinate-header
inclusion and the following IRegion2D include. The private empty constructor
was also needed for the static base-position guard in the background and
foreground callbacks, and for their by-value offset expressions.

Before/after normal builds pass all 50 rows. The final gate verifies the
30 existing unwind actions through the unchanged parent EH graphs despite
local-label renumbering; all seven graphs are EXACT. All 31 string and seven
float references pass. Full COFF comparison preserves all 116 non-debug
sections, 10,573 bytes, 616 relocations and external identities, including
static storage/guards, by-value calls, COMDATs and exception data. No external
name normalization is used. Frozen check passes and owning header acceptance
retires exactly this source's queue row. Three ICoord2D items remain. Receipts:
`iteration33-before-build.log`, `iteration33-after-build.log`,
`iteration33-accept.log`, and the normal `iteration33-commit.log`.

The control-bar commit's data check reports six existing shadow wrong-name
findings for static initialization guards. Direct before/after comparison
confirms all six guard names, sections, values, types and storage classes
are identical, in addition to the full object comparison above. They are not
new findings or retired data debt. Code identity reports zero new findings;
converged-data enforcement passes.

## Vertical button and constructor owner

On `24bac8998a`, W3DPushButtonImageDrawVertical.cpp adopts the existing
empty-constructor mode at its first include, before IRegion2D.h. The complete
source was read, including all selection and tiling paths. Normal before/
after builds retain both rows: drawing at `0x000A501C` (646 bytes) and the
constructor at `0x0047A6A9` (three bytes), 649 bytes total. The real locals
still emit the existing constructor owner; no artificial emitter is added.
Full COFF comparison preserves 13 non-debug sections, 825 bytes, ten
relocations and all external identities. No EH graph exists; frozen check
passes. Normal header acceptance removes exactly this source's queue row.
Two ICoord2D queue items remain: GameClientDrawableTOC's external default
constructor and icoord.cpp's base/operator view. Receipts:
`iteration34-before-build.log`, `iteration34-after-build.log`,
`iteration34-accept.log`, and the normal `iteration34-commit.log`.

## Rebased publication preparation

The seven new commits through `ecbe75d06f` are rebased on upstream
`bf438b551c`. All five changed coordinate consumers and the shared contract/
header are byte-for-byte identical to their pre-rebase versions. Upstream
also advances its verified BFME 1 pointer from `ff391a5e90` to `de077dd5dd`;
the clean local submodule is synchronized to that pinned commit without
changing nested references. Publication remains subject to the normal
outgoing gate at these inputs; no new full-reference verification is claimed
before that gate completes.

The rebase preserves upstream's independent string-identity retirements
and audio resize repair. The final audio source uses upstream's equivalent
DrawableVector spelling; its whole-file check passes four functions and
one data row. Three earlier string-key retirements now contribute zero net
debt change. All six historical INI queue conflicts are resolved through
the owning scoped scanner, keeping unrelated upstream queue entries.

The current net against `bf438b551c` is 19 header-queue rows, seven Microsoft-
header queue rows, three identity keys and 19 hatch entries removed, with
no additions to those registers and no net data-debt key retirement. This
seven-commit addition removes five header items and two Microsoft-header
items. Its five changed sources retain 61 function rows / 13,151 ledger
bytes; repeated checks of one source are not counted as extra functions.

The refreshed path audit covers all seven deleted INI donors across the
whole outgoing range: 61 mentions in 24 tracked files, all source comments,
attempt history or the historical census. No active tooling/include/registry
consumer remains. The exact scan is `iteration34-path-audit.log`.
`check_csv.py` passes 98,272 function rows, 15,668 symbols and 2,218 data rows.
Fresh `progress.py origin/master` retains C++ exact 7,984,346 (+0) and the
unchanged historical census; the authorized debt-cleanup loop continues.
