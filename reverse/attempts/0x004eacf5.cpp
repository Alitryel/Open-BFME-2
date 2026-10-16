// ?Rva004EACF5DistSqToSegment@@YAMPBUCoord2D@@00@Z
// partial score=0.6 date=2026-10-16
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// W9-O1 bank 0x4EACF5 (197 B): squared distance from p to segment a-b, file-static noinline -> private EAX=a EDX=b ECX=p + xmm0 float return IS emittable (old "unemittable" verdict is wrong).
// This body gives retail structure exactly (52 insns, same blocks/order) but mirrored registers: ours b=ECX p=EDX and x/y xmm roles swapped. Param order is inert; the reg choice follows body usage (most-used param a=EAX; b/p tie).
struct Coord2D { float x, y; };
static __declspec(noinline) float Rva004EACF5DistSqToSegment(const Coord2D *a, const Coord2D *b, const Coord2D *p)
{
	float dx = b->x;
	float dy = b->y;
	float apx = p->x - a->x;
	float apy = p->y - a->y;
	dx -= a->x;
	dy -= a->y;
	float dot = apx * dx + apy * dy;
	float cx, cy;
	if (dot <= 0.0f)
	{
		cx = a->x; cy = a->y;
	}
	else
	{
		float len2 = (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y);
		if (dot >= len2)
		{
			cx = b->x; cy = b->y;
		}
		else
		{
			float t = dot / len2;
			float y = t * dy + a->y - p->y;
			float x = t * dx + a->x - p->x;
			return x * x + y * y;
		}
	}
	float x = cx - p->x;
	float y = cy - p->y;
	return x * x + y * y;
}
// ?Rva004EACF5DistSqToSegmentCaller absent-from-retail
float Rva004EACF5DistSqToSegmentCaller(const Coord2D *a, const Coord2D *b, const Coord2D *p) { return Rva004EACF5DistSqToSegment(a, b, p); }
