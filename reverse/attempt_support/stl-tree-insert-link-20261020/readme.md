STL int/AsciiString tree insert ownership, 2026-10-20

At BFME 2 44d0196f61 the hint and unique insert consumers instantiate the same
renamed _M_insert_005014FF as its existing explicit-specialization owner.
Declare that specialization in both consumers before their explicit insert
instantiations. This removes their competing definitions while retaining the
real owner; no row, pin, provider body or shared header changes.

Target evidence: existing rowed callers at RVA 0x501BD8 (294 B) and 0x501587
(134 B) call the owner RVA 0x5014FF (136 B), with that relocation preserved by
the full byte gate. Existing source records its STLport provenance. The BFME 1
reference reviewed at a2c8039e61 supports declaration-only ownership as a
linking technique; its layouts and addresses are not imported.

Paired legacy check in proof.json refreshes just these three current objects
into two independent copies of the identical published b73720bed9 index
(SHA-256 recorded), with saved original objects for the before phase. All three
formerly failed on the duplicate _M_insert definition; all three now have zero
unresolved, duplicate, wrong COMDAT, address or selected-provider blockers.
Unique source-byte metric: 294 + 136 + 134 = 564 B newly linkable. The index,
link_status.csv and census history are unchanged. This is a legacy prediction,
not a closed-strict or actual full-link gain.

Before/after link_check.py --prepare-current on the same three explicit safe
providers passed 3/3 rows with self-strict receipts; ordinary build.sh passed
3/3, no EH rows, frozen-source and class gates passed. The unchanged owner is
included in preparation and the paired measurement. No compiler flags changed.
