// ?ClosestPointOnLineSegment@@YA?AVCoord2D@@ABULineSegment2D@@ABV1@@Z
// partial score=1.0 date=2026-10-17
// Reviewed Oct17: native256B6B3100..6B3200, export1138. Actual raw byte
// comparison resolves all calls through separately verified canonical39B
// Coord2D +/- providers at1040AE/7DEC8. The canonical ctor/dtor view is used.
// This complete 2D-distance source is NOT landable yet: visible inline +/-
// in the x87 caller emit29B copies, while retail's kept scalar-SSE bodies
// are39B. Paired link_check correctly refuses those copies. External-only
// declarations restore the old6-instruction tail interleave; imported inline
// definitions emit259B via6B indirect calls; extern templates lose visibility;
// SSE TU flags emit253B and SSE math rather than native x87. Scalar SSE
// intrinsics emit70B aligned-frame helpers. No check was weakened. The
// production distance unit is restored; only the real SSE providers land.
// cl: /O2 /G7 /MD /EHsc /I.
struct Coord2DBase { float x; float y; };
class Rva009F4070PositionProvider {
public:
 virtual void slot0();
 virtual const Coord2DBase *position();
};
float Rva009F4070DistanceSquared(const Coord2DBase *a,
 Rva009F4070PositionProvider *provider)
{
 const Coord2DBase *b = provider->position();
 float dy = b->y - a->y;
 float dx = b->x - a->x;
 return dx * dx + dy * dy;
}

// ClosestPointOnLineSegment, native6B3100..6B3200, export1138. The WB
// MathCoord2D.h twin and retail calls1040AE/7DEC8 establish the by-value
// Coord2D lifetime ABI. Existing x87 2D-distance unit keeps native precision;
// the canonical ctor view supplies the same non-POD representation.
// A distinct projection quotient gives retail's interleaved result copies.
#define COORD2D_VIEW_DTOR
#include "Code/Libraries/Include/Lib/Coord2DCtorView.h"
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
