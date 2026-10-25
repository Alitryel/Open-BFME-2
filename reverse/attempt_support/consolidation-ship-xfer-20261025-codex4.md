# ShipSlowDeathBehavior composition prerequisite, 2026-10-25

Allocated family A shard 1/2 target, current Behavior planner evidence,
alternatives and blockers reviewed; snapshot currency passed before editing.
Current TU routing is rebuilt in memory. No map or row was edited.

Baseline normal dry-run accepted nothing: opaque ctor declarations conflict
with the existing real multiple inheritance hierarchy, while Xfer loses its
operand declarations through include hoisting. ShipSlowDeathBehaviorView.h
shares the seed's existing accessed class prefixes with Xfer, declaring their
existing xfer methods. ShipSlowDeathXferPrefix.h keeps the donor's exact operand
declarations beside BfmeXfer.h. The Matrix3D implementation include stays in
the seed, with a forward declaration sufficient for the shared prefix.

`./build.sh` seed and Xfer: 3/3 exact, 713 retail bytes retained, one string,
three float literals and import checks pass (baseline/after receipts under
build/codex4-ship-*-build.txt). Frozen checks pass. Converged data: two sources,
ten addresses, no second names or unjudged rows. EH: no EH-bearing rows or
missing objects. Original compiler flags and implementation bodies are retained.

Ordinary `tu_skeleton.py --merge TU --dry-run` now accepts seed plus Xfer,
three rows, with the constructor still rejected (C2511, constructor absent from
shared real MI view; its opaque raw-vptr fields also require reconciliation).
Receipts: build/codex4-ship-before.txt and codex4-ship-after-trial.txt.
This is a demonstrated partial unblock, not a confirmed Luna landing.
The constructor attempt was not authored; its remaining blocker is logged.
Two protected module-data/pool-key sources and two mixed sources stay untouched.
The unplaced friend-new source is not an eligible donor and was not edited.

No edited source owns an identity/header-queue debt key; the pool-key data debt
remains with its unchanged owner. No debt key is retired or lost. File reduction,
identity retirement and recovered C++ bytes are separately zero.

Compatibility audit across all six pending commits: no source is moved or
deleted. Private header includes preserve relative resolution under normal
composition; active tools, hooks, workflows, build inputs, include consumers,
registries and ledgers have no obsolete paths to repoint. Historical EA path
strings are retained. Existing protected registers are unchanged.

Keep destination, Xfer donor, both new headers and RVAs 0x0045EA66, 0x0045EB02,
0x0045ED0E claimed until publication is confirmed. Earlier retained claims are
listed in the ClickReaction, AIGuardRetaliate and BridgeScaffold handoffs.
