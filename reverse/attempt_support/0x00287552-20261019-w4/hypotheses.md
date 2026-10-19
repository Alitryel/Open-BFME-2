# Target 0x00287552

All twelve recorded verdicts (including the older 0x287552 spelling) and the bank were read before experiments. The cited historical scratch directory build/big/fire-watch is absent in this checkout; no prior verdict cites a tracked attempt_support file for this target. Earlier trials covered declaration permutations, geometry definition visibility, math overload visibility, paired address-taken local swaps, direct floor-to-fistp expressions, scheduler rewrites, and position-copy order. They do not justify repeating those sweeps.

## H1: correct the box row update

The current farm bank ends the box row with rowX += rowStepX and a volatile update to the inner-loop sy. That drops the rowY update, so later box rows use the same starting y. Hypothesis: retail advances the persistent rowY, and replacing the volatile sy update with rowY += rowStepY restores behavior at comparable alignment. Evidence must be checked in the retail outer-loop backedge before compilation. Refutation: retail updates only the discarded inner-loop y value or never feeds the changed y into the next row. The emitted backedge and next-row loads will distinguish the two.

## Identity and constraints

Keep the existing address-derived method name. Registration twins at 0x287C21 and 0x287C39 call this setter with add values 1 and 0, gated on signed object+0x49C. The destination tool selects Code/GameEngine/Source/GameLogic/Map/FireLogicSystemObjects.cpp by neighbouring rows. Before any trial, check build/STOP_WORKER. All measurements set BFME_OBJSTORE=off and use a fresh object. No production source changes until an exact body exists.

H1 is confirmed by retail: 0x28791F loads persistent rowY from ebp+0x4C, 0x287929 adds rowStepY, 0x287933 writes back there, and 0x287856 reloads that home for the next row. H1 remains 1496 bytes, with the same six structural regions; align memory differences grow from 113 to 117 and registers stay at one. This is a semantic repair, not an alignment improvement.

## H2: restore the retail cached position and angle

Retail loads the angle once at 0x2876B7 into ebp+0x40 and passes that home to both Cos and Sin. The bank instead reloads obj->m_angle for Cos on every iteration, which need not equal the cached value after intervening calls. Restore Cos(angle), x/y/z copy order for pos and p, and remove the source-only compiler barrier before circle floor. The copy-order changes were previously measured; this trial establishes a clean semantic baseline after H1 rather than claiming a novel copy-order lever. Hypothesis: the farm barrier adds unnecessary lifetime constraints to the radius temporary. Refutation: the clean form retains the same circle structural regions and frame size, in which case it is not the missing allocation constraint.

H2 retains six regions and the 0x8C frame, refuting the barrier lifetime hypothesis. Its regions are now exactly three paired pop/fstp reorderings (the first box ceil and both circle floors). The bank baseline's circle radius store reordering disappears, but another pop/fstp ordering appears. H2 has 117 memory differences and one register difference, with 101 nonrelocation positional bytes different versus 109 originally. No alignment improvement is claimed.

## H3: explicitly share the two box ceil results

Retail stores both box ceil returns to the same float home ebp+0x50 before fistp, and both stores sit between the two argument-cleanup pops. Current source expresses two anonymous cast temporaries, with only the second store scheduled between pops. A single named float variable assigned both returns is a natural representation of the observed shared home and may change its lifetime and the first store schedule. Refutation: identical emitted bytes to H2 or the first ceil still stores before both pops. This tests shared assignment identity, not another declaration-order permutation.

H3 is refuted: all three pop/fstp reorderings remain; its six regions, 120 memory differences, one register difference and 104 nonrelocation positional differing bytes are worse than H2. No remaining new evidence justifies repeating the historical frame-slot sweeps. H2 is retained under the explicit semantic-repair exception at comparable alignment, not as a strict alignment improvement. The unresolved frame is retail 0x94 versus compiled 0x8C, with circle bounds sharing the sine and ceil temporary homes that retail keeps separate.
