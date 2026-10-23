# AptLinker 0x006D17F0 handoff

The bank is closer and restores the retail ownership and restart paths. It remains unlanded. The symbol is `?rva006D17F0@AptLinker@@QAEXXZ`; the bank is `reverse/attempts/0x006d17f0.cpp`. Input revision: `afb8f2d97046ca55551678cfc91d87582578d0b2`. Compiler: MSVC 13.10.3077 with `/O2 /MD /EHsc`; the measured region's additional `/arch:SSE` did not change this body. Every measurement used `BFME_OBJSTORE=off` and a fresh object. No Code source, ledger row, pin or verifier was changed. The destination tool names `Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp` by its neighbour heuristic, explicitly without an approved TU mapping.

## Measurements

| Probe | Old bank | New candidate |
|---|---:|---:|
| Emitted bytes | 987 | 1178 |
| Structural regions | 38 | 0 |
| Memory operand differences | 56 | 23 |
| Register operand differences | 38 | 6 |
| Positional differing bytes over the assigned 1175-byte span | 998 | 19 |
| Unresolved calls | 1 | 0 |

These are the raw align_diff counts; its memory category also includes unresolved-in-object global DIR32 operands, so those counts are not all actual field defects. Relocation and branch categories are excluded from the improvement judgment. The old bank exceeds three quarters of retail's extent, so its region comparison is usable. The complete 1178-byte comparison also has 19 differing bytes. Raw outputs and compiler receipts are in `build/aptlinker-006d17f0-w5/bank-before-{align,explain}.log`, `bank-before-receipt.json`, `final-candidate-{align,explain,byte-differences}.log` and `final-candidate-receipt.json`. The score is conservatively rounded to 0.98 from the verified remaining byte fraction; qualification rests on the alignment counts as well.

## Identity and extent

The native caller at RVA `0x006CD883` loads ECX from the existing AptLinker global at VA `0x00E176F8` and calls this address with no stack arguments. The target starts after seven INT3 bytes with a complete MSVC EH prologue and ends with a plain RET. Ghidra independently lists the start. The original method name is unproven, so the address-derived name stays. WorldBuilder `0x01752E70` independently corroborates the control flow; its decompilation is semantic evidence, not byte proof. The native body and all direct callee entry probes are in `retail-probe-complete.log`.

The assigned 1175-byte extent ends inside `ADD ESP,0x148` at RVA `0x006D1C83`. RET is at `0x006D1C89`, followed by INT3 padding. The complete body is therefore 1178 bytes. This is an extent discrepancy, not an invalid function start. Keep the native epilogue intact; an eventual exact ledger entry needs that complete extent.

## Established repairs

The farm bank's missing braces made node acquisition unconditional. Its callback arguments were reversed, its count-change check ran after the chain instead of immediately after a successful match, its outer and inner owners lacked exception cleanup, and its sprite accessors added calls absent from retail. The new body restores the conditional acquisition, callback `(loadName, cihName)`, immediate release-and-restart path, counted owner lifetimes and inlined assertions/accesses. The two array elements are four bytes each, as the native EH constructor iterator requires. The diagnostic record is 260 bytes; the native packet begins at stack +0x48 and ends before the saved exception pointer at +0x14C. The original WB-derived 264-byte declaration caused the extra frame word. The old bank's artificial volatile stores and equal-arm expressions are removed. The stale ClearCIH spelling now refers to its existing rowed provider, with no new pin.

The decisive compiler discovery was the existing iterator range checks. WB comparison `0x01754B80` calls `0x01754CE0`, which checks first/last equality and calls the empty check at `0x01750B80`. Dereference `0x01754B40` calls `0x01754C90`, checking cursor bounds through the same empty helper. Preserving those expressions restores the native loop layout and register allocation. `wb-iterators-raw.log` contains the direct disassembly; the exported decomp collection lacks those small helpers. The already recovered PlaybackIterator family in Apt.cpp supplies the same independently verified pattern for readiness `(3,2)`. No external C++ donor was ported.

## Remaining blocker

All 19 differing bytes lie in three local scheduling choices: native `0x006D19F2..0x006D19FD` loads the sprite pointer into EAX and prepares ECX for the next predicate before storing -1; the candidate stores through ECX first. Native `0x006D1A92..0x006D1A9F` loads and stores the diagnostic header through ECX before preparing the name call; the candidate uses EDX and a different instruction order. Native `0x006D1ABD..0x006D1AC2` forms and pushes the packet pointer in EDX; the candidate uses EAX. All remaining instruction lengths, control flow, call destinations, count comparison and full epilogue align.

Copy construction alone, SSE flags, an inline boolean readiness helper without checked iterators, typed diagnostic fields, inline sprite getter boundaries, typed sprite setters, the existing getter's return-load barrier and the provider's typed CIH member view were tested and did not close these scheduling differences. The successful changes and each falsifiable hypothesis are recorded before their trials in `build/aptlinker-006d17f0-w5/hypotheses.md`; every trial source and raw diagnostic remains there. The best candidate is `final-candidate.cpp`, derived from T13; later no-effect probes were not retained in the bank. All original bank comment texts are preserved, verified in `comment-preservation.log`.

## Validation

The stashed bank was independently rebuilt and remeasured after re_log wrote it; `0x006d17f0-{align,explain}.log` and `0x006d17f0-receipt.json` reproduce the final measurements. `check_csv.py` passed (`check-csv.log`), and `pin_consistency.py --check` passed (`pin-consistency.log`). The exact byte comparison still fails on the documented scheduling bytes; no matched row or nonmatching Code reconstruction was installed, so build.sh and find_declared_unmatched on a changed Code source do not apply. The partial verdict was written only through re_log.py, with its raw output in `re-log-record.log` and its clock measurement in `re-log-receipt.json`. All log names in this section are relative to `build/aptlinker-006d17f0-w5/`. No further evidence-backed codegen hypothesis was identified after T16. No background task was started; every diagnostic process exited.

The first whitespace check failed because the trial writer introduced CRLF into the stashed body after re_log's LF metadata prefix (`diff-check.log`). Only the new candidate and bank were normalized to LF, preserving every comment text. A second fresh build and both-span byte measurement still report the same mismatch (`stashed-lf-{align,explain,byte-differences}.log`, `stashed-lf-receipt.json`). The final source identity, comment preservation and whitespace audit passed (`final-audit-final.log`, `diff-check-final.log`). `changed-paths.txt` lists all deliverable and scratch paths, including object-cache files.
