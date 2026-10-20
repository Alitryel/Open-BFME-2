# FindPath: ownership and genuine floating context controls

Native 2FD344..2FD651 is 781 bytes, RET20. The complete existing bank patch,
whole current owner, all prior records and the last whole-function latch study
were reviewed. No production source or bank changed. Baseline is still 781
bytes, no unresolved calls, four differing operand bytes: reload x then y at
+1C1/+1C6 instead of native y then x. The other nine reported memory lines
are relocations. The native FindPath name/ABI and WB relationship are the
earlier target evidence; STLport ownership and mutator forms below are source
models, not newly asserted original target types.

New tests address the prior finding that genuine by-value float calls can
change the whole-function XMM order. Twenty-two valid normal diagnostic
outputs include the replayed baseline:

- Actual STLport auto_ptr<Rva0053476A>, both direct get and a cached typed
  pointer, emits a 23-byte destructor matching the native holder at 2EAD62
  (auto-ptr-proof.txt). The parent becomes 777 bytes by losing an EH-state
  store, and its latch stays x,y,z. Pointer-base/set/get ownership views keep
  781 and the same latch. No alias or provider was added for this proof.
- Four native Coord3D::set(float,float,float) contexts (destination, delta,
  adjusted or all copies), three ordinary XY-comparison interfaces, and two
  combined setter/comparison cases all retain x,y,z. Adjusted's by-value
  setter also changes earlier load order; no closer candidate.
- The existing logging call through six float or double value parameters
  produces 813 bytes. A two-point reference logging helper stays 781 with
  the old latch. Output, format, promotions and required calls are preserved;
  no dummy effect was inserted.
- The newly successful Coord3DCtorView used by port-transform recovery was
  tested as a shared explanation: constructors alone, inline mutators, and
  user copy construction for each of destination/delta/adjusted all give 781
  and the same latch. The whole owner initially cannot compile with this
  view because two unrelated local unions require POD Coord3D. For these
  five diagnostic outputs only, those unions were changed to structs with
  separate member storage. Other functions' bytes were not verified, and
  those sources are not proposals to land the whole owner. The five initial
  compiler refusals and five valid isolated FindPath results are distinct.

Replay scripts reconstruct the complete current owner with the existing bank;
they use only normal explain_mismatch and align_diff CLI calls and isolated
build/ objects. No volatile, padding, barrier, equal-arm expression, new pin,
alias, class contract or gate change. The bank and score are unchanged.

Post-pull reference refresh: BFME1 ranked/near zero free candidates; ZH 1112
exact placements all claimed and zero viable packets. A fresh live address
scan finds no literal consumers of the eight converged engine globals;
name_globals --dry-run finds zero repairs. The recorded mapper duplicate and
StringRecordCopy list blockers are stale census findings already repaired
upstream; current source previews must precede planning such work.

Model gpt-6.1-sol, about 12 minutes. New replay drivers/results are retained
here; all individual compiler logs and sources remain in the named build/
directories. Further parent work needs a different supported allocator input.
