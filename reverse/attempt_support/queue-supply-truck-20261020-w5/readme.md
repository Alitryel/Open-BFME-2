# AIPlayer::queueSupplyTruck, second follow-up of 2026-10-20

Result: blocked. The bank `reverse/attempts/0x004f37b0.cpp` (1535 B, 21 structural regions, 69 memory, 13 register) stays. Symbol `?queueSupplyTruck@AIPlayer@@IAEXXZ`, retail RVA `0x004F37B0`, extent 1537 bytes. Model: claude-opus-5-5.

## What the next attempt needs to know

Most of the remaining mismatch hangs on one register decision, and the shape of the build-list loop appears to gate it:

1. Retail loads the base filter vftable `0x00BC26E0` (the three inline destructor stores after `getClosestObject`) into esi at the head of the build-list loop (+0xF0). Every candidate so far materialises it in eax right before the stores. The matched siblings `findSupplyCenter` (0x004F21D5, same unit), ScriptConditions 0x003EA566 and `AIStructureCreepTactic::findBestInterestZone` (0x005ABEA2) show the same constant hoisted into a callee-saved register at a loop entry.
2. With the constant in esi, eax survives the destructor stores, so the null test of the search result is `test eax,eax` and the result is spilled to the shared temporary slot `[ebp-0x14]`. Without it, the constant takes eax, the null test reads memory against a zero constant, and that zero then needs esi across the calls (the `xor esi,esi` and `mov byte [ebp-0x30],0` lines where retail has `xor ecx,ecx` and `mov byte [ebp-0x30],cl`). The diagnostic truncation `x1` (else arm emptied) reproduces retail's whole sequence: `test eax,eax; mov [temp],eax`, three stores through the hoisted register, `je`.
3. Retail compiles the build-list loop as a guarded rotated loop (`test eax,eax; mov [ebp-0x18],eax; je exit` before the body, the same test at the bottom). Every full-body candidate gets a different shape: the bank's `(info ? info : info)` gives a head test with a jump back, and the plain `info` condition gives a jump into the bottom test. Over all trials of this run, the hoist of step 1 appeared only in variants with the guarded loop (`x1`, `x17`) and in none of the others. The guard is not sufficient on its own: `x3`, `x4`, `x5`, `x13`, `x14`, `y1` to `y3` and `w1` are guarded and still put the constant in eax (n=1 each).

What decides the loop shape is not a local construct. In small probes cl gives every outer loop with an inner loop the guarded shape, including with EH temporaries, a static local, `new` expressions and a `return` inside an inner loop. In the full body it disappears, and it comes back when any of several unrelated pieces is removed: the first build-queue loop (`y3`), the first harvester count loop (`y2`), the recount loop (`y1`), the template block from `new WorkOrder` with its stores onwards (`x5`, `x13`), or only `m_player->setCanBuildUnits(true)` from a body already truncated before `new TeamInQueue` (`x17`). Rewriting the first loop as a plain pointer walk with an inline `m_next` getter also brings it back (`w1`, 1534 B, 22/93/26), but the same walk calling the out-of-line getter does not (`w2`, `w3` with a visible noinline getter). Respellings of that store on the truncated body (`x21` to `x24`) and of the loop condition (`p2` to `p5`, `l2` to `l5`) do not. The trigger is therefore a function-wide threshold-like quantity, and it is not monotonic in code size: `x8` is smaller than `w1` and is not guarded. Retail has the full body and the guard, so the original source is lighter in whatever cl counts. Iterator inline layers (the by-value `DLINK_ITERATOR` temporaries, the STLport list iterators) are the untested candidates.

## Measurements

These are fresh `tools/align_diff.py <file> ?queueSupplyTruck@AIPlayer@@IAEXXZ 0x004F37B0 1537` runs with `BFME_OBJSTORE=off` and a distinct source path per trial. All figures are single compiles (cl is deterministic).

| Trial | Change against its base | Bytes | Regions | Memory | Register |
|---|---|---:|---:|---:|---:|
| bank | none (re-measured) | 1535 | 21 | 69 | 13 |
| e1 | bank, cash product written GlobalData-first | 1535 | 21 | 69 | 13 |
| e2 | bank without the `ThePartitionManager` wrapper | 1535 | 22 | 73 | 35 |
| e3 | e2 with BFME 1's named-filter block | 1535 | 25 | 75 | 31 |
| r1 | e2 with an inline accessor for the bounding radius | 1541 | 20 | 74 | 22 |
| p5 | r1 without `(info ? info : info)` | 1543 | 20 | 74 | 22 |
| c3 | p5 with the plain `team->m_priorityBuild` argument | 1537 | 19 | 70 | 22 |
| c7 | c3 with the plain `truckInQueue` test (inert) | 1537 | 19 | 70 | 22 |
| c5 | c3 without the `_ReadWriteBarrier` | 1537 | 19 | 72 | 23 |
| b1 | bank without `(info ? info : info)` | 1537 | 23 | 67 | 14 |
| b3 | bank with the radius accessor | 1535 | 21 | 69 | 13 |
| z6 | c7, search result assigned inside the `if` condition | 1541 | 20 | 78 | 27 |
| k2 | c7, kind tests through an inline `isKindOf(bit)` predicate | 1564 | 29 | 84 | 43 |
| w1 | c7, first loop as a pointer walk with an inline getter | 1534 | 22 | 93 | 26 |

