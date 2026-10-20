Standing-wave cache owner repair, 2026-10-20

Parent 817e6a6883; published legacy census 5366c4f808, 12:21 UTC.
Rva00082A53Ctor.cpp used obsolete query spelling and instantiated an EH copy
helper differing from the kept no-EH owner. Its native call at 82EAA targets
8026B, already rowed in W3DWaterStandingWaveQuery.cpp. That provider proves the
44-byte record interface. Declare the existing structural receiver/record names;
no new semantic identity or layout is asserted. The cache's existing target and
WB evidence remains unchanged. Declare the rowed vector reserve at 81A75 so it
uses its own no-EH allocation/copy owner at 7FB58. BFME1 checkout reviewed remains
92f6bbe8e1dcdb46b5d27da0674313efc822b790; this repair binds existing BFME2 owners.

Before and after use the same four explicit units and unchanged census index.
Cache 0 -> 304 bytes; query provider 968 -> 968; POD copy provider and main POD
vector provider remain 0 with independent COMDAT blockers. Total 968 -> 1272,
+304 bytes in current-object legacy preview. No closed-strict/full-link claim.
Scoped byte gate 4/4; self-strict provider preparation 158/158 with nine float
references. Declared-definition and canonical-class checks pass. No new pins,
ledger rows, shared headers or verifier changes.

The first declaration-only trial on _M_allocate_and_copy caused an MSVC C1001
inside reserve. Removed it and instead declared reserve, which byte-matches all
four rows. No failed reconstruction remains. Cause sweep found the same helper
in two large POD units, each held by many independent blockers, so no additional
positive repair is claimed. The query has no other obsolete-name consumer.
The unrelated NewMap blocker note records a newly matched footprint provider
missing from this published census: strict bytes pass but preview cannot include
it, so no unmeasured repair was retained.
