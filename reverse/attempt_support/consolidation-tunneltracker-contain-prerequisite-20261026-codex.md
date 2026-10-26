# TunnelTracker contain-list receiver prerequisite

Seat codex, family A shard 0/2, allocated queue destination
`Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp`, 2026-10-26.
This repairs the concrete Luna compiler refusals recorded by codex3 in
consolidation-tunneltracker-blockers-20261026-codex3.md. It leaves the compatible
merge to Luna. No new recovered C++ or file reduction is claimed.

## Repair, evidence and scope

The current TU plan routes 21 rows without mixed/refused donors. Its normal
baseline composition accepts nothing: contain-list compilation hits allocator
C2950 and missing getContainMax, with similar allocator diagnostics masking
other donors' receiver failures. The seed's existing NemesisView lacks the
contain donor's methods and measured Object fields.

The seed now retains _STLP_USE_STATIC_LIB, already used by the donor and needed
when its bfmealloc/STL includes are composed. This changes no emitted section,
including the seed's linker directives. The shared view incorporates the
existing contain methods and Object body/frame accesses, leaving all previous
field offsets intact. The append uses the existing four-byte list<int> carrier
through the +0x10 sentinel storage; the callback uses the same getBodyModule
provider at Object+0x254 and contained frame at +0x27C. The donor's old competing
class definitions are removed. No complete Object or TunnelTracker layout,
vtable order, external donor path or additional name recovery is asserted.

The planner at build/consolidation/tunneltracker-final is fresh. Its alternatives
are the same TU; stale-map, ZH same-spelling and WorldBuilder pairs are hints,
not original BFME 2 path proof. Current routing is rebuilt by the ordinary tool;
the committed map and every ledger source remain untouched. Other receiver,
constructor, destructor, Xfer and list donors are outside the edit set.

## Acceptance and composition proof

- `./build.sh` on seed and contain donor: **9/9 exact**, one float literal,
  strings/imports pass. Both frozen checks and the class gate pass.
- Converged data: ten addresses, no second names or unjudged rows. EH verifier:
  no EH-bearing rows and no missing objects. Scoped allowed_symbols:
  **11 references, all owner**, no wrong bindings.
- Preserved before/current object comparison through the supported COFF readers:
  seed **9 external code definitions / 10 non-debug sections**, donor **5 / 7**;
  every section byte, relocation, flag, COMDAT policy, external data, undefined
  name and alias is unchanged. Paired reference scans retain eleven findings
  without additions/removals; data facts agree. Existing debt remains owned.
- `link_check.py --prepare-current --paths-from
  build/codex-tunneltracker-sources.txt`: two safe strict current objects;
  scoped `--new-variants` passes. No census/index/status publication.
- Ordinary `tu_skeleton.py --merge TU --dry-run` now accepts **seed plus contain
  donor: nine existing rows / 611 bytes**, versus no accepted group before.
  This demonstrates an unblock, not a later Luna landing.
- Its composed object build/tu_skeleton/e516033e912bb545.obj has exactly the
  donor union's **13 external code definitions**, fingerprints, sizes, COMDAT
  selection policies, unresolved symbols after internal resolution and data
  reference facts. No new/missing/changed provider and no changed binding.
  Receipt: build/codex-tunneltracker-composition-proof.json. This used the
  ordinary trial object; no hand compilation or maintainer runner.

Scratch build/codex-tunneltracker-* retains before files/objects, source list,
before/after builds and trials, object/data/reference comparisons, current
receipts, binding report, planner packet and path audit. An early planner
snapshot became stale while temporary composition files existed; it was
regenerated before editing, and again after the final completed trial.

## Remaining prerequisites

The final ordinary trial no longer reports allocator C2950, but rejects the
constructor/destructor/deleter receivers, isValidContainerFor and its Object
fields, removeFromContain and list member views, int versus ObjectID append,
replace-owner callbacks, and Xfer/loadPostProcess member declarations. These
are real remaining structural prerequisites; no unchanged failure is retried.
The Xfer source's existing divergent push_back identity key stays intact.

