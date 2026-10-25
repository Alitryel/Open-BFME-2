# AIGuardRetaliate composition prerequisite, 2026-10-25

Allocated Sol family A shard 1/2 target:
`Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliate.cpp`.
The AI planner packet's original-path evidence, alternatives, private class
conflicts and mixed/protected-source blockers were reviewed; the scoped
snapshot currency check passed before editing. The ordinary TU tool rebuilds
current approved routing in memory; no tu_map.csv was regenerated on disk.

Before repair the normal dry-run accepted the getter and return-state ctor,
then rejected AIGuardRetaliateXfer.cpp because it hoists BfmeXfer.h before the
operand forward declarations. A private AIGuardRetaliateXferPrefix.h now keeps
the donor's exact existing operand declarations and include together. There
is no class/body/layout/flag change, and the shared Xfer header is unchanged.

Verification:

- Baseline and final `./build.sh` checks pass. Final getter, Xfer and return-state
  constructor build: 3/3 exact, 179 retail bytes retained; string/float/import
  checks pass (build/codex4-aiguard-after-build.txt).
- All three frozen checks pass. Converged data: 3 sources, 10 addresses, zero
  second names and unjudged rows. EH: no EH-bearing rows or missing objects.
- Ordinary `tu_skeleton.py --merge ... --dry-run` changes from two accepted
  donors to all three accepted donors / three rows, no rejections. Receipts:
  build/codex4-aiguard-before.txt and build/codex4-aiguard-prefix-after.txt.
  This is a demonstrated unblock for Luna, not a confirmed downstream merge.
- Seven mixed sources and the protected machine source remain untouched.
  None of the three eligible sources owns an identity/header-queue debt key;
  no key is retired, transferred or dropped. No hatch added or row moved.

Publication compatibility audit across the pending ClickReaction prerequisites
and this change: no source path is moved/deleted. The new local header preserves
its relative include at both donor and destination, proven by ordinary trial.
Active tools, hooks, workflows, build inputs, include consumers, ledgers and
registries have no obsolete path needing repointing. The private headers' direct
consumers were verified together. Historical EA paths are unchanged. File
reduction, debt retirement and recovered C++ bytes are each zero.

The runner has queued publication. Keep the AIGuardRetaliate destination,
Xfer donor, return-state ctor and new prefix file claims, plus RVAs 0x0054528D
and 0x005453BB, until publication is confirmed; then release them. ClickReaction
claims are listed in consolidation-click-object-20261025-codex4.md.

Additional allocated read-only trial: ModelConditionUpgrade accepts all three
eligible donors / three rows under the normal dry-run, no rejections. No repair
or merge applied; leave it for Luna. Its destination investigation claim was
released. Receipt: build/codex4-modelupgrade-before.txt.
