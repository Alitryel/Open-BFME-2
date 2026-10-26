# FireWeaponWhenDamagedBehavior consolidation handoff

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehavior.cpp`.

The allocation check passed. The scoped consolidation planner and report check passed. The plan listed 10 approved rows, six donor files and two mixed donors; it refused no rows. The dry run accepted no donors and reported that it could not verify a merge of two or more donors. No source changes were applied.

Rejected unchanged donors and compile blockers:

- `FireWeaponWhenDamagedBehaviorDtor.cpp`: C2504, `DamageModuleInterface` is an undefined base class.
- `Rva00482641Xfer.cpp`: C2061 in `BfmeXfer.h`, identifier `Snapshot`.
- `FireWeaponWhenDamagedBehaviorPoolKey.cpp`: C2039, `getModuleNameKey` is not a member of the class.
- `StlSweepR3Rva00482A4D.cpp`: C2950 in `_alloc.h(446)`, allocator specialization instantiation.
- `FireWeaponWhenDamagedBehaviorUpdate.cpp`: C2143, missing `;` before `*`; also reported additional syntax errors.

Mixed donor inspection:

- `ModuleNameGetters.cpp` has 38 rows with no approved TU, and its row at 0x48263B routes here. A split trial carved that row and matched 1/1, but composing it into this TU failed with C2511 because the `FireWeaponWhenDamagedBehavior` constructor overload is missing.
- `Disp8ByteChaseGetters.cpp` has 66 rows with no approved TU and two rows routed here. A split trial carved 0x4827EF and 0x4827F9; both matched alone and the composed TU trial passed. There are no accepted merge donors to batch with this split, so it was not applied because it would only increase file count.

Further progress needs Sol's declaration, header, signature or allocator repairs. No merge, source-path change, or identity-debt retirement is claimed. All task source and RVA claims were avoided; only this handoff file is claimed.
