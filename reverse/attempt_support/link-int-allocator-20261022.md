# Integer hashtable allocation provider

At BFME2 da2ff11ed3 plus the retained local repair commits, the current
legacy preview of stlport_hash_map_int_resize.cpp has one blocker: its
_STLP_alloc_proxy<void**, void*, allocator<void*> >::allocate copy differs
from the first copy in link order. The vendor allocation body is preserved
as an imported force-inline specialization. The matched resize inlines it
without an import relocation; outlined calls bind to the shared provider.
No allocation semantics, types, flags, pins or ledger claims change.

Before: 0/244 authored bytes link. After: 244/244 authored bytes link against
published census 08160bc2c9 (2026-10-22 17:08 UTC). This is a legacy current
object preview, not a closed-strict gain. build.sh passes 1/1, including
string/float/import checks. link_check --prepare-current supplies a strict
reusable source receipt; --new-variants passes.

Sweep: the census lists only DamageFX_hashtableResize.cpp and
StlSweepW4Rva00056BFE.cpp with the same allocation blocker. Both have other
blockers and prior byte-failing suppression trials (re_attempts 81694 and
81677); this change does not resolve their prerequisites. Do not repeat
those trials unchanged. BFME1 input remains the verified pointer 37c3022de1;
its newer pointer update is separately claimed. No donor update is asserted.
