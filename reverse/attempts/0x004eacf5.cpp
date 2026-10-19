// ?distSqToSegment@@YAMPBUCoord2D@@00@Z
// partial score=0.948 date=2026-10-20
// ?distSqToSegment@@YAMPBUCoord2D@@00@Z (0x4EACF5, 197 B) + ?distanceSq@Polyline@@UBEMPBUCoord2D@@@Z (0x4EADBA, 227 B)
// r26 joint candidate. helper fit 0.9481 (10 insn diffs, IPRA regs now exact: p=ECX a=EAX b=EDX); caller exact except
// the unresolved local call. Params (p, a, b) = (pt, lineStart, lineEnd) as ZH Geometry.cpp calcPointToLineDistSquared;
// retail caller lea order edx(b), eax(a), ecx(p) = right-to-left of (p, a, b). Separate returns raise p's use count (8 > b's 6).
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
template <typename NUM> inline NUM sqr(NUM x) { return x * x; }
static float calcDistSquared(const Coord2D &a, const Coord2D &b) { return sqr(a.y - b.y) + sqr(a.x - b.x); }
static __declspec(noinline) float distSqToSegment(const Coord2D *p, const Coord2D *a, const Coord2D *b)
{
float dx = b->x;
float dy = b->y;
float apx = p->x - a->x;
float apy = p->y - a->y;
dx -= a->x;
dy -= a->y;
float dot = apy * dy;
dot += apx * dx;
if (dot <= 0.0f)
{
return calcDistSquared(*a, *p);
}
float len2 = calcDistSquared(*b, *a);
if (dot >= len2)
{
return calcDistSquared(*b, *p);
}
float t = dot / len2;
Coord2D c(a->x + t*dx, a->y + t*dy);
return calcDistSquared(c, *p);
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
		float d = distSqToSegment(&p,&prev,&cur);
		if (best < 1.0f || d < best)
			best = d;
		prev = cur;
	}
	return best;
}
