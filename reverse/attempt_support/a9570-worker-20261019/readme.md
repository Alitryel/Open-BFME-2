# RVA 0x000A9570 follow-up

Result: blocked. The existing bank is unchanged byte for byte. Source revision: 9bc9d37e48e9dfea48691889f89f50b7c2bc62a5. Symbol: `?bfmeTouch982C@BfmeT982@@QAEXXZ`. Native extent: 0x000A9570 through 0x000A97A9 (569 bytes). The intended source is `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptAux.cpp`; the destination tool offers only an unrelated nearest-neighbour heuristic because it has no approved TU mapping for this address. Existing native siblings, the bank and WB evidence support W3DAptAux.cpp. No source, row, pin or bank was changed.

The initial baseline and an independently compiled control each emit 569 bytes with 8 differing bytes. The byte offsets are 0x2f, 0x30, 0x34, 0x35, 0x5f, 0x60, 0x64, 0x65. They belong to the two reversed MOVSS/MULSS operand pairs at A959C/A95A1 and A95CC/A95D1. Each pair contributes four differing bytes, so the earlier verdict's four differing instructions mean eight bytes. All relocations resolve and no comparison is masked. All 32 new variants are at least as far from retail; the best has 8 differing bytes.

All four prior verdicts and their supplied evidence were read before experimenting, including the complete bank, current W3DAptAux.cpp, Rva000A925DFloatRatio.cpp, and the relevant crack-g-parents-20261014 audit row and README. No target-specific raw trial files from the last two attempts were supplied. The initial scratch compile failed after an incomplete merge of the obsolete OnCustomRender class spelling with AptPlayer. Its source and compiler output remain under build/a9570-worker/baseline.cpp and baseline.log; the corrected baseline merges the existing provider declarations without adding an alias.

The pre-experiment hypotheses and refutations are in `build/a9570-worker/hypothesis.md`. The first hypothesis used the documented influence of later local identities on SSE operand ordering: aggregate scale, dimensions and position values, or reuse the transformed corner for final alignment. These failed to improve either product. The separate-update hypothesis follows docs/matching.md's statement-level ordering evidence: splitting all four transformed components corrects the topLeft.y pair but disrupts topLeft.x scheduling. Isolated component splits, paired statements and cross-component combinations do not improve the full body. SSE intrinsic scalar products were also tested after ordinary scalar forms failed; their loads, multiplication and scalar stores enlarge the body and are rejected. No inline assembly or encoded instructions were used.

| Trial group | Variants | Minimum differing bytes | Maximum differing bytes |
|---|---:|---:|---:|
| aggregate- | 7 | 8 | 30 |
| reuse- | 1 | 113 | 113 |
| separate- | 1 | 15 | 15 |
| split-tly- | 3 | 8 | 29 |
| split-brx- | 3 | 8 | 21 |
| split-bry- | 3 | 8 | 16 |
| interaction- | 5 | 14 | 32 |
| intrinsic- | 3 | 494 | 526 |
| paired-statements- | 6 | 10 | 36 |

Differing-byte counts compare the patched retail window; the compiled extent is recorded separately in measurements.tsv. An enlarged body fails the extent requirement regardless of its window count.

Native evidence: the Ghidra inventory independently records the start and full extent. The preceding function ends with RET at A956F, and the target ends before the next body at A97A9. The native body receives this in ECX, selects DE6130 or DE6148 via byte +2C, reads corners at +0C/+14 and dimensions at +1C, calls A925D three times with the private XMM0 result, calls the DWORD colour transform A90B0 twice, and dispatches slots +48/+28/+34/+38. The neutral bank name is retained. WB 8AB920 and its DisplayStringRender label are prior semantic identity evidence; this run does not establish the original class name or a canonical layout. The BFME 1 provenance of the unchanged ratio remains the donor revision recorded by its existing source and row, not a newly inferred target identity.

Validation and raw evidence: `build/a9570-worker/retail-abi.log` has native boundary and callee disassembly. Every successful trial has its .cpp, unmodified explain_mismatch .log, .json measurement and compared .bin files under that directory; `measurements.tsv` indexes all measurements. `bank-integrity.log` verifies the preserved bank against HEAD. `existing-source-build.log` is a passing build.sh check of the unchanged intended TU and ratio provider. `frozen-initial.log`, `csv-initial.log`, `csv-final.log` and `pins-final.log` pass. `unchanged-code-bank.log` is the successful git diff check for source, bank, functions.csv and symbols.csv. `destination.log` preserves the heuristic response. An explain_mismatch exit of zero means diagnostics completed, not an exact match; every candidate remains a byte failure. No add_match was called. No justified untested ordinary scalar hypothesis remains from this experiment series.

All trial sources and raw logs are retained under `build/a9570-worker/` as requested. Probe object caches and dependency receipts are under `build/match/` with this task's source prefix. No background process remains from these probes. Elapsed clock and verdict writer output are recorded in `build/a9570-worker/receipt.json` and `record.log`.
