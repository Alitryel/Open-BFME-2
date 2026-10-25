# Squad compact prerequisite — 2026-10-25, codex

Allocated target: `Code/GameEngine/Source/GameLogic/AI/Squad.cpp`, family A shard 0/2. The current plan approves seven rows, with four eligible source files, one mixed donor and no protected sources. The planner's original-path alternatives do not identify the address-derived owner or its pointer element. Current routing is rebuilt in memory; no TU-map regeneration is committed.

## Repair and acceptance

Before, `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/Squad.cpp --dry-run` exits 2 with no accepted donor. The compact donor duplicates the seed's partial `_STL::vector` template and uses a different spelling and pointer view for the same accessed receiver.

`SquadCompactView.h` shares those existing accessed declarations between the seed and compact donor, including the one-argument erase declaration required by compact and the two-argument erase and push_back declarations already required by the seed. Compact uses the seed's existing receiver/member spelling, with explicit casts retaining its void-pointer operations. This is no complete Squad recovery, pointer identity claim, function rename or compiler-flag change. Existing partial Object declarations stay in their original sources.

After, the same dry-run exits 0 and accepts the seed plus `Code/GameEngine/Source/Common/Gen0018BC70BfmeCompact.cpp`: four matched bodies under the seed's /MD and existing include flags. Leave the 70-byte compact donor for Luna. SquadFromContainedMembers and SquadXfer still conflict with the partial allocator/vector declarations when their real STL headers are combined; Xfer also needs its Snapshot/receiver declarations. The mixed getAllObjects donor stays untouched. No merge was applied.

## Verification and selection evidence

- `./build.sh Code/GameEngine/Source/GameLogic/AI/Squad.cpp Code/GameEngine/Source/Common/Gen0018BC70BfmeCompact.cpp`: 4/4 before and after, without float, string or import failures. `find_declared_unmatched.py` passes for both sources; `class_gate.py` passes for both sources and the new header.
- `data_check.py` reports zero findings. `allowed_symbols.py --source` reports 11 owner references, zero wrong bindings. `link_check.py --new-variants --paths-from build/codex-squad-sources.txt` passes.
- Supported object/identity APIs establish all six external code definitions and eight non-debug sections retain identical bytes, normalized relocations, section flags and COMDAT selection policies. Undefined references, external data definitions and linker aliases are identical. All eleven ledger reference sites keep the same symbol and retail target; these four bodies have no EH funclets. Neither provider candidates nor their selection rules or consumer bindings change.

Local receipts: `build/codex-squad-{before,after}-dry-run.txt`, `*-build-{before,after}.txt`, `*-before-{files,objects}/`, `*-object-proof.json`, `*-eh-binding-proof.json`, `*-code-identity.txt`, `*-data.txt`, `*-link-variants.txt`. The refreshed planner's input/output check passes.

## Complete batch handoff

Audited all seven pending commits in `a1ee5c1f39..32cb1125bc` plus this staged two-source/header change together, after pull/rebase and explicit stash restoration. No source is moved, renamed or deleted. The only new source paths are three scoped headers: ObjectDefectionHelperView.h and DynamicShroudClearingRangeUpdateView.h each have three direct consumers; SquadCompactView.h has two. Combined searches across Code, tools, hooks, workflows and reverse registers confirm no active consumer needs path repair. Build inputs and historical EA paths are preserved. No protected data/identity register or TU map changes; only the two accepted GameLogic header queue keys are removed. The upstream rebase changed none of these sources, headers, AGENTS.md, docs/consolidation.md, tools or hooks. `check_csv.py` passes. Existing HeaderTemplate creation identity debt and unrelated data/header/ms-header findings remain registered.

The new prerequisite results this session, separate from inherited Recorder recovery, are:

