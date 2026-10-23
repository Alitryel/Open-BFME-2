# FireLogicSystem update: closer bank

The candidate for `?update@FireLogicSystem@@UAEXXZ`, RVA `0x00287FAD`, retail size 1599 bytes, restores the unsigned-short fuel conversion and removes the farm's compiler barrier and volatile float reinterpretation. It keeps the farm's named key lifetimes and narrow temporary scopes. It remains a bank, with no source or ledger landing under `Code/`.

## Evidence and identity

The Ghidra inventory records the start and 1599-byte extent. Retail begins with an EH prologue, takes `this` in ECX and ends with `ret` at `0x002885EB`; the separate getter starts at `0x002885EC`. The primary FireLogicSystem vtable at VA `0x00BFB7BC`, written by its already matched constructor, dispatches this body through slot 10. The constructor's existing identity evidence includes the `TheFireLogicSystem` literal. The native body accesses the same grid at `this+0x70`, storage at `+0x74`, row/column counts at `+0x78/+0x7C`, and burning set at `+0x84`. Every aligned direct call maps to an existing symbol candidate, including the key constructor/destructor, tree operations, object lookup and damage calls. No new name or pin was introduced.

Retail `0x002880CE` reads fuel with `movzx eax,word ptr [esi+4]`, then `0x002880DB` uses `cvtsi2ss`. The farm read instead interpreted four bytes spanning fuel and check as a float after clearing check. That interpretation produces subnormal values and depends on floating point denormal handling. The corrected typed conversion reproduces the native operation. The private SubsystemInterface declarations now agree with the target shim's slots 0 through 13, placing update at slot 10; this leaves the emitted update bytes unchanged. The three quoted includes are relative to the bank directory, so its original compiler comment works without an added `/I.`. All original bank comment lines are preserved in order.

## Measurements

The inputs are checkout `584fc123ad9c144e479a42840ed048440a688d48` and the bank from farm commit `8c8f3df691f1f6293b78db2929782804795f3aed`. All builds and measurements use `BFME_OBJSTORE=off`. Trial paths are unique, so align_diff cannot reuse an earlier trial's object.

| Candidate | Emitted bytes | Structural regions | Raw memory differences | Raw register differences |
|---|---:|---:|---:|---:|
| Existing farm bank (`before.cpp`) | 1603 | 7 | 19 | 9 |
| Typed conversion (`typed.cpp`) | 1606 | 5 | 19 | 9 |
| First insertion as full-expression temporary | 1596 | 4 | 19 | 12 |
| Last insertion as full-expression temporary | 1599 | 8 | 23 | 20 |
| Actual constructor visible | 1606 | 5 | 19 | 9 |
| Tick node initialized before header | 1606 | 5 | 19 | 9 |
| Shared node local across walks | 1606 | 5 | 19 | 9 |
| Final portable bank with corrected declarations | 1606 | 5 | 19 | 9 |

The accepted candidate removes two structural regions without increasing either operand class. Relocation and branch lines are excluded from the improvement decision. The raw memory count includes global relocation operands, so it is not a count of incorrect member offsets. Both the old and new bank have the native `0xF4` frame. The old frame-size blocker in prior verdicts no longer describes this bank.

The separate raw-object probe reports 563 before and 787 after positional differing bytes outside the object's COFF relocation fields. These positional counts grow because the streams shift and are not the acceptance metric. After mnemonic alignment and ignoring relocation fields and branches, differing operand bytes are 15 before and 15 after, and differing retail instructions are 17/474 before and 15/474 after. The new bank's score is the latter matching fraction, 459/474. The emitted length remains seven bytes larger than retail.

## Experiments and remaining work

All nine prior verdicts and their sole cited evidence path, the bank, were read before the first experiment. No separate support path was cited, and targeted content search found no earlier support document. New hypotheses, evidence and refuting observations were written before each trial in `build/firelogic-287fad-w4/hypotheses.md`. Full-expression temporary variants trade fewer structural regions for more register differences or worsen both operand classes, so they were rejected. Real constructor visibility, tick initialization order and sharing the node local leave the update bytes unchanged. No further supported shape experiment was identified.

Remaining mismatches are the first insertion key and exhausted-fuel lookup key homes (`-0x70` and `-0x5C`, reversed relative to retail), an extra address reload after each insertion-key constructor, spread-loop address construction and spill scheduling near retail `+0x416`, and ESI/EDI allocation in the final tick walk. Keep the named-key candidate and its semantic correction when investigating these differences.

`tools/repair_queue.py dest 0x00287FAD` returns the adjacent vector helper's WWLib file with an explicit “no usable approved TU” warning. This is a neighbour heuristic, not evidence for putting FireLogicSystem in WWLib. `reverse/tu_map.csv` and the matched constructor identify `Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp`; existing FireLogicSystem methods live in `FireLogicSystemObjects.cpp` in that directory. No destination file was edited.

## Raw evidence

All trial sources, probe scripts and raw logs remain under `build/firelogic-287fad-w4/`. The authoritative comparisons are `before-align.log` and `final-align.log`; `before-explain.log` and `final-explain.log` contain the positional byte and instruction views. `object-probe.log` records raw-object differing bytes and direct-call mappings. `retail.log` contains the native disassembly, key providers and vtable slots. `prior-verdicts.log`, `farm-diff.log`, `boundaries.log` and `dest.log` preserve discovery outputs. The individual rejected trial logs retain their exact output.

The CSV and pin consistency checks pass before banking (`check-csv-before.log`, `pin-check.log`). The final recording and subsequent checks are in `record.log`, `check-csv-after.log` and `final-verify.log`. No commit, network operation, claim, verification runner or background task was started. This candidate is not byte-exact and no exact-result gate is claimed. Model: `gpt-6.1-sol`.
