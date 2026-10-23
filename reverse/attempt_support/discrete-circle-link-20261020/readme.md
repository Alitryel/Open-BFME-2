DiscreteCircle link repair, 2026-10-20

Paired legacy link_check against census e7a7769fe5: DiscreteCircle 0 -> 317
nonpadding authored bytes; the reserve provider stays linked at 170 bytes.
This is a legacy prediction with strict byte receipts, not a closed-strict gain.

Retail constructor at 0x002DF93D calls reserve at 0x003B0224. The rowed owner
is vector<BfmeE12>::reserve, whose three-int POD element and three-pointer
vector storage agree with HorzLine. Bind through that existing ABI view;
compile-time size checks document both assumptions. The target call and all
other bytes remain exact. No new pin or alternate symbol is added.

Use the existing static STLport configuration and declaration-only
__node_alloc<true,0>::allocate specialization to avoid an allocator IAT
reference and a competing node-allocator policy copy. A false-thread template
declaration did not suppress the actual true-thread specialization; corrected
from the mangled name and STLport thread macro. No helper policy is changed.

Acceptance: build.sh 5/5 exact, prepare-current on consumer plus reserve
provider 8/8 exact with strict reusable receipts; EH EXACT 1. Declaration gate
passes. The census has no other consumer of the HorzLine reserve copy. Legacy
unreferenced allocator-proxy deallocate diagnostic remains exempt under
retail-truth-2. Original source donor identity/provenance is unchanged.
