# RVA 0x000EB6BB farm review

Result: blocked. Retain `reverse/attempts/0x000eb6bb.cpp` byte for byte. No production source, ledger row, header or pin changed. The symbol remains `?rva000EB6BB@Rva000EC9C6@@QAEXXZ`; its retail extent is 2326 bytes at `0x000EB6BB..0x000EBFD1`. The destination resolver selects `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferUpdateTexture.cpp` by its neighbor heuristic and reports no usable approved TU. A future exact recovery needs coherent integration there.

The checkout revision is `04a6b1d12b2a4b7bc81e7ed58ccb3c2cfebdc2d7`; the BFME 1 checkout revision is `a18d9ed50607e9175de4d6568798d7d73119de09`. The source's first compiler line specifies `/O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG` and the BFME 1 WWMath, WWLib and WWDebug include directories. All measurements set `BFME_OBJSTORE=off`, use unique scratch source paths, and explicitly request the 2326-byte retail extent. All bodies exceed three quarters of retail size. These are single measurements per candidate.

## Identity and semantics

Target evidence independently establishes the function boundary: the preceding body returns at `0x000EB6BA`, this body starts with an EH prologue at `0x000EB6BB`, and it returns at `0x000EBFD0`. The Ghidra inventory separately records the same start and size. ECX supplies this and RET has no argument-pop immediate. Native accesses confirm the initialized and dirty gates, 0xE8 records at +0x5C0, 0x5C types at +0x44558, 44-byte output vertices, the 30000/60000 capacity tests, world-or-location transform initialization, scale, composition, translation, normals, colors and atlas UVs. The lock constructors at `0x00138790` and `0x001394A0`, destructors at `0x00139530` and `0x00138840`, UV accessor at `0x000D1F1A`, and normal provider at `0x0016AB90` resolve to their matched bodies. No unresolved relocation remains.

Donor evidence supplies the buffer-loader semantic relationship from Zero Hour's `GeneralsMD` W3DTreeBuffer.cpp and matrix postMul arithmetic from BFME 1's matrix3d.h. BFME 1's W3DTreeBufferRva00734270.cpp is the adjacent updater semantic guide, not an identity proof for this loader. The real loader name remains an inference, so the address-derived bank symbol is retained. The farm diff changes row-zero multiplication operand spellings and introduces a cached type reference. It does not remove an operation, add a volatile access or create a new store. The remaining equal-arm expression `(&a ? a[1][1] : a[1][1])` selects the identical initialized coefficient, and target a is a local matrix distinct from the record used as b. This audit found no semantic defect requiring replacement under the assignment's semantic-correction exception.

## Controlled experiments

All ten prior verdicts were read before the first measurement. None cites a separate attempt-support path; a targeted search of the support directory found none for this body. The hypothesis and refutation criteria were written before each experiment in `build/eb6bb_w7/hypotheses.md`.

| Source under build/eb6bb_w7 | Emitted bytes | Structural regions | Memory differences | Register differences | Patched positional differing bytes |
|---|---:|---:|---:|---:|---:|
| before.cpp, current bank | 2337 | 27 | 112 | 47 | 1863 |
| prefarm.cpp, 8a1c9f4566a73b3baeaeb21dab60756e54bba766 | 2326 | 35 | 111 | 61 | 1205 |
| oldmath_tt.cpp, old arithmetic with cached type | 2326 | 35 | 108 | 61 | 1209 |
| farmmath_nott.cpp, farm arithmetic without cached type | 2337 | 25 | 114 | 47 | 1856 |

H1 proposed that the farm's instruction metric had accepted an alignment regression. Restoring the complete pre-farm bank refutes that proposal under the required comparison: it increases structural regions and register differences. H2 separated the farm's two edits to test for opposing effects. Neither isolation is admissibly closer. The uncached farm body improves structural regions but adds two memory differences; the old arithmetic worsens structural and register differences. Lower positional differing-byte counts do not establish a gain. Retained-bank before and after measurements therefore remain 1863 positional differing bytes, 27 structural regions, 112 memory differences and 47 register differences, with an 11-byte emitted overrun.

The first mismatch remains stack homes at +0xDA. Matrix initialization, Scale and postMul still differ in XMM allocation, scheduling, stack spills and stores. Existing verdicts already exhaust the documented flag, row permutation, native-postMul, by-value and barrier searches. The controlled farm decomposition supplies no new lever for another justified codegen experiment.

## Raw evidence and checks

`build/eb6bb_w7/prior_verdicts.log` and `farm_diff.log` contain the raw prior rows and historical source diff. Each source stem has an `_align.log` containing complete align_diff output and a `_probe.log` containing patched byte counts, full target/candidate disassembly and object relocations. `probe.py` produces the latter directly from the built object and retail image. The entire trial sources and raw logs remain under `build/eb6bb_w7/` as requested.

All four align_diff diagnostics and all four object/retail probes completed successfully; none is byte-exact. `tools/check_csv.py` passed (`build/eb6bb_w7/check_csv.log`). `tools/pin_consistency.py --check` passed (`build/eb6bb_w7/pin_consistency.log`). No exact recovery was entered, so add_match and build.sh were not invoked. No background process was started. The session start was measured at `2026-10-19 07:30:53 UTC`; the final clock receipt is `build/eb6bb_w7/finish.json`.
