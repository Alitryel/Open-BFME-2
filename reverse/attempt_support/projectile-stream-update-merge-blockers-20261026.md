# ProjectileStreamUpdate mechanical merge blockers (2026-10-26)

Allocator shard 4/5 served `Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdate.cpp`; `--check-tu` exits 0. The scoped consolidation planner is current (140 groups, no compile-trial groups). The TU plan has 12 approved rows and two mixed donors. The unchanged dry-run retained no donors and applied no merge.

The dry-run reported these unchanged donor failures:

- `Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdateCtor.cpp`: `C2365: 'INVALID_ID' : redefinition; previous definition was a 'enumerator'` (reported at generated TU lines 56 and 58).
- `Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdatePoolKey.cpp`: `C2039: 'rva0033EE84' : is not a member of 'ProjectileStreamUpdate'` (generated TU line 29).
- `Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdateXfer.cpp`: `BfmeXfer.h(19): C2011: 'Xfer' : 'class' type redefinition | generated TU line 48: C2011: 'Thing' : 'class' type redefinition`. The dry-run output caps each error excerpt at 300 characters.
- `Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdateGetAllPoints.cpp`: `GameLogicObjectLookupView.h(57): C2011: 'GameLogic' : 'class' type redefinition | Coord3D.h(7): C...`. The dry-run output caps each error excerpt at 300 characters.

The overall trial was blocked because a candidate donor group did not re-verify: `_alloc.h(446): C2950: '_STL::allocator<char>' : cannot explicitly instantiate an explicit specialization`. No declaration, header or compiler repair was attempted in the mechanical lane. Sol owns these prerequisites; do not repeat the unchanged trial before they change.
