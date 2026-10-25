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

## AudioEventRTS consolidation

The prerequisite unlocks nine files into the existing AudioEventRTS.cpp:
eight donor files removed, all 17 matched rows preserved (11 repointed).
Both ordinary dry-run and claimed apply agree. `./build.sh` passes 17/17,
declared-unmatched and check_csv pass. Only source columns change in the
committed TU map; there is no regenerated routing. Mixed files and the
protected position donor remain untouched.

Remaining eligible donors: Rva002DA0CFFinish.cpp and Rva002DA153Scale.cpp
cannot establish a baseline in the destination environment. Filename-prefix
and Rva002D9FD9Seq composition need the AudioManager slot134/a29 declarations
reconciled. Their compile diagnostics are retained in
`build/audio-consolidation-apply.txt`; no failing reconstruction was written.

The outgoing audit, after fetching origin at 17d211067f, covers the merge-base
ce5e16cd06 through dfd4b0c242 plus this staged merge: 28 removed donor paths,
975 path/basename/stem hits. The additional active consumer is one GameLogic
header-adoption queue row for Rva002DA414.cpp. The owning header lane now
transfers that row and its acceptance command to AudioEventRTS.cpp. It keeps
the original failure, RVAs and retry budget and does not retire debt.
tu_skeleton applies this transfer for subsequent merges, even without a
Microsoft-header queue. Regression coverage includes two same-class debts,
an unrelated source and failed/successful acceptance; 64 tests pass, one
environment-dependent test skips, including the gate-exploit suite.
Other hits are merged provenance, unchanged symbol/header names, historical
attempt/naming/census records and independent reference evidence. No active
include, tool, hook, workflow or build input names an absorbed source.

## DataChunk consolidation

Claimed apply agrees with the prior dry run: six files become the existing
DataChunk.cpp, removing five donors. Ordinary build passes 17/17 ledger rows,
including all three named imports; declared-unmatched passes. The tool's
suggested subject reports 16 because it sums per-donor distinct-RVA sets.
There are 15 distinct RVAs: writeInt/writeReal already share 0x00306CFF with
an explicit ICF note, and the pre-existing placeholder Rva00307A2C duplicates
the seed's findMapping owner at 0x00307A2C. History confirms the placeholder
predates this pass (8e0b9308b0). Both rows remain verified, with no new row or
coverage claim; the placeholder's duplicate identity still needs cleanup.

Six rejected donors need DataChunkInput scalar/getChunkLabel declarations,
DataChunkTableOfContents getName/Mapping declarations, or DataChunkOutput
string/name-key declarations reconciled. The exact compile errors remain in
`build/datachunk-consolidation-apply.txt`. Mixed files and four protected
donors remain untouched. Rejected AudioEventRTS and DataChunk donor claims
are released; accepted path claims stay held until publication.

The combined outgoing audit now covers ce5e16cd06 through fe1710f491 and this
staged merge, with origin fetched at 70a67784ed: 33 removed donor paths and
992 path/basename/stem hits. No additional active consumer needs changing.
The owning Microsoft-header audit refreshes the destination and removes
absorbed entries, retaining fwrite's ABI conflict at the new source path.
Only source columns change in the committed TU map. Historical evidence and
source provenance remain intact.
