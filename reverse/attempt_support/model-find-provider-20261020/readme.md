# Model-condition lookup provider visibility

Base: `f8ef8c3274da993c13f3d3410857acfcc5f1b48a`.
Reference: BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`, unchanged.
Model: `Codex(runtime-model-not-exposed)`.

This applies the verified Weapon lookup repair to the same supported cause in
W3DModelDrawO1Inlines. Its opaque comparator declaration produced an 86-byte
incidental `_M_find`; the existing native provider at `0x0033AF03` is 92 bytes.
The old private-type/member-template declaration approach is not retried.

Native comparator `0x0033AD13` is 73 bytes, tests 104 bits (`cmp esi,0x68`),
and reads four 32-bit words. The donor BitFlags contains only its STLport
bitset; the source uses its actual unsigned-long storage with compile-time
word-size and 16-byte flag-size guards. Existing `BitFlags<117>` names remain
ledger contracts, not newly proven original template arguments.

The visible noinline comparator preserves VC7.1's read-only knowledge. Its
opposite-bit exits implement the measured low-to-high comparison. The first
source trial emits exactly the existing 73-byte comparator and 92-byte lookup,
including both comparator relocation targets. No flags, shared headers,
source layouts, pins, aliases, or ledger rows change. The redundant old
comparator declaration is removed.

The native fast finder `0x0033D46A` calls `_M_find` and reads the mapped pointer
at node+0x20, following the 16-byte key at node+0x10. Its slow finder, map index,
and caller wrapper remain unchanged and are included in the scoped checks.

Verification: all 25 owned rows across eight provider/caller sources pass the
ordinary build, including all 13 rows in the edited emitter. EH verification
passes the group's one row exactly, with no baseline or missing object. The affected-source
placement scan proposes zero bodies and zero pins. Frozen-source check passes.
Paired link checks use the same published index and actual objects for all eight
sources: 6/8 clean and 1,021 bytes before; 7/8 clean and 1,133 bytes after.
This is **+112 existing linked bytes, zero new unique recovered bytes**.
Remaining W3DModelDrawO1Inlines blockers are outside this lookup closure.

The eight-source group is W3DModelDrawO1Inlines,
SparseMatchFinderModelConditionCompare117, STLModelConditionBitFlagsFind,
Rva0033DCD1, Rva0033D142Permuted, SparseMatchFinderModelConditionBestInfoSlow117,
SparseMatchFinderModelConditionLowerBound117 and ModelConditionMap117InsertUnique.
Run normal `build.sh`, `eh_verify.py` and `link_check.py` on that group, and
`place_bodies.py` without `--apply` on the changed emitter.

Local immutable before/after objects, dependency receipts, source hashes,
full logs and independent source/native evidence are preserved under
`build/model-find-batch2/` and fleet `reports/zh-scout/batch2/`.
