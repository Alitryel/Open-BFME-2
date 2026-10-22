PartitionSolver assignment binding, 2026-10-22

Target facts: constructor 0x567348 is 127 bytes; both vector assignments call
0x1D9BEE. Its existing ledger owner is vector<BfmePod8>::operator= (177 B,
stlport_pod_vector_malloc_bodies.cpp). The historical typed assignment pin
already names this address. The constructor's two vector members and parameters
are vector<pair<ObjectID,unsigned int>>; both elements contain two dwords.
The established generic provider uses BfmePod8 { int a[2]; }.

Bind these two call boundaries to that rowed provider through the matching
trivial vector view. Preserve the class declaration and constructor signature.
This removes the competing typed assignment and allocator copies. No new pin,
alias, ledger name, or shared header. The ZH source remains the constructor's
semantic guide; BfmePod8 is the existing provider name, not a recovered
application element identity. The census lists this unit alone as blocked by
the typed assignment name.

Same-index current-object legacy preview (08160bc2c9, 2026-10-22 17:08):
0/1, 0 B -> 1/1, 127 B. build.sh and prepare-current: 2/2 exact;
prepare-current produced one self-strict receipt. EH 1 EXACT; new-variants and
find_declared_unmatched pass. No closed-strict or full-link gain claimed.
Diagnostics: ignored build/link-partition-{before,after,gate1,strict,variants,eh}.txt.
