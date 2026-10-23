// cl: /MD
// ?Rva001E3FADGet@@YAMPBUCoord3D@@0@Z, retail 0x001E3FAD, 80 bytes.
// Diff of two Coord3D then normalize then (y+x)*BfmeZeroRange+z.
// Evidence: calls rowed ?normalize@Coord3D@@QAEXXZ 0x000035B6, uses BfmeZeroRange VA 0x00BBAEAC.
// Callers at 0x001E9BEC 0x001E9C51 in FUN_005e9a00. Owner unproven honest Rva name.

// The data ledger identifies the shared read-only operand as float +0.0.

#include "../../../Libraries/Include/Lib/Coord3D.h"

float __cdecl Rva001E3FADGet(const Coord3D *lhs, const Coord3D *rhs)
{
	Coord3D d;
	d.x = rhs->x;
	d.y = rhs->y;
	d.z = rhs->z;
	d.x -= lhs->x;
	d.y -= lhs->y;
	d.z -= lhs->z;
	d.normalize();
	return (d.y + d.x) * 0.0f + d.z;
}
