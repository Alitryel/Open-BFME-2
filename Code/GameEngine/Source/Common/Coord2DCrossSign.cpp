// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include
//
// Retail 0x0007E06D (53 B, RET 0): the sign of the 2D cross product of
// (b - a) and (c - a), truncated to int, as a file-static helper. Retail
// passes a in EAX, b in ECX and c in EDX with no stack arguments, the private
// convention cl 7.1 picks for a file-static noinline function (parameter
// order below is the one that yields it). No retail call reaches this copy
// (its caller was folded away), so a source-only caller emits it. The name is
// descriptive; the original identity is unknown.
#include "Lib/Coord2D.h"

static __declspec(noinline) int Rva0007E06DCrossSign(const Coord2D *a, const Coord2D *c, const Coord2D *b)
{
	return (int)((b->y - a->y) * (c->x - a->x) - (c->y - a->y) * (b->x - a->x));
}

// ?Rva0007E06DCrossSignCaller absent-from-retail
int Rva0007E06DCrossSignCaller(const Coord2D *a, const Coord2D *c, const Coord2D *b)
{
	return Rva0007E06DCrossSign(a, c, b);
}
