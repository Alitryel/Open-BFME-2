# 0x148520 DX8SkinFVFCategoryContainer::Render - session 2026-10-19 21:41-22:05 PT (hans-agent-oct5)

Baseline bank: struct 13, mem 46, reg 19, 1400 B; real differing insns R=90 / O=88 (normalized difflib).

## New lever: mesh vs mmc web split (mesh -> ESI like retail)
Re-reading the model pointer after the anchor branch, just before the tempVertices resize,
`MeshModelClass*m2=mesh->Peek_Model();` (or `mmc=mesh->Peek_Model();`), with descriptor reads through it:
struct 15, mem 29, reg 9, 1400 B, R=63 / O=61. The prologue through +0x1E8 now matches (mesh ESI, count EBX).
The cost is one extra `mov edi,[esi+0xc4]` at +0x1E8 that retail doesn't have, so it isn't banked.
Retail keeps mmc in EDI from +0x170 to +0x241 with mesh still winning ESI. The open question is what gives mesh priority over mmc without a reload.
Peek_Model through the UV/color reads (mpa/mpb, +16 B) also gives mesh ESI, but it reloads too.

## Still wrong after the split
- The UV/color block at +0x247..+0x2B1: we CSE zero into EDI (`xor edi,edi`, `cmp ..,edi`, store edi).
  Retail uses immediate 0, computes uv0 in ECX and stores it once, and computes diffuse in EAX, then `mov edi,eax`.
- Get_Deformed_Vertices args: retail reloads the norm array and pushes EBP=loc. We reload loc and push EBX.

## Inert or refuted this session
- Inline Get_Color_Array (if/ternary/local forms): inert.
- Default-zero/if/else diffuse, `S2Buffer*cb` local, postincrement split: inert. The `?:` store form: worse (21/88).
- Equal-arm hack on uv0 / diffuse: worse (15/106).
- Single-exit Get_UV_Array_By_Index: struct 12 but mem 81 (extra stack slot). The ternary-return form is inert.
  Dropping the uv1 equal-arm hack: 14/65.
- loc/norm declaration order and placement, explicit &temp[0] call args: inert (with and without the split).
- Alpha via two Get_Alpha calls: 20/32/15. Vertex count via Peek_Model: worse.
- Moving the mmc read before Record_DX8 (mqd): identical to baseline.
Harness: %TEMP%\vg.py (SRC/SYM/RVA/SZ/TAG=s148); use lowercase variant names (uppercase gets ^-escaped in obj names).

## Session 2 (22:36-22:48 PT): mesh priority without the extra load
- w5: a late descriptor local right before uv0 (`S2MaterialDesc*desc=mmc->descriptor;`, all UV/color reads through desc). The zero-register CSE in the UV/color block goes away; it's immediate-0 style like retail.
  Result: struct 13->5, reg 19->16, R 90->85 at 1,400 B, but mem 46->49. Not banked because it trades one class against another.
- w5 + the mesh/mmc web split (mmc re-read before resize): R=57, reg 7, but 1,416 B (the reload stays). Re-reading only desc via mesh->Peek_Model(): 1,416 B.
- desc local declared early (right after mmc): struct 6 but R=95, so the descriptor must be read late.
- Inert on w5: a const mmc pointer, Get_Vertex_Count(), `while(mesh!=NULL)`, remainingMesh/mesh declaration order. Swapping the Anchor and Set_Base_Vertex_Offset order: worse.
The mesh-vs-mmc ESI swap still has no reload-free lever.

## Session 3 (22:40-22:46 PT)
Inert on the w5 shape: const mmc / const desc, a split declaration of mesh_vertex_count, an `mmc=0` sink after Get_Deformed_Vertices, and mmc declared at the inner-block, function, or outer-loop scope.
None of them moves mesh to ESI; mmc keeps ESI unless its web is split by a reload. No reload-free lever found.
