# Device consolidation split-lane handoff, 2026-10-25

Scope: `Code/GameEngineDevice/Source/`. The planner and scoped queue were
refreshed; no mixed-file split passed as a task that could be batched with a
verified merge. Dry runs made no source or ledger changes.

- `W3DWaterTracksTestUpdate.cpp` to `W3DWaterTracks.cpp`: two rows carved, but
  blocked by `an escape-hatch count would grow (hatch_counters rule 3): a copied
  helper or datum carries one` (`drawEditorLine`, `unbindEditorTrack`,
  `pauseWaves`).
- `W3DBufferManager_Slots.cpp` to `W3DBufferManager.cpp`: two rows alone matched
  beside the TU; six rows were refused because `2 definitions spell its name`.
  Merge trial: `accepted: []`, `rejected: {}`,
  `blocked: no verified merge of two or more donors`.
- `W3DTreeDrawModuleDataCtorG7.cpp` to `W3DTreeDraw.cpp`: the only row is the
  whole donor; `blocked: no row would remain in the file: it is a whole donor,
  use --merge`.
- `W3DGhostObjectScene.cpp` to `W3DGhostObject.cpp`: 27 rows carved, but blocked
  by `an escape-hatch count would grow (hatch_counters rule 3): a copied helper
  or datum carries one` (`animationDisableOverride`).
- `W3DLaserDrawBfmeConstructor.cpp` to `W3DLaserDraw.cpp`: both rows are the
  whole donor; `blocked: no row would remain in the file: it is a whole donor,
  use --merge`.
- `W3DBridgeBufferDrawBridges.cpp` to `W3DBridgeBuffer.cpp`: the carve leaves
  no rows in the residual and loses matched row `0x0039B780`;
  `blocked: the residual loses matched rows (flag region or a shared helper)`.
- `W3DBridgeAllocateBridgeBuffers.cpp` to `W3DBridgeBuffer.cpp`: the only row
  is the whole donor; `blocked: no row would remain in the file: it is a whole
  donor, use --merge`.

Whole donors remain for the normal merge lane; the two escape-hatch blockers
need the owning hatch analysis, and the Bridge draw residual needs its matched
row retained. No claims were acquired for trial sources or rows. Do not repeat
these unchanged trials until those prerequisites change.

