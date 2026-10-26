# WeaponSetUpgrade initialized-extern provider prerequisite, 2026-10-26

Allocated family A, shard 1/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp`.
Runner allocation check exits zero. The Upgrade-scoped name_lane planner and
currency check passed; original-path evidence and alternatives were reviewed.
The upstream plan approves the 34-byte buildFieldParse row at 0x004B56F6 in
`GameLogic/Object/Update/ModuleDataBuildFieldParseChained.cpp`. No source move,
class rename or TU-map update is made by this prerequisite.

This repairs the concrete duplicate-provider blocker recorded in
`consolidation-weaponset-upgrade-split-20261026-codexb2.md`; that history remains
valid for the old tool. Before the fix, the supported split trial accepted the
row but reported `data_moved: []`. Both its generated TU and the residual
defined `BfmeWeaponSetUpgradeFields` (retail VA 0x00C58020, 32 bytes). The
subsequent data-check refusal was correct: this was an unsafe tool output,
not a false rejection by the data gate.

`tu_skeleton.data_decls` excluded every `extern`, including objects with an
initializer. Such an object is a definition with external linkage. The split
now inventories it as data, moves its sole definition with its only user, or
keeps the definition in the residual and supplies an extern declaration when
both sides use it. An existing extern specifier is retained once. An
uninitialized extern remains a repeatable declaration. No gate is relaxed.

Verification:

- The new tests fail on the original tool for sole-user movement and both
  array/scalar shared external const definitions. They pass after the fix;
  uninitialized declarations remain on both sides.
- `python3 -m pytest -q -rs tools/tests/test_tu_skeleton_split.py
  tools/tests/test_tu_skeleton.py tools/tests/test_gate_exploits.py`: 114 passed,
  two subtests passed, one existing empty-parameter fixture skipped
  (`test_gate_exploits.py:409`). The concrete exploit cases still refuse their
  wrong-code fixtures and accept their controls.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/ModuleDataBuildFieldParseChained.cpp`:
  63/63 functions and 63/63 data rows verify; string, float and import checks
  pass. `find_declared_unmatched.py` passes. Scoped allowed_symbols reports
  162 owner bindings and zero wrong bindings.
- The supported `tu_skeleton.py --split SOURCE --for TU --dry-run` now reports
  `data_moved: ['BfmeWeaponSetUpgradeFields']`, no copied helpers or shared
  externs, 62 residual rows preserved, the one carved row exact under the TU's
  flags, and the donor accepted with no rejection. It does not apply a split.
- Compared the actual compiled trial objects
  `build/tu_skeleton/b5b46f972c80846d.obj` (residual) and
  `build/tu_skeleton/a8fd022b93e11fcc.obj` (destination) with the original
  source's current build object. Their union has the same 65 external code
  definitions (digests, sizes, exclusivity), COMDAT selection map and 50
  unresolved symbols after internal resolution. All 63 function rows retain
  exactly the same DIR32 data-binding sets. All 63 rowed data objects have one
  provider each and identical bytes and symbolic relocations within their
  ledger extents. The WeaponSetUpgrade table has exactly one provider, the
  destination object. No other selected provider or consumer binding changes.
  These checks use existing COFF readers and the supported trial's objects;
  no shared match-cache object is manually compiled.

Local receipts: `build/codex4-weaponset-{split-before,split-after,original-build,
provider-evidence,original-bindings,converged}.txt`, the scoped planner receipt,
and `build/codex4-extern-split-pytest.txt`. The ignored provider-evidence script
records the exact object comparisons for this trial.

Publication audit: reviewed `origin/master..HEAD`, its merge-base comparison,
and the staged fix together. There are no outgoing source path changes,
deletions, absorptions, include changes or registry repoints. Incoming commits
touch unrelated DX sources, funclet ledger entries and data debt; none touches
this source, tool, tests or instructions. Active tool/hook/workflow callers keep
the same API and paths. Historical EA paths remain intact. Protected registers,
header queues, hatches, fold proofs and source/row ownership are unchanged.

Luna can retry the supported split with normal claims and all acceptance
checks. This is a demonstrated provider prerequisite repair for one row / 34
already matched bytes, not a confirmed downstream landing. Constructor and
pool-key composition remain separate work; the pool-key wrong-name debt at
0x00A03E80 remains. No debt key is retired, no file is removed and no new C++
byte is recovered. No census, smoke or nightly runner was started.

Other allocated read-only investigations this session: FloatUpdate still has
distinct reference/module-data and pool-key views; AssistedTargetingUpdate's
ctor explicitly models three vptr slots while its seed uses the reference
hierarchy; TerrainTypes has mixed STLport donors and prior composition work.
Those were not edited or broadly retried. The MessageStream naming decision
remains maintainer-owned. Inherited LargeGroupAudio, Lifetime and DemoTrap
prerequisites are already on origin/master; their claims had expired and none
remained owned by this seat at session start.
