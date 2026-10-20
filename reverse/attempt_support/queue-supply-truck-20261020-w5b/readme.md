# AIPlayer::queueSupplyTruck, third follow-up of 2026-10-20

Result: blocked. The bank `reverse/attempts/0x004f37b0.cpp` stays unchanged (fresh `tools/align_diff.py`: 1535 B, 21 structural regions, 69 memory, 13 register). Symbol `?queueSupplyTruck@AIPlayer@@IAEXXZ`, retail RVA `0x004F37B0`, extent 1537 bytes. Model: claude-opus-5-5.

## What the next attempt needs to know

1. **The build-list loop is not held back by a loop-optimisation budget.** The guarded rotated loop appears whenever cl needs a pre-header for the loop: for a constant hoisted into a callee-saved register, or for a register copy of `info`. In the hack-free candidate neither happens, so cl jumps into the bottom test. The decisive argument against a budget: adding code to the loop body (item 2) turns the hoist and the guard on, which cannot happen if the loop were over a budget that switches its optimisation off. On the hoisting variant h_head, 1 and 5 extra conditionals at the top of the build-list body keep the hoist and the guard; 20, 36 and 60 lose the vftable hoist but keep the guard (the zero constant then sits in ebx for the whole function and the pre-header copies `info` into esi). Whether the 35/36-conditional budget of 0x00156A60 and 0x00157FF0 switches off loop-invariant motion here at some higher count was not measured.
2. **The deciding quantity is the register priority of the base filter vftable constant `0x00BC26E0`.** Adding one more use of that constant (one extra destroyed `Rva002611DDFilter` temporary, a diagnostic statement) in the same block as the three destructor stores (h1c), or at the top of the build-list body (h_head), makes cl put the constant in a callee-saved register at the loop entry, and the guard follows. The same extra use after the recount (h_rec) or in the else arm (h_else) does not. So the gap is less than one same-block use of the constant. The original source must give that constant slightly more weight, or its competitors slightly less, than ours does.
3. **The competitors.** Taking the address of a variable removes it from register allocation (diagnostic only). Doing that to the loose-loop list iterator, to `desiredGatherers` or to `supplyCenter` gives the hoist; doing it to the recount list iterator, to either `supplyTruckAI` or to either `obj` does not. Natural respellings that lower the weight of those three are the next thing to try.
4. **The edge is chaotic, as a priority race is.** On the truncation `x17` (guarded and hoisted, the else arm cut before `new TeamInQueue`), each of these single additions removes the hoist and the guard: one load `m_player->m_sciencePurchasePoints` at the function top, any STLport list access at the top (`empty()`, `begin()`, `front()`, an iterator loop), and `m_teamDelay = 0` or one conditional at the start of the else arm. These keep both: a DLINK iterator loop of `Team`, `Object` or `TeamInQueue` at the top, a plain counted loop at the top, one conditional at the top or the end of the function, and a call, a global store or a store to another `m_player` field at the start of the else arm. One conditional or one global store at the top of the build-list body keeps the guard but loses the hoist. 8 or 30 conditionals at the top or the end of the function also keep the guard and lose the hoist: the zero constant then sits in ebx for the whole function and the pre-header copies `info` into a register.
5. **Payoff when the hoist happens.** h_head (77 bytes of dummy code) measures 1614 B, 14 regions, 85 memory, 25 register against the hack-free candidate's 1537 B, 19, 70, 22. Its build-list guard, the three destructor stores through one callee-saved register and the `test eax,eax` on the search result align with retail's instructions. Registers still differ (the constant takes edi, `supplyCenter` esi, the recount list iterator edi), and the dummy code shifts frame offsets, which inflates the memory count. Read region counts with care: h_rec, which does not hoist, measures 13 regions only because the whole recount loop becomes one unpaired region.
6. **Placement still differs.** Retail defines `mov esi, 0xBC26E0` inside the loop header (after the `isSupplyBuilding` compare, every iteration) and reuses esi for the recount `obj`, the loose iterator and `tTemplate`. The diagnostic hoists put the definition in the pre-header and either keep the register through the loop with a rematerialisation at the latch (h1c, esi) or take edi (h_head). A natural trigger may still leave this difference.

