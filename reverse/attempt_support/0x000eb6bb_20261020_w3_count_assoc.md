# 0x000EB6BB: local-count and parentheses levers from 0x000EBFD1 tested (blocked)

Result: blocked. The bank `reverse/attempts/0x000eb6bb.cpp` (symbol `?rva000EB6BB@Rva000EC9C6@@QAEXXZ`, retail 0x000EB6BB..0x000EBFD1, 2326 bytes) stays unchanged, because no body measured closer. Model: claude-opus-5-5, seat w3, 2026-10-20.

## Measurements (align_diff, BFME_OBJSTORE=off, single runs)

| Source | Emitted | Regions | Memory | Register |
| --- | ---: | ---: | ---: | ---: |
| bank (unchanged) | 2330 B | 14 | 52 | 37 |
| best TU Translate variant (bank treePost, TU Translate, no extra locals) | 2325 B | 16 | 54 | 40 |
| best Set-arm-first variant (TU Translate) | 2330 B | 14 | 62 | 38 |
| best with WorldBuilder's natural locals (`mtx` reference, bank treePost, header Translate, five more probe locals) | 2331 B | 15 | 59 | 38 |
| all twelve postMul sums forced to retail's association, TU Translate with retail association | 2293 B | 17 | 80 | 38 |
| best native header postMul (TU Translate in retail association, 84 probe locals) | 2308 B | 15 | 82 | 36 |

None is closer than the bank in every class, so none was banked.

## How association was measured

A symbolic executor ran each object's world arm and merge through Translate and printed, for every postMul and Translate sum, which pair cl adds first (for example `{t0,t2}+t1`). It reproduces retail's associations from retail's bytes: X0 {1,2}+0, Y0 {0,2}+1, Z0 {1,2}+0, W0 {0,2}+1, all of row 1 {0,2}+1, X2 {1,2}+0, Y2 {1,2}+0, Z2 {0,2}+1, W2 {1,2}+0, and Translate {y,z}+x, {x,z}+y, {x,y}+z. The script is kept as `reverse/attempt_support/0x000eb6bb_20261020_w3_assoc_tool.py.txt` (run it from a folder holding `retail.bin`, the 2326 retail bytes).

## Findings

1. **The count model holds here, but with period 32, not 8.** Single-use probe locals of pointer, int and float type give the same object for the same total, whether placed at the function top, before the locks or in the tree loop before the matrix block. WorldBuilder's `vb`/`ib` copies (ZH and WB 0x89B6D5) act as exactly two more locals. Locals placed after the matrix block (before `startVertex`) count differently. Counts 37 and 69, and 29 and 61, compile identically.
2. **The header postMul with a count shift alone cannot produce retail's arithmetic.** Over 201 builds with the native `Matrix3D::postMul` (counts 0 to 88, all probe types, and a two-dimensional scan of locals before and after the matrix), at most 11 of the 15 sums take retail's association (count 15), and Z0, W2 and Y2 never do at any count.
3. **WorldBuilder's `mtx` reference changes the ranks.** With `const Matrix3D &mtx = trees[curTree].transform;` bound before the mesh check, as WB 0x89B7E6 has it, and the native postMul, every sum reaches retail's association at some count, but no count from 0 to 71, and no combination of locals before and after the matrix block tested, gives more than 10 of 15.
4. **The local `treePost` never re-associates rows 1 and 2.** At every count they compile in source order `{t0,t1}+t2`, which retail never uses in the postMul. Together with WB's inlined by-value `submul`, this supports the header postMul as the original source, so the bank's local `treePost` is a structural dead end for an exact match.
5. **The parentheses lever works for Translate.** A TU copy of `Matrix3D::Translate(x,y,z)` with rows 0 and 1 in `(float)( )` and row 2 written `((a + b) + c)` gives all three Translate sums retail's association in every native build. A TU `Transform_Vector` with row 2 grouped compiles byte-identically to the header form, because the vertex loop already matches retail.
6. **Forcing retail's association does not fix allocation.** With all twelve postMul sums and all three Translate sums parenthesised to retail's association, the arithmetic is retail's, but without wrappers the body is 29 to 45 bytes short (fewer spills) at every count, and with `(float)` wrappers it is 2318 to 2340 bytes and at best 16 regions, m98, r45. Neither is closer.
7. Set-arm-first (`if(!state && !flagC4) Set(location); else world`, the sibling's form) lays out identically and is worse in memory lines.

## Ruled out this run (about 700 builds)

- postMul {bank, plain, native, all-retail, all-retail with `(float)` wrappers} crossed with Translate {header, TU with grouped row 2, TU in full retail association} and with 8 to 88 count shifts.
- WB natural locals (`vb`/`ib`, `mtx`, both) crossed with the same postMul and Translate forms and 8 to 72 count shifts.
- Set-arm-first crossed with natural locals and all postMul and Translate forms.

## Next step

The ranks that drive cl 7.1's float re-association depend on more than the local count: the `mtx` reference alone reopened the three sums the count could not reach. The next agent should model the rank rule in a small controlled TU (one `Matrix3D` local, `Scale`, header `postMul`, `Translate`, and a variable number of locals and references), find which declarations give retail's 15 associations, and only then transfer them to the body. The candidates for extra rank inputs are named references that WB keeps (`mtx`) and the way the transform is built (struct copy against `Set`). Keep the TU Translate copy; it is already right.
