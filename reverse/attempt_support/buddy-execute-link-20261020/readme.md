Buddy-thread inherited Execute
==============================

BFME2 input e0e3bd4763; verified BFME1 pointer 92f6bbe8e1dc.
Published census 5366c4f808 (2026-10-20 12:21), retail-truth-2.

Retail constructor 550F01 writes C6AC0C. That table's three entries are
551323 (deleting destructor), 6104B0 (rowed ThreadClass::Execute), and
552027 (rowed BuddyThreadClass::Thread_Function). The constructor view
incorrectly declared a BuddyThreadClass::Execute override, creating an
unresolved vtable entry. Remove that declaration to inherit the real base
method. No body, ABI, pin or row change is needed. The other indexed
Execute conflicts are not this same class/cause: W3DMouse uses a nonvirtual
base signature, and PeerThreadOpaqueConstructor has eight independent
findings. No unrelated view was edited.

Current-object legacy link_check before/after: 0 -> 230 LINKED bytes,
one unresolved finding -> zero. This is a legacy prediction, not a
self-strict or closed-strict executable placement result. Bounded strict
prepare-current before and after verifies 3/3 rows, no literals/imports;
EH EXACT 1, no missing object. Frozen/class checks pass; shadow data and
enforced converged-data checks have zero findings. place_bodies finds
zero additional bodies/pins. No census, link cycle, nightly or boot run.

Diagnostics: build/link-seat-buddy-{before-gate,after-gate,after,eh,place}.txt.
The before link result is in build/link-seat-near-fresh-more.txt.
