// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B3D1@AreaPolygonBase@@QAEXXZ, retail 0x0030B3D1..0x0030B5AF (478 B,
// RET 0): AreaPolygonBase's bounds refresh. WorldBuilder's twin 0x00BF6BA0
// (AreaPolygon code with MathCoord2D.h's inline Coord2D GetLengthSqrd /
// GetLength / Normalize asserts) gives the statement shapes: the point
// bounds, the half-extent radius (+0x20), then for every edge the squared
// distance of the centre to its end point, the edge's normalized projection
// (which only its sqrt survives in release, because the minimum is taken of
// the centre offset again) and finally sqrt(min) - 0.1 clamped at zero
// (+0x1C) and the dirty flag cleared (+0x24). Layout is shared with the
// rowed AreaPolygonBase siblings (point vector at +0, bounds +0x0C..+0x18).
// The method's original name is not established: the linker name stays
// address-derived. Callees: MathCoord2D's out-of-line operator- 0x001040AE
// and the CRT sqrt 0x0062921C.
#include <vector>
#include <math.h>
#include <float.h>
#include "../../../Libraries/Include/Lib/Region2D.h"

class MathCoord2D
{
public:
	MathCoord2D() {}
	MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float ix, float iy) : x(ix), y(iy) {}
	~MathCoord2D() {}
	float Dot(const MathCoord2D &c) const { return y * c.y + x * c.x; }
	MathCoord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	MathCoord2D &operator+=(const MathCoord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthSqrd() const { return y * y + x * x; }
	__forceinline float GetLength() const { return (float)sqrt(GetLengthSqrd()); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};
MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right);

struct AreaPolygonBase
{
	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> > m_points;
	Region2D m_bounds;		// +0x0C
	float m_innerRadius;		// +0x1C
	float m_radius;			// +0x20
	bool m_dirty;			// +0x24
	void rva0030B3D1();
};

void AreaPolygonBase::rva0030B3D1()
{
	m_bounds.lo = m_bounds.y_min = FLT_MAX;
	m_bounds.hi = m_bounds.y_max = -FLT_MAX;

	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator end = m_points.end();
	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator it;
	for (it = m_points.begin(); it != end; ++it)
	{
		if (it->x < m_bounds.lo)
			m_bounds.lo = it->x;
		if (it->y < m_bounds.y_min)
			m_bounds.y_min = it->y;
		if (it->x > m_bounds.hi)
			m_bounds.hi = it->x;
		if (it->y > m_bounds.y_max)
			m_bounds.y_max = it->y;
	}

	float halfWidth = (m_bounds.hi - m_bounds.lo) / 2.0f;
	float halfHeight = (m_bounds.y_max - m_bounds.y_min) / 2.0f;
	m_radius = sqrt(halfHeight * halfHeight + halfWidth * halfWidth);

	float minDistSqr = FLT_MAX;
	MathCoord2D center((m_bounds.lo + m_bounds.hi) * 0.5f, (m_bounds.y_min + m_bounds.y_max) * 0.5f);
	_STL::vector<MathCoord2D, _STL::allocator<MathCoord2D> >::const_iterator prev = m_points.end() - 1;
	for (it = m_points.begin(); it != end; prev = it, ++it)
	{
		MathCoord2D toCenter = center - *it;
		float distSqr = toCenter.GetLengthSqrd();
		if (distSqr < minDistSqr)
			minDistSqr = distSqr;

		MathCoord2D edge(prev->x - it->x, prev->y - it->y);
		edge.Normalize();
		float along = edge.Dot(toCenter);
		edge *= along;
		edge += *it;

		distSqr = toCenter.GetLengthSqrd();
		if (distSqr < minDistSqr)
			minDistSqr = distSqr;
	}

	m_innerRadius = sqrt(minDistSqr) - 0.1f;
	if (m_innerRadius < 0.0f)
		m_innerRadius = 0.0f;
	m_dirty = false;
}
