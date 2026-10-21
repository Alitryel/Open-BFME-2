// cl: /DNDEBUG /MD
// ?Rva00264237Check@@YAHPBUCoord3D@@0@Z
// 0x00264237 61B: free 2D distance-squared check. Loads x/y from two Coord3D,
// compares dx*dx+dy*dy against g_00BF9680. Callers in 0x0026CF11 twice.
// Prev Rva00263910Goal has same /arch:SSE flags.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

// Owned here (its only reader); retail .rdata holds 1600.0f (VA 0x00BF9680).
const float g_00BF9680 = 1600.0f;

int Rva00264237Check(const Coord3D *lhs, const Coord3D *rhs)
{
	float dx = lhs->x - rhs->x;
	float dy = lhs->y - rhs->y;
	float d2 = dy * dy + dx * dx;
	return d2 < g_00BF9680 ? 1 : 0;
}
