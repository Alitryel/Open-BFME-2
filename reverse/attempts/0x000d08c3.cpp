// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z
// partial score=0.9587909409209768 date=2026-10-14
// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z
// partial score=0.97 date=2026-10-14
// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z
// partial score=0.9 date=2026-10-14
// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw /ICode
// NEAR (helper draft, not under Code/): 617 of 625 bytes; same frame,
// calls, branches and Rotate_Z tail. Remaining: (1) the two axis dot
// products use different xmm registers/load order (retail keeps axis.z in
// xmm4 and loads Row[1][1] early); (2) the turn-limit else branch reloads
// (+0x190 then +0x2E8) where cl reuses xmm0 = m_lastAngle (8 bytes). Needs
// the class-gate Coord3D allow (Normalize/dtor) as written.
// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z retail 0x000D08C3..0x000D0B34 (625 bytes, ret 4).
// A draw-module vtable slot (entry at 0x007CDD64) that limits how far a
// transform may turn about Z. It measures the matrix's X column against the
// fixed normalized (0.5 0.5 0) axis (function-local static, normalized
// through the rowed Coord3D::Normalize 0x00005A70 on every call): the
// clamped dot gives the angle (acos then the rowed normalizeAngle
// 0x00238954), capped by the module data's +0x188 and mirrored when the Y
// column's dot is negative; after the first call the change from the last
// angle (+0x2E8; +0x2EC marks it valid) is limited to the module data's
// +0x190 per call. The result is stored and applied as WWMath's inline
// Matrix3D::Rotate_Z (cos/sin imports). WorldBuilder twin 0x0095E7A0 is
// unnamed; owner and member names are not recovered.

extern "C" double __cdecl acos(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);

typedef float Real;

#include "Libraries/Include/Lib/Coord3D.h"
struct TurnAxis : Coord3D {TurnAxis(Real a,Real b,Real c){x=a;y=b;z=c;}~TurnAxis(){}Real dot(const Coord3D&o)const{return x*o.x+y*o.y+z*o.z;}};

#include <math.h>
__declspec(noinline) inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
__declspec(noinline) inline float Coord3D::GetLength() const
{
	float x_value = x;
	float y_value = y;
	float z_value = z;
	return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}
__declspec(noinline) inline float Coord3D::Normalize()
{
	float len = GetLength();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	z *= scale;
	return len;
}

Real normalizeAngle(Real angle);

class Matrix3D
{
public:
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;

		c = (float)cos(theta);
		s = (float)sin(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)(c * tmp1 + s * tmp2);
		Row[0][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)(c * tmp1 + s * tmp2);
		Row[1][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)(c * tmp1 + s * tmp2);
		Row[2][1] = (float)(-s * tmp1 + c * tmp2);
	}

	volatile float Row[3][4];
};

struct Rva000D08C3Data
{
	char m_pad[0x188];
	Real m_maxAngle; // +0x188
	Real m_pad18C;
	Real m_maxTurn; // +0x190
};

class Rva000D08C3
{
public:
	void rva000D08C3(Matrix3D *mat);

private:
	void *m_vtable;
	const Rva000D08C3Data *m_data; // +0x04
	char m_pad08[0x2E8 - 0x08];
	Real m_lastAngle; // +0x2E8
	bool m_hasLastAngle; // +0x2EC
};

void Rva000D08C3::rva000D08C3(Matrix3D *mat)
{
	static TurnAxis axis(0.5f, 0.5f, 0.0f);
	axis.Normalize();
	Real cosAngle = axis.dot(TurnAxis(mat->Row[0][0], mat->Row[1][0], mat->Row[2][0]));
	Real sinAngle = axis.dot(TurnAxis(mat->Row[0][1], mat->Row[1][1], (m_data ? (mat->Row[2][1]) : (mat->Row[2][1]))));
	const Rva000D08C3Data *data = m_data;
	if (-1.0f > cosAngle)
		cosAngle = -1.0f;
	else if (cosAngle > 1.0f)
		cosAngle = 1.0f;
	Real angle = normalizeAngle((Real)acos(cosAngle));
	if (angle > data->m_maxAngle)
		angle = data->m_maxAngle;
	if (sinAngle < 0.0f)
		angle = normalizeAngle(-angle);
	if (m_hasLastAngle)
	{
		if (fabs(angle - m_lastAngle) > data->m_maxTurn)
		{
			if (angle < m_lastAngle)
				angle = m_lastAngle - data->m_maxTurn;
			else
				angle = data->m_maxTurn + m_lastAngle;
		}
	}
	m_lastAngle = angle;
	mat->Rotate_Z(m_lastAngle);
	m_hasLastAngle = true;
}
