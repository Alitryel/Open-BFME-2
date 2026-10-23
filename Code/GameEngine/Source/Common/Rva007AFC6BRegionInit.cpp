// cl: /MD
// ?rva007AFC6B@@YAXXZ @0x007AFC6B 73B: dynamic initializer of the Region2D at
// VA 0x00E02EAC (g_00E02EAC, LivingWorldSound.cpp). Retail builds two Coord2D
// temporaries, {+FLT_MAX,+FLT_MAX} first and then {-FLT_MAX,-FLT_MAX} (literals
// at VA 0x00BBB8E0 / 0x00BBB8DC), constructs the region through the rowed
// two-endpoint ctor ??0Region2D@@QAE@ABVCoord2D@@0@Z (0x00004C06) as
// (lower = -MAX, upper = +MAX), then registers 0x007B816A with atexit.
// ?rva007B816A@@YAXXZ @0x007B816A 1B: that cleanup is a lone ret (the
// destructor work is empty). Owning TU and original names unrecovered.

inline void *operator new(unsigned int, void *where)
{
	return where;
}

extern "C" int __cdecl atexit(void (__cdecl *callback)());

#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"

extern Region2D g_00E02EAC;

void rva007B816A()
{
}

void rva007AFC6B()
{
	Coord2D upper = { 3.402823466e+38f, 3.402823466e+38f };
	Coord2D lower = { -3.402823466e+38f, -3.402823466e+38f };
	new (&g_00E02EAC) Region2D(lower, upper);
	atexit(rva007B816A);
}
