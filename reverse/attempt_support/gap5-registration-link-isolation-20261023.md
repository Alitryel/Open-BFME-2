# Registration constructor link isolation

Base 52d1653b6f; published census 0393df10e2, 2026-10-23 19:47,
retail-truth-4. The indexed GapBodiesSeat5A unit excluded all 592 nonpadding
bytes because the virtual slot0 providers for Rva005C43CFRegistration,
Rva005C459ERegistration and Rva005C47F0Registration are unresolved.

Move those three existing 24-byte constructors and their unchanged private
views to GapBodiesSeat5ARegistrationDeferred.cpp. Preserve compiler flags,
row notes, base call 0x0052B894 and vtables C745A0/C74698/C7475C. No new
body, pin, identity, layout or virtual-slot claim. The target evidence remains
address-derived as recorded in the existing rows. BFME1 f5140c1cff6a and
existing BFME2 independent-body isolation repairs were reviewed; this repair
uses the established BFME2 isolation pattern, not a new donor identity.

Paired legacy current-object prediction for the indexed original unit changes
from excluded to LINKS, 0 -> 520 B after moving the ledger rows. The deferred
unit is absent from this census and receives no credit. Its three slot providers
remain unresolved. This is not self-strict, closed-strict, a census measurement,
or an executable link. New authored C++ bytes: zero.

Acceptance: all 24 existing rows remain byte-exact across both units, with
string/float/import verification, declared-definition and ordinary commit-hook
checks. No verifier, baseline, shared header or pin changes. Scratch evidence:
build/link-seat-gap5/{original.cpp.txt,original-rows.csv,before.log,after.log,
prepare.log,prior.txt}. Other isolation siblings were investigated in the
weather and B07 handoffs; already-clean provider overlays receive no repair
credit. The published index predates these repairs; whole-current-ledger strict
closure remains blocked by missing/stale receipts (11,864 at the reviewed tree).
