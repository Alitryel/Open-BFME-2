# Coordinate arithmetic owner: canonical declarations

## ICoord2D and its companion base

On `7eb94b780a`, the whole `icoord.cpp` was read and its existing nineteen
rows verified before editing. The source, ICoord2D and ICoord2DBase claims
are held. The frozen-source check passes before and after; its two existing
emission anchors and their markers are unchanged.

The private two-dimensional declarations are replaced with explicit includes
of the canonical ICoord2D and companion ICoord2DBase headers. All function
bodies remain unchanged. The existing component-constructor and external
default-constructor modes keep this owner's out-of-class definitions valid.
The new `ICOORD2D_VIEW_MATH_METHODS` mode exposes nine existing arithmetic
method declarations and the companion's existing assignment declaration.
The contract records their exact ledger names, boundaries and owner.

The old base and derived views hold the same two integers at offsets 0 and
4 as the canonical flat pair. No body in this source needs a derived-to-base
conversion or qualified base call. Complete-object comparison below checks
the resulting compiler behavior, rather than inferring equivalence solely
from field offsets. Method declarations remain opt-in so other consumers
keep their implicit assignment and existing aggregate behavior. Mode
selection must precede the first include and lasts for the translation unit.
This does not establish that arbitrary coordinate consumers can be merged.

Normal `build.sh` verification passes all nineteen rows (548 summed ledger
bytes, sixteen distinct address/extent pairs) and six string literals. Four
pre-existing names share the 19-byte body at 0x005CFBC2; no row or alias is
added. Every non-debug COFF section, byte and relocation target is preserved:
25 sections, 633 bytes and ten relocations, with unchanged external symbols.
The first acceptance required a direct ICoord2D.h include, rather than only
its companion include; adding that explicit dependency preserves the same
object facts. The owning acceptance then retires one ICoord2D queue item.
Ordinary link preview against census index 47e030bafc retains LINKS,
491 to 491 authored bytes. It is not a new census measurement.

Local receipts: `build/codex-cleanup-20261025/iteration38-before-build.log`,
`iteration38-after-build.log`, `iteration38-accept-direct.log`,
`iteration38-link-preview.log` and the normal `iteration38-commit.log`.
The remaining ICoord3D adoption in this same file is a separate change.
No census, ownership or runtime improvement is claimed.

The normal commit `eb545529bd` passes 2,128 functions and 25 data rows
across 260 dependent sources, three STLport folds, 601 literals plus 63 empty
references, 786 floats and 232 imports. Converged-data enforcement finds
zero second names and zero unjudged rows. The separate nineteen-row owner
repeat has no EH-bearing row and is not added to those totals. Independent
review also preserves all 27 external symbols and 25 section auxiliary
records, including COMDAT selections and associations.

## ICoord3D in the same owner

The following change on `eb545529bd` removes this file's remaining private
ICoord3D declaration. `ICOORD3D_VIEW_MATH_METHODS` exposes the three existing
assignment, length and zero declarations in the canonical header; the
contract records their owners at 0x0000353A/18, 0x00004D95/58 and
0x00004DCF/11. Other consumers retain their existing implicit assignment.
Fields remain x/y/z at offsets 0/4/8, size 12, with no bases or virtual slots.

The canonical header already provides the same empty inline default
constructor, so its duplicate, unused out-of-class definition is removed
from icoord.cpp. The default constructor's pre-existing folded row stays
with its real caller in Rva00261723.cpp at 0x0047A6A9/3. The component
constructor's inline body and its existing emission anchor remain unchanged,
as do all arithmetic bodies and the equality anchor. No new body, row,
alias, marker or hatch is introduced.

Normal verification again passes all nineteen rows and six literals;
complete object comparison preserves the same 25 non-debug sections,
633 bytes, ten relocations and external identities. Frozen checks pass.
The owning header acceptance retires the ICoord3D item. All currently
queued header and Microsoft-header items for icoord.cpp are now drained;
its two existing emission anchors remain a distinct cleanup concern.
Receipts: `iteration39-after-build.log`, `iteration39-accept.log`, and the
normal `iteration39-commit.log` under the same local receipt directory.

The normal ICoord3D commit gate completes in `ecfe0c5a6b`: 348 functions and
five data rows across 32 dependent sources, 142 literals plus nine empty
references, 57 floats and four imports. Converged-data enforcement again
finds zero second names and zero unjudged rows. Independent review preserves
all 27 external symbols and 25 auxiliary records, including COMDAT; neither
the old nor the new owner object emits the empty default constructor.

## Publication preparation on d0aba6dd78

The rebase preserves both coordinate headers, their contracts, icoord.cpp
and the complete GameClient/SubsystemInterface change byte for byte. The
three final code commits are `aea99c6a01`, `1b07d6bbad` and `d1f11a6f03`.
The upstream Skirmish-pointer repair overlaps the earlier PR work; its
three declaration conflicts differ only in whitespace, and the upstream
format is retained. The owning Microsoft-header scanner resolves six
historical INI queue conflicts while retaining all unrelated upstream rows.

A normal build of 48 rebased sources and replacement providers passes
513 functions, ten data rows, two STLport folds, 172 literals plus nineteen
empty references, 57 floats and 27 imports. All ledger objects now exist
and the INI provider is current. `check_csv.py` passes 98,271 function rows,
15,658 symbols and 2,217 data rows. Receipts are `iteration39-rebase-build.log`,
`iteration39-rebase-build-sources.txt` and `iteration39-preflight.log`.

The required PR-local path audit covers all seven absorbed INI sources:
61 references remain comments or historical evidence, with no active
consumer. The supplementary audit from published `9839a436af` also covers
32 paths removed by upstream, with 213 references. It identifies pre-existing
active stale entries outside this PR's moves: the Microsoft-header queue's
Rva0048B256AnimateGridDecals.cpp entry, two absent StlSweepW5 sources still in
tu_map.csv, and the StlSweepW5Rva005FE3C1.cpp linking-target row. These require
their owning maintenance lanes; they are recorded, not silently erased or
counted as retired debt. Other matches are comments, naming history or paths
in the separate BFME 1 namespace. Receipts are `iteration39-pr-path-audit.log`
and `iteration39-outgoing-path-audit.log`.

Fresh `progress.py origin/master` retains BYTE-MATCHED 100% and C++ exact
7,984,346 bytes (+0). The now-current census is d1f046749a at 13:18:
LINKING 7,322,361 and LINKED 7,567,229 bytes. Its decline predates the
independent Skirmish repair; neither local previews nor these header
adoptions update the census. No runtime or ownership result is asserted.
