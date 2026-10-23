# Containment-list helper ownership

The three compiled callers of HordeTransportContain::rva00463A4D already use
ContainmentList (the shared opaque Rva0036ADF9Element list). The helper's private
list<int> declaration emitted another name at that address, leaving the real
callers unresolved. Existing symbols.csv already pins the opaque signature at
0x00463A4D. The rowed copier 0x0036ADF9, its insertion chain and destructor
0x004EC395 establish the one-word element/list implementation; they do not
establish a concrete application element identity.

The provider now uses the shared header and the rowed opaque destructor. Its
52-byte body and 10-byte EH handler stay exact, with their owning ledger names
updated together. No alias or new pin is introduced. The 0x00477513 caller also
uses a local scalar placement-copy overload before the list header, removing its
wrong external _Construct<int,int> COMDAT while preserving its two rowed bodies.
A source search covers all three compiled callers plus the unused home-unit
declaration. BFME1 a2c8039e has no corresponding recovered opaque helper.

Paired preview against unchanged published index b73720bed9 (2026-10-20 05:34)
changes the four-unit cohort from 62 to 527 linked non-padding bytes: +465 bytes,
two newly linking units. SiegeEngineContainDtor still has a selected wrong
TransportContain destructor; its 292 bytes are excluded. The scalar caller's
three unreferenced deallocate differences are diagnostic under retail-truth-2.
proof.json records the index hash and paired findings.

Acceptance: edited units 4/4 byte exact with strict self receipts; unchanged
callers 10/10 byte exact; EH 2/2 exact; data enforce and converged pass;
check_csv, pin_consistency for the existing helper pin and declared-unmatched
pass. This is a legacy-index preview gain, not a closed-strict gain.
