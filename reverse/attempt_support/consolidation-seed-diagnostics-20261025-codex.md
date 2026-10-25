# Rejected-seed diagnostics, 2026-10-25

The current Luna handoff records empty accepted/rejected dictionaries for
TunnelContain and FlammableUpdate and cannot identify their prerequisites.
Tool inspection found that _merge discards every greedy trial rejecting the
seed before saving its rejected-donor diagnostics. Baseline compilation and
composed trials do run; an empty report did not prove that no compiler trial ran.
TunnelContain is held by another worker and was not retried or edited.

The tool now retains the rejected map from the most productive failed seed
trial, for reporting only when no valid seed trial exists. Score ordering,
compiler verification, baseline inclusion, accepted-file selection, claims,
staging and application conditions are unchanged. A failing seed still blocks
application. New regression reproduces the empty dictionary on the old code,
then passes with the fix and asserts that apply is never called.

Checks: all 19 tu_skeleton unit tests pass. All gate-exploit cases pass their
expected controls (43 passed, one existing skipped case). Initial unittest
invocation of the pytest-only exploit module was corrected to pytest; no test
or gate was changed to accommodate it.

Current FlammableUpdate dry run still blocks and applies nothing, but reports:
- Seed C2143/C2059 at generated line 19: hoisted TheGameLogic macro now precedes
  the original extern class GameLogic *TheGameLogic declaration. A one-file
  compose proves directive at line14, declaration at line19.
- Xfer donor: BfmeXfer.h missing Snapshot declaration.
- Rva0048C7BF donor: missing doAflameDamage/member vocabulary.
- CameraMarkerVecErase donor: duplicate STL random_access_iterator_tag/member.
Other mixed and protected donors stay refused. Exact local reports:
build/codex-flammable-diagnostics.txt and build/codex-flammable-self-compose.cpp.
No source has changed. Record the seed macro prerequisite before another trial;
do not repeat unchanged blocked merges. FlammableUpdate file claim is retained
only for the immediate prerequisite follow-up; tooling claims until publication.

No source path move, debt retirement, file reduction or recovered bytes. Pending
origin/master..HEAD and staged changes contain no source path move; active path
consumers require no transfer. This is a diagnostic repair, not merge admission.
