# Mechanical consolidation batch handoff (2026-10-26)

## Verified merges

- `NetCommandRef.cpp`: absorbed two donors; 7 matched rows retained.
- `AptValueGCAllocator.cpp`: absorbed one donor; 4 matched rows retained.
- Net source-file change: 3 donor files removed. No byte recovery or debt retirement is claimed.

After rebasing on `origin/master`, both destination builds passed (`./build.sh NetCommandRef.cpp`, `./build.sh AptValueGCAllocator.cpp`); `find_declared_unmatched.py` passed for each. `check_csv.py` passed, scoped `data_check.py` reported 0 findings, and `link_check.py --new-variants --shadow` for both destinations exited 0. The latter reported only the cached compile progress lines. The full post-rebase `code_identity_gate.py --full` scan was interrupted after roughly five minutes while compiling unrelated rows; it produced no completion verdict. Pre-rebase scoped identity, provider/consumer, COMDAT, relocation, EH and data checks are documented in the respective merge handoffs; those results do not substitute for a completed full post-rebase identity scan.

## Outgoing path audit

The complete outgoing source-path range is `origin/master..HEAD`: absorbed donors were `AptValueGC_PoolManager_CleanPool.cpp`, `NetCommandRefContents.cpp` and `NetCommandRefCtor.cpp`. Searches across active tools, hooks, workflows, build inputs, includes and source consumers found no active dependency on these paths. Remaining mentions are provenance comments and historical records (`reverse/name_basis.csv`, `reverse/link_status.csv`, prior attempt/support notes and `reverse/re_attempts.log`). These historical EA/source paths remain intact; no map regeneration was committed. The publisher's `link_batch_audit.py` selected-provider, lost-byte and freshness report is still required before publication is considered verified.

## Fresh recovery check

At recovery HEAD, `./build.sh Code/GameEngine/Source/GameNetwork/NetCommandRef.cpp Code/Libraries/Source/Apt/AptValueGCAllocator.cpp` passed 11/11 matched rows, including all three EH funclet pins, and verified 17 literals plus one empty-string reference. Both frozen-file checks and `check_csv.py` passed. `data_check.py --converged` judged 10 addresses with zero second names or unjudged rows. `link_check.py --new-variants --shadow` passed both destinations; `tu_ownership.py --commit` passed both merge commits. The existing per-merge receipts above preserve the before/after code and data identity, COMDAT, relocation, EH and provider comparisons; the pending range changes no identity or data register. The earlier full-tree identity scan remains without a verdict and is not represented as passed. A fresh active-consumer search for all three absorbed source paths found no hits under `tools/`, `.githooks/`, `.github/`, `Code/`, or build inputs. Historical path evidence remains untouched. The pre-push batch audit is still required to assess selected providers, lost bytes and input freshness.

## Remaining prerequisites

The current allocated probes that did not yield an unchanged mechanical merge are documented in the adjacent `consolidation-*-20261026.md` handoffs: profile high-level identity/data conflicts; declaration/view and compiler prerequisites in SpecialPowerCreate, UpdateModule, BridgeTowerBehavior, OCLUpdate and ProcessAnimateWindow; inherited W32DI keyboard and WWLib thread blockers. No candidate source was left modified by those trials. No new claims were taken for rejected candidates. Current merge claims remain live until publication is confirmed; release them with `claims.py release --landed` after landing. If publication is held, report the outstanding file/RVA claims and `origin/master..HEAD` range for recovery.