`c7` is kept beside this file as `hack-free-candidate.cpp.txt`. It drops three of the bank's four steering spellings (the partition-manager wrapper, the loop-condition ternary, the volatile priority copy), keeps only the loose-loop barrier, and is exactly 1537 bytes long. It is not closer under the align_diff rule (19 regions against 21, but 70 memory against 69 and 22 register against 13), so it is evidence, not a bank.

## Findings that hold independently

- Radius lever (confirmed): reading the bounding radius through an inline accessor (`Real radius = 200.0f + supplyCenter->getGeometryRadius();`) keeps `radius` a memory-homed SSE local (`movss/addss/movss`), as retail has it, without the partition-manager wrapper. Read directly from the member, without the wrapper, cl computes it on x87 into a spill slot (`e2`). WorldBuilder's twin (WB 0x010F6160) also reads the radius through an accessor temporary before the add.
- The bank's three filter temporaries in one full expression and `findSupplyCenter`'s form (named map and player filters in a block, the kind filter as a temporary, the result assigned inside the block) compile identically on the same base (`e4` against `r1`, `e4b` against `e2`). BFME 1's form with all three filters named is worse (`e3`): the kind filter moves to another slot and retail's save of its `this` in `[ebp-0x14]` disappears.
- The cash product's operand order (`imul ecx,[eax+0x88]` in retail) does not follow source order (`e1`); BFME 1's near match has the same open difference.
- Inert on the counts of `c7` (19/70/22 each): the compile flags `/Ob1` and `/Oy-` removed or `/Ob2` added (`c7f1` to `c7f3`; the same on the bank), a separate `info` declaration, `if (!info->isSupplyBuilding())`, direct member reads for the gatherer counts, and a `!= 0` accessor (`c7l2` to `c7l5`).
- Leave the build-list loop unguarded (only the shape was checked): direct member reads for the Object or the info accessors (`v1` to `v3`), a class `operator new` or throwing constructors for WorkOrder and TeamInQueue (`n1`, `n2`), a struct copy of `center` (`u1`), and dropping single statements from the full body (`u2` to `u4`).
- An inline `isKindOf(bit)` predicate with a computed bit materialises `setne`/`test al,al` (`k1`, `k2`); retail's kind tests are direct byte tests.

## Remaining mismatch of the hack-free candidate (c7)

1. Build-list loop: jump into the bottom test instead of retail's guard (regions +0xE1, +0x10A).
2. The consequences listed in the chain above (+0xF0, +0x1E2, +0x229, +0x258).
3. Recount loop: `obj+0x258` folded into esi (`lea esi,[eax+0x258]`) where retail keeps `obj` in esi and reloads `[esi+0x258]`; the recount list iterator cached in esi instead of retail's ecx with home `[ebp-0x24]`; the `curGatherers = 0` zero not shared with the iterator's member-pointer adjustment (+0x284 to +0x339).
4. Loose loop: the `!team` test cached in ecx where retail compares `[ebp-0x5c]` in memory, and `obj` spilled because of the barrier where retail keeps it in edi (+0x398 to +0x3D6, +0x5E1, +0x5EA).
5. Register-only: the first loop's list and team iterators swap esi and edi.

## Next step

Find which part of the source carries the extra weight that suppresses the guarded rotation, starting from `c7` and the truncation pairs above. Compare the iterator spellings against Zero Hour's headers, one construct at a time, and keep the loop's guard as the observable. Each pair differs in one construct and one of them flips the shape, so the pairs bracket the threshold. If the guard appears with the full body, check next whether the constant hoist follows (it did in `x1` and `x17`, not in nine other guarded variants); items 1 and 2 close only if it does. Re-measure the recount and loose-loop allocations after that, before any work on them.

## Inputs and scratch

The bank's own first `// cl:` line (O1, Ob1, G7, SSE, Oy-, GX, STLport) controls every trial; no flag override or shared header was edited. Scratch sources, `.align.log` and side-by-side `.sbs.txt` listings, the loop-shape probe (`probe.cpp`, `probe.dis.txt`), the WorldBuilder dump (`wb.txt`) and the helper scripts are in the seat's untracked `build/w5_4f37b0/`.
