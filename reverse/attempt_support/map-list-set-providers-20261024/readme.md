# Existing map list and set providers

BFME2 input d11f837768; published legacy index 11b3872700 (2026-10-23
23:06, retail-truth-4). Twelve existing rows move from MapMetaDataCopy to
eight existing consumers emitting the complete retail body and relocations.
No C++, flags, names, pins, aliases or layouts change. The typed Coord3D list
and AsciiString set identities are already established in the receiving units;
their comments preserve target evidence and any provisional identities.

Reviewed BFME1 f5140c1c MapMetaData_assign/dtor and the existing beacon donor
context. The donor has the same container roles; BFME2 extra fields and layout
remain as independently recovered. No donor body, layout or address is imported.
The broader unchanged donor scan is link_library_providers_20261023.

All twelve destination bodies pass full-byte/resolved-relocation preflight,
with zero unresolved relocations. Paired scoped legacy link_check: 8/9 units
clean, 3,780 -> 4,396 B, **+616 B linked**. Extents sum to 617 B; the scoped
metric merges overlaps. Existing ICF twins are retained, so this measures
ownership/availability, not newly unique code recovery. No self-strict,
closed-strict or whole-image census gain is claimed.

MapMetaDataCopy's independent waypoint-map clone/copy/pair identity blockers
remain; the paired logs preserve them. No retry of the deferred map family.

Acceptance: 139/139 byte gates, imports/strings/floats pass; EH 12/12 EXACT,
zero baseline. Code identity findings decrease 11 -> 10 (existing divergent
pair destructor definition no longer row-owned here); no new findings.
Frozen-definition, CSV and whitespace checks pass.

Rows (RVA, extent, receiving source):

- 0x00280B87, 48 B, Code/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
- 0x00281A58, 30 B, Code/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
- 0x00280A8D, 41 B, Code/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
- 0x002820DD, 88 B, Code/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
- 0x000589BE, 56 B, Code/GameEngine/Source/Common/Rva001FDB55Ctor.cpp
- 0x00301AB1, 115 B, Code/Libraries/Source/WWVegas/WWLib/stlport_asciistring_set_base.cpp
- 0x00301B54, 107 B, Code/GameEngine/Source/GameClient/MapCacheAddMap.cpp
- 0x00280A68, 37 B, Code/Libraries/Source/WWVegas/WWLib/StlportListInsertFootprints.cpp
- 0x002819AD, 28 B, Code/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
- 0x004EC395, 23 B, Code/Libraries/Source/WWVegas/WWLib/Rva00534E13Dtor.cpp
- 0x00059068, 5 B, Code/GameEngine/Source/Common/System/INIMacroTable.cpp
- 0x0023DAA5, 39 B, Code/GameEngine/Source/GameClient/MapMetaDataDefault.cpp
