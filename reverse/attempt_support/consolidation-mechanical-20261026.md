# Mechanical consolidation handoff, 2026-10-26

Shard 3/5. No source or ledger changes remain; no merge passed the complete
composition checks. `python3 tools/progress.py origin/master` reports all
coverage deltas at zero.

## Trials

- `SupplyWarehouseDockUpdate.cpp` passed its allocation check and current
  scoped planner. Its normal merge dry run admitted no donors: the seed itself
  fails with `reference\\shims\\bfmealloc\\stl\\_alloc.h(446) : error C2950:
  '_STL::allocator<char>' : cannot explicitly instantiate an explicit
  specialization` and `SupplyWarehouseDockUpdate.cpp(293) : error C2227: left
  of '->getSupplyTruckAIInterface' must point`. Another rejected donor reports
  C2039, `rva004A7E43` is not a member of `Rva004A7D55`. Pool-key donor is
  refused because it is keyed in a protected path register. No claim was
  acquired and no source was changed.
- `Display.cpp` passed allocation, planner currency and routing. Its dry run
  accepted no donor. The unchanged composed class view rejects donors with
  missing members, including C2039 `'setDisplayMode' : is not a member of
  'Display'`, C3861 `getHeight: identifier not found`, C2039
  `'setDebugDisplayCallback' : is not a member of 'Display'`, and C2065
  `m_debugDisplayCallback: undeclared identifier`. Four other files are keyed
  in protected path registers. No claim was acquired and no source was changed.
- `HeaderTemplate.cpp` dry run admitted the seed plus four donors, but after
  `tu_skeleton.py --merge` staged them, the destination contained exactly the
  seven bytes `compile`. `./build.sh Code/GameEngine/Source/GameClient/GUI/HeaderTemplate.cpp`
  then failed with C1004, `unexpected end of file found`, at line 2; data checks
  could not compile the source. The trial was restored and all acquired file
  and RVA claims were released. This matches the generated-source write failure
  already recorded for W3DSmudge in
  `consolidation-device-20261025.md`; do not retry without resolving that tool
  failure.
- `dx8polygonrenderer.cpp` now dry-runs with both constructor donors accepted
  (9 rows, no rejected donors). The required scoped provider preview,
  `python3 tools/link_check.py --refresh --current-ledger
  Code/Libraries/Source/WWVegas/WW3D2/dx8polygonrenderer.cpp`, exits 1 because
  48 current-ledger object receipts are missing. The existing DX8 handoff also
  records stale-index duplicate-provider predictions. Do not apply or publish
  until current provider selection and consumer bindings can be verified.

The fresh planner snapshots for GameLogic/Object/Update, GameClient and
WW3D2 passed `name_lane.py consolidate --check build/consolidation` before
those trials. `find_declared_unmatched.py` passed the staged HeaderTemplate
composition before its build failure; the staged CSV check passed. No
provider, COMDAT or link-clean improvement is claimed.

## Queue and handoff

`/opt/runner/consolidation_queue.py --limit 100000` lists 34 unheld allocated
TUs in this shard. The allocator has more candidates, but composition review
is blocked by the missing current-ledger receipts; the merge-tool write failure
also prevents publishing the one accepted HeaderTemplate composition. This
seat did not change identity/data registers or repair tools.
