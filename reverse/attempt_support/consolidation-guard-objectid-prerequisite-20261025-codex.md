# AITNGuard ObjectID prerequisite — 2026-10-25, codex

Allocated target: `Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`, family A shard 0/2. Current routing approves 33 rows overall, with seven eligible source files, five mixed files and four protected sources. The planner's same-spelling donor/path alternatives are hints, not proof of BFME 2 identity. The current TU map is rebuilt in memory, never committed.

## Demonstrated repair

Before, `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp --dry-run` exits 2 and accepts nothing. The seed's late `_GAME_TYPE_H_` definition is hoisted ahead of its private ObjectID enum, suppressing the canonical header's ObjectID definition and breaking GameLogicObjectLookupView.h.

The seed now includes the canonical header at its normal include site and uses its ObjectID enum and zero-valued INVALID_OBJECT_ID sentinel. The private duplicate and header-guard override are removed. No class layout, function identity, compile flag or runtime behavior changes.

After, the same supported dry-run exits 0 and accepts the seed plus `Code/GameEngine/Source/Common/Rva00545DB0Ctor.cpp`: two matched rows, with /DNDEBUG /MD. Leave the compatible constructor for Luna. Five donors still fail: AITNGuardXfer needs Snapshot/PooledString declarations and compatible receiver views; Rva00545D7ECtor needs StateMachine declared before AIUpdateInterface; AITNGuardScan needs Object position; HasAttackedMeCondition needs Relationship available before Object; ReturnStateOnEnter needs TAiData before AI. These are remaining prerequisites, not failures of the verified seed repair. Mixed and protected sources remain untouched.

## Verification and binding evidence

- `./build.sh Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`: 1/1, 395 bytes, before and after; no string, float or import failures. `find_declared_unmatched.py` passes.
- `header_adopt_lane.py accept --class GameLogic` passes for the seed; there was no existing queue key, so no debt retirement is claimed. `data_check.py` reports zero findings; `allowed_symbols.py --source` reports 12 references (11 owner, one alias), zero wrong bindings; `link_check.py --new-variants --paths-from build/codex-guard-sources.txt` passes.
- Before/after object evidence through the existing allowed_symbols/link_census APIs: all 23 external code definitions, undefined references, linker aliases and external data definitions are identical. Moving the header changes section numbering, so a raw section-index comparison is insufficient. Matching sections by their symbol/name keys and normalizing local relocation targets proves all 25 non-debug sections retain identical contents, relocations, flags and COMDAT selection policies. All 12 ledger reference sites retain their symbols and retail targets; no EH sites occur in this source. Provider candidates, selection rules and consumer bindings are unchanged.

Local receipts: `build/codex-guard-{before,after}-dry-run.txt`, `*-build-{before,after}.txt`, `*-before-{files,objects}/`, `*-object-proof.json`, `*-section-reorder-proof.json`, `*-eh-binding-proof.json`, `*-header-accept.txt`, `*-code-identity.txt`, `*-data.txt`, `*-link-variants.txt`. The refreshed planner snapshot passes its input/output check.

## Batch audit and publication handoff

Audited origin/master at `fce2c6327a`, all five pending commits and this seed change together. No source is moved, renamed or deleted. The only new source paths in the batch are the two previously audited scoped receiver headers, each used by exactly its three direct consumers. Active tools, hooks, workflows, includes, build inputs and registries retain their existing paths; historical EA paths are preserved. Rebase touched none of these prerequisite consumers, their headers, AGENTS.md or docs/consolidation.md. `check_csv.py` passes. This repair removes zero cpp files, adds zero headers, retires zero debt keys and recovers zero C++ bytes.

Pending commits before this repair: `245dd4aad6` Recorder recovery, `4ceb2946d6` HeaderTemplate, `8387464f67` production-exit GameLogic, `cbf670792a` ObjectDefectionHelper and `b3a5fb4c37` DynamicShroud. Keep this seed's file claim and those earlier scopes until confirmed publication, then release file/class scopes and settle landed RVAs. No maintainer-only link, census, nightly or smoke run was started. Dry-run acceptance is demonstrated; a downstream Luna landing is not yet claimed.
