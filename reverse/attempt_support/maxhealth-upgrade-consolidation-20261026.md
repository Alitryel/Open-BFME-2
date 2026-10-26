# MaxHealthUpgrade TU consolidation audit — 2026-10-26

The approved merge absorbed `MaxHealthUpgradePoolKey.cpp` and
`MaxHealthUpgradeModuleDataCtor.cpp` into
`Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp`. The
allocator accepted both donors and preserved three matched rows; other donors
failed unchanged dry-run checks and were left in place.

After the accepted merge, a fresh allocator check and merge dry-run still
accepted no remaining donors. `MaxHealthUpgradeModule.cpp` fails with C2511 for
the `MaxHealthUpgrade(Thing *, const ModuleData *)` constructor. The
`MaxHealthUpgradeUpgradeImplementation.cpp` donor fails with C2039 because
`getModuleNameKey` is absent from `MaxHealthUpgrade`, followed by C2270. Both
donors remain unchanged; this is the handoff for the remaining TU work.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp` passed: 3/3 functions, string, float and import checks passed.
- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp` reported no unmatched defined functions.
- `python3 tools/data_check.py --converged` reported 0 sources, 10 addresses, 0 second names and 0 unjudged rows.
- `python3 tools/repair_queue.py retire data Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp` refused retirement because its fresh verdict still finds two `wrong-name` keys at `0x00A03EBC` and `0x00A03EB8`. The transferred data debt remains; no baseline entry was removed.
- Header and MS-header queue refreshes found no MaxHealthUpgrade entry. The only header queue regression was an unrelated vanished source, `DrawableCalcPitchRollRva00270276.cpp`.
- No code-identity, header, MS-header or pin-consistency register entry referenced either absorbed donor path. The merge transferred the two data-ledger owners, data-check baseline row and protected alternatename hatch to the destination through `tu_skeleton.py --merge`.
- `link_check.py` said the destination is not in census `d2636bb381`, so no link preview is available. `reverse/link_status.csv` still has two `yes` rows keyed by the deleted donor filenames; this is the committed per-file census snapshot, not a per-row link-cycle receipt. These rows are historical discovery data and were not edited by the merge tool.
- The tooling/config/source/docs search found no active path consumer for either deleted donor. The remaining source mention is a comment in `MaxHealthUpgradeModule.cpp` describing its constructor's previous owner.
- The build and byte checks cover the changed TU. Selected-provider and changed-unit unresolved-symbol results remain subject to the required pre-push `link_batch_audit.py` hook; no link gain is claimed.

## Remaining prerequisites

Review the pre-push `link_batch_audit.py` report. If it reports a changed provider binding or lost bytes, investigate before publication. The old census file-name rows remain historical until the next census measurement. The two transferred data keys remain until their names are resolved through the data lane.
