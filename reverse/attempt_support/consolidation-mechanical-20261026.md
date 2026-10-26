# Mechanical consolidation handoff — 2026-10-26

Shard 3/5; only allocated destinations were considered. Planner snapshots were regenerated for each parent and passed `name_lane.py consolidate --check`.

## Binding blocker: DetachableRiderUpdate

`--merge --dry-run` accepted only the unchanged `DetachableRiderUpdatePoolKey.cpp` donor. The staged merge preserved six matched rows, transferred one data-check key and two data-ledger keys, and passed `./build.sh`, `find_declared_unmatched.py`, `check_csv.py`, `tu_ownership.py --staged`, `verify-removed`, and the staged COMDAT check. `code_identity_gate.py --staged` found zero new findings.

The scoped link audit required refreshing stale receipts; `link_check.py --refresh` rebuilt 285 stale objects from the old index at 47e030bafc (2026-10-26 08:28). It then reported `DetachableRiderUpdate.cpp: does not link LINKED 699 -> 0 bytes`, with duplicate `?getModuleNameKey@DetachableRiderUpdate@@UBE?AW4NameKeyType@@XZ` and the selected definition not retail's. The index predates current `origin/master`, so this is provisional, but it is a concrete provider collision requiring Sol's investigation before the move can publish. `data_check.py --staged` also reports two outside-baseline shadow findings for the moved function-local statics at 0x00A03D5C and 0x00A03D60; current compiler names use `getModuleNameKey`, while transferred ledger/baseline names encode `rva004AE832`. No identity debt was retired.

Path-consumer search found no active references in tools, hooks, workflows or build configuration to the deleted donor path. Historical EA path evidence and ordinary source references remain. No census was run.

## Rejected allocated destinations

- `AssaultTransportAIUpdate.cpp`: no unchanged accepted donors. Representative exact failures: `C2039: 'Rva0048F365Helper' is not a member of 'AssaultTransportAIUpdate'`; pool-key donor: `C2039: 'rva00048F411' is not a member of 'AssaultTransportAIUpdate'`; Xfer donor: `C2011: 'Xfer' : 'class' type redefinition`; other rejected donors fail on private/missing members or missing class methods. Sol prerequisite repair required.
- `SupplyWarehouseDockUpdate.cpp`: no unchanged accepted donors. Seed fails under merged flags at `_alloc.h(446)` with `C2950: '_STL::allocator<char>' : cannot explicitly instantiate an explicit specialization`, then `C2227` for `getSupplyTruckAIInterface`; slot donor fails because `rva004A7DA5` is not a member. Sol prerequisite repair required.
- `OneRingPenaltyUpdate.cpp`: no unchanged accepted donors. Rejections include `C2039` for `xfer`, `getModuleNameKey`, and `update` missing from `OneRingPenaltyUpdate`; `C2248` private access to `m_specialObjectName`; module-data destructor also fails byte verification. Planner recommended adopting `Coord3D`; no repair attempted.
- `DetachableRiderUpdate.cpp`: remaining unchanged donors were rejected for declaration/method mismatches or STL duplicate definitions (`C2995` `_STL::_Construct`, `C2011` `_STL::__false_type`). No rejected donor was repaired or moved.

All failed trials were dry-runs; no source or ledger edits from them remain. Destination eligibility and the mixed-file split lane still need further assessment by the consolidation seat.
