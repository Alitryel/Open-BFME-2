// ?ClosestPointOnLineSegment@@YA?AVCoord2D@@ABULineSegment2D@@ABV1@@Z
// partial score=0.99 date=2026-10-17
// ?ClosestPointOnLineSegment@@YA?AVCoord2D@@ABULineSegment2D@@ABV1@@Z
// partial score=0.967 date=2026-10-15
// cl: /O2 /MD /EHsc
// ?ClosestPointOnLineSegment@@YA?AVCoord2D@@ABULineSegment2D@@ABV1@@Z, retail
// 0x006B3100..0x006B3200 (export 1138 names it). WB twin 0x6F6610 (file
// MathCoord2D.h asserts): operator- twice, dot products, `projection /= length`,
// a copy of direction scaled by operator*= and operator+ with the start.
// Callees: the rowed ??G/??H 0x001040AE / 0x0007DEC8 (rowed with the
// MathCoord2D view name; BFME 2's class is Coord2D per the exports).
// Residue (nd6, size exact): the y product's fmul/fstp and the final fstp st(0)
// schedule before the begin.y arg copy / result push; retail interleaves them.
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	~Coord2D() {}
	Coord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	float x;
	float y;
};
inline Coord2D operator-(Coord2D left, const Coord2D &right) { left.x -= right.x; left.y -= right.y; return left; }
inline Coord2D operator+(Coord2D left, const Coord2D &right) { left.x += right.x; left.y += right.y; return left; }

struct LineSegment2D {
	Coord2D m_start;
	Coord2D m_end;
};
Coord2D ClosestPointOnLineSegment(const LineSegment2D &segment, const Coord2D &point)
{
	Coord2D direction = segment.m_end - segment.m_start;
	Coord2D offset = point - segment.m_start;
	float projection = 0.0f;
	float length = 0.0f;
	float t = 0.0f;
	projection = direction.x * offset.x + direction.y * offset.y;
	if (projection <= 0.0f)
		return segment.m_start;
	length = direction.x * direction.x + direction.y * direction.y;
	if (projection >= length)
		return segment.m_end;
	t = projection / length;
	Coord2D scaled(direction);
	scaled.x *= t;
	scaled.y *= t;
	return segment.m_start + scaled;
}
