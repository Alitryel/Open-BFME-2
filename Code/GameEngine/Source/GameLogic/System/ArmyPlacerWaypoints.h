#ifndef ARMY_PLACER_WAYPOINTS_H
#define ARMY_PLACER_WAYPOINTS_H
#include "Coord3D.h"
class Rva0037F7B6Record;
struct Rva0037F90FInput;
struct Rva0037FE3DList;
class Player;
// WB ArmyPlacer names and native ECX receivers; no instance layout is asserted.
class ArmyPlacer {
public:
    bool GetSpawnPointInFarthestPair(Rva0037F90FInput*, int, Coord3D*, Coord3D*);
    bool GetFarthestSpawnPointFromPlayerStart(Rva0037F90FInput*, int, Coord3D*, Coord3D*);
    bool GetDefenderReinforcementWaypointLocations(Coord3D*, Coord3D*);
    bool GetStartPosWaypointLocations(int, Coord3D*, Coord3D*);
    bool GetWalkOnWaypointLocations(Rva0037F7B6Record*, Coord3D*, Coord3D*);
    void rva0037FE3D(const Rva0037FE3DList&, int);   // 0x0037FE3D
    void rva0037FAC6(const Rva0037FE3DList&, const Coord3D*, const Coord3D*, Player*, bool);   // 0x0037FAC6, WB PlaceObjects
};
#endif
