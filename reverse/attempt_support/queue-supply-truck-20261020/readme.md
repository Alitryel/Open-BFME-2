# AIPlayer::queueSupplyTruck, follow-up of 2026-10-20

Result: closer partial. Symbol `?queueSupplyTruck@AIPlayer@@IAEXXZ`, retail RVA `0x004F37B0`, extent 1537 bytes, banked at `reverse/attempts/0x004f37b0.cpp`. Model: claude-opus-5-5.

| Body | Emitted | Structural regions | Memory | Register | Score |
|---|---:|---:|---:|---:|---:|
| previous bank (2026-10-19) | 1535 B | 21 | 75 | 13 | 0.7733 |
| new bank | 1535 B | 21 | 69 | 13 | 0.7867 |

Both rows are fresh `tools/align_diff.py` runs with `BFME_OBJSTORE=off` and the object deleted first. The score is the previous handoff's method (one minus unmatched retail instructions plus memory and register differences, over 450 retail instructions); recomputing it for the previous bank reproduces its recorded 0.7733 exactly.

## The change

The three partition filters are now temporaries of the one full expression that calls `getClosestObject`, chained through the pinned `link` (0x00625790, `PartitionFilter::And` in WorldBuilder): `Rva0004584D(...).link(Rva0026137EFilter(m_player,false).link(&Rva002611DDFilter()))`. Before, the map and player filters were named locals in an artificial block and only the kind filter was a temporary. Construction order (map, player, kind), destruction order (kind, player, map, right after the search) and the EH states are unchanged, so the behaviour is the same, and the source no longer needs the extra block.

Read the gain for what it is. The emitted code differs from the previous bank in one place only: the wrapper's preload `mov edi, [ThePartitionManager]` (retail has none; it loads the manager into ECX just before the call) moved from inside the filter-construction run to inside the centre copy. Every other instruction is identical. In its old position the preload shifted align_diff's pairing of the identical filter stores from +0x163 to +0x1C9 by one instruction; in its new position nothing is mis-paired. With relocations masked, aligned-but-different instructions drop from 86 to 80 and unpaired ones stay at 28. So the six fewer memory differences are an alignment effect of moving one extra instruction, not a removed defect. The body qualifies as closer under the align_diff rule, but the real distance to retail is unchanged.

## Hypotheses refuted in this run

- Callee visibility: retail's unit plausibly saw the header-inline bodies of the mask constructor 0x00045411, the 28-byte mask copy 0x0004543D and the kind-filter constructor 0x0004584D, and the fleet's visibility lever suggested `__declspec(noinline) inline` copies (also of `And` 0x00625790) could move register allocation. Four combinations produced align_diff output identical to the bank: refuted.
- Plain priority argument: `natural-args.patch` (against the previous bank) replaces the volatile helper `__cp(__vref(team->m_priorityBuild))` with Zero Hour's `team->m_priorityBuild`: 1529 B, 20 regions, 76 memory, 17 register, a trade. Its byte slots then follow retail's pattern, but three adjacent pairs of stack homes come out swapped (info and the recount count, the recount list iterator and totalHarvesters, teamName and isSupplyTruck). On the new bank the same change gives 20 regions, 70 memory, 17 register, again a trade.
- Plain partition manager: dropping the `(ThePartitionManager ? ... : ...)` wrapper on the new bank reproduces most of retail's build-list loop head (info in memory at [ebp-0x18], the inverted loop, supplyCenter in EDI) but costs 22 regions, 73 memory, 35 register: the radius becomes an x87 temporary at [ebp-0x1C] instead of retail's SSE home at [ebp-0x68], and a zero constant takes ESI, with supplySource compared from memory against it. Radius operand order, declaration order and a whole-struct centre copy did not help.
- Testing supplySource inside the filter scope, or inside the same full expression, regresses (22 to 31 regions).
- Dropping the remaining iterator barrier, or the build-list `(info ? info : info)` condition, on the new bank trades classes (22/71/15 and 23/67/14).
- The `(truckInQueue ? true : true)` wrapper is inert (identical align_diff output with and without it); it can go whenever the bank is next replaced.

## Diagnostics for the next attempt

- The build-list loop form follows `info`'s allocation: a probe with the bank's flags emits the jump-to-bottom-test loop while the loop pointer is in a register and retail's duplicated top and bottom test once it lives in memory, so the back-edge difference is a consequence, not a separate lever.
- In the recount loop cl folds `obj+0x258` into a register whenever `[obj+0x258]` is read again after calls. Small probes reproduce the fold under every spelling tried (loop-variable form, visible `advance`, extra later use of `obj`, more pressure), while retail keeps `obj` in ESI and reloads `[esi+0x258]`. One to three diagnostic sink stores of `obj` in the bank did not change it either. No local spelling tried reproduced retail's shape there.
- Remaining mismatch: stack homes and registers around `info`, `obj` and the list iterators, retail's early `mov esi, 0x00BC26E0` (base filter vtable for the three destructor stores), the partition-manager preload into EDI caused by the wrapper, and the head-tested build-list loop.

## Ledger note

This run first recorded a `blocked` row and then, after the closer result, the `partial` row that banks this body. The later row supersedes the earlier one; the earlier row's `t=45` is wrong (the run had taken about 12 minutes at that point). The partial row's phrase "filter construction now in retail order" is also inaccurate: the construction order was already retail's, and the measured gain comes from the moved preload described above.

Scratch evidence in the seat checkout (untracked): `build/w4_4f37b0/`, holding every trial source, its `.align.log`, side-by-side listings (`*.sbs.txt`) and the probes under `probe/`.
