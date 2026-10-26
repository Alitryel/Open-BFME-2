# Sol prerequisite handoff, 2026-10-26, codex session 3

Family A, shard 0/2. Own work starts at dfc0c39c28. The inherited session-2 batch was already upstream; its thirty file claims were released only after confirming that landing. Inherited recovery is excluded from the results below. AGENTS.md, consolidation checks and the complete path-consumer audit were read. No helpers, independent naming decisions, merges/splits, manual compiler-cache writes or maintainer-only runs were used.

## Verified work

| Target | Commit before any publication rebase | Concrete result |
| --- | --- | --- |
| SquishCollide | 84d78f24f6 | Shared existing collision/pool-key receiver; ordinary trial accepts both donors, five rows / 1,244 existing bytes. Newly accepted: two rows / 79 bytes. |
| SubObjectsUpgrade | 4e67734403 | Constructor adopts canonical GameLogic; header acceptance retires one queue row. Ordinary trial accepts the additional rate donor: one row / 151 bytes, ten rows total. |
| BeaconClientUpdate | 9584682028 | Shared existing update/pool-key receiver; ordinary trial accepts both donors, twelve rows / 937 existing bytes. Newly accepted: two rows / 79 bytes. |
| ExperienceTracker | 7bd3591deb | Fresh acceptance of the already-included canonical GameLogic header retires one stale queue row; unchanged destination verifies 25/25. No donor unblock is claimed. |

Detailed before/after evidence and remaining prerequisites are in the four adjacent consolidation-{squish-receiver,subobjects-gamelogic,beacon-pool-receiver,experience-header}-20261026-codex.md handoffs. Scratch evidence is build/codex-{squish,subobjects,beacon,experience}-*.

Three additional donors / five existing rows / 309 retail bytes now pass ordinary composition trials. These are demonstrated compatibility improvements; later Luna landings remain unconfirmed. Header debt retired: two rows, both through header_adopt_lane.py accept. Identity/data debt retired: zero. File reduction: zero; no C++ file was deleted and two scoped headers were added. Recovered/authored C++ bytes: zero. Existing pool guard/key data findings and the Squish Coord3D identity finding remain registered. SubObjectsUpgrade's texture-binding/unused-alias identity work remains outstanding.

## Acceptance and binding evidence

All four scopes pass their byte builds and declaration scans. Squish, SubObjects and Beacon each pass EH, class, converged-data and new-variant checks. Current explicit strict receipts were prepared for all five edited C++ providers. Squish/Beacon before/after object/reference/data comparisons retain the existing definitions and bindings. SubObjects adds only the canonical four-byte getFrame COMDAT, matching all 394 index copies and a current unchanged provider. Final ordinary composition objects preserve the explicitly compared standalone/old-composition code/data definitions, selected COMDAT policies, payloads, relocations, aliases, unresolved symbols and per-row data ownership/reference facts. The detailed handoffs identify the one proved Squish guard renumbering and the pre-existing SubObjects generated destructor; neither is silently ignored.

The scoped-header commit hooks also verify their reached Eva consumer. check_csv and all pre-commit gates pass. ExperienceTracker's retirement changes no C++ or object/provider input. Its ordinary trial remains blocked on private-view declarations, so no composition result is claimed for it.

## Complete pending-batch path audit

Audited origin/master..HEAD plus staged paths and this seat's own dfc0c39c28..HEAD log. The origin comparison also includes inverse differences for independently incoming commits; those are outside this batch. There are no source moves, renames or removals. The two new scoped headers each have exactly two direct consumers, rebuilt together. Combined active tools, hooks, workflows, Code includes, build/configuration inputs and reverse registry searches find no required repointing. Canonical GameLogic headers and historical EA paths remain unchanged. The only own protected-register edit is the supported two-row header-queue shrink. No TU map, fold proof, pin, baseline, identity/data register or source list is changed. Relevant audit captures: build/codex-session3-{outgoing-paths,active-consumers-final}.txt and each prerequisite's path audit.

The normal pre-push hook will run the outgoing source batch audit once if the publisher obtains a slot. Read its selected-provider, lost-byte and input-freshness findings; leave inconclusive index comparisons for the next published census. Direct before/after scoped composition proofs above establish these prerequisite changes without claiming whole-link closure.

## Remaining work and intentionally skipped trials

- Squish: opaque constructor/hierarchy remains incompatible; mixed foreign rows stay for the split lane.
- SubObjects: pool-key/constructor/xfer declarations and the separately registered identity findings still block a complete merge.
- Beacon: opaque constructor, xfer/base and module-data views still disagree; mixed constants/parser rows stay behind.
- ExperienceTracker: ExperienceLevelHandle ordering and other mismatched receiver members prevent any two-donor merge. The unchanged-source link predictor also reports duplicate destructor/anchor providers and a selected nonretail destructor against the old 00:54 index at 763dc8759f. This is a preview limitation and an identity prerequisite, not a measured lost-byte regression from header-queue cleanup.
- Read-only alternatives: FireWeaponWhenDamaged/FireWeaponWhenDead require receiver and constructor/vtable ABI reconciliation; DefaultProductionExitUpdate requires broad include/compiler-context and private-view reconciliation while retaining its frozen-file markers; CrateCollide has an opaque constructor/contiguous-table identity prerequisite. No unsupported declarations, virtual slots or identities were guessed. Previously handed-off unchanged blockers were not rebuilt again.
- MessageStream/MessageStreamSubsystem at 0x00A00950 remains untouched pending maintainer issue #116.

docs/linking_obstacles.md is currently claimed by yasinschroeder-codex4; this seat's claim was refused and the shared file was not edited. Handoff to that owner: retain LINK-017's stale-index history and add this batch's strict provider receipts/scoped composition evidence plus ExperienceTracker's duplicate/selected-destructor preview. The register is still open; no census closure or new regression is claimed. Record the eventual normal pre-push report alongside that update.

## Publication, claims and measurement

Every commit called /opt/runner/publish in the same shell command. The first four were held for batching; the final handoff commit retries publication. If still held, the runner publishes the final batch. Keep these fifteen file claims until actual publication is confirmed, then release them and run claims.py release --landed:

```
Code/GameEngine/Source/Common/Rva004B4DBFRates.cpp
Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdate.cpp
Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateView.h
Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp
Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollideOnCollide.cpp
Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollideView.h
Code/GameEngine/Source/GameLogic/Object/Die/SquishCollidePoolKey.cpp
Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
Code/GameEngine/Source/GameLogic/Object/Update/BeaconClientUpdatePoolKey.cpp
Code/GameEngine/Source/GameLogic/Object/Upgrade/SubObjectsUpgradeCtor.cpp
reverse/attempt_support/consolidation-beacon-pool-receiver-20261026-codex.md
reverse/attempt_support/consolidation-experience-header-20261026-codex.md
reverse/attempt_support/consolidation-sol-prerequisites-20261026-codex-session3.md
reverse/attempt_support/consolidation-squish-receiver-20261026-codex.md
reverse/attempt_support/consolidation-subobjects-gamelogic-20261026-codex.md
```

progress.py origin/master reports BYTE-MATCHED 7,978,500 / 100%, LINKING 7,370,962 / 98.11%, LINKED 7,614,012 / 98.75%, all deltas zero (published 2026-10-26 08:28 census at 47e030bafc). These are the census headline figures; none of the scoped trials changes them. No image-ownership receipt or NOT OURS reduction is claimed.
