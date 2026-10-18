// ?distanceSq@Polyline@@UBEMPBUCoord2D@@@Z
// partial score=0.998 date=2026-10-18
// ?distanceSq@Polyline@@UBEMPBUCoord2D@@@Z
// partial score=0.97 date=2026-10-16
// W9-O1 joint bank for 0x4EADBA (227 B caller, virtual polyline min distance, RET 4) + 0x4EACF5 (197 B file-static helper).
// The caller compiles EXACT apart from the helper argument registers (retail lea edx,cur / lea eax,prev / lea ecx,p;
// ours edx=p, ecx=cur) because the helper convention cl picks gives b=ECX p=EDX where retail has b=EDX p=ECX.
// Toy rules measured (build/o1/rr3-rr5 in ws/o1): most-used pointer -> EAX; then more uses (after CSE) -> ECX; equal uses ->
// the one used in the then-branch -> ECX; parameter order only breaks exact ties. 128 spelling combos + goto/inverted
// branch forms kept b=ECX. Constants: best init -1.0f, test best < 1.0f. Owner class/identity unknown (names neutral).
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
struct Coord2D { float x, y; Coord2D() {} Coord2D(float ax, float ay) : x(ax), y(ay) {} };
struct Coord3D { float x, y, z; };
class PointSource
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual Coord3D getPosition() const;	// +0x34
};
static __declspec(noinline) float distSqToSegment(const Coord2D *b, const Coord2D *a, const Coord2D *p)
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
		float ex = b->x - a->x;
		float ey = b->y - a->y;
		float len2 = ex * ex + ey * ey;
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
class Polyline
{
public:
	virtual float distanceSq(const Coord2D *pt) const;
	PointSource *m_start;		// +4
	PointSource **m_begin;		// +8
	PointSource **m_end;		// +0xC
};
float Polyline::distanceSq(const Coord2D *pt) const
{
	float best = -1.0f;
	Coord2D p(pt->x, pt->y);
	Coord2D prev(m_start->getPosition().x, m_start->getPosition().y);
	PointSource **end = m_end;
	for (PointSource **it = m_begin; it != end; ++it)
	{
		Coord2D cur((*it)->getPosition().x, (*it)->getPosition().y);
		float d = distSqToSegment(&p, &prev, &cur);
		if (best < 1.0f || d < best)
			best = d;
		prev = cur;
	}
	return best;
}
