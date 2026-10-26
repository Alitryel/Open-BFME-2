# ICoord2D external constructor in GameClient

On d7a2d8bff6, the complete GameClientDrawableTOC.cpp adopts the canonical
ICoord2D header through a declaration-only default-constructor mode. The
whole source and prior MetaEventTranslator attempts were read; its frozen
check passes before and after. The class and source claims are held.

## Target evidence and compiler view

Native MetaEventTranslator `0x001DB432..0x001DB48E` (92 bytes) passes the
constructor at VA `0x0087A6A9`, count three and stride eight to the vector
constructor iterator at RVA `0x00001423`. The constructor's existing owner
is W3DPushButtonImageDrawVertical.cpp, native `8B C1 C3`; it initializes
neither field. The GameClient object references only the undefined
`??0ICoord2D@@QAE@XZ` coordinate symbol. That constructor spelling carries
no class/struct key, and none of this source's 92 ledger names carries an
ICoord2D class-key spelling.

The contract-generated header adds `ICOORD2D_VIEW_EXTERN_DEFAULT_CTOR`
before the existing inline-default branch, using mutually exclusive
`#if/#elif`. The external view is an ordinary `ICoord2D();` declaration,
without inline body, exception specification or import annotation. It is
selected before this source's first coordinate include. Existing aggregate,
component-constructor and inline-default views remain available. Selection
still lasts for the entire translation unit; this is a composition
prerequisite, not evidence that arbitrary private views can be merged.

## Verification and scope

Normal before/after builds pass all 92 rows (8,863 ledger bytes), including
the existing constructor iterator callback and emitted helper COMDATs.
All eleven EH graphs are EXACT; 28 string literals, two empty references,
one float reference and three imports pass. One STLport constructor fold
is independently verified against its retail owner.

Complete before/after COFF comparison preserves 353 non-debug sections,
16,313 bytes, 991 relocations and 531 external symbol identities. Independent
review also preserves every section auxiliary record, including COMDAT
selection/association. The 59 renumbered local-label references retain their
physical targets. No external-name normalization is used, and no constructor
copy is introduced. The frozen check passes; `header_adopt_lane.py accept`
retires exactly this source's ICoord2D queue item.
The ordinary link preview against census 47e030bafc retains LINKS and
8,248 authored non-padding bytes; it does not record a census gain.

Local receipts in `build/codex-cleanup-20261025/` are
`iteration35-before-build.log`, `iteration35-after-build.log`,
`iteration35-accept.log` and `iteration35-link-preview.log`; the before
object and full-object comparison script are retained there. The shared
header's normal dependent commit gate remains the final acceptance step.

ICoord2D's remaining queue item is icoord.cpp's base/operator view.
GameClientDrawableTOC.cpp also retains its separate SubsystemInterface and
Microsoft-header items. Its base view has fourteen virtual slots, whereas
the canonical base currently exposes only its destructor; adoption needs
slot evidence and dependent-source validation. No census, ownership or
runtime improvement is claimed by this header-only cleanup.
