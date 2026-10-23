# Existing vector push providers

Input BFME2 df5a0f6812; published census b711de3634, 2026-10-23 14:28,
retail-truth-4. Move existing named rows out of the blocked
StlportVectorPushBackFamily collector into already-emitted matching copies.
Names, boundaries, element views, code, flags, pins and aliases are unchanged.
No new authored C++ coverage is claimed.

Preflight verifies complete bodies and relocations with compile_function
against current receiving objects: all sixteen exact, no unresolved relocations
and no wrong code-identity bindings in the moved rows. Existing row notes and
same-name instantiations/call relationships supply identity evidence; no new
application-level name or layout is inferred from byte placement.

BFME1 reviewed at verified f5140c1cff6a58e16276fd6de6788186286953d4.
The prior donor-update comparison is in link_library_providers_20261023/readme.md.
No donor row has these BFME2-specific instantiation names. Reviewed donor
ParkingPlaceInfoVectorReserve.cpp and AnimSetVectorInsertOverflowBody.cpp:
their typed out-of-line cleanup/node-allocation patterns are already present,
but their layouts/names are not BFME2 evidence. Existing target copies and
relocation proof, rather than a donor source change, control these moves.

The six previously excluded overflow-provider moves remain deferred for the
exact identity issues documented in vector-existing-provider-link-20261023.md;
no source trials repeated. Push-back 0x0020A227 is additionally excluded:
ScriptEngineDoXfer's current copy byte-matches but its typed _Construct at
0x0020596A has a wrong/unknown identity binding. Recorded blocked and released.

Moved rows (RVA, extent, receiving unit):

- 0x00082BE6, 55 B, Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterAreaRenderables.cpp
- 0x00082C1D, 55 B, Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterAreaRenderables.cpp
- 0x000CF83C, 55 B, Code/Libraries/Source/WWVegas/WWLib/CameraMarkerParse.cpp
- 0x001741EB, 55 B, Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva001741eb_fill.cpp
- 0x00287F76, 55 B, Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva00287f76_overflow.cpp
- 0x002B9062, 55 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp
- 0x0040457D, 55 B, Code/Libraries/Source/WWVegas/WWLib/Rva004045B4.cpp
- 0x00414258, 55 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveResourceBonus.cpp
- 0x004F87BC, 55 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveBattle.cpp
- 0x005E1E9B, 55 B, Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIRegionDetailsArmiesPage.cpp
- 0x005EFD53, 55 B, Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/StrategicHUDRegionDetailsArmiesMovieClip.cpp
- 0x005F13E6, 55 B, Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/StrategicHUDRegionDetailsStructuresMovieClip_IconSlot.cpp
- 0x003324D5, 38 B, Code/Libraries/Source/WWVegas/WWLib/StlportVectorReserveFamily.cpp
- 0x004140FD, 38 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveResourceBonus.cpp
- 0x00414123, 37 B, Code/GameEngine/Source/GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveResourceBonus.cpp
- 0x005E825C, 55 B, Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIBuildQueueIconSelect.cpp

Paired scoped legacy link_check: before 13/14 clean, 31,571 B;
after 13/14 clean, 32,399 B: **+828 B newly linked**. Both runs exit 1
for the same collector, whose remaining unrelated blockers are retained in
before.txt/after.txt. Census's old 31,037 B is not this paired baseline.
No self-strict, closed-strict or executable link result is claimed.

Acceptance: all 443/443 function rows across 14 units pass the byte gate;
29 literals, three empty-string references and four float literals pass.
EH 75/75 exact, no baseline. Code-identity shadow findings remain unchanged
at 25 (the pre-existing private-view/helper debt is not suppressed).
Frozen-definition, check_csv and git diff --check pass. No source, pin,
compiler option, verifier or baseline changes, and no full census/link run.
