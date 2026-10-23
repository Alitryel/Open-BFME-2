# FXShaderGeometry::Init: WorldBuilder-faithful inline layers

Target `?Init@FXShaderGeometry@@QAE_NPAVMeshModelClass@@@Z`, retail 0x0018C84E, 2,333 bytes, RET 4. The new bank is `reverse/attempts/0x0018c84e.cpp` (partial, score 0.995). No production source, pin or ledger row changed.

## Result

| Measurement (`tools/align_diff.py`) | Previous bank | New bank |
| --- | --- | --- |
| Size | 2,333 B, 735 insns | 2,333 B, 735 insns |
| Structural regions | 2 | 0 |
| Memory operand differences | 14 | 12 |
| Register operand differences | 0 | 0 |
| EH tables (`eh_verify.verify_row`) | EXACT | EXACT |
| Unresolved calls (`explain_mismatch.py`) | short `_Vector_base` ctor at +0x473 | same, unchanged |

Five of the twelve memory lines in the new bank are absolute-address relocation slots (`[0xde0880]` twice, `[0xdfcebc]` twice, `[0xbcf628]`), which the old bank had too. The seven real ones form one block: the two-bone bone-index read at retail +0x707..+0x71E.

## What changed and the evidence for it

The WorldBuilder body (WB 0xA39110, `tools/wb_show.py 0x0018C84E`) is an unoptimised build of the same source, and it shows every accessor the source called. The new bank spells those calls instead of reading fields directly:

- Descriptor offsets go through inline getters. WB calls the location and normal getters with a stream index (0 for the base stream, 1 for the second skinning stream), so the descriptor's 0x10..0x1C fields are two arrays of two offsets. The other getters mirror the existing field names, and `Is_Plain_FVF` is WB 0xA2D130 (the VB-path test).
- Mesh access goes through the ZH `meshmdl.h` forwarders (`Get_Color_Array`, `Get_UV_Array_By_Index(int)`, `Peek_Single_Material`, `Has_Material_Array`), the WB assert's `Peek_Single_FX_Shader()`, `Get_Vertex_Bone_Links()`, `Get_Polygon_Array()` and `Get_Vertex_Count()` everywhere WB calls it.
- The STL mock follows STLport 4.5.3 more closely: vector teardown through `_Destroy` and `allocator::deallocate(p, n)`, the set's size and iterators through an `_Rb_tree` member, and `m_bones.assign(bones.begin(), bones.end())` through `_M_assign_dispatch` into the rowed 0x18C73C body.
- The link count is `Get_Vertex_Count() * rva0018C088()` in WB's order. That order only matches retail when the 19-byte helper is visible, so the bank carries a `__declspec(noinline) inline` copy of it, which the measurement shows is byte-identical to retail 0x0018C088.
- The old `firstBone` local is gone. The two-bone sum is written as WB evaluates it.

## Why it moved: the offset-0 operand order follows the IL temp count

For the induction-variable families with no displacement (the binormal pointer at ebp-0x10 and the bone-link pointer at ebp-0x2c), cl orders `diff + iv` in the SIB by internal number. A diagnostic copy with N throwaway statements shows that the flip depends only on the total count, not on where the statements sit: inserted after the index-buffer loop at the end of the function, they flip it just as they do at the top. The number of throwaway statements needed to flip it fell with each faithful layer: more than 32 for the old bank, 38 to 56 after the descriptor getters (partial at 38, complete at 56), 29 after the mesh forwarders and the visible helper, 14 after the shader and material forwarders, 13 after the bone-link and FVF-path accessors, 3 to 4 after the STLport teardown, and 0 with the tree and assign layers. So the new bank needs no dead code. Around 450 statements the order flips back, which fits a wrap of the internal numbering. The throwaway statements were used only for measurement and are not in the bank.

## Remaining mismatch

The two-bone block allocates its registers the other way round. Retail loads the link difference into ecx and the link pointer into eax, keeps the remap base in ecx and computes `remap[links[0][i]]` before `remap[links[1][i]]`. Ours puts the difference in eax and the pointer in ecx, and computes `remap[links[1][i]]` first. Ruled out on the new bank:

- Total temp count: no count of throwaway statements from 0 to 450 makes this block match (some counts break other places instead).
- Local insertion before the two-bone statement, before the one-bone statement, at the top of the vertex loop and before the remap vector: no change.
- Commuted sum, `* 256`, explicit `int` casts and an unsigned store: no change.
- The old `firstBone` local brings back the two-region hoist (2 regions, 3 memory lines).

The short `_Vector_base` constructor call (retail 0x00211E58) is still unresolved. Its fold proof is blocked by the short alloc proxy pinned at 0x7410 while 0x211E58 calls 0x14F3C4 (see `reverse/attempt_support/fxinit-provider-20261019/readme.md` and `reverse/attempt_support/fxinit-utf16-family-20261020/readme.md`).

## Notes for landing

- The bank builds with `/EHsc`, and the home `Code/Libraries/Source/WWVegas/WW3D2/FXShaderGeometry.cpp` links without it, so an exact body goes into a new standalone unit next to it.
- The visible `rva0018C088` copy needs its home `Code/Libraries/Source/WWVegas/WW3D2/MeshGeometryRva0018C088.cpp` to become `__declspec(noinline) inline` with an absent-from-retail anchor, or the two definitions collide (LNK2005).
- `Get_Vertex_Bone_Links` is already select-any in its home: `meshgeometry.cpp` takes it from the header as an inline accessor.
- The accessor names mirror the bank's existing field names, ZH or WB. None of them is a new identity claim.

Scratch sources, objects and the sweep scripts are in the ignored `build/fx6/` of the seat that produced this attempt.
