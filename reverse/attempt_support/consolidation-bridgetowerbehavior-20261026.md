Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp` (mechanical shard 0/5); `consolidation_queue.py --check-tu` passed. The scoped `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Behavior/` report was regenerated after upstream rebase and `--check build/consolidation` passed. The current plan has 12 approved rows, 7 donor files, 2 mixed files, and no refused rows.

The merge dry run accepted only the existing destination plus unchanged `BridgeTowerBehaviorCtor.cpp` (5 rows total). `tu_skeleton.py --merge` removed the ctor donor and repointed its rows while carrying the donor's protected-register keys; it did not retire debt. Net source-file reduction: 1. Rejected unchanged donors were left in place:

- `BridgeTowerBehaviorPoolKey.cpp`: `C2039`, `rva00045876C` is not a member of `BridgeTowerBehavior`.
- `BridgeTowerBehaviorXfer.cpp`: `C2011` class redefinition and `C2039` for `Version1` on the current view.
- `BridgeTowerBehaviorGetInterfaceFromObject.cpp`: `C2039`, `isBridgeTower` is not a member of `Object`.
- `BridgeTowerBehaviorOnDamage.cpp` and `BridgeTowerBehaviorOnHealing.cpp`: class redefinition / `C2039` member errors in `GameLogic` views.

These need Sol's declaration/view reconciliation before another merge trial; this seat made no manual code repairs and should not retry these unchanged donors.

After rebasing the inherited commits, the destination rebuild passed (5/5 function rows); `find_declared_unmatched.py` passed for the destination; `check_csv.py` passed. Staged scoped checks: `code_identity_gate.py --staged` reported 0 new findings in shadow mode; `data_check.py --staged` reported 0 findings and `--converged` reported 10 addresses, 0 second names and 0 unjudged rows; `tu_ownership.py --staged --shadow` was clean; `link_check.py --staged --new-variants --staged-peers` exited 0 with no new variant; `allowed_symbols.py --source` reported 0 wrong bindings; `eh_verify.py` reported no EH differences; `ms_header_audit.py check` passed.

The complete outgoing path-change audit covered inherited `origin/master..HEAD` moves plus the staged BridgeTower donor removal/repoint. Searches of active tools, hooks, workflows, build inputs, includes and source consumers found no active dependency on the absorbed path; remaining mentions are provenance comments or historical evidence. The two inherited merges' audits are recorded in `consolidation-commandbuttonhuntupdate-20261026.md` and `consolidation-shipslowdeathbehavior-20261026.md`. The generated `tu_map.csv` edit is the merge tool's row repoint, not a regenerated map. Matched rows and provenance were preserved; no code-identity debt retirement is claimed.

## Follow-up allocation probe (2026-10-26)

A later shard allocation rechecked the remaining candidates in this TU after the already-landed constructor merge above. Current plan: 12 approved rows, 6 donor files, 2 mixed files, none refused. The unchanged merge dry-run accepts no donor batch. `BridgeTowerBehaviorPoolKey.cpp` fails because `rva00045876C` is not a member of `BridgeTowerBehavior`; `BridgeTowerBehaviorXfer.cpp` fails on `Xfer` redefinition and `Version1` member errors in `BfmeXfer.h`; `BridgeTowerBehaviorGetInterfaceFromObject.cpp` fails because `Object::isBridgeTower` is undeclared; the damage/healing donors hit `GameLogic` view redefinition/member errors.

Mixed `ConstIntGetters4.cpp` row 0x00458759 split dry-run hits C2259 for abstract `GlowMaterial` in `BuffManager.h`. `Disp8LeaNegSbbGetters.cpp` row 0x0045875F can be carved unchanged but does not create a multi-donor merge batch. No edits or claims were made. These declaration/view prerequisites remain with Sol.
