# Opaque vector placement-copy binding

StlportVectorOverflowRva004DA181.cpp's only published-index blocker was the
unresolved `_Construct<Rva004DA181Element>` spelling of target 0x004D9B98.
The existing overflow row documents that direct call, and the rowed provider
StlportConstructFamily.cpp owns it as `_Construct<BfmePod340>` (45 bytes,
placement copy through constructor 0x001E4DEB, with its rowed EH graph).
Neither opaque name establishes the application's concrete record identity.

A TU-local overload installed before vector headers casts the opaque receiver
and argument to the existing helper's view. It inlines completely: all 15
external COMDAT names and all their bytes remain identical. The only relocation
changes in overflow, uninitialized-copy and uninitialized-fill-n replace the
unresolved helper name with its rowed owner; offsets and relocation types agree.
An initial inline template specialization emitted a conflicting wrapper, so
it was replaced with this static overload; no alias, pin, or wrapper remains.

Paired preview against unchanged index b73720bed9 (2026-10-20 05:34) gives
0 -> 274 linked non-padding retail bytes, one unit. proof.json contains the
index and objects' hashes and before/after findings. A same-name source search
found no other consumers of this missing specialization to sweep. Existing
reserve already binds these two emitter views through explicit casts.

Acceptance: ./build.sh 4/4 rows exact; strict self preparation current;
link_check clean; EH reports no EH-bearing rows and no missing objects;
data_check --enforce and --converged pass; declared-unmatched passes.
This is a legacy-index preview gain, with self-strict byte evidence; no
closed-strict gain claimed. BFME1 a2c8039e has no corresponding opaque unit.
