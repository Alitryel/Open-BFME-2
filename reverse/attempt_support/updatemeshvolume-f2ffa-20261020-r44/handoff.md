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
