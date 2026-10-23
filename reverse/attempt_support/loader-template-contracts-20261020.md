# Loader template contracts after 4a30e2c909

This is a linking repair, not new C++ byte coverage. The existing loader
307EDC/372 and caller308050/90 remain exact; both EH records are exact.
The census-based preview improves from seven blockers to three but still
reports LINKED0->0. No closed-strict or linked-byte gain is claimed.

The private vector view made _M_clear, _M_set and _M_insert_overflow public.
STLport's real declarations make these protected. In particular this changed
the growth callee's name from the existing IAEX owner to an unresolved QAEX
name, although the fill helper otherwise reproduced all179 bytes. Restoring
the access contract and the existing owner's target-observed zero-allocation
guard produces the complete native136-byte growth worker and179-byte fill
worker, with every call resolved. Bodies are reused from the already-verified
stlport_pod_vector_bodies.cpp, preserving copy/fill/release behavior. POD copy
sites use the same rowed __copy_trivial helper directly, and an external
instantiation declaration removes an unused __uninitialized_copy copy.

Allocator rebind/allocate and base destruction retain their actual header
operations as inline-only definitions. The implicit vector destructor must
remain available to the parent EH graph: declaring it imported creates an
unresolved import, while removing its body changes the loader. Its actual
14-byte body instead passes pin_admission's full-body proof against every
owner at7FAB3, including all relocations. That fold pin records the typed
cleanup the native parent already calls; char remains a one-byte element view.

The char fill interface is the existing48-byte owner at237C0. A TU-only header
adapter names the untouched header fill implementations bfmeLoaderHeaderFill
while including _algobase.h, then declares the real external char fill. The
recovered functions call the real _STL::fill; no renamed helper is pinned or
emitted. This avoids exporting a competing18-byte optimization of the same
name. This is declaration selection, with no changed shared header or runtime
fallback. The loader and the whole179-byte helper still match after it.

Remaining preview debt:

- allocator-proxy copy constructor differs from the census's first copy;
- this O1 unit emits31-byte proxy swap, while retail selects the proven34-byte
  Od copy in stlport_vector_voidptr.cpp;
- the census keeps a wrong fill_n<unsigned int> copy (first stlport_rope_char,
  then stlport_narrow_string, then stlport_pod_vector_bodies).

Native proxy swap34 has no calls; the O1 copy31 calls the implicit proxy copy
constructor. Making swap opaque, before or after the loader definition, loses
non-escape analysis and makes the loader376 bytes. An explicit inline-only copy
constructor also produces376. External copy-constructor instantiations retain
the implicit emitted copy. Capacity-member projection through the actual
four-byte proxy likewise gives376. Scalar char-pointer swap is not an ICF
alternative: its existing name owns357A0/19; do not pin it onto25AD0/34.
MSVC13.10 refuses noalias with C2485. These controls were scratch-only.

Source/settings reference: verified BFME1b3cc6b1588f2; actual _vector.h protected
sections, _alloc.h operations, and BFME2's matched word-vector inline-only
pattern were reviewed. No decoder reference, runner, tool or gate was changed.

Evidence: build/loader-inline-contracts-oct20/, loader-canonical-overflow-oct20/,
loader-fill-view-oct20/, loader-late-externs-oct20/ and
loader-projected-proxy-oct20/. The final preview is
loader-fill-view-oct20/link-preview.txt. A source patch against4a30e2c909 is
retained beside this note. Normal verification commands are build.sh on the
loader source, eh_verify.py on that source, and explain_mismatch.py on the
179/136-byte helper names at7FE65/7EA1F. No duplicate body rows were added.

Time about17 minutes; model gpt-6.1-sol.
