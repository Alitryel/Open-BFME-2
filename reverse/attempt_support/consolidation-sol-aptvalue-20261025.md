# Sol codexb consolidation prerequisite, 2026-10-25

## Cleared: AptValue string-copy declaration

Target: `Code/Libraries/Source/Apt/AptValue.cpp`.
Donor: `Code/Libraries/Source/Apt/Rva006DE870ToCString.cpp`.

The initial `tu_skeleton.py --merge TARGET --dry-run` rejected the donor with
C2039/C2270: `rva006DE870` was absent from the seed's included AptValue class.
The existing matched body at RVA 0x006DE870 independently establishes the
public const member taking a caller-owned char buffer. Add that same nonvirtual
declaration to `AptObject/AptScriptFunction.h`; layout and virtual order stay
unchanged. This preserves the existing neutral name and adds no binding.

Afterward the same dry run accepts the seed and donor, rejects none, and
reports three approved rows (including the donor's EH handler). No merge was
applied: leave this now-compatible pair for Luna. The seed's existing alias
rows also remain present; standalone `./build.sh TARGET DONOR` verifies all
11/11 matched rows and eight string literals. `find_declared_unmatched.py`
passes for the header and both sources. The normal header-dependent commit
gate supplies the wider acceptance check.

No source paths moved in this prerequisite or the outgoing batch at audit
time (HEAD 7d1555ce5f, no commits ahead of origin/master). No path consumers
need repointing. No files removed, new recovered bytes, or identity debt retired.

## Other scoped checks

Fresh planners and scoped queues were inspected for GameNetwork,
GameEngineDevice, and Libraries. Preserve held PingThread, Bridge, Shrub and
APT destinations for their owners.

* GameInfo: current composer already accepts the seed plus four clean donors,
  18 approved rows, no rejection. The old SlotState enum discrepancy needs no
  source repair. File/RVA investigation claims were released; leave for Luna.
* W3DPropDraw: React still rejects with C2011 Coord3D redefinition. Its optional
  ctor/dtor companion and the seed's real headers need coherent reconciliation;
  no speculative source edit made. ModuleDataDtor split dry-run selects both
  0x000CEF3C and 0x000CF058, then refuses because no residual row would remain:
  this is a whole donor for the merge lane.
* W3DTreeDraw: ModuleDataCtorG7 split dry-run selects 0x000CEBBF and refuses
  because its attached compiler rows leave no residual donor. The existing
  DrawModule virtual-slot prerequisite remains; adding a guessed slot is not a
  repair.
* Existing WWVegas HTree declaration/byte blockers and mixed Common donors
  remain as documented in the previous scoped handoffs. No outside-pool source
  was edited. Previously verified BIG, Font, Laser, debug and network subsets
  remain mechanical work for Luna.

Local dry-run receipts: `build/sol-aptvalue-before.txt`,
`build/sol-aptvalue-after.txt`, `build/sol-prop-before.txt`,
`build/sol-prop-split-dry.txt`, `build/sol-tree-split-dry.txt`.
