# Keep restricted DX8 helper paths with their callable owners

Base commit: 15fbf3141f. Discovery: repair_queue.py link, link_rank.py and
receipt-current object probes. Several ranked findings were already repaired;
no source trial was spent on those stale findings. Measurement uses the
published index 825b86983f, 2026-10-15 12:37 UTC, underlying census
5986a99448, 04:52 UTC. The paired proof files record its SHA-256.

W3DVolumetricShadowRenderShadows.cpp emitted two non-retail callable helpers:
Set_DX8_Texture_Stage_State and Set_DX8_Texture. Both omit the stage>=16
uncached path implemented by the existing retail owners at 0x000661DD in
DX8WrapperSetDX8States.cpp and 0x00075412 in BfmeApplyTextureRef_Apply.cpp.
Its calls use stages 0 and 1. The same restricted stage-state definition in
W3DBuffBufferFill.cpp only serves constant stages 0..2. Marking these local
forceinline definitions dllimport retains their verified inline paths and
leaves callable definitions to the existing owners. No import reference,
new function identity, layout claim, pin or alias is introduced.

Reference review: BFME1 66b19a8e95a4add525ef808fcea088e306798e2b uses the
same inline-import emission technique for competing Apt allocation helpers;
4966496c5ae401ec877a044e1ae6dd04f9d9f65c illustrates local ownership repair.
The technique applies; their subsystem code/layout is not imported. Existing
BFME2 retail owners, native call arguments and byte verification establish
this repair independently. The clean verified donor pointer remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
61be6c32ce6c50039791b566ea40b8d22789783f. The overdue pointer update remains
foreign-claimed and retains the recorded comparative full-gate blocker
(2,982 stale TUs, 2,806 left after 21 minutes). No unchanged multi-hour
baseline, pointer edit or success stamp was attempted.

Acceptance:

- Both files were scope-claimed and passed find_declared_unmatched before
  editing and after. build.sh passes all 32 shadow rows and both buff rows.
- Bounded link_check.py --prepare-current passes before and after: 38/38 for
  shadow plus its two unchanged owners, 6/6 for buff plus the unchanged
  stage-state owner. These cover 40 unique rows across four sources. All
  have reusable strict self receipts, with no skipped or baselined references.
- object-proof.json and buff-object-proof.json independently refresh saved
  before/after objects in memory against the same index. Exactly two and one
  losing copies disappear. Every retained consumer COMDAT body and normalized
  relocation is unchanged. Strong, undefined and weak binding sets are
  unchanged (symbol ordering may move). Owners remain unchanged and clean.
  Three legacy local findings removed, zero added. The paired EH checks each
  report three EXACT graphs, zero debt (four unique parents across the batch).
- Prescribed local link_check previews still exit 1 for the consumers. Shadow
  retains unresolved lastActiveVertexBuffer/shadowCameraFrustum and selected
  FrustumClass::operator=. Buff retains unresolved nested render_state,
  competing Vector4 constructor/Matrix4 assignment, and selected
  MeshModelClass::Get_Shader. Owners link cleanly in both previews.
  Legacy local LINKED gain is zero; authored gain is zero. Closed-strict
  closure, whole-census gains and actual link.exe placement were not measured.
- Class, frozen-definition, new-variant, data and converged-data checks pass.
  Each source's place_bodies rescan finds zero bodies and zero pins. CSV passes.
  Normal commit/publication hooks run without bypasses.

The same-cause index sweep (same-cause.json) finds no other wrong texture
setter and two additional stage-state copies in render2d.cpp/vertmaterial.cpp.
Those cached objects are stale; their definitions come through shared donor
headers/shims, unlike the two verified local definitions repaired here. They
need their own current-object/header-scope investigation, and this batch
claims no result for them. W3DBuffBufferFill was refreshed and verified after
that discovery snapshot. It is covered by buff-object-proof.json.

Scratch snapshots, receipts, acceptance logs and reproducible proof scripts
remain under build/shadow-dx8-link-20261015 and build/buff-dx8-link-20261015.
No tracked census/index/history result was changed. No full census, link
cycle, nightly, boot or scheduler was run. Unrelated untracked files remain.