## Hypothesis of this run and its refutation

Hypothesis: the build-list loop exceeds cl 7.1's per-loop loop-optimisation budget in our source and not in retail's, so a lighter natural spelling of the loop body would restore the guard and the hoist. Refuting observation, registered before the trials: the guard or hoist flipping on an edge body through a change outside the loop that adds no block to it, or the loop staying optimised under many added conditionals. Both happened (item 1 and item 4), so the hypothesis is refuted and replaced by the priority race of item 2.

## Natural respellings measured on the hack-free candidate (no hoist, n=1 each)

All start from `../queue-supply-truck-20261020-w5/hack-free-candidate.cpp.txt` (c7) and were read with the hoist probe below.

| Trial | Change | Bytes | Guard | Hoist |
|---|---|---:|---|---|
| r1 | STLport iterators declared in the `for` initialiser | 1537 | no | no |
| r2, s1, s2 | the function-scope iterator reused by one or both inner scans | 1537 | no | no |
| i1 | without the two in-loop `if (!team) continue;` (diagnostic) | 1542 | no | no |
| i2 | without the two in-loop `if (!obj) continue;` (diagnostic) | 1531 | no | no |
| i3 | without the loose-loop `_ReadWriteBarrier` | 1537 | no | no |
| j1 | `if (!supplyCenter) continue;` instead of the nested block | 1537 | no | no |
| j2 | j1 with the short-count arm first, ending in `continue` | 1531 | no | no |
| g1, g2 | build-list loop as `if (info) do { ... } while (...)` | 1556 | yes | no |
| z1, z2 | player filter `true`, mask constructor first argument 1 (diagnostic) | 1537, 1538 | no | no |
| m1, m2, m12 | Zero Hour's initialised declarations of `truckInQueue` and `totalHarvesters` | 1537 | no | no |
| m3 | kind tests without the `!= 0` | 1537 | no | no |
| o1 | current count read before the desired count | 1539 | no | no |
| o2 | current count read inside the comparison | 1537 | no | no |
| t1 | Zero Hour's `Coord3D center = *supplyCenter->getPosition();` | 1518 | no | no |
| t2, t3 | member-wise copy through `getPosition()` or a position pointer | 1537 | no | no |
| u1, u2 | empty virtual destructors in the derived filter classes | 1537 | no | no |

Earlier runs' trials, rescanned from their side-by-side listings: none of the 41 measured trials hoists the constant into a callee-saved register, although several are guarded.

## Diagnostic recipes (never for landing)

- h1c: c7 with `g_out[0] = Rva002611DDFilter().allow(0);` inserted before `if (!supplySource) {` (declare `extern int g_out[256];`). 1616 B, guarded, constant in esi, 21 regions, 106 memory, 23 register.
- h_head: c7 with the same statement after `if (info->isSupplyBuilding() == false) continue;`. 1614 B, guarded, constant in edi, 14 regions, 85 memory, 25 register.
- The competitor test of item 3 adds `g_pp[n] = &variable;` after the variable's definition.

## Ledger note

This run's `blocked` row says that 1 to 60 extra in-body conditionals keep the loop guarded "with LICM active". Item 1 above is the corrected statement: the guard survives all of them, the vftable hoist only 1 and 5, and whether loop-invariant motion stays on at the higher counts was not measured. The row's `t=27` overstates the elapsed time; the run's clock read 24 minutes when the row was written.

## Tools and scratch

`hoist-probe.py.txt` compiles a trial and prints its size, whether the build-list loop is guarded, and which register holds the three destructor stores' constant and where it is loaded. A callee-saved register loaded about 60 instructions earlier means the hoist happened. It needs no align_diff run and takes a few seconds per trial. To use it, copy it and `dumpobj.py.txt` into one folder under `build/` as `shape.py` and `dumpobj.py`, put the trial sources there, and run `python build/<folder>/shape.py <name>...` from the repository root. Every trial source, disassembly, align log and side-by-side listing of this run is in the seat's untracked `build/w5_4f37b0_r3/`. The bank's first `// cl:` line controls every trial; no flags, headers or `Code/` files were changed.
