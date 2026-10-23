// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBC34 @0x002EBC34 37B. Frameless bounded-cell
// helper: rowed IsOdd on one arg (sharing a pushed arg), then the pinned
// bounded WorldToCell 0x002E7964, returning the out pointer. Identity unproven.
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
bool __cdecl Rva002EBBFBIsOdd(void *p);
class Rva002E7964
{
public:
	void rva002E7964(ICoord2D *out, unsigned char center, const Coord3D *pos);
};
class Rva002EBC34
{
public:
	ICoord2D *rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3);
};
// ?rva002EBC34@Rva002EBC34@@QAEPAUICoord2D@@PAXPBUCoord3D@@@Z @0x002EBC34 37B.
// Select-any: PathfinderSelectBridgeLayer.cpp keeps a visible copy for 0x002ED313.
__declspec(noinline) inline ICoord2D *Rva002EBC34::rva002EBC34(ICoord2D *a1, void *a2, const Coord3D *a3)
{
	((Rva002E7964 *)this)->rva002E7964(a1, Rva002EBBFBIsOdd(a2), a3);
	return a1;
}

// The anchor keeps the rowed body emitted.
// ?bfmeAnchorRva002EBC34@@YAXPAVRva002EBC34@@@Z absent-from-retail
void bfmeAnchorRva002EBC34(Rva002EBC34 *p) { p->rva002EBC34(0, 0, 0); }
