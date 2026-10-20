# UpdateShadowCamera handoff, second pass (2026-10-20, seat w5)

Result: partial, closer bank. `reverse/attempts/0x0007c8ae.cpp` now emits retail's exact size with no structural region left. Nothing was placed in `Code/`, and no pin or ledger row was added. model=claude-opus-5-5.

Target: `?UpdateShadowCamera@W3DShadowMapManager@@QAEXXZ`, RVA `0x0007C8AE`, 4176 bytes. Read the morning handoff `reverse/attempt_support/update-shadow-camera-20261020-w5/readme.md` first; this file only adds to it.

| Body | Emitted bytes | Regions | Memory | Register |
|---|---:|---:|---:|---:|
| Morning bank (RefCountPtr members) | 4184 | 7 | 62 | 2 |
| New bank | 4176 | 0 | 48 | 0 |

Measured with `tools/align_diff.py <file> <symbol> 0x0007C8AE 4176` on freshly compiled objects. About 20 of the 48 memory lines are unrelocated global operands (`[0x...]` against `[0]`); the remaining 28 are real operand differences, listed below.

## What changed

The new bank is the morning's WB-faithful variant (`wb-faithful-variant.cpp.txt` in the morning folder) plus one named reference in the hull intersection loop:

1. Both hull loops test `i < hull.size()` and no `count` local exists (WB recomputes `(end-begin)>>3` in each loop condition).
2. The points push converts through `BfmeE8(const Vector3 &)` (WB copies through a reference).
3. The final loop builds `PlaneClass plane(p1, p2, p3)` (retail emits that constructor out of line at `0x0007C292`).
4. New: `const Vector3 &p = (const Vector3 &)hullPts[i];` in the intersection loop, used in all four statements. This is the change that removed the 7 regions in the second corner loop and the operand differences around the two later `mulVector3Array` calls. Caveat: WB does not name this reference. It computes `&hullPts[i]` once for the inlined `operator+` parameter and recomputes it for the `Compute_Intersection` argument, so `p` is a readable spelling that the measurement favours, not one the WB twin proves. A pointer (`const Vector3 *p`) compiles identically.

## Remaining mismatch (28 operand sites, all re-association or load/fold picks)

- `Transform_Vector` row 0 at +0x68A..+0x698 (4 sites): retail computes the Z product first (`m02` loaded, `v->Z` folded) and then the X product with `v->X` loaded and `m00` folded; ours computes the X product first with `m00` loaded and `v->X` folded. Both then add Y.
- Rows 1 and 2 of the same call at +0x6B8..+0x703 (12 sites): retail sums `(X + Y) + Z`; ours sums `(Y + Z) + X`.
- `lightDir + p` in the intersection loop at +0x7A2..+0x7E8 and +0x839..+0x877 (12 sites): retail loads `p.Z` (`[esi]`, displacement 0) and folds `lightDir.Z`, and computes Y before Z; ours loads `lightDir.Z` and folds `[esi]`.

## Mechanism found this pass

A chain of N pointer-copy locals (diagnostic only, never for landing) rotates every re-association and load/fold pick in this body with period 8, and the result barely depends on where the chain sits: at function scope (top, before the hull call, before the four-corner `mulVector3Array`) and inside the first corner, intersection, min/max, second corner or final loop body it gives the same code at every shift; only a chain before the last `mulVector3Array` differed slightly, at shifts 6 and 7. Each code region has its own window of shifts in which it matches. For the new bank (shift 0 = the bank as written):

| Region (retail offsets) | Matches at shifts |
|---|---|
| Normalize and cross products, +0xD5..+0x179 | 0 only |
| Frustum lerp and point push | all |
| First `mulVector3Array` | 0, 1, 2 |
| `Transform_Vector` row 0 | 4, 5, 6 |
| `Transform_Vector` rows 1 and 2 | 1, 2, 5, 6, 7 |
| `lightDir + p` in the intersection loop | never |
| Second `mulVector3Array` of four corners, second corner loop, last `mulVector3Array` | 0, 1, 2 |
| Z range, centre and camera tail | all |

So no global count fixes the rest: the row and intersection-loop regions need a change in their own IL, and every natural knob tried either acted as a pure shift (breaking the normalize region) or left them unchanged.

## Ruled out this pass (each measured on top of the new bank or the WB variant)

- Named `minZ` removed (WB has no named slot for it; it is a temporary feeding `max`): identical code.
- `PointList` of `Vector3` with a `Vector3 blank`, and WB's per-vector default fill (`PointList x(n, Vector3())`, three separate sentinel temporaries in WB, no `blank` local): with `p` they reproduce shifts +1 and +2 of the new bank exactly; without `p` (the fully WB-faithful form) the normalize region stays wrong at all eight shifts.
- Named `Vector3 pt` for the `Transform_Vector` input: a +1 shift (rows 1 and 2 then match, the normalize region breaks).
- Named `Vector2` in the min/max loop, named `Vector3 &c` in the second corner loop, a named reference for `groundPts[i]`: worse or pure shifts.
- `p` declared before `t`, non-const `p`, `p + lightDir` operand order, `&(Vector3 &)hullPts[i]` output spelling: identical code.
- `p` used in only some of the four statements: the variant using `hullPts[i]` for the first `Compute_Intersection` argument and `p` elsewhere fixes the `lightDir + p` sites but reopens the 7 corner-loop regions (4184 B, 7/89/6).

## Still open for landing

The morning readme's flag conflict stands: the destination unit's `/Oi` turns the three `fabs` calls into intrinsics and `/D_CRTIMP=` turns retail's `call [__imp__finite]` into a direct call, so an exact body needs a unit without `/Oi` that keeps `_finite` dllimport.

Raw logs (untracked): `build/w5_7c8ae_b/results.log` (one line per trial with every differing site), `build/w5_7c8ae_b/k1.tab`, `k2.tab`, `k5.tab` (knob grids), trial sources and disassembly under `build/w5_7c8ae_b/`.
