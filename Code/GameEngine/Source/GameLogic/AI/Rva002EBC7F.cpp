// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EBC7F @0x002EBC7F 40B. Cdecl helper: rowed
// IsOdd on one arg (sharing pushed args), then pinned cdecl 0x002E79A8
// with a struct pair unpacked, returning the first arg. Identity unproven.
struct Rva002EBC7FPair
{
	int x;
	int y;
};
bool __cdecl Rva002EBBFBIsOdd(void *p);
struct PathfinderCellPoint { int x; int y; };
enum PathfindLayerEnum { LAYER_INVALID = 0 };
// Rowed 0x002E79A8 returns its cell point through the hidden first argument;
// this caller forwards that buffer, so it calls the rowed symbol through the
// five-slot cdecl view.
PathfinderCellPoint __cdecl rva002E79A8(bool, int, int, PathfindLayerEnum);
typedef void (__cdecl *Rva002E79A8View)(int, unsigned char, int, int, int);
// ?rva002EBC7F@@YAPAXPAX0PAURva002EBC7FPair@@H@Z @0x002EBC7F 40B (name guess).
void *rva002EBC7F(void *a1, void *a2, Rva002EBC7FPair *a3, int a4)
{
	((Rva002E79A8View)&rva002E79A8)((int)a1, Rva002EBBFBIsOdd(a2), a3->x, a3->y, a4);
	return a1;
}
