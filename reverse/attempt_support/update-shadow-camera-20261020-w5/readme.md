# UpdateShadowCamera handoff (2026-10-20, seat w5)

Result: partial, closer bank. `reverse/attempts/0x0007c8ae.cpp` now models `m_camera` and `m_sceneCamera` as `RefCountPtr` members whose inline `operator->` retail expands to a member load. Nothing was placed in `Code/`, and no pin or ledger row was added. model=claude-opus-5-5.

Target: `?UpdateShadowCamera@W3DShadowMapManager@@QAEXXZ`, RVA `0x0007C8AE`, 4176 bytes. All measurements use `tools/align_diff.py <file> <symbol> 0x0007C8AE 4176` on a freshly compiled object (each trial at its own path, object deleted first).

| Body | Emitted bytes | Regions | Memory | Register |
|---|---:|---:|---:|---:|
| Previous bank | 4173 | 24 | 97 | 30 |
| New bank (RefCountPtr members) | 4184 | 7 | 62 | 2 |

About 20 of the memory lines in both rows are unrelocated global operands (`[0]` against `[0xdfe758]` and similar), which the tool counts as memory.

## Identity and new evidence

The WorldBuilder twin (WB VA `0x7F0310`, 23902 bytes, `python tools/wb_show.py 0x0007C8AE`) reaches both cameras through out-of-line accessors whose assertions name `RefCountPtr<class CameraClass>::operator->` (WB `0x4675A0`, on `this+4`) and `RefCountPtr<class W3DShadowMapManager::ShadowMapCamera>::operator->` (WB `0x7F6F70`, on `this+0`). The previous bank used raw pointers. With the inline accessor modelled, the initial cross product, the axis1 and temporary stack slots, both `Set_Clip_Planes` call sequences, the ceiling-point pointer in ESI in the final plane loop and the `lea ecx,[eax+0x3FC]` forms all match retail. This is target evidence (WB is the same source tree built unoptimised); the class body is a minimal view.

## Remaining mismatch in the new bank

1. Frustum interpolation `(Corners[i+4] - Corners[i]) * t + Corners[i]` at retail +0x447: retail computes the three differences, then the three products, then folds `Corners[i]` into each sum; ours multiplies Z early and loads `Corners[i].Z` and `.X` into registers (4 regions, +8 bytes).
2. Hull point push at +0x5A9: retail loads and stores X, then Y, through xmm0; ours loads Y first (3 regions).
3. `lightInv.mulVector3Array(corners, 8)` at +0x4D6: retail associates each row as `(R1*Y + R2*Z) + R0*X`; ours as `(R2*Z + R0*X) + R1*Y`. The out-of-line copy this unit emits is already identical to retail's `0x0007B459`, so only the inlined context differs.
4. `Transform_Vector` row 0 at +0x68A and the Z component of `lightDir + hullPts[i]` at +0x7A2/+0x839: retail loads the `[reg]` (displacement 0) element and folds the local; ours does the reverse.

All four are operand-rank or scheduling choices; none is a semantic difference.

## WorldBuilder-faithful spellings (measured on top of the RefCountPtr body)

WB shows several details that the bank does not spell the same way. Each is evidence about the source, but none beats the new bank under the region-first rule:

| Variant | Bytes | Regions | Memory | Register | Effect |
|---|---:|---:|---:|---:|---|
| `i < hull.size()` in both hull loops, no `count` local (WB recomputes the size each iteration) | 4176 | 17 | 100 | 0 | fixes items 1 and 3, disturbs both intersection loops |
| same, element type `Vector3` (WB fill values carry the Vector3 debug sentinel) | 4176 | 17 | 88 | 0 | |
| `BfmeE8(const Vector3 &)` conversion for the point push (WB copies through a reference local) | 4183 | 18 | 112 | 1 | fixes item 2 exactly, disturbs later loops |
| hull.size() + conversion + `PlaneClass plane(p1, p2, p3)` constructor (WB builds N after the arguments; retail emits that ctor at `0x0007C292`) | 4184 | 7 | 79 | 6 | items 1, 2 and 3 all match; 7 regions remain in the second corner loop (+0xB8B..+0xC95) |
| `Matrix3D lightTm(axis1, axis2, lightDir, Vector3(0,0,0))` (WB constructs the matrix after its arguments) | 4184 | 7 | 62 | 2 | no change |

The fourth row is saved as `wb-faithful-variant.cpp.txt` beside this file. It is the more source-faithful starting point for the next attempt: its only structural regions are in the `ground`/`ceiling` loop over `corners[0..3]`, where the same "displacement-0 element against local" operand rank decides the order.

## Hypotheses ruled out

- Callee visibility. Retail's unit range holds out-of-line `PlaneClass::Set(p1,p2,p3)` (`0x0007BFC2`) and `vector<Region2D>::erase` (`0x0007C2F0`), so their bodies were visible there; byte-faithful `__declspec(noinline) inline` copies change nothing (identical code). Making `camera.cpp`'s `Get_Clip_Planes` or `Set_View_Plane` visible regresses badly (29 regions), consistent with retail not seeing them; `Set_Clip_Planes` visible changes nothing.
- Statement spellings of the interpolation (named delta, `C0 + d*t`, `t * d + C0`), the point temporary (named local, member assignment), `p + lightDir` operand order and a `Vector2`-style body constructor all compile identically or regress.
- Flags: the destination unit's `/Oi` turns the three `fabs` calls into intrinsics (4078 bytes, 49 regions), and `/D_CRTIMP=` turns retail's `call [__imp__finite]` into a direct call. Landing this body in `W3DShadowMapConvexHull.cpp` therefore needs that unit to drop `/Oi` (the bank uses `#pragma intrinsic(sqrt)` for the hull's square root) and keep `_finite` dllimport; check the hull row still matches when doing so.

Raw logs (untracked): `build/w5_7c8ae/*-align.log`, `build/w5_7c8ae/summary.tsv`, retail and trial disassembly in `build/w5_7c8ae/*.asm`, WB dump in `build/w5_7c8ae/wb_show.txt`.
