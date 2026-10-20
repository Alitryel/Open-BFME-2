# updateMeshVolume 0xF2FFA, r44 (2026-10-20, claude-opus-5-5)

Bank `reverse/attempts/0x000f2ffa.cpp` now carries real, byte-exact ports of the
three callees instead of stand-ins; it includes the two TU-local header copies in
this directory (12-byte Vertex/IndexBuffer AppendLockClass with `device_lock`,
BFME 4-arg index lock ctor `...@PAV1@IIH@Z`).

Scores from the bank TU (explain_mismatch):
- updateMeshVolume 0xF2FFA 3369/3369, 4 instructions differ (row-1 x87 pair at
  f3121..f312c), no unresolved calls.
- constructVolume 0xEFDF6 1115 exact; constructVolumeVB 0xF0251 1277 exact;
  buildSilhouette 0xF2D25 422 bytes equal (one REL32 name, item 2);
  GetPolygonIndex 0xF0FCD 67 exact; AABoxClass copy ctor 0x9AC04 43 exact.

Row work to land once row 1 is solved:
1. Move buildSilhouette (from W3DVolumetricShadowSilhouette.cpp), constructVolume,
   constructVolumeVB and its ehhandler 0x7639F8 (from
   W3DVolumetricShadowConstructVolume.cpp) into the new unit, or keep noinline
   inline copies here and give the homes select-any linkage (as 7ebbac515c).
2. 0x000F17CA row/pin is the public `...@@QAEXH...` name; the ZH header declares
   addNeighborlessEdges protected (`?addNeighborlessEdges@W3DVolumetricShadow@@IAEXHPAUPolyNeighbor@@@Z`).
3. AABox copy F3473 resolves through the existing fold pin (fold-proof
   W3DVolumetricShadowRenderDynamicMeshVolume.cpp).

Remaining: retail row 1 is `fld [ebp-0x48]; fmul [edi+0x14]; fld [ebp-0x44];
fmul [edi+0x18]` (Y then Z then X); ours Z first. Rows 0 and 2 match (Z,Y,X).
Inert: const Matrix4x4 *prevXForm, (const Vector3&) casts, *(Vector3*)& row-1
operands, three skinned-flag forms. Regressed: WWMath::Fabs (3403 B), direct
row-1 (Y+Z)+X (3372 B, Corners reschedule), direct rows 0+1 (8 diffs; row-2
Transform_Vector SSE order flips f3435..f345d). BF1 matrix4.h inline bodies equal
ZH's; WB 0x806A80 shows three plain Dot_Products. Callee content does not move
row 1 (confirms the earlier seat).

## r48 (claude-opus-5-5, ~200 compiles): struct-temp count does not move the dot products
Diagnostic exact (NOT landable): build/nbr/r48/f2ffa/v/f_n_k7.cpp = row 1 written
direct and right-associated `fabs(p[1].X*o[1].X + (p[1].Y*o[1].Y + p[1].Z*o[1].Z))`
plus 7 discarded `meshXform->Get_Translation();` before `// get the light`.
- Through any inline with reference params the 3-term order is always Z,Y,X
  (Dot_Product, custom bodies X+Y+Z / X+(Y+Z) / Z+Y+X / Y+Z+X, Vector4, a/b
  swapped); Z+(Y+X) gives Y,X,Z; Y+(Z+X) gives Z,X,Y. Direct left-assoc: X,Y,Z
  for every permutation. Direct right-assoc X+(Y+Z)/X+(Z+Y): Y,Z,X = retail.
- 1..32 struct temps at any position, dummy Vector3 locals, TU context,
  scalar inlines, cutting later code, /Op /Oi /Ob1 /Oa /Ow /O2: dot order never
  moves (later Transform_Vector/Corners code does; ~30 temps flips row 0).
- ZH's two unused locals prevPosToLight / prevObjPosition are evidence-backed
  (WB 0x806A80 local_dc/local_cc): alone or with Dot_Product row 1 -> 3372 B;
  with direct left-assoc row 1 -> all but row 1 exact (6 diffs).
- The rest needs exactly k=7 extra temps after the rows (threshold, not mod 8).
Open: what makes retail's row-1 inline behave like direct right-associated
addressing (a BFME2 Matrix4 operator[] / Vector4->Vector3 conversion that is not
a reference cast?), and a natural source of the ~7 temps.

## Landed (2026-10-20, claude-opus-5-5)
updateMeshVolume landed byte-exact in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdateMeshVolume.cpp`.
- **Row-1 x87 order.** Rows 1 and 2 of the rotation test go through two TU-local helpers.
  `Dot_H` accumulates Y, Z, X and `Dot_Z` accumulates Z, Y, X, one product per statement.
  cl 7.1 keeps statement order for the x87 products, while single-expression helpers are
  re-associated to Z, Y, X. With `Dot_H` alone, 8 bytes at 0xF31FC differ: the
  m_shadowLengthScale load lands after the sqrt store. Routing exactly one more row
  (row 0 or row 2) through `Dot_Z` restores retail's order.
- **No private Region3D.** Geometry::setBoundingBox copies through the AABoxClass copy
  ctor, resolved by the 0x9AC04 fold pin. `m_boundingBox = box` compiles to the same bytes
  but names the cullsys operator= row at 0x1492E0, which is not retail's call target.
- **DX8 buffer headers.** This directory's DX8 vertex/index buffer copies became
  `reference/shims/bfme_volumetricshadow_update/`.
- **Globals.** The unit no longer defines the unused shadow-buffer globals. The frustum
  binds to the ledger's `shadowCameraFrustum`.

Left for link work:
- The select-any copies of buildSilhouette, constructVolume and constructVolumeVB
  duplicate their homes' strong definitions.
- The buildSilhouette copy calls the protected `addNeighborlessEdges` name, while the
  0x000F17CA row carries the public one.
