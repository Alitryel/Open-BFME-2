# PerFrameStats resize isolation

Base 759b3558ab, published census b711de3634 (2026-10-23 14:28,
retail-truth-4). Current-object legacy preview before editing excluded all
162 nonpadding bytes in ScoreKeeperPerFrameStatsVectorResize.cpp: the
constructor emitted a conflicting Rva0039B893 vtable and referenced unresolved
loadPostProcess, crc and xfer methods.

Keep the independent 96-byte by-value resize and its ten-byte EH handler in
the indexed unit. Move the existing 34-byte constructor and 33-byte default
wrapper, unchanged, to ScoreKeeperPerFrameStatsDefaultResizeDeferred.cpp.
The latter preserves the constructor-visible call shape and its non-novtable
record: suppressing that table would contradict the constructor's retail DIR32
store. It remains deferred pending canonical virtual providers and receives
zero link credit because it is absent from the census.

No identity, field layout, pin, flags or donor inputs change. Existing target
provenance (native 39D170, WB FA55B0 and C1AD6C) and BF1 ba7ddda resize lead
are retained. Reviewed current BF1 96c88c73a5cd and prior linking handoffs;
this follows the accepted CameraMarker and Armor isolation pattern. Reference
freshness remains blocked on the previously recorded full-gate import/float
regressions, rather than silently advancing the pointer.

After: original unit LINKS 0 -> 96 B in the final current-object legacy
preview (final-total.log). The existing ten-byte compiler EH handler remains
byte-exact and is excluded from linked C++ credit by its retained gen-ehstub
classification. The provisional 106 B result had omitted that ledger token.
This is not a self-strict or closed-strict link result or an executable link.
New authored C++ bytes: zero.

Acceptance: both units byte-exact 4/4 with strict reusable receipts;
string/float/import gates pass; EH EXACT 1/1; declared-definition, class gate
and new-variant admission pass. No verifier/baseline/shared-header changes.
Scratch before/after/strict logs: build/link-seat-stats-isolation/.
