# SpecialAbilityUpdate consolidation blocked (2026-10-25)

Destination: `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`.

The allocated destination passed `consolidation_queue.py --check-tu`. I refreshed the scoped `name_lane.py consolidate` report and its `--check`, read the TU plan, and ran one `tu_skeleton.py --merge ... --dry-run`. It approved 43 rows, found 11 donor files (six mixed), and accepted **no** donors. No merge was applied and no claims were acquired.

Two donors are protected path-keyed entries and cannot be absorbed in this lane without a verifier change:

- `SpecialAbilityUpdateDtor.cpp`
- `SpecialAbilityUpdatePoolKey.cpp`

The remaining clean donors all failed the tool's composition compile. Representative exact diagnostics:

- `SpecialAbilityUpdateModuleData.cpp`: C2600, `SpecialAbilityUpdateModuleData::SpecialAbilityUpdateModuleData` cannot define a compiler-generated special member not declared in the class.
- `SpecialAbilityUpdateSlot8.cpp`: C2039, `rva0044EDA6` is not a member of `SpecialAbilityUpdate`.
- `Rva0044EECACheck.cpp`: C2039, `m_val20` is not a member of `Overridable`.
- `Rva0044EF5EFinish.cpp`: C2504, `BehaviorModule` base undefined; subsequent `m_object` unresolved.
- `SpecialAbilityUpdateXfer.cpp`: C2061 at `BfmeXfer.h` for `Snapshot`.
- `SpecialAbilityUpdateRva0044FEB6.cpp` and `Rva00451EACMethod.cpp`: C2061 for `CommandSourceType`.
- `SpecialAbilityUpdateIsWithinStartAbilityRange.cpp` and `SpecialAbilityUpdateInitiateIntent.cpp`: C2143/C2501 around undeclared `Object::AIUpdateInterface`.
- `SpecialAbilityUpdateTriggerAbilityEffect.cpp`: C2143/C2501 around `SpecialAbilityUpdate` declaration.

These require declaration/header work outside mechanical consolidation. Leave the donors and protected entries unchanged for Sol. This trial removed no files and changed no matched rows.
