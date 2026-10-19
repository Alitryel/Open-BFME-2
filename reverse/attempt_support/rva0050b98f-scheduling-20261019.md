# Blocked: RVA 0x0050B98F scheduling

The existing bank remains unchanged. Symbol `?rva0050B98F@Made002CCC2D@@QAEXPBUFadeInputPrefix@@H@Z`, retail size 383 bytes, source `reverse/attempts/0x0050b98f.cpp`. No reconstruction was placed in Code and no row or pin was added. Checkout: `1d7d3716bc22594f17dca9ec14b3d2ccd4a337c9`. Donor checkout reviewed: `a18d9ed50607e9175de4d6568798d7d73119de09`. Recorded elapsed time: 8.99 minutes; model=gpt-6.1-sol. Clock receipt: `build/w7-50b98f/receipt.json`.

## Remaining mismatch

The retained bank has 18 patched differing bytes before and after this attempt. It emits the complete body. The four mismatching instruction lines are one scheduling permutation at retail offsets +0x7C through +0x8D. Retail stores position.z, loads offsetX, saves EAX to EBX, then loads angle. The bank saves EAX to EBX first and loads angle before offsetX. The original align_diff result is two structural regions, seven raw memory differences and one register difference. Six raw memory differences are absolute global relocations, leaving one memory and one register operand difference associated with the scheduling alignment. Relocation and branch lines are excluded from defects.

## Identity and ABI evidence

`build/w7-50b98f/identity.log` contains raw retail disassembly and vtable words. The preceding body returns at 0x0050B98C; this body begins with its own prologue at 0x0050B98F and ends with RET 8 at 0x0050BB0B, immediately before the matched constructor at 0x0050BB0E. No matched ledger range overlaps it. The constructor installs vtable VA 0x00C64EB0; slot 6 contains this entry and slot 5 contains the preceding subobject adjuster. Matched SpawnAndFadeNugget parsing and the constructor establish the address-derived owner's association, name field at +0x12C and offset fields at +0x130. The original method name and full class layout remain unresolved.

The raw call destinations agree with the bank's existing declarations: GameLogic lookup, ThingFactory template lookup and creation, Object's layer query, TerrainLogic's five-argument slot 7, Thing position/orientation setters, Object kill, Pathfinder registration, and CRT sin/cos. The body uses ECX as this, reads input+8, and ignores its second stack argument. Source position +0x38/+0x3C/+0x40, angle +0x44, team +0x304 and the final template flag are direct target accesses. The factory's fourth argument retains the existing opaque bool declaration and zero value; no stronger type claim is made. BFME 1 coord2d.cpp was read only as the cited arithmetic guide; no donor body or identity was imported.

## Hypotheses tested

Every hypothesis and its refuting observation was written before testing in `build/w7-50b98f/hypotheses.md`; all experiments checked STOP_WORKER first. H1 moved volatility to the offsetX read and was inert. H2 removed or moved the barrier. Moving it after the offset.x store repaired the original prefix but introduced three structural regions in the offset setup. H3 split the load and spill, adding a stack home and disturbing later allocation. H4 tested one-sided barriers: _WriteBarrier was inert, while _ReadBarrier emitted an unresolved call in this compiler. H5 tested a forceinline barrier helper and plain/read-volatile z copying; the helper retained the extra home and the copy changes were inert. None satisfies the required improvement rule. In particular, fewer operand differences accompanied more structural regions in H2. No further evidence-backed scheduling experiment was selected.

Each trial below has one fresh-object measurement. Scratch sources preserve the bank's comments. Flags are the bank's first cl line: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG and its three existing include directories. BFME_OBJSTORE was off for every compile and measurement. Each trial's `.align.log`, `.explain.log`, and `.measurement.json` are under `build/w7-50b98f/`; raw run logs are `h1-run.log` through `h5-run.log`. An align tool exit of zero means the diagnostic completed, not that the body matched. The ReadBarrier trials are invalid due to the named unresolved call.

| Trial | Emitted bytes | Patched differing bytes | Structural regions | Raw memory | Register | Unresolved |
|---|---:|---:|---:|---:|---:|---|
| before | 383 | 18 | 2 | 7 | 1 | [] |
| h1-both | 383 | 18 | 2 | 7 | 1 | [] |
| h1-read | 383 | 18 | 2 | 7 | 1 | [] |
| h2-after-offset | 383 | 23 | 3 | 6 | 0 | [] |
| h2-before-z | 383 | 26 | 2 | 8 | 1 | [] |
| h2-remove | 383 | 21 | 4 | 6 | 0 | [] |
| h3-split-read | 382 | 207 | 5 | 23 | 6 | [] |
| h3-split | 382 | 207 | 5 | 23 | 6 | [] |
| h4-before-ReadBarrier | 388 | 231 | 3 | 6 | 0 | ['__ReadBarrier'] |
| h4-before-WriteBarrier | 383 | 18 | 2 | 7 | 1 | [] |
| h4-h3-split-ReadBarrier | 387 | 221 | 5 | 23 | 6 | ['__ReadBarrier'] |
| h4-h3-split-WriteBarrier | 383 | 18 | 2 | 7 | 1 | [] |
| h5-helper | 383 | 50 | 3 | 25 | 6 | [] |
| h5-z-plain | 383 | 18 | 2 | 7 | 1 | [] |
| h5-z-read | 383 | 18 | 2 | 7 | 1 | [] |

## Checks and resume inputs

`check_csv.py` passed (`build/w7-50b98f/check-csv.log`), and `pin_consistency.py --check` passed (`build/w7-50b98f/pin-consistency.log`). Identity extraction passed (`build/w7-50b98f/identity.log`). All alignment and explanation diagnostics completed; byte equality failed for every candidate as shown above. No Code source changed, so build.sh and find_declared_unmatched were not applicable. The bank is byte-for-byte equal to `build/w7-50b98f/before.cpp`; its digest is in the clock receipt. All trial sources and raw outputs remain under the task scratch folder for coordinator review.

All eleven prior verdicts were read and saved in `build/w7-50b98f/prior-verdicts.txt`. None cites a tracked attempt_support path. The cited historical scratch `build/mp3/r10/wins/ms_best_0x0050b98f.cpp` is absent. `repair_queue.py dest` offers S3SubObjectAdjusters.cpp only as a nearest-neighbour heuristic; the vtable and constructor evidence above belong to the Made002CCC2D owner. No destination file was edited.
