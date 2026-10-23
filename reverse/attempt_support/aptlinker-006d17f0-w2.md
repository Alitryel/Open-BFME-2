# AptLinker 0x006D17F0 exact recovery

The body is exact and uncommitted in `Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp`, the destination returned by `repair_queue.py dest`. The row is `?rva006D17F0@AptLinker@@QAEXXZ` at RVA `0x006D17F0`, with the complete 1178-byte extent. `add_match.py` verified the unit, appended the matched row and landed verdict, and deleted the bank. No later verdict was recorded. Input revision: `ab83d635b0ffe5b8dfee2219b877acc0384f81f9`. Model: `gpt-6.1-sol`.

## Measurements and decisive change

| Candidate | Emitted bytes | Structural regions | Memory differences | Register differences | Differing bytes |
|---|---:|---:|---:|---:|---:|
| Existing bank | 1178 | 0 | 23 | 6 | 19 |
| T01 byte-buffer representation | 1178 | 0 | 23 | 6 | 19 |
| T02 inline record constructor | 1178 | 0 | 23 | 6 | 19 |
| T03 direct sprite accessor expressions | 1178 | 0 | 22 | 0 | 0 |
| Integrated source after declaration cleanup | 1178 | 0 | 22 | 0 | 0 |

The byte counts agree over both the assigned 1175-byte span and the complete 1178-byte body. Alignment's remaining 22 memory differences are unresolved-in-object global address operands; the normal relocation resolution removes all of them. Structural counts exclude relocation and branch lines. All calls resolve. The raw measurements are `before-align.log`, `before-bytes-1178.log`, `t01-align.log`, `t02-align.log`, `t03-align.log`, `t03-bytes-1178.log`, `home-inline-align.log` and `home-inline-bytes-1178.log` under `build/aptlinker-006d17f0-w2/`.

T03 replaces the shared local sprite pointer with a direct accessor expression for each field operation. This changes the first store's register selection and also recovers both diagnostic scheduling choices. The operations, accessors, assertions and offsets are unchanged. Hypotheses, their refutations and results were written before the experiments in `build/aptlinker-006d17f0-w2/hypotheses.md`. Every trial source and raw probe output remains in that directory. The existing bank's exact contents, including all comments, remain in `before.cpp`; the bank itself was untouched until `add_match.py` deleted it after verification.

## Identity, ABI and extent

Retail caller `0x006CD87D` loads ECX from the AptLinker global at VA `0x00E176F8`; its call at `0x006CD883` targets this entry without stack arguments. Seven INT3 bytes precede the complete EH prologue at `0x006D17F0`. RET is at `0x006D1C89`, followed by INT3 padding, so the complete extent is 1178 bytes. The supplied 1175-byte span ends inside ADD ESP at `0x006D1C83`. Ghidra independently lists the start, although its recorded size is truncated. This is a valid function start with an incorrect old extent. The original method name remains unproven, so the address-derived name stays.

`retail-probe.log` contains the full native function, caller and direct callee entry disassembly. Retail independently establishes the counted releases, pool sizes, calls, field offsets, callback order and restart paths. WorldBuilder `0x01752E70`, extracted in `wb-01752e70.c.txt`, corroborates their source structure; decompiled types and names are semantic leads rather than target facts. The earlier handoff `reverse/attempt_support/aptlinker-006d17f0-w5.md` was read in full, as were all five attempt-log verdicts. Its referenced `build/aptlinker-006d17f0-w5/` directory is absent from this checkout. The starting measurement and identity evidence were therefore reproduced locally.

## Integration and verification

The destination already owns the counted getter, owner and linker registration families. Integration reuses those declarations, supplies the complete holder release, extends the target-proven entry layout, and reads the existing vector through an inline view. The getter stays out of line because retail calls it. The holder family follows its pool-owner declaration so its destructor can remain inside the class. The synthetic vector view is also defined inside its class. No unmatched markers, pins, assembly, verifier edits or compiler-setting changes were added. The existing override retains `/O2 /MD /EHsc` without SSE for this unit. No external C++ donor was ported; existing donor function comments remain with their bodies.

All log paths below are relative to `build/aptlinker-006d17f0-w2/`. Every build and measurement used `BFME_OBJSTORE=off`; measurements deleted their object's cache first.

- `add-match-final.log`: PASS, all 30 unit rows exact, including all 29 existing rows and four verified string references. `add-match.log` preserves an earlier notes-format refusal before any ledger write.
- `build-sh-verified.log`: PASS, explicit `./build.sh` after the final declaration cleanup, all 30 rows exact.
- `declared-verified.log`: PASS with `--fail`. The initial audit named two out-of-class inline helpers; both were moved into their class declarations and the fresh byte comparison stayed exact.
- `pin-consistency-verified.log`: PASS. No pin changed.
- `pre-land-integrity.log`: PASS. `check-csv-final.log`: expected FAIL because `check_csv.py` reads the deleted but still unstaged bank from its tracked-path list. The coordinator must stage the deletion with the source and ledger changes; no index change was made here.
- `whitespace-verified.log` and `final-audit.log`: final whitespace and local artifact checks. `changed-paths.txt` lists deliverables and retained scratch paths. `elapsed.json` records the clock-based elapsed minutes.

The byte gate has no remaining blocker. The CSV deletion check is pending coordinator staging. No background task was started, and every probe and gate process exited. All changes remain uncommitted; no network operation was run.
