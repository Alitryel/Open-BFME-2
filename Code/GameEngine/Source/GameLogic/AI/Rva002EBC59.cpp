// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBC59 @0x002EBC59 38B. Cdecl helper: rowed
// IsOdd on one arg (sharing pushed args), then pinned cdecl 0x002E79A8,
// returning the first arg. Identity unproven.
bool __cdecl Rva002EBBFBIsOdd(void *p);
struct PathfinderCellPoint { int x; int y; };
enum PathfindLayerEnum { LAYER_INVALID = 0 };
// Rowed 0x002E79A8 returns its cell point through the hidden first argument;
// this caller forwards that buffer, so it calls the rowed symbol through the
// five-slot cdecl view.
PathfinderCellPoint __cdecl rva002E79A8(bool, int, int, PathfindLayerEnum);
typedef void (__cdecl *Rva002E79A8View)(int, unsigned char, int, int, int);
// ?rva002EBC59@@YAPAXPAX0HHH@Z @0x002EBC59 38B (name from build; see below).
void *rva002EBC59(void *a1, void *a2, int cellX, int cellY, int layer)
{
	((Rva002E79A8View)&rva002E79A8)((int)a1, Rva002EBBFBIsOdd(a2), cellX, cellY, layer);
	return a1;
}
