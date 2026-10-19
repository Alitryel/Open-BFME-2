# 0x000470D5 inline receiver experiment

Result: blocked. The existing bank is unchanged, including all comment lines. No source, pin or matched row was added. Model: gpt-6.1-sol. Base revision: a1be768a5f12223be7bd1e2feb558f0e74f6eb52. The start clock was 2026-10-19 02:47:12 UTC; the verdict records elapsed minutes from that clock.

The symbol remains `?Rva000470D5GetTexture@@YA?AVBFME2ParticleTextureHandle@@PBURva000470D5Source@@@Z`, RVA 0x000470D5, complete extent 216 bytes. Bank: `reverse/attempts/0x000470d5.cpp`. `repair_queue.py dest` returns `Code/GameEngine/Source/Common/StringContainerRecordVector.cpp` through a nearest-neighbour heuristic; that output is not evidence that this image-clock helper belongs to the string-container unit.

Before experimenting, all ten target verdicts and the entire bank were read. The target verdicts cite the bank but no separate support file. The additional crack-g-wave5 target trial records, outcomes, diagnostic diff and wrapper scripts were read. Their unified-return, reference binding, owning-base, visibility, nothrow and flag-spelling failures were treated as ruled-out routes.

## Measurements

| Candidate | Compiled bytes | Differing bytes within retail extent | Structural regions | Memory differences | Register differences |
|---|---:|---:|---:|---:|---:|
| Existing bank, unchanged | 219 | 100 | 4 | 2 | 0 |
| Remove barriers and constant-condition expression | 219 | 100 | 5 | 2 | 0 |
| Inline handle getFilter wrapper | 219 | 100 | 5 | 2 | 0 |
| Inline handle quality wrapper | 219 | 100 | 5 | 2 | 0 |
| Inline TextureClass::Add_Ref wrapper | 219 | 100 | 5 | 2 | 0 |
| All three wrappers | 219 | 100 | 5 | 2 | 0 |

Every candidate has three excess compiled bytes and no unresolved relocation. The byte count compares the normal resolver-patched first 216 bytes, so it is positional and is not the ranking criterion. `align_diff.py` supplies the structural, memory and register counts; its reloc and branch counts are excluded from defects. Each source and its raw explain/align output and measurement JSON are retained under `build/470d5-worker/`. The repeated unchanged-bank control reproduced the same body and metrics. No candidate satisfies the required closer-bank ordering.

## Hypothesis and refutation

H1 was written in `build/470d5-worker/hypotheses.md` before the first compile. The BFME1 clock helper `texture006F18F0` in `game/GameEngineDevice/Source/W3DDevice/GameClient/RadialImage006F1AC0Draw.cpp` uses inline handle methods for filtering and flag forwarding, and its TextureClass::Add_Ref performs the same WORD+4 increment as target. This suggested that preserving receiver methods rather than flattening casts and increments could change the optimizer's receiver lifetimes and preload the hidden result pointer. This is donor structure, not target class-name proof. Refutation was unchanged hidden-result scheduling or failure to improve all required difference classes. Four individual/combined receiver-wrapper controls refuted H1: all reproduce the clean control's delayed EDI loads and metrics. Removing the farm's two barriers and constant-condition expression also produces no improvement.

The exact remaining native-versus-bank mismatch is the prologue schedule and duplicate hidden-result EDI loads: native loads the source into EAX, saves ESI/EDI, loads the hidden result into EDI once at +0x11, then clears the return-construction flag at EBP-0x14. The bank clears that flag first and loads EDI separately near each return copy. The redundant second load adds three bytes and shifts the final cleanup and epilogue. The clean control additionally schedules the register saves after the flag test. Existing failed unified-return and ownership routes give no support for repeating those experiments. No further new evidence-backed experiment was identified in this run.

## Independent target evidence

`build/470d5-worker/retail.log` decodes all 216 native bytes through RET at VA 0x004471AC, followed by the separately inventoried clock start 0x004471AD. The source argument is EBP+0xC and hidden result is EBP+8. The caller at VA 0x00447283 pushes the source and a result address and pops two arguments, establishing caller-cleaned hidden return ABI. Native accesses establish filename +8, retained handle pointer +0x2C and flags +0x30. Copying increments WORD+4; destruction releases through 0x0061ED10. Native calls are filter accessor 0x00132856, loader 0x00132D89 and quality forwarder 0x00132FE9. Their existing ledger declarations agree with the decoded receiver and argument use. Native cleanup 0x0017098D loads the single pointer and tail-calls the same release worker. The Ghidra inventory independently lists `0x470D5,216,FUN_004470d5`. These establish the address-derived counted-texture getter interpretation, but not an original helper or source-class name.

`build/470d5-worker/h1.run.log` is the raw probe-run receipt. `baseline.explain.log`, `baseline.align.log`, `clean.explain.log`, `clean.align.log` and `h1_*.explain.log`/`h1_*.align.log` are raw tool output. The trial script calls the supported mismatch/align tools with `BFME_OBJSTORE=off`; it does not hand-compile a shared-cache object. Every probe checks `build/STOP_WORKER` before writing or measuring its candidate. No production reconstruction was left in `Code/`.
