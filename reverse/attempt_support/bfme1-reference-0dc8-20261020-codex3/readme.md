# BFME1 reference refresh

Previous verified pointer and clean checkout:
a2c8039e61ad4dfb20c095d8eafe048248d31f25.
Official Open-BFME/Open-BFME-1 master fetched and checked out:
0dc8a26a9c6041c73dc564754cd059dc54faa72a.
The three new donor commits change only Palantir dispatch,
DebugExceptionhandler_LogRegisters and MemoryPool::_Init source bodies,
plus BFME1 ledgers/evidence. No headers, compiler flags, toolchain, include
directories or layout changed. The existing game/ and inputs/ resolver
migration remains applicable; no migration repair is needed.

Both full byte gates pass: 97302/97302 functions, 1116 data rows, all
reference/identity checks, no-op patch and FULL GATE OK. Function/reference
comparison phases used the fixed BFME2 e46d1b72b2 source state; the later
independent six-consumer assignment trial started only during the new
gate's data-probe phase and touches no data rows or headers. The combined
staged tree must also pass the normal commit hook. No update regression
or pre-existing full-gate failure remains.

No current compiled BFME2 dependency receipt reads the three changed
donor TUs; no active donor compile trial or ZH dependency is affected.
Refreshed bfme1_sweep scan: 5522 unique placements, all owned, 5513
independent boundary controls; ranked 0; near one previously blocked
25-byte Fade cleanup at 76962A. lift_lane: 154 bodies, 107 servable.
Dedicated linking review of this official revision is recorded in
script-cleanup-link-20261020-codex3; no unchanged donor scan repeated.
