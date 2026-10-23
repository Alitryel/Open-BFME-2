# 0x000EBFD1 `?rva000EBFD1@Rva000EC9C6@@QAEXXZ` (1710 B): header-helper matrix block

Result: partial, banked at `reverse/attempts/0x000ebfd1.cpp` with score 0.93 (difflib byte ratio against retail; the previous bank measures 0.81 the same way). Model claude-opus-5-5, seat w5, 2026-10-20.

## Measurements (`tools/align_diff.py <file> ?rva000EBFD1@Rva000EC9C6@@QAEXXZ 0x000EBFD1 1710`)

| body | regions | memory | register | size |
|---|---|---|---|---|
| previous bank (0.82) | 23 | 57 | 35 | 1703 |
| this bank | 18 | 18 | 17 | 1710 |

## What changed

Only the matrix block. The previous bank built the matrix with the world arm first, `Make_Identity()` plus `Set_Translation(location)`, nine hand-written scale multiplies and a hand-written offset translation. This bank writes:

```cpp
Matrix3D transform;
if(!trees[i].state && !trees[i].flagC4)transform.Set(location);
else transform=trees[i].world;
transform.Scale(scale);
transform.postMul(trees[i].transform);
{const Vector3 &t=types[type].offset;transform.Translate(t);}
```

Everything from the entry to the merge of the two arms (retail +0x000..+0x224) is now retail's instruction stream apart from relocations: location.X lives in xmm5 with no stack home, M13 and M22 are enregistered at the merge (xmm7, xmm0), and the world arm loads rows 1 and 2 through `lea edi`. The body has retail's length.

## Remaining mismatch

All remaining differences follow from the float re-association of three sums. A symbolic execution of the world path prints each sum's tree for retail and for any trial source (`0x000ebfd1_20261020_assoc.py.txt`; copy it to `build/<dir>/assoc.py`, since it finds `tools/` two levels up, and run `python build/<dir>/assoc.py <trial.cpp>`):

- postMul row 0, tmpX: retail `(T00*M00 + T20*M02) + T10*M01`, ours `(T20*M02 + T10*M01) + T00*M00`. The other eight tmpX/tmpY/tmpZ sums match retail.
- Translate row 0: retail `(oX*X0 + Z0*oZ) + Y0*oY + M03`, ours `(Z0*oZ + Y0*oY) + oX*X0 + M03`. Row 2: retail X, Y, Z order, ours X, Z, Y. Row 1 matches.

These drive the scale schedule (ours multiplies M00 before M20), the spill order of [ebp-0x58], [ebp-0x5c] and [ebp-0x60] in the postMul block, and the firstVertex load (retail loads it before the translation, ours after). In the vertex loop rows 0 and 1 we emit `movaps xmm7,xmm2; mulss xmm7,[ecx]` where retail loads `[ecx]` and multiplies by the register, and row 2 sums in another order.

## Mechanism found

The association of every postMul and translation sum depends only on how the matrix block is spelled (arm order, identity form, Scale form, Translate form and how the offset is bound). Unrelated statements do not move it: splitting the visible/hidden test, pre-declared loop variables, declaring `vb` before the lock, three spellings of the arm condition, the position of `Matrix3D transform;` and four spellings of the vertex loop all give identical align_diff counts.

- Previous bank (world arm first, Make_Identity+Set_Translation, manual scale and translation): all nine postMul sums and all three translation sums equal retail, but the prefix allocation is wrong.
- Identity arm first + `Set(location)` + header `Scale` + `Translate(types[type].offset)` without the reference: prefix exact and all nine postMul sums equal retail, but translation rows 1 and 2 differ (28/53/54).
- This bank (offset bound to a reference): prefix exact, translation row 1 right, row-0 tmpX and translation rows 0 and 2 wrong.

## Ruled out this run (regions/memory/register/size)

- Arm order alone on the previous bank: 20/61/36/1706.
- Identity spellings (both arm orders, with header or manual scale): `transform=Matrix3D(location)`, 12-float `Set`, `Matrix3D(12 floats)`, `Matrix3D(true)`+`Set_Translation`, `Make_Identity`+`Adjust_Translation`, per-row `Vector4::Set` (with `.X` or `[i]`), `Set(axes, location)`, ternary construction: all at least 18 regions and 47 memory differences.
- Scale with this translation: all 36 manual column/row orders, `Scale(x,y,z)`, `Scale(Vector3&)`. The best manual order (columns 0,2,1) gives 11/23/20, which trades regions for memory and register differences and is no natural spelling.
- Translation: hand-written rows in all six row orders (term order inside a row is irrelevant; row order 1,0,2 with the hand-written form gives 15/20/24), `Translate(x,y,z)` in three spellings, a Vector3 copy, `Transform_Vector`+`Set_Translation`, `mulVector3`, a pointer to the offset (identical to the reference), a `TreeType` reference for the offset and the mesh.
- A separate product matrix (`mul` into a new local, or copy then `postMul`), a `const Matrix3D &` to the tree transform in four positions, moving `cur` or `firstVertex` before the translation or the product, moving the offset reference before the product.
- Flags and compilers, tried on the hand-written-translation candidate (17/25/22/1718): `/O2` and `/Op` far worse; `/G6`, `/Ob2` and `// compiler: vc71-ddk-4035` give identical counts; `vc71-sp1` worse (25/50/28).

## For a landing

The body still declares private `TreeRecord` and `TreeType` views. The canonical layouts are `Rva000EDA94Record` (`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h`, non-POD with a constructor) and `Rva000EC67F` (`W3DTreeTypeRecord.h`); whether compiling against them moves the allocation has not been tested. `repair_queue.py dest` only offers the neighbour heuristic `W3DTreeBufferAddTreeType.cpp` (proposed TU `W3DTreeBuffer.cpp`).
