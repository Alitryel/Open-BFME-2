# UpgradeModule composition prerequisite, 2026-10-25

Allocated family A shard 1/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeModule.cpp`.
The scoped Upgrade planner was reviewed (original paths, alternatives, mixed
routing, flag differences); currency check passed before editing. The TU tool
rebuilt current routing in memory. No map, source owner or ledger row is moved.

Before: ordinary `tu_skeleton.py --merge TU --dry-run` accepted no donors:
composition hoisted BfmeXfer.h before Snapshot and its other operand declarations,
so even the seed failed compilation. UpgradeXferPrefix.h keeps the existing
operand forward declarations and include together. Both existing consumers use
this private wrapper; the shared BfmeXfer header, class layouts, bodies and flags
are unchanged. No new private class definition or hatch is introduced.

After: the same ordinary dry run accepts the seed, UpgradeMuxXfer.cpp and
Rva004CE3B9UpgradeName.cpp together: five rows, 366 retail bytes. This is a
demonstrated composition unblock for Luna, not a confirmed downstream landing.
UpgradeMuxCtor.cpp remains rejected: the chosen UpgradeMux view has no declared
constructor; its explicit vtable/member view needs separate ABI reconciliation.
Three mixed files remain outside this subset. No merge was applied.

Checks and receipts (ignored build/):
- ./build.sh seed and UpgradeMuxXfer: 4/4 exact, 302 retail bytes retained;
  string, float and import checks pass. codex4-upgrade-{baseline,after}-build.txt.
- find_declared_unmatched.py passes both consumers. No keyed identity, data or
  header/MS-header queue entry belongs to either edited source.
- allowed_symbols.py --source both: 13 owner references, zero wrong bindings;
  complete refs.tsv before/after identical (codex4-upgrade-refs-before.tsv).
- Fresh HEAD baseline and final builds through ./build.sh compare all emitted
  external code definition digests, COMDAT exclusivity and undefined provider
  names using allowed_symbols._object_defs: identical. Receipts:
  codex4-upgrade-object-defs-{before,after}.json and compare-{before,final}-build.txt.
  No selected provider or consumer binding can change from this textual wrapper.
- data_check.py --converged: two sources, ten addresses, zero second names and
  zero unjudged rows after the final build. EH: zero rows requiring EH and zero
  missing objects. link_check.py --new-variants both exits 0.

Publication compatibility audit: origin/master..HEAD plus the staged change has
no source moves or absorptions. Active tools, hooks, workflows, includes, build
inputs and registries need no path repointing; the two wrapper consumers compile
and compose together. Protected registers are unchanged; historical EA paths
remain intact. File reduction, identity debt retired and recovered C++ bytes are
separately zero. Current census figures are not a link improvement claim.

Keep claims until publication confirms: destination, UpgradeMuxXfer.cpp,
UpgradeMuxCtor.cpp, Rva004CE3B9UpgradeName.cpp, UpgradeXferPrefix.h and
0x004CE2A3/0x004CE2B0/0x004CE342/0x004CE397/0x004CE3B9/0x004CE3F9.

Other allocated investigation: RadarUpgrade ordinary trial accepted its
constructor and Rva004B47DB donor (two rows), rejected the implementation donor
with Object declaration errors. Its three incompatible class views and
constructor vtable definitions require coherent reconciliation; no edit made or
claim retained for that trial. Earlier AIGuardRetaliate, ClickReaction,
BridgeScaffold and ShipSlowDeath repairs remain documented by the prior session.
