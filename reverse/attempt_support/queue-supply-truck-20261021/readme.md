# AIPlayer::queueSupplyTruck 0x004F37B0 (1537 B), 2026-10-21

Bank: `reverse/attempts/0x004f37b0.cpp` (score 0.7867), unchanged. Best
hack-free candidate: `../queue-supply-truck-20261020-w5/hack-free-candidate.cpp.txt`
(1537 B, 19 regions, 70 memory, 22 register diffs by align_diff).

Refuted this run (each compiled against the bank's TU flags):

- Ctors without throw() defined in this unit (TeamInQueue 0x4EF5CE, WorkOrder
  0x4F10E6, now landed in AIPlayerTeamBuild.cpp): identical code. The merged
  new-expressions already match retail.
- Same-TU callee visibility: stub bodies for findFactory, prependTo_TeamBuildQueue
  and checkForSupplyCenter defined ahead of the caller. Bodies that call
  externals as the real ones do (nameToKey, findModule, compare) leave the code
  identical. Only an unrealistic leaf checkForSupplyCenter stub moved one zero
  store (16/71/23, not better).
- `tools/permute.py --flags 0x004F37B0`: closed 0 of 1.

Remaining residue (unchanged): retail loads the base filter vftable 0xBC26E0
into esi at the build-list loop head, after the isSupplyBuilding test. Its loop
is guarded (top-tested) and keeps info in the stack home [ebp-0x18]. Ours is
bottom-tested and keeps info in eax. Stack slots also differ: totalHarvesters at
-0x28 vs retail -0x20, objIter at -0x68 vs -0x64, radius at -0x50 vs -0x68.
Retail shares [ebp-0x14] among desiredGatherers, a temp, supplySource and
factory.
