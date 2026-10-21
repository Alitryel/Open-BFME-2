Miles volume cleanup repair, 2026-10-21
======================================

Paired current-object legacy link_check previews at census c7845fd6e7
(2026-10-21 15:41): Rva006ABC60Destructor_Rva0005925E.cpp changes from
0 to 85 linked bytes. MilesAudioVolumeConstructor.cpp stays clean at 286.
The destructor's two ledgered cleanup funclets are folded with already
counted addresses; do not count their 36 bytes again.

Before: undefined Rva006ABC60VectorElement::~Rva006ABC60VectorElement.
After: actual STLport vector<BfmePod8> member array, declaration-only vector
and AsciiString tree destructors, and the existing native allocator shim.
The constructor at 0x0005A2E6 independently establishes six 12-byte vector
headers at +0x4c, opaque trivial eight-byte records and set header +0xa0.
Real tree size is 0xc (subsequent scalar starts +0xac); adjust padding so
the trailing helper remains +0x1b8. Keep its existing rowed qualified cleanup.
The source's historical Rva006ABC60 label is not a new identity claim.

The native array cleanup callback binds the existing 0x0007FAB3 vector
cleanup provider. No new pin or alias or original record type is asserted.
This is the same missing member-cleanup cause as the Render2D repair,
although the unique gain is below 100 bytes. The independent constructor
makes it a bounded repair within that sweep. The first compile lacked the
stlport source marker; adding that marker and using normal STL headers
corrected include selection. No failed source trial remains.

Acceptance: build.sh 3/3 rows (both funclet labels renumbered, independently
resolved by the exact parent EH graph); eh_verify EXACT 1; frozen-file
check passed. link_check.py --prepare-current on destructor, constructor
and Rva003FA62BDtor.cpp passed 16/16 rows with strict reusable receipts.
The two consumer units link cleanly, 286 -> 371 legacy bytes. Self-strict
receipts do not establish closed-strict closure; no closed-strict gain,
full link cycle or changed census/status is claimed. No authored C++ bytes
are added. Existing donor provenance remains in the ledger; BFME2 target
constructor evidence supplies this repair's layout and member relationship.
