# Transaction registry providers

Paired current-object `link_check.py` against the published census 17918792f6
(2026-10-21 09:22) changes the two edited units from zero linked bytes to 2,639:
1,386 in `Rva007B55E0TxnNameInits.cpp` and 1,253 in
`Rva007E9A50Lookups.cpp`. The former includes the newly rowed 25-byte ICF twin
of the existing CollisionTestClass constructor; this is a per-unit prediction,
not a claim of 25 new unique recovered retail bytes. No closed-strict closure
or full census/link cycle was run.

The initializer unit had 56 undefined record globals and an undefined
constructor. Its 62 native initializer calls identify each destination and
supply the service-type and transaction-name pointers. The target constructor
at RVA 0x65D070 stores the two arguments at +0/+4 and zero at +8; the compiled
C++ reproduces its complete 25-byte body. `add_match.py --icf-owner` records
this independently verified folded definition without adding another pin. The
record's original class/name remains unrecovered. Contiguous 12-byte record
spacing and the three constructor fields support the existing layout. Each
new record's complete 12-byte initial retail span is zero and owns no previous
data-row range. Existing canonical TheRankUpdateStatsTransaction is reused;
its pre-existing sole data_ledger ownership is now also backed by a data row.

Each lookup's two native absolute operands identify one registry table. Decode
all pointer entries through the first null terminator, then define that whole
array using the existing initializer unit's record symbols. The tables are at
VA DD7F50 (21 pointers including null), DD80B0 (11), DD80E0 (3), DD80F0 (12),
DD8124 (5), DD813C (12), and DD8174 (5). The lookup prefix view only reads the
independently target-proven name pointer at +4; casts preserve the one global
per record instead of introducing another spelling for the same storage.
The donor's address-derived lookup/table identifiers are retained and are not
asserted to be original BFME 2 names. Existing donor provenance stays in source.

Acceptance: byte gate 70/70 code rows and 76/76 data rows, with 69 literal refs;
data_rows integrity, check_csv, find_declared_unmatched, and converged data
checks pass. `link_check.py --prepare-current` supplies strict reusable self
receipts for both units. The measured gain above is the legacy per-unit link
prediction against frozen peers, not a closed-strict gain.

The first hook also exposed two pre-existing 4-byte integer definitions in
BfmeConv1871.cpp at the fsys/Ping and fsys/Goodbye record addresses. Remove
those definitions and make the registration consume the already rowed typed
records instead. The 67-byte registration remains exact and linked before
and after; this is a provider-convergence prerequisite of the registry repair,
not an additional claimed gain. The three-unit prediction is 67 -> 2,706 B,
so the net gain stays 2,639 B. The extra unit passes its own byte gate and
strict self receipt. The committed derived data ledger still carries old
provisional aliases; a read-only regeneration is in build/txn-data-ledger-current.csv.
