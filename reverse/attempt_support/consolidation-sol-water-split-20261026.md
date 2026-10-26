# WaterTracks mixed-file split handoff, 2026-10-26 (codexb)

Allocated family B shard 0/2. The runner's --check-tu authorizes
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp.
The Water/ consolidation planner remains fresh after the two prerequisite
repairs. Destination and mixed donor file scopes were held for this trial.

The supported inventory reports ten rows routed to W3DWaterTracks.cpp and
two without an approved destination in W3DWaterTracksTestUpdate.cpp.
find_declared_unmatched.py reports twelve matched rows, two existing
unclaimed definitions, and all defined functions already matched. Prior
bindTrack/TestWaterUpdate attempts and existing generated EH companions were
reviewed; these are existing matched bodies, not missing conversions.

Command:

    python3 tools/tu_skeleton.py --split Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracksTestUpdate.cpp --for Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp --dry-run

Exit 2, captured in build/sol-water-split-trial-20261026.txt:

    candidates: 2
    carved: ['0x000FDF4C', '0x000FF8FA']
    refused_rows: {}
    copies: [(None, 'drawEditorLine'), (None, 'unbindEditorTrack')]
    data_moved: ['pauseWaves']
    externs: []
    blocked: an escape-hatch count would grow (hatch_counters rule 3): a copied helper or datum carries one

The refusal precedes residual and destination byte verification. No split,
file reduction, moved row, provider-binding acceptance or downstream unblock
is established by this trial. The file has two existing EditorCoord3D lifetime
present-unmatched hatches; the diagnostic does not identify an individual
growing token. No hatch, class identity, compiler flag or gate was changed to
force acceptance. The source and ledger remain unchanged. The blocked verdict
is recorded with re_log.py and the mixed donor file claim is released.

## Verified batch available to Luna

8b3cf06c06 aligns the existing save donor's track view; 2e07bea406 reconciles
shutdown/destructor declarations and its include closure. The ordinary merge
dry-run now accepts five files/fifteen rows together, formerly three files/ten
rows. That is five newly compatible existing rows (435 retail bytes), not
newly recovered C++ bytes or a confirmed downstream merge. The separate save
and shutdown handoffs contain exact commands and evidence for all fifteen
function rows, unchanged standalone and composed code/data providers,
relocations, COMDAT selections, undefined references, three EXACT EH graphs,
strict link receipts, and preserved identity/data debt. Leave the compatible
merge for Luna. eb0e311873 records the independent blocked Line3D shared-ABI
experiment after restoring its sources.

Other remaining WaterTracks prerequisites are the Common-owned release/find
declarations, WaterTracksObjRender's RealRange collision, and the actual flush
donor's RenderInfoClass/header conflicts. The shutdown donor repaired here is
WaterTracksRenderSystemFlush.cpp; the actual flush implementation is separate.
Vegetation's complete binder/destructor donor is Common-owned and was left
for its owner. Previously recorded allocation blockers were not rebuilt.

## Pending publication and audit

Before this evidence commit, the runner held eb0e311873, 8b3cf06c06 and
2e07bea406 locally for the shared publication batch. Recheck origin before
releasing claims; publication has not yet been confirmed. Retained file scopes:

- Water/W3DWaterTracks.cpp and Water/WaterTracksRenderSystemFlush.cpp;
- WWMath/Rva000FF50DSaveTracks.cpp;
- reverse/attempt_support/consolidation-sol-line3d-renderer-20261026.md;
- reverse/attempt_support/consolidation-sol-water-save-20261026.md;
- reverse/attempt_support/consolidation-sol-water-shutdown-20261026.md;
- this handoff.

The complete outgoing source batch was audited again against origin/master
and its merge-base before this commit. All three edited sources stay at their
existing paths; no outgoing source/header move, new source, deleted source,
compiler flag, protected register or TU-map change exists. Incoming unrelated
path changes are not outgoing edits. Active tools, hooks, workflows, includes,
build inputs and registries need no repointing. The shutdown repair's direct
refcount include is an unchanged member of its original header closure and
its emitted provider set is verified unchanged. This evidence-only addition
does not change that dependency set. Historical EA paths remain intact.

Actual file reduction zero; debt keys retired zero; recovered C++ bytes zero.
Linked/census improvement is unmeasured. After confirmed publication, release
the retained file scopes and settle landed RVA claims through claims.py.
