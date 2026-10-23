Build-queue range destruction, 2026-10-22
========================================

At the published census08160bc2c9 (2026-10-22 17:08), the current
StrategicInGameUIBuildQueueUnitQueued.cpp object fails on its emitted
Rva005E71C6Ref range dispatch and worker. The established rowed dispatch
at005E7FB0 in StrategicInGameUIBuildQueueIconSelect.cpp calls the native
range worker005E7BE2. Declare the dispatch/worker specializations so this
caller binds the existing implementations. Keep placement-copy, backward
copy, reference ownership and private object layouts visible and unchanged.
All main bodies remain exact; no name, address pin or layout claim added.

Five original ledger entries name raw $L compiler labels. The declarations
shift those ordinals; their bytes are unchanged. Add gen-funclet and
parent= notes to these existing rows, based on the exact native EH graphs:
005E8519 uses7A3E98/7A3EA2;005E868F uses7A3EB4/7A3EBE/7A3EC8. The byte
gate independently resolves each new label through its parent's native
exception graph. No object-symbol alias, numeric label update or rename.

Before: current caller0/929B linked. After:929/929B. The five funclets total
46B and are excluded from authored-byte credit after their classification.
The read-only dispatch
provider remains0/3276B because of six unrelated unresolved names. This is
a legacy prediction, with current byte-verified caller and reusable strict
receipt; self-strict/closed-strict placement gains have not been measured.
Acceptance:15/15 rows, all string/float/import checks; EH3/3 EXACT;
check_csv, declared-unmatched, data checks and diff check. Cause search:
the only other ranked emitter is StlportVectorInsertOverflowFamily.cpp,
which retains many independent unresolved elements and COMDAT findings.
No speculative cleanup there for zero linked gain. Replace the explicit
vendor include flag with the normal stlport source marker; this preserves
all bytes and lets the strict dependency inventory verify its include roots.

Local logs:build/link-seat-20261022e/buildqueue-{trial1,trial2,eh,strict,
after1,after-final,strict-final}.log. Trial1 failed only on five unmapped raw compiler labels;
all parent rows and their native EH graphs already passed.
