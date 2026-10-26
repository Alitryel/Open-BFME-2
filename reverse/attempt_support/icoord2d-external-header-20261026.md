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

## Completed shared gate and SDK declarations

Commit `306bf80b31` passes the normal dependent gate over 259 sources:
2,107 functions, 25 data rows, three STLport folds, 595 string literals plus
63 empty references, 786 floats and 232 imports. Converged-data enforcement
finds zero second names and zero unjudged rows. The separate changed-source
repeat is not added to these totals; it again passes 92 rows and eleven
EXACT EH graphs. The source's fourteen shadow code-identity findings and
one shadow data-name finding for TheMessageStream remain; complete-object
equivalence shows this change preserves their definitions and references.

The following whole-file change replaces both private Windows imports,
timeGetTime and Sleep, with the toolchain's actual `<windows.h>` and
`<mmsystem.h>`, using the existing `// platformsdk` build opt-in. Configuration
defines WIN32_LEAN_AND_MEAN and NOMINMAX avoid unused Windows declarations
and macro substitution of the file's existing STL max overload. The SDK's
DWORD timeGetTime return replaces the private unsigned-int spelling while
retaining its native 32-bit imported call and external symbol.

Normal verification again passes 92/92 rows, eleven EXACT EH graphs and all
three import references. Complete object comparison preserves the same
353 non-debug sections, 16,313 bytes, 991 relocations and external identities,
including linker directives; no external-name normalization is used. The
frozen check passes. The owning Microsoft-header scan is clean, and its
scoped refresh removes exactly the one queue item for these two declarations,
preserving every unrelated queue byte. Receipts are `iteration36-build.log`,
`iteration36-verification.log` and the normal `iteration36-commit.log`.
Only the SubsystemInterface item remains queued for this source.

## Published full verification

The package is published at `9839a436af` in PR 115. Its normal full gate
passes 98,272 functions, 2,218 data rows, 214 STLport folds, 31,536 literals
plus 2,257 empty references, 9,116 floats and 6,419 imports. DIR32, pins,
module registry, source ownership and the no-op image pass. The outgoing
EH check covers 417 graphs, all EXACT, without baseline exceptions or missing
objects. Converged-data enforcement covers 22,845 sources with zero second
names and zero unjudged rows. PRE-PUSH OK follows the full gate.

The initial push refusal was caused by seven absent objects and one stale
INI provider after upstream moves. The normal eight-source build verifies
76 functions and one data row; the missing-object condition is then absent.
No gate or register was changed to obtain the successful retry.

The link audit remains INCONCLUSIVE: its index predates the outgoing base,
and 155 source objects lack current strict receipts. The actual outgoing
path audit also covers 24 upstream donor moves: 138 references are comments,
history or valid paths in the separate BFME 1 namespace, with no active
consumer of an absent BFME 2 path. The seven PR-local INI path audit is
unchanged. These are publication controls, not a new census or runtime pass.

The following post-push rebase to `9885fa1597` preserves the GameClient source,
ICoord2D header and contract byte for byte. Its new ledger totals are 98,271
functions, 15,659 symbols and 2,217 data rows; check_csv passes. This does not
revise the historical full-gate counts above. The remaining same-file base
adoption is tracked separately in
[the complete-vtable handoff](subsystem-full-vtable-gameclient-20261026.md).
