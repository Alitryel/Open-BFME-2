# LifetimeUpdate frame header prerequisite, 2026-10-26, codex4

Allocated family A shard 1/2 target:
`Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp`.
The Update naming planner and currency check passed before editing
(`build/codex4-update-planner-stable.txt`). Its packet identifies the historical
LifetimeUpdate.cpp path, line-sensitive calcSleepDelay donor, conflicting
private GameLogic/LifetimeUpdate declarations, flag disagreements and mixed
constructor/pool-key/field-parser routing. These warnings are not merge approval.
The normal current-map `--plan` approves 11 rows, six donors and two mixed files.

The concrete queued prerequisite was GameLogic header adoption for
LifetimeUpdateCalcSleepDelay.cpp, RVA 0x003A49F0. Its private view read frame
at +0x40, as the canonical GameLogicObjectLookupView.h already does. Including
that header replaces the private definition. Padding preserves the random
call's retail __LINE__ value 118 and historical EA filename literal.
No shared header, receiver layout, body statement or compiler flag changes.

Acceptance and binding evidence (`build/codex4-lifetime-*` and
`build/codex4-prereqs-*`):

- Before/after `./build.sh LifetimeUpdateCalcSleepDelay.cpp` matches 1/1 row,
  55 bytes, and its filename literal. The combined after build verifies 5/5
  rows across this donor and both DemoTrap prerequisite sources. Frozen-file
  checks pass.
- `header_adopt_lane.py accept --class GameLogic <donor>` passes and retires
  exactly one row from reverse/header_queue.tsv. No manual queue edit.
- Object snapshots retain the exact calcSleepDelay definition fingerprint,
  size and exclusivity, the two undefined references and all data facts.
  The sole added definition is inline GameLogic::getFrame() const. Upstream
  allowed_symbols object/definition helpers in strict mode find it is an ANY
  COMDAT (selection 2), bytes 8b4140c3, no relocations, fingerprint 84449fef877c.
  All 300 pre-existing copies have identical fingerprint/size/exclusivity.
  The selected FiringTrackerXfer object remains selected before and after;
  there are zero undefined referrers to this inline symbol. Thus no changed
  consumer binding needs a new provider. This is scoped object evidence,
  not a new census or a full-game link claim.
- Scoped allowed_symbols across the three prerequisite sources reports
  18 references (16 owner, one EH, one alias), zero wrong code bindings.
  Converged data checks three sources/ten addresses: zero second names or
  unjudged rows. Ordinary data check retains DemoTrap's unrelated vtable
  finding; this Lifetime donor has none. Neither this donor's code nor data
  identity register has a key. Identity/data debt retirement: zero.

This is demonstrated header-queue acceptance for one 55-byte donor. No merge
is performed and no new acceptance of the complete LifetimeUpdate composition
or later Luna landing is claimed. The constructor's canonical header adoption
still needs getHulkMaxLifetimeOverride; mixed donors and private module/base
views remain outside this change.

Publication compatibility audit across origin/master..HEAD and pending source
edits: no sources move, rename or disappear. The existing canonical header is
unchanged. Active tools, hooks, workflows, includes, build inputs and registries
need no path repointing; historical paths remain. The pending LargeGroupAudio
private-header prerequisite and DemoTrap private-header repair each have their
two intended consumers verified together. Evidence: build/codex4-prereqs-path-audit.txt.
Keep this donor/RVA/evidence claim until confirmed publication.

Measurements: one header-queue row retired; zero files removed, zero new C++
bytes, zero identity/data debt retired. No maintainer-only link or smoke runner.
