#ifndef BFME2_PLACEMENT_POSITION_VALUE_H
#define BFME2_PLACEMENT_POSITION_VALUE_H

#include "../../../Libraries/Include/Lib/Coord3D.h"

// Native placement callers construct the three-float argument to 0x0030596C
// component by component. WB DAF523..DAF593 also tracks its empty destructor.
// This ABI value view preserves that copy contract without changing the
// canonical Coord3D layout-only declaration for unrelated callers.
struct PlaceCoord : Coord3D
{
    PlaceCoord() {}
    PlaceCoord(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
    PlaceCoord(const PlaceCoord &p) { x = p.x; y = p.y; z = p.z; }
    ~PlaceCoord() {}
};

#endif
