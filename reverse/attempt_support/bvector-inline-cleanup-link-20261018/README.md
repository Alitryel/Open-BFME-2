# Bool-vector inline cleanup linking repair

Recovery reconciliation: upstream commit `fb378110f1` already landed the
four equivalent source specializations. The rebased commit retains only this
historical verification and the deferred PlayerTemplate evidence; it claims
no additional linked bytes over upstream. Upstream source blobs are retained.

At HEAD 79d9498351, four units fail only on the external copy of
`_Bvector_base<allocator<bool> >::_M_deallocate`. The published index is
2967eab33e (2026-10-18 08:17, retail-truth-2). This name has no retail
address, but the index reference walk reaches it from the kept bool-vector
and base destructors, so it is a live first-copy conflict rather than an
exempt unreferenced copy.

Each unit already inlines the vendor STLport 4.5.3 cleanup into its matched
body. A TU-local dllimport/forceinline specialization preserves that exact
vendor operation and prevents an external competing copy. This is the
existing inline-only specialization pattern used by the Image map unit.
No new function identity, pin, alias, layout, or retail bytes are asserted.

Paired current-object `link_check.py` previews: 0/4 units, 0 B before;
4/4 units, 1,057 B after (reserve 147, insertion 392, assignment 209,
Xfer 309 including the 26 B iterator row). These are LEGACY index preview
gains, not a closed-strict or self-strict link-closure measurement.

`link_check.py --prepare-current` independently verifies all 5/5 rows and
writes strict reusable byte receipts. String 2/2, float 0 and import 0
checks pass. Source-claim checks pass. This receipt step does not establish
link closure.

The four source blobs were unchanged between the census revision and the
pre-repair HEAD. Comparing emitted COMDAT byte-and-relocation digests to
the census copies: 551, 566, 17, and 38 retained definitions respectively
are unchanged; no additions or changed retained definitions. Each unit
removes the cleanup copy and three now-unused allocator wrappers
(`_STLP_alloc_proxy<unsigned*>::deallocate`, `allocator<unsigned>::deallocate`,
and `__stl_alloc_rebind<unsigned,unsigned>`). No new external references to
the cleanup name are emitted.

The concurrent PlayerTemplate declaration-only/extern-template experiment
was reverted after three of nine rows changed; its separate blocked log
entry records that prerequisite. GameInfo's pre-existing register-preservation
deferral also remains unchanged; no repair is claimed there.
