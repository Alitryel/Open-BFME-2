# BFME 1 reference freshness, 2026-10-21

Compared the last committed/clean reference `a80da2e3be84ebdb3b6bc280faca3f99a44788af`
with official `Open-BFME/Open-BFME-1` master
`cea1e9734dc0c5355613b61226fe3cc2faab4aa4`, at BFME 2 `cdada2a7a4`.
No dirty or unpublished donor work was overwritten. The prior verified donor
commit is retained locally as branch `bfme2-verified-a80da2e3` as well as in
BFME 2 history (the upstream branch histories diverge). The existing layout resolver
already resolves `game/`, `inputs/reference/`, vendor and toolchain inputs;
resolved directories and the intended headers were checked, including include
paths carried in source compiler flags. No layout repair was needed.

The old-reference full gate was rerun at the current BFME 2 revision and passed
all 97,928 rows, including the list-assignment adapter in this batch and every
data, literal, import and pin check. The final updated-reference full gate also
passed all 97,928 rows and all checks with the same adapter and ledger inputs.
Logs: `old-reference-current-gate.log` and `new-reference-final-gate.log` in the
local log directory below. No update regression or pre-existing byte failure
was observed. The same six-unit Buffer cohort remained 6/6 and
13,926/13,926 B linked (legacy preview).

Dedicated linking donor review: reviewed the eleven incoming commits and their
source/evidence. The only changed dependency header used by BFME 2 is `buff.h`;
the Buffer destructor visibility repair is inherited. The six direct BFME 2
users (`ini`, `xpipe`, `cstraw`, `readline`, `buff`, `xstraw`) already predicted
13,926/13,926 bytes linked before this pointer update. The ScoreKeeper map
provider, AsciiString concatenation, GlobalData binding, typed Shroud forwarding,
and terrain getter repairs were compared against BFME 2 callers and blockers.
They are already inherited or have no supported matching blocker here. The
fifteen-task donor handoff was also reviewed; its class/vtable findings do not
justify transplanting a donor layout into BFME 2.

Refreshed donor discovery at the new revision: `bfme1_sweep.py scan` found 38,757
donors, 5,514 control placements and 616 near comparisons; `ranked` and `near`
each served zero unclaimed candidates. `lift_lane.py --limit 1000` ran and listed
149 lifted bodies, including the ZH leads. Lifted bytes remain leads, not C++
recovery or BFME 2 identity proof. The revision and hash receipt for these cached results is
`build/bfme1_sweep/link-seat-inputs.json`.

No authored C++ or newly linked bytes are claimed for this mandatory freshness
update. Full logs are local under `build/link-seat-20261021d/`.
