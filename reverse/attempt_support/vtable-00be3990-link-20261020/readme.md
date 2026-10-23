Disp0DwordImmSetters.cpp predicted 0 linked bytes before and 337 after changing
its existing alternate binding from the undefined BfmeDualVtableReleaseBase
vtable to the emitted Rva00203E76 vtable. Measurements use the published
b73720bed9 census of 2026-10-20 05:34, with current objects for the consumer.
This is a legacy local prediction with strict reusable byte receipts, not a
self-strict placement measurement or a closed-strict gain.

Target evidence: retail VA 00BE3990 is a four-byte table containing 00603E76;
the next four-byte table begins at 00BE3994. InlineDtorDeletingDtorsC01.cpp
already rows the 29-byte scalar deleting destructor at RVA 00203E76, whose
inline destructor installs 00BE3990. Its compiler-emitted Rva00203E76 table has
one relocation to the weak vector-deleting name, resolving to that scalar
deleting destructor. The data ledger already lists this table name among the
names for RVA 007E3990. This identifies a byte-and-relocation provider; it
does not establish the original semantic class name. No data definition, pin,
ledger alias, compiler setting or verifier changed.

Acceptance: consumer build passes 49/49 rows; strict reusable receipt preparation
passes 49/49 consumer and 51/51 unchanged provider rows, with normal reference
gates. link_check reports the consumer LINKS, 0 -> 337 existing nonpadding
bytes, and the provider remains LINKS at 951 bytes. Frozen-file check passes.
The same alternate exists unused in Disp0DwordImmSettersAddr.cpp, which already
links; leave it alone. A scan of the recorded unresolved vtable blockers and
data-ledger aliases found no other consumer with this supported cause.
