# 0x00175E50: AABoxRenderObjClass::Render, blocked on when cl folds the diagonal 1.0

## Result

Blocked. The banked body in `reverse/attempts/0x00175e50.cpp` stays as it is (score 0.48). No source in this run came closer than it, but the run found what the remaining difference is, which no earlier verdict had pinned down.

Retail and every natural spelling compute the same three translation sums after the identity's zero products, but they group them differently. Writing `x`, `y` and `z` for `Transform[0][3]`, `[1][3]` and `[2][3]`:

| | row 0 (`_41`) | row 1 (`_42`) | row 2 (`_43`) |
|---|---|---|---|
| retail 243 B | `(y*0 + z*0) + x` | `(y + x*0) + z*0` | `(z + x*0) + y*0` |
| every natural source here, 246 B | `(y*0 + z*0) + x` | `(x*0 + z*0) + y` | `(x*0 + y*0) + z` |

In our compiles the unit term of every row is added last. In retail that holds for row 0 only. In rows 1 and 2, retail adds the unit term first.

## The diagnostic that isolates it

The `Matrix3D` 12-float constructor gives the identity with a chosen diagonal. Only the diagonal was changed, so these trials are diagnostics and cannot land:

| diagonal (rows 0, 1, 2) | row 0 | row 1 | row 2 |
|---|---|---|---|
| 1, 1, 1 | `(y*0+z*0)+x` | `(x*0+z*0)+y` | `(x*0+y*0)+z` |
| 1, 2, 2 | `(y*0+z*0)+x` | `(y*2+x*0)+z*0` | `(z*2+x*0)+y*0` |
| 1, 2, 1 | `(y*0+z*0)+x` | `(y*2+x*0)+z*0` | `(x*0+y*0)+z` |
| 2, 1, 1 | `(x*2+y*0)+z*0` | `(x*0+z*0)+y` | `(x*0+y*0)+z` |
| 2, 2, 2 | `(x*2+y*0)+z*0` | `(y*2+x*0)+z*0` | `(z*2+x*0)+y*0` |

Diagonal (1, 2, 2) reproduces retail's grouping in all three rows (the trials with a 2 are 255 to 263 B because the 2.0 multiplications stay), and each row responds only to its own diagonal. So retail behaves as if `Row[1][1]*t[1]` and `Row[2][2]*t[2]` were still multiplications when cl reassociated the row sums, and were folded to plain `y` and `z` only afterwards, while `Row[0][0]*t[0]` was folded to `x` early (a 2 in row 0 gives `(x*2+y*0)+z*0`, which retail does not have). In our builds cl folds `1.0*y` and `1.0*z` to the leaves before it reassociates. A leaf is the oldest value in its row, and cl adds the oldest value last.

A partial model: cl combines the two most recently created values of a sum first. It explains why the folded leaf always goes last and why a fresh product in rows 1 and 2 goes first, but it does not predict row 0 with a 2 on the diagonal, so it is incomplete.

## Retail evidence that the construct differs

The matched BFME 2 body `W3DBoatWakeModelDraw::doDrawModule` (0x000D0D24, `Matrix3D mtx(true); mtx.Translate(transformMtx->Get_Translation());`, /O1 /G7 /arch:SSE) has our unit-term-last grouping in retail at 0x000D0DC0 to 0x000D0E44. BFME 2's own Translate on a fresh identity therefore folds the diagonal early, like ours. AABox Render's retail body is not the plain `Matrix3D temp(1); temp.Translate(...)` construct with this header set, or something in its unit delays the fold of the diagonal for rows 1 and 2.

The identity and boundary from the earlier verdicts stand: the AABox vtable 0x7D3D50 slot 12, a native 0x175E50 to 0x175F43 `ret 4`, and its only call is `render_box` 0x00174F40. The 1.0 at 0x00BBB8D8 is the literal `__real@3f800000`, the same symbol our build references.

## Ruled out in this run

Each trial is measured by its grouping signature (above) and size. Every item of this list except the static identity emits the unit term last in rows 1 and 2.

- BFME 1's Z/X/Y translation local with `Translate(const Vector3&)`: 246 B, loads y, z, x like retail.
- The same local with `Translate(float,float,float)`, or `Matrix3D(1)` placed before the local: 246 B.
- Zero Hour's `Translate(Transform.Get_Translation())`, `Get_Translation(&v)`, and `Translate(Get_X_Translation(), ...)`: 246 B.
- The identity from the 12-float constructor or the four-`Vector3` constructor: 246 B.
- Translate written out with `.X/.Y/.Z` members, or with raw `float *` indexing of `temp`: 246 B.
- Translate on `temp` through a pointer, and an inline helper returning the translated identity by value: 246 B.
- The Matrix4x4 overload of `Set_Transform`, and a direct transposed write of `render_state.world` as the consumer: 246 B.
- `Translate_X(x)` followed by `Translate(Vector3(0,y,z))`: 261 B.
- `Transform_Vector(temp, t, &t)` then `Set_Translation`: 247 B. `Rotate_Vector` then Translate: 295 B.
- The identity assigned from a temporary (`Matrix3D temp; temp = Matrix3D(1);`): 246 B.
- `Matrix3D temp(Matrix3D::Identity)`: 423 B, every coefficient becomes a memory load, so retail does not read a static identity.
- `/O1`: 248 B with the same grouping. `/arch:SSE2` on the bank, the BFME 1 form and the Zero Hour form: 246 B with the same grouping.
- The pinned `// compiler: vc71-sp1` profile on the bank and on the BFME 1 form: 246 B with the same grouping.

## Measurements

`python tools/align_diff.py <file> '?Render@AABoxRenderObjClass@@UAEXAAVRenderInfoClass@@@Z' 0x00175E50 243`

| source | size | structural regions | memory | register |
|---|---|---|---|---|
| existing bank (unchanged) | 246 B | 7 | 21 | 10 |
| home `boxrobj.cpp` copy (present-unmatched, current link-view headers) | 355 B | 9 | 18 | 9 |

The 21 memory lines of the bank are almost all unpatched global store addresses (`render_state.world` and `render_state_changed`) plus the three load registers. The real defects are the grouping above and the register assignment it causes.

## Next lead

Look for a source or header construct in which the identity's diagonal of rows 1 and 2 reaches the Translate sums as a value cl does not fold before reassociation, while the zeros are known. The refutation check is cheap: evaluate the compiled SSE stream symbolically and compare the three groupings with retail's. Any candidate whose rows 1 and 2 still end with the unit term cannot match.
