# LifetimeUpdate module-data prerequisite, 2026-10-26, codex4

Allocated family A repair shard 1/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp`.
No inherited changes or unpublished commits at session start; unrelated untracked
reverse/zh_sweep remains preserved. BFME1 freshness receipt is within 72 hours.

## Repair and demonstrated unblock

The current-map normal dry-run accepted no pair. In particular the module-data
constructor failed C2600 against the update's constructor-less private view.
Share the existing constructor/update prefix in LifetimeUpdateModuleDataView.h:
explicit vtable pointer and untouched word at +4; frame endpoints at +8/+C;
existing start-disabled/credit-killer bytes at +10/+11 and death type at +14.
The constructor keeps its explicit vtable store, inline definition and anchor.
The names come from existing accessed views; this asserts neither an original
header nor a new canonical class. No virtual method or layout extent is added.

The after dry-run accepts the seed and module-data constructor, five existing
rows / 274 retail bytes, where the before trial accepted no donors. Leave that
pair for Luna. This demonstrates an unblock, not a confirmed downstream landing.
Remaining: calcSleepDelay's frame fields; pool-key receiver declaration; Xfer's
base declarations; primary constructor/base ABI and its canonical GameLogic
adoption; two mixed donors. No merge, split or ledger move is applied.

## Verification and provider/consumer evidence

- Before/after ./build.sh on both sources: 5/5 rows exact; string, float and
  import checks pass. find_declared_unmatched passes both; the existing anchor
  retains its absent-from-retail marker. class_gate passes.
- Complete standalone code-definition fingerprints, sizes and exclusivity,
  undefined references and per-row data facts compare equal before/after
  (build/codex4-lifetime-moduledata-{before,after}.json). Thus this prerequisite
  changes no standalone provider/consumer binding or selectable code body.
- allowed_symbols: 12 references, all owner, zero wrong code bindings.
  Converged data: two sources, ten protected addresses, zero second names or
  unjudged rows. EH: zero applicable rows, zero missing objects/nonexact rows.
- Ordinary data_check preserves the existing constructor vtable wrong-name
  finding _vtbl_00C4ED70 at 0x0084ED70; snapshot data facts prove it unchanged.
  No data/code-identity/header/hatch register is edited or key retired.
- Inspect the actual composed object build/tu_skeleton/c97681a031647859.obj:
  all five rowed definitions and the other incidental code definitions retain
  fingerprints/sizes and all eight COMDAT selection values. The sole changed
  code definition is the explicitly non-retail anchor, from 9 to 28 bytes.
  Disassembly shows the former loads ECX then tail-jumps to the constructor;
  the latter directly performs exactly its vtable and zero-field stores.
  Current strict allowed_symbols inventory finds no external anchor referrers.
  The composed object's eleven unresolved names equal the donor union after
  internal resolution. Per-row data references remain the same vtable alias
  and TheGameLogic. No changed runtime binding is left unexamined.
- link_check --fetch-index succeeds, retains index 47e030bafc (2026-10-26
  08:28), imports 22,549 objects. Scoped --new-variants exits zero. This is
  prediction/admission evidence, not a new census or ownership measurement.

Receipts: build/codex4-lifetime-moduledata-*; source backups remain under
build/codex4-moduledata-original-*.cpp. The composition evidence explicitly
excepts the inspected anchor; it does not assert identical anchor bytes.

## Planner and publication audit

The scoped Update planner was regenerated after an initial scan encountered a
vanishing temporary dry-run file. Its subsequent --check passes. Reviewed the
Lifetime group: existing destination alternatives and donor hints do not prove
retail placement; the normal tool rebuilt the stale TU map in memory. Mixed
routing, line-sensitive calcSleepDelay, private types, flags and register
prerequisites remain explicit. No regenerated map is staged.

Audited all pending origin/master..HEAD changes plus this prerequisite: no
source moves/deletions/renames; the new header has exactly the two intended
consumers, verified together. Searches across active tools, hooks, workflows,
includes, build inputs/registries and documentation require no repointing.
Historical EA paths remain intact. Header/MS-header queues and protected
identity/data/hatch registers remain unchanged. No maintainer-only run.
Measurements: zero recovered C++ bytes, zero net file reduction (one private
header added), zero debt retired. Hold source/header/evidence file claims until
publication confirms landing, then release them.

## Other allocated investigations

ModelConditionUpgrade's current dry-run accepts five rows but rejects the
primary constructor because its pool-key view lacks the constructor/base.
A claimed local declaration trial passes the pool's 2/2 byte rows and admits all
six eligible rows. However scoped COFF inspection shows composition changes
??_7ModelConditionUpgrade@@6BBehaviorModule@@@ from 4 to 8 bytes, appending
getModuleNameKey at +4 after an existing placeholder anchor. Retail slot
placement is not established; byte equality alone cannot authorize this ABI.
The trial was reverted and re_log records the blocker at 0x004B63E3. All four
claims were released. Evidence: build/codex4-modelcondition-receiver-*;
no trial C++ remains. Needs actual base/vtable contract before retrying.

ExperienceScalarUpgrade and UnpauseSpecialPowerUpgrade current normal trials
likewise reject primary receiver constructors and implementation declarations;
module-data/pool pairs remain compatible. No edits/claims for those probes.
RadiusDecalUpdate still accepts its already repaired seed/constructor; remaining
pool, update and Xfer donors lack matching receiver/method declarations.
No repeated repair or new gain is claimed for those unchanged prerequisites.
