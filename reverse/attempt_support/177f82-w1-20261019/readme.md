# Renderer 0x00177F82

Result: a closer bank for `?rva00177F82@Rva00177860@@QAEXAAVRenderInfoClass@@@Z`, retail RVA `0x00177F82`, extent 3781 bytes. The replacement changes only the two UV loop guards from unsigned less-than to non-equality. The compiled changes are exactly two conditional-branch opcode bytes, at candidate offsets `+0xA85` and `+0xAA7` (76 to 74). All 149 relocation records are unchanged. No source was placed in Code and no function row or pin was added. Model: `gpt-6.1-sol`.

Inputs: checkout `6f2cb58a14cdbc926ff80cb09be62daad12e64b3`, BFME 1 pointer `a18d9ed50607e9175de4d6568798d7d73119de09`. All eleven earlier target verdicts were read. They cite the bank but no per-target support file. The related caller handoff `reverse/attempt_support/quad-5601d9-20261019/readme.md` and BFME 1's `targets/game/reverse/identity_evidence/0090fee0-quad-buffer-renderer.md` were also read. The BFME 1 renderer remains a semantic guide, not a verified target name.

## Measurements

All paths below are relative to `build/177f82-w1-20261019/`. `align_diff.py` was run unchanged with the explicit 3781-byte extent, `BFME_OBJSTORE=off`, and fresh objects. The table reports its structural, memory and register classes; relocation and branch-target lines are excluded from the selection.

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Probe-masked positional differing bytes |
| --- | ---: | ---: | ---: | ---: | ---: |
| Before | 3781 | 21 | 179 | 15 | 1824 |
| H1a, all nonzero guards | 3781 | 24 | 196 | 16 | 1823 |
| H1b, ordinary normals pointer | 3774 | 26 | 188 | 16 | Not recorded |
| H1c, ordinary diffuse getter | 3781 | 21 | 179 | 15 | Not recorded |
| H2, branch cursors and countdowns | 3773 | 20 | 191 | 33 | 2537 |
| H3, default-color lvalue | 3781 | 21 | 179 | 15 | 1824 |
| H4, matched vector-copy helper | 3771 | 28 | 397 | 43 | 2888 |
| H5, diffuse branch cursors | 3778 | 23 | 189 | 26 | 2635 |
| H6, selected UV guards | 3781 | 20 | 179 | 15 | 1824 |
| H7, normals guards on H6 | 3781 | 25 | 196 | 16 | 1823 |
| H8, diffuse guards on H6 | 3781 | 26 | 196 | 16 | 1824 |
| H9, positions guard on H6 | 3781 | 20 | 179 | 15 | 1824 |

H1c and H3 emit the same body as before; H9 emits the same body as H6. H7's smaller positional count does not qualify it because all three required alignment classes regress. H2's lower structural count does not qualify it because its memory and register counts regress. The before and selected probe outputs also report 1848 patched positional differing bytes each. These byte counts are supplementary, not the reason for replacing the bank. The selected source improves structural regions with no other class regression.

The new ranking score is `745/868 = 0.8582949308755761`. `shape_score.py` reproduces it by aligning mnemonics, masking each object's relocation fields and direct branch-target fields, and comparing remaining instruction bytes. It reports 743 equal retail instructions before and 745 after. This is a separate measure from the previous farm score of 0.804; no comparison between those score definitions is claimed. The unchanged alignment tool remains authoritative for acceptance.

Raw measurements are `before-align.log`, `before-object.log`, and each trial's `<stem>-align.log` and `<stem>-object.log`. `h6-raw-changes.log` records the exact two-byte change and identical relocation records. `hypotheses.md` records each hypothesis, evidence and refutation condition before its experiment. Every trial source and raw log remains in the scratch task directory.

## Identity and semantics

Target facts: the preceding function returns at `0x00177F81`; this entry starts at `0x00177F82`. The body ends with `RET 4` at `0x00178E44`, followed by INT3 padding from `0x00178E47` through `0x00178E4F`. The Ghidra start and extent agree. Callers at `0x005609F2` and `0x0056134C` forward their first stack argument and load the receiver from their renderer globals. The established constructor at `0x00177825` and destructor at `0x00177860` corroborate the four owned buffer pointers, count at `+0x10`, texture at `+0x14`, shader at `+0x18` and four default-color floats at `+0x1C`. The initializer at `0x00177923` proves the two 3072-index quad buffers. Buffer array pointers at `+0xC` and native record strides identify the copied three-, four-, three- and two-float payloads. Original owner identity remains unknown, so the address-derived name is retained.

`retail-audit.log` contains the complete target, constructor, destructor, initializer and end padding. `callee-audit.log` checks all 18 direct native call targets against the corresponding object relocation names in order. The dynamic vertex-access constructor's four arguments, 24-byte access view and 12-byte lock view agree with the independently matched provider in `bfmedynamicvertexbuffer.cpp`. Existing aliases and pins are retained, not newly admitted. The indirect material-release calls use the established refcount at `+4` and disposal slot zero.

The native UV loops test the vertex count for zero at `+0xA81/+0xA83` and `+0xA9A/+0xAA5`. The signed outer loop ensures positive remaining primitives; `MIN(...,512)` bounds each UV loop to 4 through 2048 vertices. Both source guard forms traverse exactly the same valid range. Texture-coordinate copies and default corner cycling are unchanged. The farm commit changed only FVF getter volatility; the audit found no deleted buffer operation, equal-arm expression or volatile self-store in this bank. That finding does not establish the original source spelling.

Donor facts: BFME 1's renderer and PointGroup submission guide the common transform, shader, material and dynamic-buffer pipeline. The unchanged bounded CMOV helper retains its previously documented codegen proof. The adjacent exact copy/fill helpers supplied H4's native loop evidence; that trial was rejected. No new EA function body was ported into the selected bank, and every existing comment line is preserved in order. The only added descriptive comment explains the UV iteration range.

## Remaining mismatch and checks

The reconstruction still saves EDI at candidate `+0x384` instead of the native prologue `+0x19`, uses receiver home `[ebp-0x4C]` instead of `[ebp-0x50]`, initializes the current index before the default-color conversion, and differs in optional-buffer cursor placement, normal-pointer spills and zero-register use. The global allocation and frame changes propagate through the vertex loops. H1 through H9 rule out the specific guard, pointer, branch-cursor, helper and default-color copy hypotheses recorded above. Repeating the rejected all-loop guard rewrite or selecting H7 solely for one fewer positional byte would violate this assignment's comparison rule.

`before-explain.log` records the expected byte mismatch at `+0x19`; it is not a successful exact gate. `bank-align.log`, `bank-object.log` and `bank-explain.log` are the final replacement measurements. `check-csv-before.log`, `check-csv-after.log`, `pin-consistency.log` and `diff-check.log` record integrity checks. No matched source exists for this attempt, so a scoped `build.sh` or source-declaration gate is not applicable to this partial result. `repair_queue.py dest` reports `Code/GameEngine/Source/Common/SmallGaps/copyPairsStrided.cpp` by a neighbour heuristic and explicitly says there is no usable approved TU; it is not evidence for placing this renderer there.

`record-receipt.json` records the clock-measured interval from `2026-10-19 07:38:10 UTC` to the verdict. `receipt.json` records the final elapsed time and result codes. No git write command, network call or background task was started. The coordinator must commit and publish the three changed reverse paths after review.
