# Region record construct provider

Rva00541DDFFinish.cpp newly links 152 unique matched bytes under local legacy prediction against published census c2c5ac8c27 (2026-10-18 11:36). Before: insert unit 0, reset sibling 70, helper provider 18. After: insert 152, reset 70, provider 18. The reset unit already had the declaration-only helper binding and already linked with current objects, so its stale census gain is not attributed to this change.

The insert unit now uses that same declaration-only specialization of _Construct<Rva0054103E,Rva0054103E>, bound to the existing 18-byte row at 0x0054106D. The strict 152-byte caller and normal literal/import checks pass. No code layout, member access, identity pin or alias was added. Code identity output is retained separately. No closed-strict or runtime claim.

The index was searched for the same blocking helper: only these two consumers were served, and the sibling is already repaired. Existing target-owned copy constructor and reset sibling establish this compiler/provider choice; the previously reviewed BFME 1 pointer is unchanged.
