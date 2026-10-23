# Overflow placement-copy binding

At parent e063e879cc, the published b73720bed9 census (2026-10-20 05:34)
plus the current object reports StlportVectorOverflowRva004DA181.cpp unlinked:
its only blocker is the unresolved _Construct<Rva004DA181Element> spelling.
The original declaration has a candidate pin at RVA 004D9B98. The ledger's
real owner there is _Construct<BfmePod340>, 45 bytes, emitted by
StlportConstructFamily.cpp. Target overflow 004DA181/191 and its helper
chain already establish this shared call address and the 0x154 element
stride. The concrete application type/layout is still not asserted here.

Bind the pointer-preserving copy call with a TU-local overload declared
before vector's template definitions. Its target is the existing rowed
_Construct<BfmePod340> specialization. Keep the opaque polymorphic element
view used for the separately rowed virtual-destroy helpers. No pins, flags,
ledger rows, aliases or data definitions change.

A first inline-specialization trial passed all four byte rows but emitted
an out-of-line wrapper with the old pinned name; link_check correctly
refused that non-retail COMDAT. Replacing it with the static overload removes
that external definition while preserving the rowed bodies. No bypass or
verifier edit is involved. Scanning the recorded rank found no other unit
with this unresolved spelling. The older BfmePod340 allocate/copy unit has
multiple different COMDAT/selected-definition blockers and remains untouched.

Checks:

- ./build.sh on the changed unit: 4/4 rows, string/float/import checks pass.
- find_declared_unmatched: all definitions already matched.
- link_check on changed unit: 0 -> 274 bytes, clean (legacy local prediction
  against the published census; no self-strict or closed-strict gain claimed).
- Unchanged StlportConstructFamily.cpp provider: 899 -> 899 bytes, clean.
- link_check --prepare-current on consumer and provider: 40/40 rows, strict
  reusable byte receipts; no census, placement or closure measurement changed.

Rebase reconciliation: upstream 61c02fb746 independently landed the same
binding before publication. Keep its implementation; the 274-byte improvement
is already upstream and is excluded from this seat's new linked-byte total.
The verification above independently confirms the shared repair.
