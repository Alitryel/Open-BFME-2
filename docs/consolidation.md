# Consolidation: one retail translation unit, one source file

The ledger mostly holds one function per file (about 23,000 units under `Code/`).
Retail was linked from real translation units, and a TU's functions sit next to
each other in `.text` in object order. This lane merges the small files back into
the TU retail built them from, one TU at a time, without losing a matched row.

Three tools do the mechanical part; a seat does the judgement.

| Tool | Role |
|---|---|
| `tools/tu_map.py` | Which TU each retail function came from: `__FILE__` strings, Zero Hour definitions and class sites, naming inside an anchored address cluster, contiguity. `approved` rows are the only ones a merge moves. |
| `tools/tu_skeleton.py` | The lane: `--queue`, `--plan`, `--merge`. It verifies every merge by compiling and byte-matching, claims its scope, and repoints the ledger. |
| `tools/tu_ownership.py` | The commit hook's invariants (a row moved to a file other than its approved TU, a second body for one address). Shadow mode. |

`tu_skeleton.py` rebuilds the map in memory when the committed `tu_map.csv` is
stale, so a merge commit never carries a regenerated map. Never commit a
regenerated `tu_map.csv` from this lane.

## Workflow per TU

1. **Pick.** `python3 tools/tu_skeleton.py --queue --limit 20` ranks approved TUs by
   how many files a merge would remove and marks those another worker holds
   (`HELD`). Take an unheld one. `removes` is an upper bound: the merge keeps only
   donors that compile together without losing a row.
2. **Read the plan.** `--plan TU` lists every approved row in retail order and what
   happens to it: `pull` (a clean donor), `mixed` (its file also holds rows of
   another TU), `refused` (deleting the file is not mechanical: vendored, keyed in
   a protected register, `#include`d by another file, or expanding `__FILE__`), or
   a placeholder comment (unmatched; it compiles to nothing and is never credited).
3. **Dry run.** `--merge TU --dry-run` composes and verifies without writing.
   `accepted` donors merge as they are. Each `rejected` donor carries the compile
   error or `bytes` (a row the merged text no longer matches).
4. **Reconcile the rejected donors, one ordinary commit each.** The usual cause is
   a private view of a class or struct that differs from the seed's: a local
   `Coord3D`, an enum declared twice, a member declared `private` in one view and
   reached from another. Make the donor compile against the seed's headers, or
   move both to the canonical header (`tools/class_views.py --class X`,
   `tools/header_adopt_lane.py`). Verify the donor with `./build.sh` and commit it
   before merging. Duplicate *identical* declarations and donor-local copies of a
   type that the seed or an included header defines are removed by the merge
   itself, and the byte check decides whether that was safe.
5. **Merge.** `BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --merge TU`
   claims `file:` for the TU and every donor, plus each moved row's RVA. It writes
   nothing when another worker holds one of them. Then it writes the TU, deletes
   the absorbed donors, repoints `functions.csv`, `data_rows.csv`, `tu_map.csv`
   and `body_owners.csv` `source` columns and the `docs/doxygen/sources.cfg`
   inputs, and stages the result. It prints the paths it staged and a commit
   subject.
6. **Verify and commit.** `./build.sh TU`, then
   `python3 tools/find_declared_unmatched.py TU`, then commit with the printed
   subject. The hook byte-verifies the TU again. Publish under AGENTS.md #7: a
   merge recovers no new bytes, so batch merges and push them together.
7. **Name while you are there.** The rows of the TU are a natural naming group:
   rename placeholder rows with `tools/rename.py` (`docs/naming.md`) in separate
   commits. A merged TU path is an approved retail TU, so `rename_files.py` never
   renames it.
8. **Release** the `file:` claims after the push
   (`python3 tools/claims.py release file:<path> ...`) and let
   `python3 tools/claims.py release --landed` settle the RVAs.

## What the lane does not do yet

- **Mixed files** (a file holding rows of two TUs) are never split: about as many
  donor files are mixed as clean. Do not split them by hand inside a merge; a
  split is its own verified change (move the foreign bodies to their own TU or a
  file of their own first, then merge).
- **TU paths that hold another TU's rows** are skipped by the queue for the same
  reason (`blocked: ... split it first`).
- **Linking.** `tools/link_check.py` cannot preview a new path before a census
  has seen it; an existing TU path is previewable. A merge that changes which
  COMDAT copy a link keeps shows up in the next census.
