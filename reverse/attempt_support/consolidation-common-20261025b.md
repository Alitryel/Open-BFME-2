# Common consolidation continuation, 2026-10-25

Scope: `Code/GameEngine/Source/Common/`. The session resumed a clean tree at
`9cffd391b3`, including four verified pending merge commits from the previous
session. Their claims remain held until publication. `check_csv.py` passes
(98,244 rows); the BFME 1 verification receipt is under 72 hours old.

The scoped planner regenerated `build/consolidation`, and its `--check` passed.
It catalogued 173 retail C++ paths. Stale committed TU routing is rebuilt in
memory by `tu_skeleton.py`; no map regeneration is included in these commits.

## AudioEventRTS directive prerequisite

All thirteen eligible donors pass the declared-unmatched check. The first
ordinary merge dry run accepted nothing. Its destination's six rows establish
a baseline, but composing that destination alone fails with C2226 on
`ClientFrameSubsystem`: lifting the `TheGameClient` macro before its external
declaration makes the preprocessor rewrite that declaration. Two other donors
cannot establish a baseline under the destination environment.

The prerequisite removes the redundant pointer-reinterpretation macro and its
unused forward declaration. Both call sites already cast the global back to
the declared `GameClient *` view. There is still one external declaration of
the real global. `./build.sh` passes all six bodies; declared-unmatched passes.
No layout, symbol, compiler flag, pin or ledger row changed.

Before publishing this prerequisite, fetched origin at `ce5e16cd06` and audited
all pending path changes from that base through the staged prerequisite:
twenty absorbed paths from the previous four merge commits, 218 path/basename/
stem hits. No active tool, hook, workflow, include, build input or mutable
registry consumes the removed paths. Remaining hits are merged provenance,
unchanged symbol identifiers, historical attempts/naming/census records and
independent reference-tree evidence. The owning Microsoft-header auditor has
already refreshed affected destination queue entries in that pending batch.
No directory was moved, so generic directory discovery remains valid.
Scratch evidence: `build/consolidation-audit.json` and
`build/consolidation-audit-hits.txt`.
