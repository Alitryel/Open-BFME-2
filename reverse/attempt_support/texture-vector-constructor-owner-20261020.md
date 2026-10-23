# Texture-vector constructor ownership repair

The explicit `DynamicVectorClass<BfmeHandleCX>` instantiation in
`MaterialCollectorDestructor.cpp` emitted a size constructor competing with
the existing matched owner in `DynamicVectorBfmeHandleCtor.cpp`. Fresh paired
link checks found that this kept the owner's 46 bytes at `0x0016FE00` out of
the link, while the collector's 1,322 matched bytes already linked.

The measured owner forwards to the texture-vector base constructor at
`0x0016ED80`, installs vtable `0x00BD4688`, and sets the vector's count and
growth step. The generic instantiation in the collector expanded a different
base-constructor body. A declaration-only specialization in the collector now
leaves the size constructor to its existing owner. This changes neither the
owner's source nor its ledger row.

MSVC 7.1 stops emitting the collector's vtable and matched deleting destructor
when the size-constructor specialization is declared. An uncalled static
function that copy-constructs the vector retains those required artifacts.
Object inspection confirms that this anchor itself is not emitted, that the
competing size-constructor symbol is absent, and that the copy constructor,
vtable and matched scalar deleting destructor are present. The existing source
already uses an analogous compiler-instantiation anchor for its VCI helper.

Alternatives tested:

- The specialization declaration alone preserves the other collector rows but
  omits its matched deleting destructor at `0x001708B0`.
- An uncalled virtual-delete anchor does not restore that definition.
- An explicit template copy-constructor instantiation is accepted by MSVC but
  does not restore the vtable or deleting destructor. The retained static
  copy-construction anchor is required for this compiler.

Validation at BFME2 `413ecd9e74b1c122e930f26a1f9d3099f4ad6d20`, pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`:

- Paired `./build.sh` passes all 26 existing rows (25 collector, one owner).
- `eh_verify.py` reports three exact collector EH graphs and no baseline debt.
  Compiler funclet label renumbering is resolved through their parent graphs;
  no ledger labels or extents are changed.
- Fresh paired `link_check.py` changes 1,322 linked bytes to 1,368, with both
  sources clean and no new COMDAT blockers, against published census
  `5366c4f808` from 2026-10-20 12:21.
- `find_declared_unmatched.py` reports all defined functions already matched.
- `place_bodies.py` finds no new collector bodies or pins.
- Independent review checked the final source and object-symbol evidence.

This repairs 46 already matched bytes of linking coverage. It adds no new
recovered retail bytes and introduces no new pins or symbol aliases.