| Destination | Verified improvement | Downstream acceptance | Commit at final audit |
| --- | --- | --- | --- |
| HeaderTemplate | Canonical HeaderTemplate declarations and string include environment | Seed plus four donors, 12 rows | 23e85675d4 |
| QueueProductionExitUpdate | Two canonical GameLogic consumers; two header queue keys retired through acceptance | No merge yet; two adoption blockers removed, Coord3D/Xfer/BitFlags conflicts remain | a99db03c69 |
| ObjectDefectionHelper | Shared receiver for timer and Xfer | Seed plus two donors, six rows | 959f4c2477 |
| DynamicShroudClearingRangeUpdate | Shared receiver for animation and Xfer | Seed plus two donors, seven rows; update donor still blocked | ca25ab2c33 |
| AITNGuard | Canonical ObjectID before GameLogic lookup | Seed plus one constructor, two rows; five other donors remain blocked | 1d0f776c77 |
| Squad | Shared compact/visitor declarations | Seed plus one compact donor, four matched bodies | THIS_COMMIT |

Inherited Recorder recovery is 3728632e0c (4/4 verification); it is not attributed as new prerequisite work. GiantBird's enum trial accepted no donors: receiver/base-class prerequisites remain. Its source was restored, evidence recorded with re_log.py and a handoff, and its claim released (32cb1125bc). Broad receiver/layout prerequisites in AssaultTransport, Garrison, BridgeTower, Radar and SupplyWarehouse were assessed without speculative edits. MultiplayerSettings includes cross-family donors and known flag failures; no new claim or trial was taken. AIUpgradeScienceBuilder needs coherent container identity. No prohibited fallback lane was used.

The batch removes zero C++ files, adds three scoped headers, recovers zero C++ bytes, retires two header queue keys and retires zero code-identity debt keys. Existing data and identity findings remain accounted for. These are demonstrated dry-run unblocks, not confirmed downstream Luna landings. No maintainer-only link, census, nightly or smoke run was started.

`python3 tools/progress.py origin/master` at the final audit reports BYTE-MATCHED 7,978,500 (100.00%), LINKING 7,267,914 (96.74%) and LINKED 7,518,133 (97.51%), all with zero delta. Linking figures are the existing 2026-10-25 21:36 census, not a new measurement. No ownership receipt is claimed.

Keep the following scope claims until publication is confirmed. Then release these file/class scopes and run `python3 tools/claims.py release --landed`. If publish returns a cooldown/busy result, the runner retains the batch; the next session must confirm landing before releasing these scopes.

- `class:HeaderTemplate`
- `class:HeaderTemplateManager`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate.cpp`
- `file:Code/GameEngine/Source/GameLogic/AI/Squad.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate_notifyProductionBurstFinished.cpp`
- `file:Code/GameEngine/Source/Common/System/RecorderClass_readArgument.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdateView.h`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/Rva0048B256AnimateGridDecals.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelperXfer.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelper.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateExitObjectViaDoor.cpp`
- `file:Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp`
- `file:Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-02-238DE4.cpp`
- `file:Code/GameEngine/Source/Common/Gen0018BC70BfmeCompact.cpp`
- `file:Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplateManagerRva00201B05.cpp`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplateView.h`
- `file:Code/GameEngine/Source/GameLogic/AI/SquadCompactView.h`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplateManagerGetFontFromTemplate.cpp`
- `file:Code/GameEngine/Source/Common/ConstIntGetters5.cpp`
- `file:Code/GameEngine/Source/Common/System/RecorderClass_writeArgument.cpp`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplate.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdateXfer.cpp`
- `file:Code/GameEngine/Source/Common/System/RecorderClass_logPlayerDisconnect.cpp`
- `file:Code/GameEngine/Source/Common/HeaderTemplateManager_findHeaderTemplate.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelper_startDefectionTimer.cpp`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplateParse.cpp`
- `file:Code/GameEngine/Source/Common/HeaderTemplateManager.cpp`
- `file:Code/GameEngine/Source/GameClient/GUI/HeaderTemplateCreation_Rva00201c39.cpp`
- `file:Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelperView.h`
- `file:Code/GameEngine/Source/GameClient/GameClientDisplayModeChange.cpp`
