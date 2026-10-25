# QueueProductionExitUpdate GameLogic prerequisite — 2026-10-25, codex

Allocated target: `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate.cpp`, family A, shard 0/2, runner queue. This is a prerequisite repair, not a merge.

The current approved plan contains 17 rows, seven source files, two mixed donors and three protected-register refusals. The before dry-run accepts no donor and explicitly lists GameLogic adoption for ExitObjectViaDoor and notifyProductionBurstFinished under `adopt_first`. The existing Luna handoff is `consolidation-gamelogic-codex2-20261025b/README.md`.

Both donors now include the registered `Common/GameLogicObjectLookupView.h` instead of redeclaring GameLogic and ObjectID privately. Their zero-valued private ObjectID enumerators were unused. No function body, receiver field access, layout, compiler option or global name changes. The canonical header is unchanged, so the complete affected consumer set is these two donors.

## Acceptance

- `./build.sh` both sources, before and after: 5/5 exact functions, six float references, no string or import failures.
- `find_declared_unmatched.py` both sources: all defined functions already matched.
- `header_adopt_lane.py accept --class GameLogic <both sources>`: both PASS, two rows retired from `reverse/header_queue.tsv` by its acceptance path. No other header row changed.
- `allowed_symbols.py --source <both>`: 47 references: 43 owner, two fold, one EH, one alias; zero rows with wrong binding.
- `data_check.py <both>`: zero findings, zero outside baseline.
- `link_check.py --new-variants --staged-peers --paths-from build/codex-queueexit-sources.txt`: exit 0, no new COMDAT variant.
- `check_csv.py` and `git diff --check`: pass.

Saved before objects are in `build/codex-queueexit-before-objects/`. Read-only supported `allowed_symbols.Obj`, `_object_defs`, census COMDAT selection and row-reference APIs establish that all 53 external code definitions, undefined references and linker aliases are identical. All 65 non-debug sections retain identical bytes, relocation edges, flags and COMDAT selection policies after local compiler-label spelling is normalized to section/offset. The only other section differences are debug object paths (the cached census object was produced in the census checkout). All 47 ledger reference sites have identical symbol/target bindings. No provider definition, selected-COMDAT policy, external data definition, or consumer binding changes. Code-identity and data baselines remain untouched; no identity key is retired.

The scoped planner was regenerated for the ProductionExitUpdate directory, its original-path alternatives and prerequisites reviewed, and `name_lane.py consolidate --check build/consolidation` passed before the after dry-run. Routing was rebuilt in memory; no TU map is committed.

## Remaining prerequisites and publication

The after dry-run still exits 2 with no accepted donor, and no longer has an `adopt_first` section: the GameLogic adoption prerequisite is cleared for both donors and five existing rows. This is two header-debt rows retired, zero files removed and zero recovered C++ bytes. The destination still needs compatible Coord3D, Xfer and BitFlags declarations; the three protected donors remain refused. No downstream Luna merge is claimed.

Local receipts: `build/codex-queueexit-{before,after}.txt`, `*-build-{before,after}.txt`, `*-header-accept.txt`, `*-all-sections-proof.json`, `*-provider-proof.json`, `*-eh-binding-proof.json`, `*-code-identity.txt`, `*-data.txt` and `*-link-variants.txt`.

Publication audit: `git diff --name-status --find-renames origin/master` covers pending Recorder 0531a74ca3 and HeaderTemplate e3493a2bfa plus this staged change. No source is renamed, deleted, moved or added. Existing includes, build inputs, active tools/hooks/workflows and source registries keep their paths; historical EA path evidence remains intact. The inherited Recorder data-baseline retirement stays accounted for in its own verified commit; this change only retires the two header rows through acceptance.

Retain the two donor file claims until publication is confirmed, then release them and settle landed RVAs. Earlier Recorder and HeaderTemplate claims also remain held while the publisher batches the commits. No maintainer-only link, nightly or smoke run was started.
