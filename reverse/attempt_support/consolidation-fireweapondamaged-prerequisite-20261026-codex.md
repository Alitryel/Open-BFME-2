# FireWeaponWhenDamaged ctor/dtor prerequisite, 2026-10-26

Seat codex, family A shard 0/2; fresh allocation check passed. Read earlier
consolidation-fireweaponwhen-20261026-codex3.md and Sol prerequisite handoffs.
The ordinary current-verifier baseline still accepts no composition. Its dtor
candidate fails C2504 DamageModuleInterface undefined after private-declaration
reconciliation. Other donors have independent missing methods/allocator errors.

FireWeaponWhenDamagedView.h shares the ctor and dtor's existing measured receiver
views. It preserves UpdateModule 0x20, UpgradeMux +0x20, DamageModuleInterface
+0x28 and eight Weapon pointers +0x2C..+0x48. It uses the seed's BodyDamageType
spelling and pure interface. Weapon combines the dtor's slot-zero deleteInstance
with the ctor's reloadAmmo/status access: implicit vptr plus four padding bytes
keeps status at +0x08. Neither source constructs Weapon or depends on its complete
size. This is a scoped union of existing target declarations, not recovered
BFME 2 source or a full canonical class. No compiler flags, hatches or aliases
are added. Sources include the view in place of their private copies.

Ordinary after --merge --dry-run accepts seed/dtor, four existing rows / 838
retail bytes (including EH), versus no accepted group before. No merge is applied;
leave compatible donors to Luna. Remaining rejects: pool getModuleNameKey missing;
UpdateModule::xfer and target xfer declarations missing; update member missing;
Libraries StlSweepR3 allocator specialization C2950. Mixed ModuleNameGetters and
Disp8ByteChaseGetters remain. The Libraries provider is a cross-family dependency,
not permission to edit that donor. No confirmed Luna landing is claimed.

Acceptance evidence:

- ./build.sh both consumers before/after: 4/4, no literal/import divergence.
  Frozen-file check: every body matched; class gate accepts the local view.
  Two EH graphs EXACT, including the independently verified renamed funclet.
- Staged identity: four rows, zero new findings. Data: two sources, zero findings
  outside baseline (zero total). Converged: ten addresses, zero second names or
  unjudged rows. Header/MS queues and protected registers remain untouched.
- Upstream COFF readers show every standalone non-debug section unchanged:
  5+2 external code definitions, 15+11 sections, identical bytes/relocations,
  COMDAT policies, aliases, undefined references and external data. All 34 code
  reference facts and all data definition/reference facts remain identical.
  allowed_symbols: 34 refs (31 owner, two EH, one alias), zero wrong bindings.
- Accepted scratch composition build/tu_skeleton/7c30eacf47b031a5.obj preserves
  the union's six external code and six external data definitions, selected
  COMDAT policies, vtable payloads/relocations, aliases and external references.
  All data facts agree exactly; no new provider or consumer binding exists.
  No compiler-local guard normalization is needed for this target.
- Scoped planner/check reviewed same-name Zero Hour/stale-map hints with no
  alternative destinations; EH placements remain unresolved in that catalogue.
  Only current tool routing authorizes composition, not those source hints.

Receipts: build/codex-fireweapondamaged-{before-build,after-build,before-trial,
after-trial,allowed,prepare,variants}.txt; *-object-proof.json,
*-reference-delta.json, *-data-delta.json, *-composition-proof.json, *-eh.json;
planner build/consolidation/codex-fireweapondamaged. All builds use build.sh or
the supported scratch verifier, never a manual match-cache compile.

Complete outgoing batch plus staged audit: no source move/deletion/rename.
Three added declaration headers have the intended consumers: GameMemory 2,
FireSpread 1, FireWeaponWhenDamaged 2. Combined searches through active tools,
hooks, workflows, includes, build inputs, doxygen and registries find no path
consumer requiring repointing. Historical EA paths, debt owners and current TU
map remain. Raw two-tip and actual outgoing diffs retained separately in
build/codex-final-path-audit-*.txt.

Actual file effect: one added header, zero source files removed. Identity debt
retired 0, recovered C++ bytes 0, census/ownership gain none. Keep the seed, dtor,
new header and handoff file claims while this commit is pending publication;
release them after landing. Unchanged UpdateModule/HealContain source scopes
were released; those investigations are documented separately.
