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
