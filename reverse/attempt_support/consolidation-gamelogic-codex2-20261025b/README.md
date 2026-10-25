# GameLogic consolidation, codex2, 2026-10-25, second pass

Scope: `Code/GameEngine/Source/GameLogic/`. Current AGENTS.md and consolidation
workflow read; previous session's batch is published and its worktree clean.
The BFME 1 freshness receipt is less than 72 hours old.

## ExperienceTracker

The scoped planner packet was reviewed, including original-path alternatives,
mixed files, compiler context and private type conflicts. The report passed
`name_lane.py consolidate --check` before applying the merge. Current routing
was rebuilt in memory; no map was regenerated on disk. The target path is
supported by retail string anchors, donor definitions and bracketing routes;
only the merge tool's approved rows moved.

The trial and normal-claim application accepted nine fragments into a new
approved TU, preserving fourteen matched rows / 754 retail bytes. This merge
is blocked and was fully restored; no file-count or coverage gain is claimed. All twelve eligible donors passed frozen-file checks before
application. The destination's ordinary build passed 14/14, including string,
float and import checks, and its frozen-file check passed. EH verification
found no EH-bearing row or missing object; enforced converged-data checking
judged ten addresses with no second name or unjudged row.

Three eligible files remain rejected: ExperienceTrackerXfer needs Snapshot
and coordinate forward declarations visible before BfmeXfer.h;
ExperienceTrackerRva0039B315 needs an Object view preserving getRelationship;
ExperienceTrackerSetExperience needs compatible GameLogic and tracker receiver
declarations. Ten mixed files and three protected files remain untouched.
These are prerequisites, not lost retail rows. Exact tool diagnostics are in
`experience-merge.txt`.

The normal pre-commit gate refused the new TU because it inherits a private
GameLogic definition. Its canonical header does not provide m_i114; the
existing GameLogic header queue records this prerequisite on
Common/Rva0039AF9B.cpp, outside this seat's destination scope. The check was not
changed or bypassed. All source/ledger/header-queue changes were restored, the
blocked verdict recorded through re_log.py, and the merge scope released.
No debt is retired and no names, pins, hatches or ABI layouts were added.

## Pending-path compatibility audit

Audited `origin/master` 2278ad51d20dd5950bf20a151ee450e48e3ffdf8 through HEAD
plus the staged ExperienceTracker merge. Searched all nine removed full paths
and basenames across tracked consumers, including tools, hooks, workflows,
source/header includes, root build/config files, registries and docs. Common,
GameLogic/System and Object directory roots remain; no directory moves occur.

The only active old-path consumer was the header queue, repointed by the trial
and restored along with the blocked merge.
Its original compiler failure path is historical. Remaining hits are merged
source provenance comments, published census snapshots, append-only attempt
logs, banked patches and transaction evidence. Preserve these and EA strings.
No active include/build/tool consumer needs repair. The ordinary destination
build creates new receipts; old donor objects are not verification evidence.

## SubObjectsUpgrade

The scoped planner's alternatives, mixed/protected prerequisites and compiler
differences were reviewed; its currency check passed before applying. Current
in-memory TU routing and the dry run approved the existing retail TU and two
drawable-broadcast helpers. Normal-claim merge removed two fragment files,
preserving all six matched rows, including the existing compiler EH handler.
The ordinary build passed 6/6 and verified two emitted STLport constructors
against retail owners/callees; frozen-file and staged canonical-class checks
passed. EH verification reports one EXACT row and no missing object.

Four donors remain: Rva004B4DBFRates has no destination-context baseline
match; Rva004B4E56Check needs receiver members; Rva004B4CDFXfer needs forward
declarations before BfmeXfer.h; SubObjectsUpgradeParseReplacement conflicts
with the real STLport allocator/vector. Three mixed files and two protected
files remain intact. See `subobjects-merge.txt` for exact diagnostics. No
prerequisite was bypassed, no register or hatch was changed, and only two
function/map source columns moved.

The complete pending-path audit was refreshed against fetched origin
d9f789c76e4a789fa660334874e9bb08ce7b5b7f through HEAD plus this staged merge.
Only these two fragment paths are pending (ExperienceTracker was restored).
Full tracked-tree searches of paths/basenames found only merged provenance
comments and historical census snapshots. Behavior's directory remains, with
no changed directory assumptions. No active tool, hook, workflow, include,
build/config input or registry needs a repair. EA strings remain intact.
