# 0x00148180 DX8RigidFVFCategoryContainer::Add_Mesh — escape closure handoff (2026-10-20)

Bank: `reverse/attempts/0x00148180.cpp`, fit 0.9973, 919/919 B, nd=2, run from a
directory five levels below the root after its `HEADER_TRIAL` prerequisite.
Model claude-opus-5-5, about 3 h.

## Target facts (retail bytes)

- Retail holds `split_table` fields (`mmc`, polygon/vertex counts) in callee-saved
  registers across the ctor, `Peek_*`, ITTC and GTC calls, rematerialising them
  from `[esp+obj+off]` under pressure. The old bank (0.8152) reloaded them after every call.
- The frame is 4 bytes larger than with the ZH `AppendLockClass`: BFME's lock is
  `VertexBuffer, Vertices, BFMEDX8DeviceLock device_lock` (0xC B, see
  `Code/Libraries/Source/WWVegas/WW3D2/VertexBufferLockClasses.cpp`, 4-arg ctor
  0x1395B0 `??0AppendLockClass@VertexBufferClass@@QAE@PAV1@IIH@Z`).

## Structural inference (compiler behaviour, probed)

MSVC 7.1 performs intra-TU escape analysis: `&split_table` must reach only
functions with bodies in the same TU for its fields to survive calls. Retail's
TU therefore defined all of these (now split across repo TUs):

| RVA | body | current TU |
|-----|------|------------|
| 0x1454D0 | Vertex_Split_Table ctor (129 B) | VertexSplitTableConstructorBFME.cpp |
| 0x144380 | Vertex_Split_Table::Peek_Texture (returns RefCountPtr) | VertexSplitTablePeekTexture.cpp |
| 0x1443D0 | Vertex_Split_Table::Peek_Shader | VertexSplitTablePeekShader.cpp |
| 0x145560 | Vertex_Split_Table::Peek_Material | DX8GenerateTextureCategoriesBFME2.cpp |
| 0x146BA0 | Generate_Texture_Categories (788 B) | DX8GenerateTextureCategoriesBFME2.cpp |
| 0x146950 | Insert_To_Texture_Category (589 B) | DX8InsertTextureCategory.cpp |
| 0x145620 | DX8TextureCategoryClass::Add_Mesh (1096 B) | DX8TextureCategoryAddMesh.cpp |
| 0x143A70/0x144330/0x143AA0 | dtor, Get_Vertex_Array, Get_Vertex_Count | dx8renderer.cpp already |

The bank uses in-class/visible stand-ins for them (ITTC as a non-escaping stub)
— enough to probe codegen, not landable. Probes: build/am/mini m9–m14 (untracked).

## Fit history

0.8152 (old bank) -> 0.90 (pure ZH body on base t3) -> 0.9509 (closure visible)
-> 0.9973 (device_lock in AppendLockClass).

## Remaining residue (2 bytes)

```
 cmp dword ptr [esp + 0x20], 0
 je T
-mov ebx, dword ptr [esp + 0x18]     retail
-mov eax, dword ptr [esp + 0x1c]
+mov ebx, dword ptr [esp + 0x1c]     ours
+mov eax, dword ptr [esp + 0x18]
 mov eax, dword ptr [eax + ebx]
```

Commutative operand order of the strength-reduced `diffuse[i]` address expressed
through the specular induction variable (`[iv + delta]` vs `[delta + iv]`).

Tried, no change or worse: local declaration order, `*(p+i)` spelling, `int i`,
colour arrays fetched first, ITTC visible vs stubbed (base t2 vs t3), non-const
colour pointers (does not compile: accessors return const), /Oa and /Ow.
`tools/permute.py 0x00148180`: "only constants or offsets differ (2 instruction(s)):
a layout fact, not an order" (one trial, no search possible).

## Port prerequisites (the real work)

1. Every closure body above defined in dx8renderer.cpp (rehome the rows; out-of-class
   members must be single definitions, not inline COMDAT copies, and must keep
   their own flags: GTC/TextureCategory Add_Mesh use `/O2 /arch:SSE /G7`, ITTC has
   no /G7 or /arch:SSE, Peek_Texture/Peek_Shader `/DNDEBUG /MD /EHsc`). A flag
   conflict inside one TU is itself evidence to check against retail first.
2. A dx8vertexbuffer view with the 4-arg AppendLock ctor and device_lock
   (`reference/shims/vertexbufferlock/dx8vertexbuffer.h` has device_lock but only
   the 3-arg ctor; users: W3DTerrainTracksReAcquire, W3DRoadBuffer, W3DBibBuffer).
3. The `const Vector3 *Get_Vertex_Normal_Array(bool)` overload (meshgeometry shim
   lacks it).
4. S2FVFInfo / BfmeDynamicSortingVB / BfmeDynamicNativeVB views as in the bank.
Real TU context may move the residue; re-score after each step.
