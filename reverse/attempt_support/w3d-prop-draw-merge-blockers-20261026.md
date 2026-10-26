# W3DPropDraw mechanical merge blockers (2026-10-26)

Allocator shard 4/5 served `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDraw.cpp`; `--check-tu` exits 0. The scoped consolidation planner is current (22 groups, no compile-trial groups). The TU plan has 9 approved rows and two mixed donors. The unchanged dry-run accepted no donors and applied no merge.

The dry-run reported these compile blockers:

- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDrawPoolKey.cpp`: generated TU line 146, `C2039: 'rva000CEEE6' : is not a member of 'W3DPropDraw'`.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDrawModuleDataCtor.cpp`: generated TU line 173, `C2614: 'W3DPropDrawModuleData' : illegal member initialization: 'm_distanceFog' is not a base or member`.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDrawReact.cpp`: `Coord3DCtorView.h(21): C2011: 'Coord3D' : 'struct' type redefinition`. The dry-run also reports `adopt_first` for this donor's `Coord3D` view.

The candidate donor group did not re-verify because `Coord3D` is defined twice. No source or header repair was attempted in the mechanical lane. Sol owns these declaration/header prerequisites; do not repeat the unchanged trial before they change.
