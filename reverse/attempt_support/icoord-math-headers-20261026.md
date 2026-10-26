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
