# WeaponBonusUpgrade receiver prerequisite

Seat codex, family A shard 0/2, 2026-10-26. The allocated destination is
`Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponBonusUpgrade.cpp`.
This prerequisite shares a partial receiver between the pool-key and constructor
files; it leaves the tool-owned merge to Luna.

## Target facts, structure and provenance

The current routing plan approves four primary bodies: the 69-byte pool key at
0x004B55EE, the 49-byte constructor at 0x004B5633, a 28-byte deleting destructor
in FireWeaponWhenDeadBehaviorDerived.cpp and the 11-byte implementation in
WeaponBonusUpgradeUpgradeImplementation.cpp. The latter two donors are mixed
(42 and one foreign primary rows respectively) and remain untouched.

The pool key proves the receiver's existing virtual method signature and literal
WeaponBonusUpgrade. The constructor calls UpgradeModule and stores pointers at
+0, +0x0C, +0x10 and +0x18. Those explicit stores and their existing TU-local
placeholder targets remain; this is not vtable/data identity recovery. The
shared partial base uses opaque bytes for +4 through +0x0B rather than retaining
the old unproved owner-field meaning. The polymorphic base is a structural
inference consistent with the existing ObjectModuleBase/UpgradeModule view in
the implementation donor, not a recovered complete inheritance or vtable order.
`novtable` prevents compiler-generated replacement vtable stores; no vtable is
emitted. The explicit primary pointer write replaces the old stand-in member
without changing bytes or relocations. No virtual slot number is inferred.

The scoped planner is build/consolidation/weaponbonus-final; freshness check
passes. Its same-spelling ZH and stale-map evidence are donor/routing leads,
not BFME 2 original-path proof. The ordinary TU tool rebuilds routing in memory;
no map, source path or ledger row moves. class_views reports other private views;
there is no registered WeaponBonusUpgrade/UpgradeModule canonical header.

## Acceptance and demonstrated unblock

- `./build.sh` on both donors: **3/3 exact**, including the pool-key EH row;
  literal, float and import checks pass. `find_declared_unmatched.py` passes.
- Class gate passes; converged data check covers ten addresses with no second
  names or unjudged rows. EH verifier: **one EXACT**, none missing/baselined.
- `link_check.py --prepare-current --paths-from
  build/codex-weaponbonus-sources.txt`: two safe strict current objects;
  scoped `--new-variants` passes. No census/index/status update.
- Supported allowed_symbols/census object readers compare preserved before
  objects with current objects. Each donor retains its one external code
  definition. All **8 pool-key and 3 constructor non-debug sections** have
  identical bytes, relocations, flags and COMDAT selection policies; external
  data, undefined references and aliases are identical. No provider candidate
  or consumer binding changes. Paired reference scans retain **5 findings**,
  no additions/removals; data object facts are identical.
- Ordinary `tu_skeleton.py --merge TU --dry-run` before: only the pool-key donor
  accepted; constructor rejected C2511 because the selected receiver omitted its
  constructor. After: **both direct donors accepted, no rejected donors,
  3 existing rows**. This demonstrates compatibility, not a later Luna landing.
- `check_csv.py`: 98,271 functions, 15,683 symbols, 2,215 data rows; pass.

Scratch: build/codex-weaponbonus-{before-files,before-objects,build.txt,
object-proof.json,reference-delta.json,data-delta.json,current-receipts.txt,
before-trial.txt,after-trial.txt}, source list and final planner packet.
No hand compilation, link cycle, smoke or nightly runner was used.

## Remaining prerequisites and complete batch audit

The mixed deleting-destructor and implementation sources need the supported
split lane and receiver reconciliation; neither is accepted by this repair.
The ordinary trial prints one data-check key and six data-ledger entries to
transfer if a later merge is applied. Keep all existing data/code identity debt;
this commit retires none. Full vtable identity remains unresolved.

The pending batch from 26a7b4f8f6 through 187a3f7e30 plus this prerequisite has
no source moves, renames or deletions. There are two added scoped headers,
each with exactly two direct consumers verified together. Combined path and
basename searches cover tools, hooks, workflows, includes, tracked build/config
inputs and registries; no active consumer needs repointing. Historical paths
remain intact. Upstream-only baseline changes fetched during the session are
excluded from our outgoing diff. Pre-push batch audit must still be read when
publication runs; deferred publication is not a landing.

File reduction **0**, recovered C++ bytes **0**, identity/data/header debt retired
by this prerequisite **0**. Its improvement is one additional direct donor
accepted by the ordinary composition trial. Retain five scope claims (TU,
constructor, pool-key, view header and this handoff) plus the previously retained
batch scopes until confirmed publication; then release file scopes and settle
RVA claims with claims.py release --landed.
