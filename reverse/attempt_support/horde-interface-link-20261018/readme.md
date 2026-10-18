Horde secondary-interface link repair, 2026-10-18

At BFME2 ee446917ca, published census c2c5ac8c27 (retail-truth-2), the two
Horde constructors have only one unresolved name: g_00C50868. Their current
objects reproduce that finding before the change; this is not credit for
refreshing an already repaired census entry.

Target evidence: rowed constructors 49A7F3 and 49AD15 install C50868 at +3E4.
The matched destructor 49A64B and existing secondary overrides 49A8A1/49A8FA
independently establish the complete-object +8 Object member as secondary-this
minus 3DC. Native 49A880..49A8A1 is a whole 33-byte query through Object+250,
provider slot7C and optional provider slot18. An explicit null early return
reproduces retail; the equivalent conditional-expression trial only reordered
its two return blocks and was replaced.

Data: all 20 pointers in C50868..C508B8 are bound to existing whole-byte owners,
including the new slot0. No new pins, aliases or claimed application identities.
The constant/no-op folds deliberately retain their code owner's names. Data-row
verification proves all 80 bytes and 20 relocation destinations.

Measurement: identical explicit three-unit list, unchanged census/index:
legacy local LINKED 154 -> 454 (+300 code bytes). This consists of 267 existing
constructor/EH bytes newly linking and 33 newly recovered query bytes. All three
units are clean. The changed provider was clean before the change. Authored
C++ grows 33 bytes; defined target data grows 80 bytes.

Acceptance: prepare-current provides self-strict reusable receipts for all
three explicit units, 7/7 rows; data 1/1; EH EXACT 2/2; declared-unmatched clean;
converged-data check zero second names across 9 addresses; check_csv clean.
These are scoped self-strict object gates and paired legacy link predictions.
No closed-strict closure, census update, link.exe cycle or runtime claim.

Donor review: BFME1 64d369b90170b7e9ec917d646f020b11f13eb0d5 remains the verified
input. Upstream link repairs 06a23066c, 4f7c322cd, f718d5183, 5c363dc06 and
95ca17f14 were inspected as guides (canonical declarations, provider naming,
rehome and StringBase reconciliation); this target-specific interface table
has independent retail evidence and does not import a donor layout.