GarrisonContain's queued Coord3D destructor adoption requires retaining a
nontrivial array teardown absent from the current canonical trivial type;
MultiplayerSettings' queued SubsystemInterface constructor has an empty-base
stand-in versus the canonical polymorphic base. Neither is treated as a simple
include substitution. RankInfo's string/vector lifetime, GiantBird's complete
command/base receiver and CrateCollide's constructor/data/interface differences
were reviewed without speculative edits or claims. Earlier BridgeTower and
InstantDeath trials and the restored AITNGuard frozen-file refusal are recorded
in their existing handoffs. No unclaimed fallback lane was taken.

## Publication and complete batch audit

The prior six-commit batch **89d07ee333..0b692726c4** is confirmed pushed.
Its pre-push hook verified **40/40 rows**, one data row and seven EXACT EH
rows. The link-batch audit is **inconclusive**, because the provider index is
at 763dc8759f versus outgoing base dd4a917878 and Eva.cpp lacks a current
link-audit receipt. This is a carry-forward to the next normal census, not
link clearance or a measured gain. No link/nightly/smoke runner was started.
The publisher's post-push pull reported multiple branches; a subsequent normal
`git pull --rebase origin master` succeeded (already up to date), and check_csv
passed 98,271 functions / 15,683 symbols / 2,215 data rows. Sixteen landed file
scopes were released; docs/linking_obstacles.md remained held for this handoff.

The new pending batch consists only of this prerequisite on top of 0b692726c4.
No source moves, renames, deletions, new header or protected-register changes.
Combined header path/basename searches across tools, hooks, workflows, source
includes, tracked build/configuration inputs and registries show exactly its
two direct consumers, verified together; no repointing required. Historical
paths remain intact. All surviving data/code/header debt stays with its owner.
Pre-push audit findings remain provisional until the next accepted census.

This prerequisite: recovered bytes **0**, file reduction **0**, debt retired
**0**, demonstrated accepted composition **9 existing rows / 611 bytes**.
Keep claims for seed, contain donor, shared view, this handoff and the obstacle
register until publication is confirmed; release them after landing. There is
no unfinished source trial or moved row awaiting recovery.

## Final hook identity warning and publication handoff

The prerequisite's full header gate passed 36/36 rows, including the shared
header consumers. Its shadow identity report flagged divergent
`?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ`. The preserved contain
object and current object both already define the same seven-byte +0x254
getter (digest `489e997541f4`); moving its declaration into the shared view
added no provider or changed body. Receipt:
build/codex-tunneltracker-body-provider-proof.json. The earlier
consolidation-tunnel-xfer-view-20261026-codex4.md handoff records this existing
cross-owner +0x254 versus +0x194 discrepancy and its provider inventory.
Resolving those other private receivers requires their owners' claims and
evidence. This prerequisite preserves its correct existing copy and retires
no identity key.

The final rebase picked up the normal 08:28 census at 47e030bafc and unrelated
mechanical consolidation/debt work; it touched no source in this repair.
check_csv.py still passes 98,271 functions, 15,683 symbols and 2,215 data rows.
The outgoing source prerequisite is now 2d2d0cb165. Its complete pending path
audit still contains no moved or deleted source, protected-register change,
or new consumer; the before/after and composition receipts remain applicable.
The new census is repository-wide evidence, not an attributable gain for this
prerequisite. Retain the five listed file scopes if final publication defers.

## Recovery verification, next session

Recovered clean pending commits 3d51de24e0 and 22f0ed403a before selecting any
new work. Fresh pull/check_csv pass; both source files pass the frozen check
and build 9/9 exact. Repeated the retained composition proof: thirteen external
providers and their COMDAT policies, internally resolved undefined references
and data facts still agree exactly. Repeated paired consumer scan: eleven
facts, no additions or removals. Complete origin/master..HEAD path audit has
no moves; active header searches still find only the two verified consumers.
This recovery adds no source change or attributable progress. Five scope
claims remain held until publication is confirmed.
