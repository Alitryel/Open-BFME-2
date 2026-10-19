Apt keyboard table duplicate-provider repair, 2026-10-19

Base da7b6104a271a1b0e0c89a81594577621f04933c. Published census index
495c0e1789, 2026-10-19 01:53, retail-truth-2. link-proof.json includes its hash.

The published sole-blocker ranking attributes 2,223 row-extent bytes to two
units blocked by ?Rva008A5250KeyTable@@3QBHB. Larger outstanding sole blockers
moveAllies and getPortTransform have existing unresolved reconstruction banks;
the vector<void*> const-index mismatch above this table is already repaired
in master (3a8433d02), newer than this index. This is the next actionable repair.

The split b0556fe0e copied the initialized external table from AptKeyLookup.cpp
into AptKeyLookup_ObjectMemberLookup.cpp. Both are strong definitions, so even
identical bytes conflict. The latter does not use the table. Keep its declaration
and the original definition in AptKeyLookup.cpp, which owns the existing 80-byte
data row at 0x008EC538. No algorithm, ABI, class layout, data name, data owner,
pin, function ledger, shared header or verifier changes are involved.

The normal gate verifies all 22 matched bodies in four provider/consumer units,
eight literals, both complete exception graphs and the whole 80-byte data row.
An independent read of the gate-built object proves the table equals all 80
native bytes with zero relocations. Refreshing these four current objects into
the same index leaves exactly one strong provider, the ledger owner. Across
the before/after object pairs all retained COMDAT digests, undefined names and
weak bindings are unchanged; only the redundant strong definition is removed.
Object hashes and the complete binding comparison are in object-proof.json.

Paired current-object legacy preview: two duplicate findings removed, none
added; AptKeyLookup.cpp (364 nonpadding authored bytes) and its split member
lookup (1,733 bytes) become clean. Cohort link-clean bytes rise 100 -> 2,197,
a gain of 2,097. The existing aptKeyCode.cpp consumer stays clean; the analog
callback unit keeps its six independent unresolved names. This is a local
preview, not a full executable link or a closed-strict link measurement.
C++ exact coverage is unchanged.

Required BFME1 scan/ranked/near/lift and ZH match/packets refreshed at verified
BFME1 a18d9ed50607e9175de4d6568798d7d73119de09. Ranked donors and ZH packets
are zero. BFME1's game/Libraries/Source/EA/Apt/aptKeyCode.cpp (history 2591e449)
provides a single external special-key table and its two consumers. Its matching
20 entries corroborate semantics; BFME2's existing data row and native bytes,
not the donor address or return types, establish this repair. BFME2 aptKeyCode
already uses the external owner. No unchanged reconstruction trial is repeated.

The source-file placement scan finds zero new bodies or pins. Frozen-definition,
CSV and normal commit/push hooks must pass. Strict preparation cannot issue
reusable receipts for the three Apt units: existing included headers lie
outside the inventoried search roots. The ordinary full-byte/data/EH checks
remain valid; no strict receipt or global linking result is claimed.
