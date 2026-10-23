// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
// ?rva0030B232@AreaPolygonBase@@QAEXABVMatrix3D@@@Z @0x0030B232 132B
// Transform every 2D point of the polygon by a 3x4 matrix (z = 0) and mark it dirty.
// Target facts: AreaPolygonBase layout as the rowed siblings 0x0030B1A7 (scale) and
// 0x0030B92C (assign); one pointer argument, the dirty byte at +0x24; caller 0x00330BAD.
// WorldBuilder twin 0x00BF6660 shows a Vector3 (x, y, 0) per point run through WWMath's
// Matrix3D::Transform_Vector with in == out (its aliasing copy); the BFME 1 reference
// matrix3d.h supplies that inline. The original method name is unknown.
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
struct BfmePod8 { float x; float y; };
struct AreaPolygonBase
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	unsigned char m_24;
	void rva0030B232(const Matrix3D &matrix);
};
void AreaPolygonBase::rva0030B232(const Matrix3D &matrix)
{
	BfmePod8 *e = m_vec.end();
	for (BfmePod8 *p = m_vec.begin(); p != e; ++p) {
		Vector3 v(p->x, p->y, 0.0f);
		Matrix3D::Transform_Vector(matrix, v, &v);
		p->x = v.X;
		p->y = v.Y;
	}
	m_24 = 1;
}
