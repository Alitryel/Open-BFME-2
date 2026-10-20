# Link seat reference freshness handoff

Published census used for this seat: b73720bed9, 2026-10-20 05:34 UTC;
SHA256 b8320517782cc37a63d817317b08074d0e126ec7a612e4b35afaad840b5b07f6.
No census/status was rebuilt or rewritten. Results in adjacent per-repair
proofs are paired legacy-index previews, with strict self byte receipts.

The BFME1 success stamp was missing. Official Open-BFME/Open-BFME-1 master
was fetched: verified gitlink and clean checkout a2c8039e61ad4dfb20c095d8eafe048248d31f25,
upstream 0dc8a26a9c6041c73dc564754cd059dc54faa72a. Current layout resolver and
resolved game/inputs paths are already migrated. The update changes three C++
files (Palantir, DebugExceptionhandler_LogRegisters, memorypool_allocator) and
no headers. Reviewed the allocator's local helper/MemoryPool::_Init additions;
none supplies a corresponding repair for the opaque vector/list/tree units.
Existing BFME1 linking-repair evidence plus a2c8's DX8Wrapper device-lock datum
ownership repair informed the single-owner approach; no donor import occurred.

Attempted baseline full ./build.sh under a2c8 before any pointer update. It
reported 20,027 cached TUs, 2,555 restored objects and then waited on the
host-wide /home/agent/.cache/open-bfme-build.lock in portable_lock._lock_posix.
After roughly 100 seconds without acquiring that lock the waiting invocation
was interrupted (exit 130); it did not complete baseline verification. Local
log: build/bfme1-freshness-20261020/before-byte.txt. No comparison with updated
inputs was possible, no pointer was advanced and no success stamp was written.
The next freshness check remains due and should retry the baseline/update
comparison when the shared full-build lock is available. Do not treat this
blocker as an exhausted donor/reference lane.
