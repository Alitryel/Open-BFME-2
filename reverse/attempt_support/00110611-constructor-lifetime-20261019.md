# 0x00110611 constructor lifetime

Result: blocked. The existing bank is unchanged. Symbol: `?bfmeEnd982C@BfmeHub982@@QAEXXZ`. Retail boundary: RVA `0x00110611` through `0x00110CFE`, exclusive, 1773 bytes. Model: `gpt-6.1-sol`. Input checkout: `0a64aa2c20ddcdffbb141e63677e11cdc62e991f`; BFME 1 input: `a18d9ed50607e9175de4d6568798d7d73119de09`. Compiler: default MSVC 7.1, bank settings `/O1 /G7 /arch:SSE /DNDEBUG /MD` and its original include directories.

## Prior evidence and identity

All four previous target verdicts and the whole bank were read before compiling. The relevant `crack-g-parents-20261014` audit and README were also read, along with BFME 1 revision `39df6df1`'s Vector4 definition and revision `0a9669ef`'s renderer source and `targets/game/reverse/identity_evidence/0078b4f0-renderer-end.md`. The donor uses a separate unused row array. It supplies no independently supported matrix lifetime and was not copied.

Fresh retail decoding is in `build/worker-110611/retail-complete.log`. The target saves incoming ECX into ESI at VA `0x00510645`, uses fields through that receiver, and returns with plain RET at `0x00510CFD`. The matched caller at RVA `0x000AA645` loads ECX from the renderer global and calls this target at VA `0x004AA730`, with no new stack arguments or consumed return value. This supports the bank's nullary thiscall contract but does not establish the original class or method spelling. The older verdict's claim that the target does not preserve an ECX owner is contradicted by these bytes. Keep the inherited placeholder spelling as uncertain identity.

The same raw log decodes the complete 27-byte viewport callee, 23-byte preset callee, 132-byte vertex-buffer callee, 34-byte vector iterator and three-byte callback. The iterator accepts destination, stride, count and callback, calls each row with ECX, and returns with RET16. At VA `0x00510B87` the target passes callback `0x0087A6A9`, four rows, stride sixteen and destination `ebp+0x38`. The callback is exactly `mov eax,ecx; ret`. The sixteen transposed world values are saved before that call and copied to the world cache afterward. The callback alone proves neither its original class identity nor a particular matrix source spelling. Reference Matrix4 and DX8Wrapper source provide semantic guidance; the field offsets and sequence are target evidence.

The bank is a whole-unit candidate for `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DAptRendererRva00111319.cpp`. `repair_queue.py dest` instead returns `Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp`, explicitly labelled a nearest-neighbour heuristic without an approved TU. This is not independent source-file ownership proof. No production source was edited.

## Experiments and refutation

Hypotheses and falsification conditions were written before each trial in `build/worker-110611/hypotheses.md`. Every probe checks `build/STOP_WORKER` first. Trial sources, copied objects, emitted bytes, input bank snapshot and unedited tool outputs remain in that task directory. `receipts.jsonl` records command arguments, UTC timestamps and exit codes.

1. H1 tested a real named WORLD transpose result with Matrix4's default constructor explicitly `__forceinline`. The earlier named-local trial had called Matrix4() out of line. This test was intended to retain the native row-array lifetime through that constructor. Refutation was omission of the iterator, additional iterators, or failure to improve the ordered comparison. After correcting a missing switch-case scope, it emitted the baseline body exactly and omitted the iterator. The initial C2360 compiler error is retained in `inline-default-world-align.log` and its source snapshot; the corrected comparison is `inline-default-world-fixed-align.log`.
2. H2 tested a visible empty Vector4 default constructor marked `__declspec(noinline)`. Unlike the previous declaration-only trial, this exposes its lack of side effects while requesting a non-inlined call. Refutation was an absent iterator, extra iterators, or no ordered comparison improvement. The emitted standalone constructor remains the correct three-byte empty callback, but the target again omits the iterator and is identical to baseline. Raw comparison: `noinline-vector-align.log`.

| Measurement | Baseline bank | H1 | H2 |
|---|---:|---:|---:|
| Emitted bytes | 1670 | 1670 | 1670 |
| Structural regions from align_diff | 5 | 5 | 5 |
| Raw memory operand differences | 185 | 185 | 185 |
| Register operand differences | 2 | 2 | 2 |
| Positional differing common bytes, object relocations masked | 1171 | 1171 | 1171 |
| Missing bytes at the end of the positional comparison | 103 | 103 | 103 |

The positional sum is 1274 before and after. It is diagnostic only because instructions are misaligned. Relocation and branch lines are not acceptance defects. The tool's raw memory category also includes unresolved absolute relocation operands. Exact raw target-body and relocation-list equality between both trials and baseline independently rules out any improvement. `measurements.log` records the bytes, relocations, SHA-256 values, callback bytes and unchanged-bank check. `baseline-align.log` is the required initial comparison. `baseline-explain.log` is retained verbatim; its retail-filled relocation operands become misleading when instructions shift and are not used to judge improvement.

## Remaining mismatch and checks

The WORLD row-construction iterator and its spills are still absent. Retail uses a `0x98` frame with biased EBP, while every trial retains the bank's `0x88` frame. The two new hypotheses are refuted; there is no further evidence-backed experiment identified. No unrelated row array, assembly, pin, flag override or verifier change was introduced.

`check-csv.log`, `pins-check.log` and `declared-home.log` pass. The last check covers the unchanged production home. Align diagnostics complete successfully for baseline and both corrected trials but establish mismatch, not gate success. No add_match or production byte gate was run because no improved or exact candidate exists. All work remains uncommitted; no network or prohibited runner was used, and no background process remains.
