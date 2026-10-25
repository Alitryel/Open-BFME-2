# Consolidation pass (seat-tu), 2026-10-25

Scope: the unheld `tools/tu_skeleton.py --queue` across the tree, after a
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
survey (137 investigation groups, 0 with static checks clear, 633 unresolved
files). Every applied move used the normal claimed `tu_skeleton.py --merge`.
There was no mixed-file split, routing-map regeneration, protected-register
edit or maintainer runner.

## Approval path

`approved` in `reverse/tu_map.csv` has no manual or agent-held admission path.
It is a pure function of the ledger, `ghidra_functions.csv`, `string_xrefs.tsv`,
`data_xrefs.tsv` and the ZH tree (`tools/tu_map.py` docstring: an F/Z/S anchor
in the TU's main cluster, contiguous span, no contradicting own F/Z/S).
`tu_skeleton.py` rebuilds the map in memory, and this lane never commits a
regenerated map. A proposed row becomes approved only when its evidence
changes. Examples: a real name that Z/S can anchor (`rename.py`, the naming
lanes), a removed contradiction, or a non-contiguous span resolved. This pass
approved no rows.

Proposed rows are mostly C (8,372), X (5,187) and N (4,675). Their largest TUs
are Object.cpp (524), LivingWorldLogic.cpp (404, with no ZH anchor at all) and
AIPathfind.cpp (401).

## Results

There are twelve merges on `a487245066`. 39 donor paths were removed and six
new TU files written: net 33 fewer sources and 76 rows. Each TU passed
`./build.sh`, `find_declared_unmatched.py` and the normal hook. The TUs are
debug_except (9 rows), Win32BIGFileSystem (21), W3DLaserDraw (8),
PoisonedBehavior (7), PropagandaTowerBehavior (6), AIGuard (2),
FireWeaponWhenDamagedBehavior (2), RankInfo (5), DemoTrapUpdate (3),
LifetimeUpdate (4), W3DGameFont (6) and InactiveBody (3).

These include the BIG, Laser and Font TUs that `consolidation-device-20261025.md`
held back. The current `tu_skeleton` refreshes `ms_header_queue.tsv` for the
destination, so no queue row is left at an absorbed path.

## Register keys of deleted donors

None. `tu_skeleton` refuses a donor keyed in `PROTECTED_PATH_KEYED`
(flag_overrides, hatch_baseline, data_check_baseline, code_identity_baseline,
data_ledger). After the batch, no deleted path appears in those registers, nor
in gate_baseline, data_converged, the unclaimed-sources whitelist or
ms_header_queue. One `header_queue.tsv` row (Coord3D) was repointed to
AIGuard.cpp. Its `failure` text still quotes the old path as history. The old
paths remain only in naming evidence (`name_agreed`, `name_votes`,
`name_basis`), attempt evidence and the census-owned `link_status.csv`.

## Blockers found

- **DisconnectManager.cpp**: the merge verifier accepted four donors, but
  `./build.sh` failed 2/7 (`??0Rva004D376A`, `??_GRva004D376A`: frame and
  stack-cleanup codegen). The TU path has an empty-flags `flag_overrides.csv`
  entry. Verifier and build disagree on its flags. The merge was reverted, and
  another worker now holds the scope.
- **ProjectileStreamUpdate.cpp**: two donors were accepted, but the written TU
  fails `C1004 unexpected end of file` at line 2. The seed's `// cl:` line is
  very long. This reproduces on `a487245066`, and the merge was reverted.
- `tu_skeleton --merge` writes `functions.csv` before it refuses a CRLF
  `tu_map.csv`, which leaves a partial repoint. A worktree on Windows with
  `core.autocrlf=true` checks `tu_map.csv` out as CRLF (it has no `eol`
  attribute). Run with `core.autocrlf=false`.
- 37 queued TUs gave `no verified merge of two or more donors`: private class
  views (Coord3D, Xfer, `_STL`), `bytes` or `no baseline match` donors. A merge
  removes no `refused` (register-keyed) donor.

## Compatibility audit

Checked once over the batch (the merge base to HEAD): deleted paths
against `tools/`, `.githooks/`, `.github/`, includes, `reverse/` and
`docs/doxygen/sources.cfg` (repointed by the tool). No active consumer names an
absorbed path, and no containing directory was removed.
