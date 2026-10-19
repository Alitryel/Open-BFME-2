// ?Rva004EACF5DistSqToSegment@@YAMPBUCoord2D@@00@Z
// partial score=0.90571 date=2026-10-19
// Joint candidate for native 0x004EACF5 (197 B) and 0x004EADBA (227 B).
// Descriptive Polyline/PointSource labels, not proven original class names.
// Native: helper a=EAX, b=EDX, p=ECX; compiler still swaps b/p registers.
// Correct semantic call below: a=prev, p=input point, b=current segment end.
// Coord2D constructor expression + y-square-first sum closes projection tail
// and length-squared XMM scheduling. No pins or exact/link claim.
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
static __declspec(noinline) float distSqToSegment(const Coord2D *a, const Coord2D *p, const Coord2D *b)
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
		Coord2D e(b->x-a->x,b->y-a->y);
		float len2 = e.y*e.y+e.x*e.x;
		if (dot >= len2)
		{
			cx = b->x; cy = b->y;
		}
		else
		{
			float t = dot / len2;
			Coord2D q(t*dx+a->x-p->x,t*dy+a->y-p->y);return q.y*q.y+q.x*q.x;
		}
	}
	Coord2D q(cx-p->x,cy-p->y);return q.y*q.y+q.x*q.x;

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
		float d = distSqToSegment(&prev,&p,&cur);
		if (best < 1.0f || d < best)
			best = d;
		prev = cur;
	}
	return best;
}
