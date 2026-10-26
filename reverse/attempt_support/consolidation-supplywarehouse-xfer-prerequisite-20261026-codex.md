# SupplyWarehouseDockUpdate canonical Xfer prerequisite

Seat: codex, family A shard 0/2, 2026-10-26. The allocated queue approves
`Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp`.
The repair changes only its `SupplyWarehouseDockUpdateXfer.cpp` donor and retires
one Xfer header-queue row through `header_adopt_lane.py accept --class Xfer`.

## Evidence and acceptance

The donor's private 32-slot interface is replaced with the registered
`BfmeXfer.h` and local forward declarations for its operand types. The integer
transfer uses the canonical `operator==`. The actual MSVC 7.1 object still calls
vtable offset **0x7C**, preserving the 42-byte body at **0x004A7D7B**, including
both external calls, the receiver and field offset +0x88. No name, layout,
compiler flag, shared header, source path or ledger row changes.

- `./build.sh` on seed and donor: **4/4** exact; strings, floats and imports pass.
- `find_declared_unmatched.py` on both: pass; the seed's six existing unclaimed
  definitions are unchanged. Class gate and converged data gate pass (10
  addresses, no second names or unjudged rows). No EH rows or missing objects.
- `link_check.py --prepare-current --paths-from
  build/codex-supplywarehouse-sources.txt`: one strict current safe object;
  `--new-variants` passes. No census/index/status update.
- Supported allowed_symbols and census object readers compare a preserved
  before object with the strict current object: **one external code definition,
  two non-debug sections** on each side, identical section bytes, relocations,
  flags, COMDAT selection policies, external data, undefined references and
  aliases. Therefore no emitted provider candidate or consumer binding changes.
  This comparison does not validate unrelated existing binding debt.
- Paired `allowed_symbols.scan`: **two** reference findings before and after,
  none added or removed. Paired `data_check.object_facts`: identical. No data or
  code-identity debt key is retired or transferred. `check_csv.py` passes.

Scratch receipts: `build/codex-supplywarehouse-*` source/object snapshots,
object-proof.json, reference-delta.json, data-delta.json, final-build.txt and
composition reports. No hand compilation, maintainer runner or link cycle.

## Routing and remaining composition prerequisites

The scoped planner is `build/consolidation/supplywarehouse`. Its packet has
only same-spelling ZH and stale-map hints for the transfer donor, with the
SupplyWarehouse TU as the sole alternative. These are donor facts, not original
BFME 2 path proof. The ordinary TU tool rebuilds routing in memory: 13 approved
rows, three mixed donors, no routing refusals. No move is applied or map committed.

The composition trial still accepts no complete merge. Its seed fails with
`_STL::allocator<char>` explicit-specialization C2950 and an incomplete
`getSupplyTruckAIInterface` receiver after directive lifting; the slot donor
also lacks pool member `rva004A7DA5`. Canonical adoption alone does not reconcile
the seed's legacy includes or supply-truck declarations. No downstream TU or
row acceptance and no later Luna landing is claimed. The mixed name-getter,
destructor and parse-chain sources remain untouched.

Read-only allocated trials also confirmed unchanged blockers in
`BridgeTowerBehavior.cpp` (pool member rva00045876C, legacy Xfer, Object and
GameLogic views) and `InstantDeathBehavior.cpp` (pool member rva00045CF10,
constructor/destructor bytes, GameLogic/AsciiString redefinitions and the
DestroyDieModuleData base). Their `accepted: []` reports are
`build/codex-{bridge,instantdeath}-before-trial.txt`. No source edit or claim.

## Complete pending-batch audit

The audit covers the three inherited commits from 26a7b4f8f6 through 893c550a7d
plus this prerequisite. An upstream-only data-baseline retirement fetched
during the session is not part of our changes. There are **no source moves,
renames or deletions**; the inherited AITNGuardObjectView.h addition has exactly
its two verified direct consumers. Combined path searches across active tools,
hooks, workflows, source includes, build inputs and registries require no
repointing. Historical EA paths and the current debt owners remain intact.
The existing canonical header is unchanged. Review the pre-push batch audit
when publication runs; a deferred publisher is not a confirmed landing.

File reduction **0**; header debt retired **1**; identity/data debt retired **0**;
recovered C++ bytes **0**. No census linking or ownership gain claimed. Retain
seed/donor, header queue, obstacle register and this handoff's scope claims
until publication is confirmed; release them afterward. Inherited claims are
listed in the AITNGuard handoff and also remain held while its batch is pending.
