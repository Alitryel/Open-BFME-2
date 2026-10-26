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
