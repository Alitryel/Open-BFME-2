# PreorderCreate TU consolidation audit — 2026-10-26

The fifth mechanical shard allocation approved
`Code/GameEngine/Source/GameLogic/Object/Create/PreorderCreate.cpp`. A fresh
scoped name-lane report passed its currency check and the allocator's TU
ownership check passed. `tu_skeleton.py --plan` approved four rows from two
mixed sources and two donors. The unchanged merge trial accepted only
`Code/GameEngine/Source/GameLogic/Object/Upgrade/PreorderCreatePoolKey.cpp`
(two rows). It rejected `PreorderCreateConstructor.cpp` with C2511: the
`PreorderCreate(Thing *, const ModuleData *)` definition has no declared
member in the current class view.

The `ConstIntGetters4.cpp` mixed split trial accepted row `0x004B9281`, but
that shared source was held by another worker, so it was left untouched. The
`Rva004B8CDEDerived.cpp` split trial for `0x004B9287` was rejected because a
copied helper or datum would grow a hatch. Only the accepted pool-key donor was
merged. The tool transferred its existing data-check baseline and data-ledger
keys to the destination; this is path ownership transfer, not data-debt
retirement.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Create/PreorderCreate.cpp`
  passed both matched rows, byte checks, string/float/import checks and exact
  funclet verification.
- `find_declared_unmatched.py` found no unmatched definitions;
  `eh_verify.py` reported one exact EH row.
- Staged code identity reported zero new shadow findings; staged TU ownership
  passed; `data_check.py --converged` found zero second names or unjudged rows;
  CSV and case-collision checks passed.
- Active path consumers were searched across tools, hooks, workflows, source,
  docs, config and reverse controls. No active consumer refers to the absorbed
  pool-key source path. Remaining matches are path-keyed ledgers or historical
  records.
- The merge removes one source file net and preserves the two verified rows.
  No identity or data debt is claimed retired. The pre-push link batch audit
  still must report selected providers, lost bytes and input freshness for the
  complete outgoing range; no link gain is claimed here.
