# ClickReactionBehavior consolidation handoff (2026-10-26)

Allocated TU: `Code/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehavior.cpp` (consolidation shard 2/5). The accepted merge moved three unchanged matched rows from `ClickReactionBehaviorXfer.cpp`, `Rva0045969F.cpp`, and `ClickReactionBehaviorRva004596F9.cpp`. The local build and declaration scan passed; all three rows remain matched. This does not establish a link census change or retire code-identity debt.

Rejected donors for a later Sol pass:

- `Rva0024A797Grandchildren.cpp`: split trial for this TU refused with `blocked: no row of that file is approved for that TU`.
- `BehaviorModuleDataBuildFieldParse.cpp`: the split tool accepted row `0x0045960C`, but the required build gate reported a shadow `duplicate-def` for `?m_fieldParse@ClickReactionBehaviorModuleData@@2QBUFieldParse@@B` at `0x008412F8`. `rg` confirmed definitions in both the proposed TU and residual donor. The split was reverted; no duplicate provider remains in the accepted merge.
- `ClickReactionBehaviorCtorThunk.cpp`, `ClickReactionBehaviorModuleDataCtor.cpp`, and `ClickReactionBehaviorPoolKey.cpp`: merge planner refused each as `keyed in a protected path-keyed register (needs a Verifier-Change commit)`.

No rejected donor was repaired or moved. The accepted merge leaves these prerequisites for the appropriate source/register owner.

## Batch audit

Outgoing source paths are `ClickReactionBehaviorXfer.cpp` and `Update/AIUpdate/Rva0045969F.cpp` absorbed into `ClickReactionBehavior.cpp`; the third donor is a rename of `ClickReactionBehaviorRva004596F9.cpp` to the same destination. The tooling compatibility search found no active `tools/`, hook, workflow, include, or build-input consumer requiring a path edit. Remaining matches are the destination's generated provenance comments, the retail `string_xrefs.tsv`/`retail_paths.csv` evidence, and the prior census snapshot in `reverse/link_status.csv`; that snapshot remains census-owned and was not rewritten.

Scoped checks after composition: `./build.sh ClickReactionBehavior.cpp` passed 3/3 matched; `find_declared_unmatched.py` passed; staged `code_identity_gate.py` reported 3 rows and 0 new findings; staged `data_check.py` reported 0 findings and converged data reported 10 addresses with no second names or unjudged rows; `tu_ownership.py --staged --shadow` passed; `link_check.py --staged --new-variants --shadow` exited 0 with the destination object current. This checks for duplicate COMDAT variants against the census index; it does not refresh the maintainer-owned selected-COMDAT census. No data rows or providers moved, and the moved function rows retain their verified bytes. The latest consolidation planner snapshot passes `--check`.

## Second TU in the pending batch

`ObjectDefectionHelper.cpp` accepted its own source plus `ObjectDefectionHelper_startDefectionTimer.cpp` and `ObjectDefectionHelperXfer.cpp`; two donor files were absorbed. `./build.sh ObjectDefectionHelper.cpp` passed 6/6 matched rows, including two EH funclet pins verified at `0x007917D8` and `0x007917E3`; the declaration scan passed. Staged identity reported 6 rows with 0 new findings; staged data had 0 findings, and converged data had 10 addresses with no second names or unjudged rows. Staged TU ownership and the scoped `link_check.py --new-variants` check exited 0.

The combined outgoing-path audit found no active tooling, hook, workflow, include, build-input, body-owner, header-queue, or debt-register consumer needing an edit. Remaining old-path records are provenance in the moved TU and `reverse/name_basis.csv` (the inferred-name evidence), plus `reverse/link_status.csv` from the last census; those evidence records remain intact. Header ordering and the Microsoft-header queue were inspected; no queue entry names these TUs or donors. No data row/provider moved. The link check guards COMDAT variants against the census index but does not refresh the selected-COMDAT census.
