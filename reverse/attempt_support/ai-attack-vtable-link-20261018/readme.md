AIAttackState destructor view, 2026-10-18

Target evidence: the existing row ?isAttack@AIAttackState@@UBE_NXZ at
0x0034141F is identified by slot 8 of retail table C13B78. The already matched
constructor view Rva0034B0DDFinish.cpp declares this virtual, while the destructor
view omitted it. Add the same declaration without changing bodies or layout.
This reconciles the two emitted primary vtable copies. The index contains only
these two holders. It does not complete the provisional State virtual surface.

Acceptance: strict reusable receipts verify all four provider/consumer rows;
changed source 2/2 exact, parent EH graph 1/1 EXACT. Same-index paired legacy
preview at c2c5ac8c27 rises from 143 to 256 B (+113 B). This is legacy selection
measurement with self-strict bytes; no closed-strict or authored-byte gain.

Donor repair review: fetched BFME1 master67f4eab2437e8a7ab3f22d3b3f9bf1eac91e081b;
reviewed c42f040f declaration-only ShareBuffer dtor, 991da24d WeaponSet vtable
anchor, 06a23066 canonical UnicodeString and 67f4eab2 local helper rename.
This repair uses BFME2's existing row and constructor declaration, not donor ABI.
Verified gitlink64d369b9 retained: pointer update still needs the documented
full old/new baseline comparison (previously 2982 stale TUs); no freshness stamp.

Separate Debug net destructor trial: imported forceinline base dtor preserves
87B parent and 33B scalar wrapper, but EH cleanup becomes imported (5 bytes
at75CDEF differ). Restored it and recorded/released the blocker; no gain claimed.
