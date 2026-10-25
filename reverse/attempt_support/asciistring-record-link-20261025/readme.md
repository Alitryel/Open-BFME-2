# AsciiString record algorithm link repair

At BFME2 1eeeffb466, stlport_asciistring_record_bodies.cpp instantiated whole
STLport vector classes to emit 47 recovered APIs. The object also emitted
seven non-retail copies: two implicit record destructors, three allocate-and-copy
helpers, the 172-byte record destroy loop, and the 28-byte insert-overflow helper.
Those copies prevented every row in the object from linking.

Instantiate the recovered APIs individually. Isolate the four reserve/push_back
APIs that still need those non-retail dependencies in
stlport_asciistring_record_deferred.cpp, preserving their source, flags, existing
names, boundaries and call pins. Keep shared forward-copy/construct providers
used by other units; eliminating every unrowed helper would break those consumers.
No target application identity or complete layout follows from these size-only
emitter views. No new pins, aliases, annotations or data definitions were added.

The 24-byte _Destroy<172*> wrapper stays in the original object. Its target
worker at1EAF5E is independently implemented in Rva001EAF7BClear.cpp: it walks
0xAC-byte records and calls virtual slot0 with argument0. It reads first/last
only. Forward the existing unused tag argument through the native row name,
matching the already established 104-byte-record technique. The historical
int-array/AsciiString assignment view cannot establish native destruction.
The wrapper still passes its whole-byte and relocation gate.

Paired current-object previews against census ce1b975697 (2026-10-25 03:51,
retail-truth-4), recompiling original and repaired inputs at the same revision:

- Main object: 0 -> 1,396 nonpadding bytes.
- StlportVectorDtorDeferred.cpp: 461 -> 461.
- StlportVectorEraseRangeDeferred.cpp: 2,464 -> 2,464.
- StlportVectorInsertOverflowRva003A46FA.cpp: 221 -> 221.
- StlportVectorEraseRangeFamily.cpp: 614 -> 614.
- Total current-object comparison: 3,760 -> 5,156, **+1,396 B linked**.

These are legacy previews, not self-strict or closed-strict census gains or
executable placement. The new deferred unit is absent from this census and is
not previewable in its unknown link position; its four APIs total413 B, retain
the unresolved native copy/destruction dependencies and receive no link credit.
Do not replace this paired comparison with link_check's stale census baseline
of835 B. No maintainer-only runner was invoked.

Acceptance: both sources pass ./build.sh (43+4 rows), link_check.py
--prepare-current yields strict reusable byte receipts for47/47, new-variants
with staged peers passes, find_declared_unmatched.py and check_csv.py pass.
Scratch original/repaired gates, paired previews and source backup are in
build/link-seat-record/. The initial narrow experiment omitted shared copy and
destroy providers; restoring them was necessary before taking this gain.

Reference basis: pristine STLport4.5.3 already used here; committed BFME1
0bf534ea7ccde110c456edb9cd2dd5dae823c953 and its tracked October24 verified
update/reference-lane evidence were reviewed this session. This repair follows
existing BFME2 isolation/owner-binding evidence; no new donor identity is inferred.
