# SwayClientUpdate Xfer include prerequisite

Follow-up to the Snapshot/coordinate include-order blocker in
`consolidation-gameclient-20261025-codex3-next.md`. A fresh ordinary merge dry
run reproduces C2061 in BfmeXfer.h: the composer collects includes before the
source's forward declarations. The shared Xfer header deliberately leaves
operand class-keys to each caller, so it is unchanged.

The transfer donor now includes a local SwayClientUpdateXferPrefix.h that keeps
its exact existing operand declarations with BfmeXfer.h. No class body, class
key, base, field, function body or compiler setting changes. The include path
resolves from both the donor and approved destination directory; the header
contains no definitions or new layout view.

Verification on 2026-10-25:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/SwayClientUpdate_xfer.cpp`:
  1/1 exact (0x004C9505, 142 bytes); string, float and import checks pass.
- Frozen-file checks pass before/after. Scoped planner regenerated and its
  `--check` passed. `git diff --check` passes.
- Ordinary merge dry run no longer reports Snapshot/coordinate include errors.
  It reaches the independent class conflicts: the seed has no xfer member,
  its ClientUpdateModule hierarchy is not the donor's ObjectModule base, and
  their field spellings differ. There is still no verified two-donor merge.
  Local reports: `build/sway-prefix-{before,after}.txt`.

The remaining class reconciliation is recorded as blocked in re_attempts.log;
no unverified reconstruction is left in Code. The two protected constructor/
pool-key files and mixed file are untouched. No rows moved, files removed,
bytes recovered, hatches added, or debt retired. This is a verified include
prerequisite only, not a claim that the complete merge is ready.

Outgoing compatibility audit: the prerequisite batch adds this local header and
handoffs but moves/deletes no existing source path. Its only new active include
is the transfer donor; normal dry-run compilation proves it also resolves beside
the destination. Existing retail source strings and #line provenance are kept.
