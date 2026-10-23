# Link seat handoff, 2026-10-21

This session repaired six units, with paired current-object legacy gains of
+333 B (vector helpers), +765 B (E8 deque owners), and +277 B (narrow money-get).
Each repair has its own evidence directory and commit. These gains do not claim
closed-strict closure, a full link cycle or runtime verification. No new authored
C++ coverage was added. All touched code passed normal byte/hook checks and
self-strict receipt preparation. Session stops at the context review limit.

## Next concrete lead: water shadow-map guard

`WaterTracksRenderSystemFlush_Flush.cpp` remains blocked on undefined
`?stats@DX8Wrapper@@2VDX8_Stats@@A`, but defining that donor object would be wrong.
The native flush row 0x0010004D (392 B, 391 nonpadding) reads byte VA 0x00DEC404:
`0x0010008F: cmp byte ptr [0x00DEC404],bl`. The current donor expression is
`DX8Wrapper::stats.m_disableWater`, whose offset is 2. The data-ledger label at
RVA 0x009EC402 was inferred from that expression; it is not evidence for a
16-byte DX8_Stats object there. Its range would overlap several real globals.

The byte at RVA 0x009EC404 already belongs to
`?IsCurrentlyRenderingShadowMap@WW3D@@0_NA`, verified in data_rows.csv and defined
in W3DShadowMapManagerUpdateShadowMap.cpp. Its native setter is independently
established there. W3DWaterRender.cpp already uses the same flag to skip water
while rendering the shadow map. Its small WW3D view provides an inline
`Is_Currently_Rendering_Shadow_Map()` reader. Replacing the flush's donor stats
expression with that established reader is the next supported hypothesis.
Correct the source/row provenance note accordingly if it verifies. Do not add a
second data name or a stats object at this address.

No edit or byte trial was made: nbr-L5 holds the file claim (about 0.3 h remained
when checked). The acquired RVA claim was immediately released. Read-only
self-strict baseline verification passed for flush, its shadow-map flag owner
and W3DWaterRender. Their diagnostic logs remain in build/link-seat; no new
function verdict is imposed merely because another worker owns the file.

## Other checked causes

Current previews show the ranked Vector4 assignment consumer, freeBlock
consumers and Rva000C38F8Ctor already link; refreshing these is not repair work.
name_globals.py --dry-run found no available rewrite in the three ConstIntGetters
address units or the FadeInTextRender constructor. HordeContainChangeToFormation,
SceneSpatialRescale and the Apt tribute handle retain the exact provider/inline
summary conflicts documented in their prior attempts; no unchanged trial was
repeated. LivingWorldAIBuildingTypes retains its pair destructor conflict.
E16 deque requires actual map/subtract providers, recorded in re_attempts.log.
Claims for unpublished verified repairs are released on final handoff; the
runner publishes remaining commits under its shared-account batching rules.
