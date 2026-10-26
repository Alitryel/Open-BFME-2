# CommandSetUpgrade TU consolidation audit — 2026-10-26

The current flex-shard allocation approved
`Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp`.
`tools/tu_skeleton.py --plan` approved seven rows from four donors, with two
mixed sources; its unchanged dry run accepted the constructor and
`Rva004B3B42Mask.cpp` donors (five rows). The tool applied only those accepted
donors and repointed `reverse/functions.csv` and `reverse/tu_map.csv`. The two
other donors remained untouched after unchanged trial failures:

- `CommandSetUpgradePoolKey.cpp`: C2039, `getModuleNameKey` is not a member of
  `CommandSetUpgrade`, then C2270.
- `Rva004B3AFFNotify.cpp`: C2143 before `*`, then C2501 for `TheControlBar`.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp`
  passed all five matched rows, byte checks, string/float/import checks and the
  verified funclet pin.
- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp`
  reported no unmatched defined functions.
- `python3 tools/eh_verify.py Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp`
  reported one exact EH row.
- `python3 tools/code_identity_gate.py --staged` reported zero new findings in
  shadow mode; `python3 tools/tu_ownership.py --staged` passed.
- `python3 tools/data_check.py --converged` found zero second names or
  unjudged rows; `python3 tools/check_csv.py` passed.
- `python3 tools/check_case_collisions.py` passed. `header_adopt_lane.py order`
  showed no new header adoption requirement for this TU. The MS-header queue
  listed unrelated candidates only.
- `rg` across active tools, hooks, workflows, source, headers, build/config,
  registries and docs found no active path consumer for the absorbed files.
  Old paths remain in generated consolidation reports, historical evidence,
  and provenance comments in the merged TU. The same batch audit for the
  pending MaxHealthUpgrade merge is recorded in
  `maxhealth-upgrade-consolidation-20261026.md`.
- The pre-push `link_batch_audit.py` is still required to report selected
  provider bindings, lost bytes and input freshness for the complete outgoing
  range; no link gain is claimed before that report.

The merge deletes two donor files and creates the previously absent TU, for a
net reduction of one source file, and preserves five matched rows. No
identity or data debt was retired. The existing census snapshot has not been
rerun and is not evidence for the new source composition.

## Mixed-source split follow-up

The allocated TU's mixed plan had one row in
`UpgradeModuleDataGetterBuildFieldParse.cpp` approved for this destination.
`tu_skeleton.py --split FILE --for TU --dry-run` accepted the unchanged 34-byte
row at `0x004B3A90` and its associated `s_commandSetTable`; it carved the row
into the existing destination and retained seven donor rows. The second mixed
file, `FireWeaponWhenDeadBehaviorDerived.cpp`, had no row approved for this TU
and its split was refused unchanged.

- `./build.sh CommandSetUpgrade.cpp UpgradeModuleDataGetterBuildFieldParse.cpp`
  passed 13/13 matched rows across both files, including byte, string, float,
  import and funclet checks.
- `find_declared_unmatched.py` reported no unmatched definitions in either
  file; `eh_verify.py` reported one exact EH row.
- Staged code identity reported zero new findings in shadow mode; staged TU
  ownership, converged data, CSV and case-collision checks passed.
- The split tool updated the destination in `docs/doxygen/sources.cfg`; no
  source path was added or removed, so this split has zero net source-file
  reduction. The pre-push provider, lost-byte and freshness audit remains
  required for the full pending range.
