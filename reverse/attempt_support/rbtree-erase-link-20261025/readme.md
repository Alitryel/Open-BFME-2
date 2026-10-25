# Rva0027EA49 tree erase link repair

The six existing rows in `stlport_rb_tree_rva0027EA49_erase.cpp` total
302 authored retail bytes. Whole-class instantiation also emitted insertion
paths referencing the declaration-only `_M_create_node` specialization.
No provider for that specialization exists in the current index.

Instantiate only the rowed `_M_erase`, `clear` and three `erase` overloads.
The rowed `_Destroy` helper is still emitted. Remove the unused allocation
specialization declaration. No type, layout, identity, callee pin or body
semantics change is claimed.

Paired legacy previews against retail-truth-4 census ce1b975697
(2026-10-25 03:51) show 0 -> 302 linked bytes. The blocking name occurs in
only this unit in the ranked census. All six rows pass the byte gate;
bounded current-provider preparation produces strict reusable receipts,
and new-variant and declared-definition checks pass. This is a legacy
preview gain; neither a closed-strict gain nor a full link-cycle result.

The same session's readonly rehome scan found four exact placements, all
already marked linked in the current published census, so none was moved.
String-replacement work remains blocked by the existing template-name
admission prerequisite (attempt 83639 and its 2026-10-24 handoff); no
source trial was repeated.
