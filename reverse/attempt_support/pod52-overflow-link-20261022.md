# Pod52 overflow ownership, 2026-10-22

Input tree 6da142cb94; verified BFME 1 donor remains
42bba2ddbd5cb895d99293583891d3b7315fa49e. Frozen published census
08160bc2c9, 2026-10-22 17:08. This changes emission and row ownership;
it establishes no new application identity for the size-only Pod52 view.

The EH-profile stlport_pod_vector_bodies unit emits a non-retail overflow
copy before the verified no-EH owner (RVA 0x001DE402). Declaration-only
suppression initially changes the rowed push_back from 55 to 58 bytes:
its compiler-visible callee register summary matters. The no-EH provider
can emit the whole native 55-byte push_back with the correct overflow call.
Explicitly instantiate it there, move its existing 0x001DE7D8 ledger row,
and stop instantiating it in the EH-profile unit. Then the EH-profile
unit can declare the overflow specialization instead of supplying a copy.
No pins, aliases, flags, or type layout changes are required.

Paired current-object legacy link_check over stlport_pod_vector_bodies,
stlport_pod_noexc_bodies, and stlport_pod52_fill_insert_1de5d2 reports
0 -> 221 linked bytes, with total matched bytes unchanged (10,110 B).
The fill-insert unit is now clean. The two broad units remain blocked;
the three Pod52 wrong-selected findings disappear but their independent
COMDAT, selected-provider and unresolved-name findings remain. The census
contains no other unit blocked on this overflow name. This is a legacy
prediction, not a closed-strict gain.

Normal build.sh verifies all 180/180 rows in the cohort, and both edited
source files pass find_declared_unmatched. Strict provider preparation
verifies the same explicit cohort; it does not measure LINK closure.
