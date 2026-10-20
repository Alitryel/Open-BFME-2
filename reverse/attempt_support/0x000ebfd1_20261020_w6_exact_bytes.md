# 0x000EBFD1 `?rva000EBFD1@Rva000EC9C6@@QAEXXZ` (1710 B): byte-exact bank

Result: partial, banked at `reverse/attempts/0x000ebfd1.cpp`. The banked body compiles to retail's 1710 bytes with no difference outside the four relocation slots (two WriteLockClass calls, TheGlobalData and the 1.0f constant), checked by a relocation-masked byte comparison of the object. It is not landed, because the steps under "For a landing" are still open. Model claude-opus-5-5, seat w6, 2026-10-20.

## Measurements (`tools/align_diff.py <file> ?rva000EBFD1@Rva000EC9C6@@QAEXXZ 0x000EBFD1 1710`, fresh objects)

| body | regions | memory | register | size |
|---|---|---|---|---|
| previous bank (0.93) | 18 | 18 | 17 | 1710 |
| this bank | 0 | 2 | 0 | 1710 |

The two remaining memory lines are the TheGlobalData load (+0xC2) and the 1.0f constant load (+0x171); both are relocation slots that read `[0]` in the object, and both were present in the previous bank's 18 as well. Raw difflib byte ratio 0.993 (previous bank 0.933 the same way).

## The two levers

**Surviving-local count.** The float re-association of every postMul and translation sum rotates with the number of surviving locals declared before the matrix block, exactly as at 0x00561564. A probe chain of pointer copies gave the same code for N and N+8 in the first cycle, and +6 locals turned the previous bank into 0 regions with only translation row 2 and vertex-loop row 2 wrong. Pointer, float and reference locals count alike when they precede the matrix; locals after the matrix block (in the vertex-loop setup or the loop) count differently. Locals that change the code (dropping `target`, `scale`, `location`, the offset reference, or rewriting all `trees[i]` through one `TreeRecord &`) do not act as pure count changes. The bank reaches +6 with six single-use copies: `indexCount`, `buffer`, `array`, `bufferIndex`, `record` and `visibleTree`.

**Parentheses.** cl 7.1 does not re-associate a float sum across explicit parentheses. Retail evaluates row 2 of both the offset translation and the vertex transform in source order, `(X+Y)+Z`, while rows 0 and 1 are re-associated. Writing row 2 as `((a + b) + c)` in TU copies of `Matrix3D::Translate(x,y,z)` (rows 0 and 1 verbatim with their `(float)( )` wrapper) and of `Matrix3D::Transform_Vector` closes both. A free helper indexed with `m[i][j]` and one using `.X/.W` members give the same bytes, and so does a derived-class copy with the header's `Row[i][j]` IL. The grouping only works with outer parentheses on rows 0 and 1; with plain rows 0 and 1 the same row-2 grouping costs 11 regions.

## Ruled out this run

- Counts +1 to +9 with the chain after the lock, counts +5 to +7, +13 and +14 at eight other positions, and a two-dimensional scan (0 to 7 locals before against 0 to 7 after the matrix block): none fixes row 2 on its own.
- Earlier single-shift rejects re-scored at all eight counts: world arm first, `Make_Identity`+`Set_Translation`, 12-float `Set`, `Matrix3D(location)`, `Scale(x,y,z)`, `mulVector3`, a pointer-walking loop, `Adjust_Translation`, `Transform_Vector`+`Set_Translation`, `Rotate_Vector`+`Adjust_Translation`. None beats the header form.
- Header-faithful nesting of the views (`Get_Vertex_Array` through a `Get_Array()`, STLport `operator[]` through `begin()`): worse at every count.
- Parentheses alone on the loop helper (outer parentheses present or absent): no effect; source operand order inside a product: canonicalized.

## For a landing

- The six count locals are single-use copies whose only job is the count. They are not dead code, but a reviewer may judge them as steering; a more natural set (for example locals the BFME 2 source really had, such as `startVertex`) has to give the same count from before the matrix block. `startVertex` itself sits after the matrix and counts differently.
- The body still declares private views. The canonical layouts are `Rva000EDA94Record` in `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h` and `Rva000EC67F` in `W3DTreeTypeRecord.h`; switching to them may move the count. `VertexBufferClass` is a private view too.
- `repair_queue.py dest 0x000EBFD1` only offers the neighbour heuristic `W3DTreeBufferAddTreeType.cpp` (proposed TU `W3DTreeBuffer.cpp`).
- Any rewrite changes the count, so re-measure after each step and adjust the count with locals before the matrix block.
