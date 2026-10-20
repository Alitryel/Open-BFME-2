# Record32 vector cleanup linkage

At census 5366c4f808 (retail-truth-2), the geometry caller at 4E3E91
instantiates a POD vector<Rva004E3E5AElement>. Its emitted _M_clear omits
record destruction; the growth TU calls that name, which is fold-pinned to
the native nontrivial cleanup 4E3C71. The pin's old fold-proof source did
not actually emit the complete native body. This causes wrong_selected in
the growth unit and several other competing helpers in the geometry caller.

Target facts: native push_back 4E3E5A steps 32 bytes and calls _Construct
4E2F27, whose copy call reaches 4E2C66. Native cleanup 4E3C71 calls the
record range destructor 4E377E then frees the begin pointer via 30830. The
existing rowed Rva004E3C71 provider establishes the destruction identity
Rva004E2382; the original record name and full layout remain unknown.
No donor identity or layout is newly asserted.

Use the same nontrivial opaque element view in the geometry caller and
call the existing rowed push_back instead of instantiating private helpers.
The committed caller change makes its three rows (88 nonpadding bytes)
link. The growth unit changes from wrong_selected to unresolved _M_clear,
with no linked gain of its own. Paired final preview: 0 -> 88 linked bytes.
Caller strict-current preparation passes 3/3; no closed-strict/full-link gain
is claimed. Frozen/class/data/new-COMDAT checks pass.

A complete cleanup candidate is preserved in growth-candidate.cpp.txt. It
explicitly specializes _M_clear with the established range-destroy/free
implementation. Its whole 30 bytes match retail (cleanup.txt), and its trial
cohort linked all three units: 39 -> 382 (+343). Strict trial gates passed8/8.
These are candidate results only. They were NOT retained in Code or counted
in the commit because another worker holds the 4E3C71 body claim. The existing
fold pin's proof source also needs reconciliation: the repaired geometry
caller no longer emits that helper. A trial note changing its proof source
to the growth TU was restored along with the candidate. Claimant can resume
from the preserved source, repeat the byte/relocation proof and update the
existing fold pin's evidence. No new pin or alias is needed.
