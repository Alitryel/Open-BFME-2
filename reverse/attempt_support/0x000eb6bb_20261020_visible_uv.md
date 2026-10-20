# 0x000EB6BB: visible Get_UV_Array body (closer bank)

Result: partial, banked as `reverse/attempts/0x000eb6bb.cpp` under the unchanged symbol `?rva000EB6BB@Rva000EC9C6@@QAEXXZ` (retail 0x000EB6BB..0x000EBFD1, 2326 bytes). Not byte-exact. Model: claude-opus-5-5.

## What changed and why

1. **MeshMatDescClass::Get_UV_Array(int,int) now has its body in the unit.** Retail spills the mesh model pointer to [ebp-0x58] before the capacity checks and reloads it after the Get_UV_Array call (0x60D) to call Get_Vertex_Normal_Array, but re-derives the model through `m_treeTypes[type]` after the opaque Get_Vertex_Normal_Array call (0x630). The old bank only declared Get_UV_Array, so cl re-derived the model after both calls. The body is header-inline in the original tree (its home `Code/Libraries/Source/WWVegas/WW3D2/MeshMatDescGetUVArrayRva000D1F1A.cpp` already defines it `inline`, so it is select-any and needs no linkage change). cl 7.1 at /O1 still calls it out of line, and seeing a store-free body lets it keep the model pointer across the call. The in-unit copy compiles to retail 0x000D1F1A's 38 bytes exactly. `__declspec(noinline)` is not needed here (byte-identical without it); a larger landing unit may need it.
2. **No `TreeType &tt` reference.** WorldBuilder's debug body (WB 0x89B530) re-derives `m_treeTypes[type]` for every accessor. Dropping the reference removes two structural regions.
3. **The equal-arm `(&a?a[1][1]:a[1][1])` term is gone.** On the new base it changes nothing in the counts, so the bank no longer carries it.

Semantics are unchanged from the previous bank. One inherited non-original spelling remains: the row-0 X sum of the local postMul is parenthesised `(t0 + t1) + t2`, while retail computes X0 as `(t2 + t1) + t0`, so X0 can differ from retail in the last rounding bit. Removing the parentheses makes alignment clearly worse (2323 B, 25 regions, m103, r50).

## Measurements (align_diff, BFME_OBJSTORE=off, single runs)

| Source | Emitted | Regions | Instructions inside regions (retail/ours) | Memory | Register |
| --- | ---: | ---: | ---: | ---: | ---: |
| previous bank (score 0.55) | 2337 B | 27 | 64 / 65 | 112 | 47 |
| new bank | 2331 B | 20 | 60 / 61 | 90 | 44 |

Branch lines stay at 45 and reloc lines are not defects. The stack homes that were the first difference (+0xD8: curIb, curVb, numVertex, pVert, uvs, colors) now match retail, as does the whole capacity, UV, normal and colour setup (0x58D..0x695).

## Remaining mismatch

All of it is in the transform block. (a) The shared model/colours slot sits at -0x28, above the matrix, where retail has it at -0x58 below the matrix. Every matrix home is therefore 4 bytes lower than retail's (-0x58 against -0x54). Moving declarations does not move it, so the slot order most likely follows the matrix block's spill weights. (b) At the Set/world merge retail keeps m00, m01, m02, m10, m11, m12 and m20 in XMM registers, and ours keeps m22 instead of m20. That changes the Scale, postMul and Translate allocation and scheduling, plus the summation order in Transform_Vector rows 0 and 1.

Retail's twelve postMul sums, written with t0=a_r0*b_0c, t1=a_r1*b_1c, t2=a_r2*b_2c, are: X0 (t2+t1)+t0, Y0 (t0+t2)+t1, Z0 (t2+t1)+t0, W0 (t0+t2)+t1; all of row 1 (t0+t2)+t1; X2 (t2+t1)+t0, Y2 (t2+t1)+t0, Z2 (t0+t2)+t1, W2 (t2+t1)+t0. Translate is row 0 ((z+y)+x)+W, row 1 ((x+z)+y)+W and row 2 ((x+y)+z)+W.

## Ruled out this run (sources in the seat's build/w3_eb6bb/)

- Local names do not matter: renaming 24 locals compiles byte-identical (t2_ren).
- Sharing loop variables as WB does: one `curTree` for the init loop and the tree loop moves curTree's home to -0x48 and is worse on both bases (t3, t24). One `i` for both inner loops is byte-identical (t5).
- A named `const Matrix3D &` to the record's transform, as in WB, makes things worse (t9, 2302 B). So does a Vector2 copy of uvs[i] (t10, 2302 B).
- ZH-style `Get_UV_Array_By_Index(index, create)` and `Get_Color_Array(index, create)` accessors are byte-identical (t15).
- Native Matrix3D::postMul on the new base is worse (t11: 2308 B, 22/m105/r49; t12 with the reference: 2311 B, 22/m96/r50).
- Product operand order inside the postMul is canonicalised: 16 variants differ only by the row-0 parentheses (post/).
- Forcing retail's association with parentheses: for all twelve sums (t16: 2297 B, 20 regions, but 96/90 instructions inside regions) and for subsets (t19 to t23). None is closer, because the lower operand counts come from larger unaligned regions.
- Declaration position of colors or of the Matrix3D is byte-identical (t17, t18).

## For a landing

The destination resolver offers only the neighbour heuristic `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferUpdateTexture.cpp` (tu_map proposes `W3DTreeBuffer.cpp`). Whichever unit receives the body must also carry the select-any Get_UV_Array body. The opaque Get_Vertex_Normal_Array (0x0016AB90, ordinary linkage) and the lock constructors and destructors must stay declaration-only, as retail's unit saw them.
