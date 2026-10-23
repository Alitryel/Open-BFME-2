# DamageFieldUpdate update: closer bank

The source remains `reverse/attempts/0x00491316.cpp`, symbol `?update@DamageFieldUpdate@@UAE?AW4UpdateSleepTime@@XZ`, retail RVA `0x00491316`, extent 615 bytes. No source was put in `Code/`, no row or pin was added, and nothing was committed. The destination query proposes `Code/GameEngine/Source/GameLogic/Object/Update/DamageFieldUpdate.cpp`; its neighbouring-unit fallback is `FamilyDeletingDtors.cpp`, which is not suitable for this update implementation. Inputs: BFME 2 da7b6104a271a1b0e0c89a81594577621f04933c and BFME 1 a18d9ed50607e9175de4d6568798d7d73119de09. Worker model: gpt-6.1-sol. The clock started at 2026-10-19 04:44:37 UTC; the appended verdict records elapsed minutes.

## Result and measurements

Fresh `align_diff.py` runs use separate trial paths and delete each object and dependency receipt before measuring. Every build/measurement uses `BFME_OBJSTORE=off`. The exact commands are in `build/damagefield491316/measure.py`; all trial sources and raw logs remain in that folder. The two adjacent alignment logs preserve the original bank and selected candidate measurements without reconstruction.

| Measurement | Original bank | Selected candidate |
| --- | ---: | ---: |
| Emitted bytes | 645 | 623 |
| Retail bytes | 615 | 615 |
| Structural regions | 11 | 6 |
| Memory differences | 33 | 31 |
| Register differences | 17 | 15 |
| Relocation-patched positional differing bytes | 202 | 184 |
| Unresolved direct bindings | 2 | 0 |

The original positional byte count includes two unresolved insert references. The structural, memory and register measurements independently establish the improvement; the byte count is supplementary. Relocation and branch lines are excluded from the decision. The bank score is computed from the selected alignment as one minus the sum of memory differences, register differences and retail instructions in structural regions, divided by the retail instruction count. It is a scheduling estimate, not exact byte verification.

## Identity and declarations

The target vtable at RVA `0x0084d964` holds VA `0x00891316`. The matched DamageFieldUpdate constructor installs it at primary-this plus `0x10`. This body reads data and Object at secondary-this minus `0x0c` and minus `8`, then calls the rowed DamageFieldUpdate fire helper at `0x004911ae` with primary this. The rowed xfer begins at `0x0049157d`, immediately following the target's final ret. These establish the real class name, secondary-interface convention and complete extent independently of byte similarity. Raw target disassembly is `build/damagefield491316/retail.log`.

The target constructs relationship, not-self, alive and extra filters in that order, then calls link on not-self, alive and extra. The farm changed the chain order; this candidate restores retail's order. Each loop now passes the native four-byte saved ID. The second loop reuses that saved value for find and insert, and the third no longer initializes an unrelated three-word aggregate. The existing BfmePod12 provider spelling is retained only through an external reference view: the complete native remove body at `0x002abfc3` reads only the first word of the referenced key. Its original element identity is not claimed.

The native destructor at `0x00268902` calls the rowed reset at `0x0026549e`, which walks nodes into the pool without callbacks or allocation; the remainder returns the sentinel to the pool. Declaring this cleanup nonthrowing removes both extra EH-state writes and matches the target's consecutive destructor calls. Insert now uses the already admitted private `Rva002A1B6FNativeList::insert` ABI from `Rva002A1316.cpp`, rather than the bank's unresolved declaration. Retail independently proves hidden result, one-word iterator and four-byte const element reference with ret12. Its provider ignores ecx. No new alias or pin was introduced. The older constructor/destructor and provider-name views remain reconstruction debt; their bindings do not establish original STL names.

## Hypotheses and controls

All three prior verdicts and the complete bank were read before experiments. They cite no additional support paths. The historical bank changes at fe6e53d924 and 116edad4b8 were inspected. New hypotheses, supporting observations and refutation criteria were written before each experiment in `build/damagefield491316/hypotheses.md`.

Scalar IDs improve the original alignment to 9 structural, 32 memory and 17 register differences. Passing the saved ID by reference and declaring native list destruction nonthrowing improves it further to the selected alignment. Rebinding insert resolves both calls without changing that alignment. The ObjectID find spelling, const end locals and unifying insert/find iterator types do not improve shape. Direct end expressions, explicit sentinel caching, C++ labels matching the third-loop graph and reversing equality operands either regress a difference class or leave the graph unchanged. Those trials are rejected. The idref-only explain probe fails its extent check because its final call displacement crosses the target extent; its raw error is `build/damagefield491316/idref.explain.log`. No retail extent was changed.

## Remaining mismatch and next prerequisite

The candidate's frame is `0x5c` against retail `0x58`, shifting the four filter temporaries by one word. First-loop find materializes its first iterator before the argument push and uses different result/ESP-save slots. Second-loop find retains an extra load/store sequence and delays caching its end in edi. The third loop duplicates the pretest and reloads the sentinel where retail caches it and branches to one common comparison. These account for the remaining six structural regions and eight excess bytes. No new evidence-backed shape experiment remained after the recorded controls. Resume from the corrected bank, not a rejected trial; do not add no-op operations or change filter order to influence register allocation.

`check_csv.py` and `pin_consistency.py --check` pass; raw logs are `build/damagefield491316/check_csv.log` and `build/damagefield491316/pin_consistency.log`. Exact verification is not achieved. `build.sh`, `add_match.py` and production-source declaration checks were not run because no matched source or ledger row was introduced. Every original bank comment is retained. No background task remains from this run.
