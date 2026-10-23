# 0x102F83 W3DCamTransform::rva00102F83 — round r62 (2026-10-21)

Bank unchanged: `reverse/attempts/0x00102f83.cpp` 0.91227 (r61). Session ended on runner wind-down.
Read r61 and r55 handoffs first for the full disproven list and the residue (t.X/t.Y register
candidates where retail keeps s.X/s.Y/t.X/t.Y memory-resident at [ebp+0x58/5c/68/6c]).

## Disproven this round
- g1: 2^8 = 256 numbering-only natural edits on the bank (A `float angle` local, B `float pitch`
  local, C split `Vector3 sourcePos; Vector3 targetPos;`, D named `upAxis`, E targetHeight
  declared at top, F `object=0; if(live) object=find(...)`, H separate `float height;` decl,
  I `distSqr` temp). A/C/E/H inert; B 0.8991, D 0.83, F 0.908, I inert or worse. No variant
  changed the X/Y candidacy fingerprint, none beat 0.91227.
- BFME1 counterpart 0x6E0580 (x87, ~0xd48 B; context layout Gen_006DFC60 in
  `reference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewBuildCameraTransformBfme.cpp`,
  same field offsets): caches realZoom in a local bool (BFME2 retail rereads [ebx+0x8c], so no
  cache; already disproven as v36), single-if realZoom with merged lerps (x87 tail merge is
  harmless there), same `zoom*offset.Z` order. No new lever.

## WB-faithful shape (from WB 0x7E3040, not yet compiled as one variant)
The bank's two-if realZoom, targetHeight local, inversePitch multiply and target-first live
translate are local optima, not WB's source. WB reads as:
- single `if(realZoom)`: clamp, `v->fxPitch = ...`, then division-form lerps rereading v->fxPitch;
- live translate source first: `s.X+=pos.x; s.Y+=pos.y; s.Z+=pos.z; t.X+=pos.x; t.Y+=pos.y;
  t.Z += pos.z + tza;`
- non-live: `s.Z += groundLevel; t.Z += groundLevel + tza;` (no targetHeight local);
- live arm: `m_cameraSource=sourcePos; Vector3 p1=targetPos; p1.Z=0; Vector3 p2=sourcePos;
  p2.Z=0; float distance=Vector3::Distance(p1,p2); float height=tan(v->fxPitch)*distance;
  targetPos.Z=sourcePos.Z-height;`
- `sourcePos *= factor` via operator*=.

## Next step (planned, not run)
Build f0 = all WB-faithful edits on `build/b4-102f83/v32/s0.cpp` (single-if base 0.88893), then a
factorial toggling each WB edit plus the r61 levers (translate addXY, `targetPos+=delta`, helper vs
inline per arm); score with `build/b4-102f83/run.sh`, check whether the X/Y fingerprint moves off
(11,13). Earlier single trials of these edits were on the bank (two-if) shape; their combination on
the single-if shape is untested. Tools: `build/b4-102f83/{sc2.py,run.sh,sbs.py,w1/reg.py,w1/ana.py}`.
