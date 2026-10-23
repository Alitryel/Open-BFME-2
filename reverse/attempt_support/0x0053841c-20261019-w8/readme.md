# RVA 0x0053841C handoff

Result: blocked. Model: gpt-6.1-sol. Input revision: 91fba4cb2309f15615826aeb57167360b96c583b. All changes are uncommitted. No Code source, ledger row or pin was added or changed. The original bank is byte-for-byte unchanged.

## Boundary and identity

Retail is a 239-byte leaf from RVA 0x0053841C through RET 4 at 0x00538508; a preceding RET 4 ends at 0x0053841C and the next entry starts at 0x0053850B. ECX supplies this and one stack argument supplies the matrix pointer. Caller 0x0030BC9E forwards that argument after adding 0x68 to this. There are no callees. Retail reads a range at offsets 0 and 4, advances 16-byte records, transforms each pair by the first two matrix rows with explicit zero-column products, and sets byte 0x20. These facts are target evidence. The exact original class identity and full layout remain unknown, so the address-derived symbol is retained: ?rva0053841C@Rva0053841C@@QAEXPBURva0053841CArg@@@Z.

repair_queue.py dest proposes Code/GameEngine/Source/Common/RvaAdjustCallEchoFamily.cpp by a neighbor heuristic; its QuadStrip2D.cpp TU-map lead is unapproved. No donor code was copied, and no stronger source identity is claimed. See retail.log and destination.log for raw output.

## Measurements

All trials use unique source paths, MSVC 7.1 with /O1 /arch:SSE /G7 /DNDEBUG /MD and BFME_OBJSTORE=off. Every new trial checked build/STOP_WORKER first. The exact machine-readable results are measurements.json; this table was generated from that file. Positional byte counts include missing or excess bytes and are diagnostic only. Relocation and branch differences do not decide closeness.

| Trial | Bytes | Structural regions | Memory differences | Register differences | Positional differing bytes including missing or excess |
|---|---:|---:|---:|---:|---:|
| baseline | 202 | 5 | 14 | 12 | 210 |
| h1-corrected | 231 | 5 | 20 | 18 | 204 |
| h2-no-barrier | 231 | 6 | 20 | 19 | 208 |
| h3-staged | 236 | 2 | 21 | 19 | 212 |
| h4-literal-zero | 236 | 2 | 21 | 19 | 212 |
| h5-independent-products | 236 | 4 | 22 | 19 | 212 |
| h6-intrinsics | 286 | 8 | 14 | 18 | 255 |
| h7-input-refs | 223 | 6 | 15 | 15 | 206 |
| h8-split-products | 228 | 6 | 20 | 18 | 208 |

The structurally best scalar candidate is staged-candidate.cpp.txt, which emits three fewer bytes than retail. It restores all four zero-column products and has retail's second-pair mnemonic sequence, but still lacks the initial MOVAPS copy and early zero-coefficient load. Its zero is allocated to XMM0 instead of retail's XMM2, with corresponding result-register and load/store scheduling differences. Its fewer structural regions come with more memory and register differences, so it does not qualify as closer. The other corrected candidates also fail the no-tradeoff criterion. This is why the bank was retained despite its semantic defect; the semantic correction is preserved here for further work.

## Semantic finding

The farm bank omits the second pair's m_08*zero and m_18*zero products. Retail executes them at RVAs 0x005384B9 and 0x005384E1. When either coefficient is infinite or NaN, the farm leaves a finite second-pair result where retail produces NaN. The scalar SSE single-iteration interpreter in build/attempt-0053841c-w8/measure.py found 258/264 passing cases for the farm and 264/264 for H1 and H3, including 256 deterministic finite inputs and eight special-value inputs. See measurements-final.log. NaN payloads are normalized in that comparison. These probes do not prove full native equivalence, exception-state behavior or arbitrary alias behavior.

## Excluded explanations and resumption

hypotheses.md records each hypothesis, its evidence, refutation criterion and observed result before the next experiment. Restoring arithmetic alone, removing the farm barrier, changing zero lifetime, separating product variables, scalar SSE intrinsics, scalar input references and splitting loads from products all failed the alignment condition. Earlier verdicts already tested vector-return, alias-temporary, in-place, store-order and cached-end helper shapes. Repeating those without new evidence is not justified. Remaining work needs a supported explanation for the initial input copy, zero register allocation and interleaved row loads.

## Checks and raw artifacts

align_diff.py and explain_mismatch.py completed successfully for all nine sources, and every source remains non-exact. Full per-trial sources and raw outputs remain under build/attempt-0053841c-w8/. The best alignment and disassembly are copied here. check_csv.py passed (check-csv.log); pin_consistency.py --check passed (pin-consistency.log). build.sh and find_declared_unmatched.py were not run because no matching Code source was produced or changed. No background process was started. No git-writing or network command was run.
