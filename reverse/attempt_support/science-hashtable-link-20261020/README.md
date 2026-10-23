ScienceType hash-table link blocker, 2026-10-20

Inputs: BFME2 2c5c1dfc73, BFME1 0dc8a26a9c60; published retail-truth-2 index b73720bed9. MSVC 7.1, source flags preserved in trial.patch.

The two hash_map<int, vector<ScienceType>> units own 433 nonpadding bytes. Current baseline objects both emit the same wrong 222-byte resize helper, pinned at native 0x53F1EC (184 bytes). Declaration-only resize specializations preserve all 15 rowed bodies, but removing both copies leaves resize unresolved: there is no other provider under this spelling. Do not land suppression alone.

/O1 /Ob2 preserves all 15 rows but retains the 222-byte helper. Following the existing FXListStoreParse import-inline vector/base destructor pattern and restoring allocator destructor visibility reduces resize to 211 bytes, still with EH and an imported vector destructor reference. An empty import-inline allocator destructor adds an IAT reference instead of disappearing; specialization must precede base-destructor definition to avoid C2908. The attached last trial is diagnostic, not a partial recovered body. Paired results show no linked gain; strict-current is false for this discarded trial. Native resize has no EH frame, calls get_allocator, fill-vector constructor and swap, then directly frees the temporary bucket array. A future attempt needs that exact lifetime/inlining shape while retaining all existing row bodies and avoiding import references.

Both source files restored to HEAD and their own byte gates rerun. No pins, ledger identities, verifier code or shared headers changed.
