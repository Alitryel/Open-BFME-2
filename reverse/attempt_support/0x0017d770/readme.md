# PointGroup UV helper at 0x0017D770

## Result

Blocked; the existing bank (score 0.913, 20 aligned instruction differences) is kept for `?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z`, retail extent 1583 bytes. The best of 50 probes (H4: separate per-mode frame locals plus barriers before the table lookup) also emits 1583 bytes and cuts the verifier's positional differing bytes from 510 to 465 (independently resolved 530 to 485), but raises aligned instruction differences from 20 to 60, so it was not banked. Exact matching remains blocked by register allocation, load scheduling, and SSE operand scheduling. No Code source or function-ledger row was changed. The repair-queue destination is `Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassDiffuseFill.cpp`, reported as a neighbour heuristic with no approved TU.

The positional byte count falls only because shifted code lines up better by position; prefer the aligned instruction count when choosing the next starting point.

## Identity and provenance

Target evidence: Ghidra records a function start at 0x0017D770 with this extent. Retail ends with `ret 12` at 0x0017DD9C, then INT3 at 0x0017DD9F and the next function at 0x0017DDA0. The complete body contains no calls. The matched PointGroupClass array updater at 0x0017F3A0 calls this entry at 0x0017F3DE with ECX=this and three stack arguments. Retail reads grid log2 at this+0x20, PointMode at this+0x2C, and default frame at this+0x49. Its four-float optional address remains an opaque integer argument. No semantic helper name is established beyond the address-derived donor symbol.

Donor evidence: original bank identifies BFME1 `game/Libraries/Source/WWVegas/WW3D2/PointGroupClassUVFill.cpp` at 6583b3c1ff. Its identity document is `reference/open-bfme-1/targets/game/reverse/identity_evidence/00916cd0-pointgroup-uv.md`. Both files and all eight earlier verdicts were read before experimenting. Their behavior duplicates frame zero for a nonnull incoming frame pointer; the null path masks the default frame and optionally modifies the selected UV-table entry before copying it. BFME2 retail independently supports that behavior and the above offsets. The donor's semantic member names and broader class layout remain donor evidence where no separate target witness was reviewed.

Inputs: BFME2 9bc9d37e48e9dfea48691889f89f50b7c2bc62a5, pinned and checked-out BFME1 a18d9ed50607e9175de4d6568798d7d73119de09, default MSVC 7.1 command with /O2 /arch:SSE /G7 /DNDEBUG /MD. Final explain_mismatch dependency receipt resolves the intended canonical sharebuf, vector and vector2/3/4 headers in the current donor layout. No header, pin, ABI declaration or compiler flag was changed.

## Hypotheses and outcomes

Hypotheses and explicit refutations were recorded before their experiments in `build/worker-17d770/hypotheses.md`. Every trial checks `build/STOP_WORKER` immediately before compiling.

| Batch | Trials | Hypothesis | Best verifier differences | Emitted bytes |
|---|---:|---|---:|---:|
| H1 | 6 | Shared UV pointer scope and explicit default frame | 772 | 1583 |
| H2 | 8 | Shared counters and separate base/cursor identities | 510 | 1583 |
| H3 | 8 | Barriers before branch-local global reads | 496 | 1583 |
| H4 | 12 | Per-mode selected-frame locals and table-index order | 465 | 1583 |
| H5 | 6 | Inline loop parameter identities | 747 | 1583 |
| H6 | 10 | Early returns and removal of member self-comparisons | 465 | 1583 |

H1 hoisted the shared global read to entry. H2 changed allocation without improvement. H3 prevented hoisting in the default-only pre-barrier variant, but changed SSE registers; one variant gave a smaller positional byte count. H4's separate unsigned frame locals and barriers before table lookup gave the retained candidate. H5 emitted no calls, but parameter order did not improve allocation. H6 emitted the same code with early returns; removing the existing member self-comparisons made the body longer. Those comparisons remain in the bank and are not new semantic claims. No inline assembly, emitted bytes, naked function, or optimization pragma was added.

The H4 candidate first differs at +0x8: retail pushes EDI and forms the mask in EDI, while the candidate forms it in EDX before pushing EDI. The nonnull branch still lacks retail's initial `mov edx,ecx` UV-pointer split. The default branches still differ in frame/table/global load order, with additional SSE register and operand differences. No justified scope, dataflow, inlining, or early-return hypothesis tested here produced exact bytes. Prefer fresh source or compiler evidence over repeating these trials.

## Raw evidence and reproduction

All trial sources, compiler commands, compiler output, objects, independent disassemblies, alignment diffs and measurement JSON files remain in `build/worker-17d770/`. `h1-run.log` through `h6-run.log` contain the unmodified probe outputs. `baseline-explain.log`, `after-explain.log`, and `final-explain.log` are raw explain_mismatch output. Compilation succeeded; every exact comparison reports a mismatch (the tool exits zero even for a mismatch). `baseline-measure.log` and `final-measure.log` count differing bytes from the same compile_function result that explain_mismatch prints. `identity-retail.log` is the raw retail boundary and caller disassembly. `summary.json` is generated from those measurements; `probe.py` contains the independent byte and alignment counters.

Reproduce the final comparison with `python tools/explain_mismatch.py '?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z' --rva 0x0017D770 --size 1583 --source build/worker-17d770/bank-final.cpp`. `python build/worker-17d770/probe.py bank-final --cached` reads that object and reports both byte metrics. The independently resolved addresses are VertexUV base 0x00DF94C0 with addend four, triangle table 0x00DF7060, and quad table 0x00DF7074. Since verifier DIR32 resolution copies retail bytes at compiled offsets even when instructions have moved, its count and the independently resolved count differ; both improve here.

No full build or matched-source gate is appropriate for this unmatched bank. Final `check_csv.py` and `pin_consistency.py --check` both pass; raw outputs are `build/worker-17d770/check-csv.log` and `build/worker-17d770/pin-consistency.log`. `final-check.log` records preservation of the original bank and all preceding attempt-log bytes, the single appended verdict, equality of the bank payload with the measured final source, and unchanged Code sources, function ledger and pins. Clock readings and elapsed minutes are in `build/worker-17d770/timing.json`, with the first retained clock reading identified explicitly. Model: gpt-6.1-sol. No background process was started. Changes remain uncommitted for coordinator review.
