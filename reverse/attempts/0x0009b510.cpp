// ?rva0009B510@Rva0009C134Host@@QAEXAAVMatrix3D@@MM@Z
// partial score=0.98 date=2026-10-19
// ?rva0009B510@Rva0009C134Host@@QAEXAAVMatrix3D@@MM@Z
// partial score=0.85 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0009B510@Rva0009C134Host@@QAEXAAVMatrix3D@@MM@Z retail 0x0009B510..0x0009B7EA
// (730 bytes, ret 0xC): the camera transform builder the rowed refresh
// 0x0009BAA4 calls on the factory product (pinned there under the
// Rva0009C134Host view). Target facts from retail: an eye offset
// (0, -sin(pitch) * distance, cos(pitch) * distance) whose Y becomes -0.5
// when zero; the +0x110 look-at point lerped from +0xF8 towards +0x104 by
// the rowed ease 0x0009AAA8 of the +0x134 zoom, then its X/Y towards the
// base's +0x1C/+0x20 by the +0x198 fade; with a +0x188 object, a translation
// matrix (0x00BC8978, 0x00BC8974, 2 * distance * ease) handed to its slot 21;
// a yaw eased from +0x11C towards 0 (and on by the fade) rotating the offset
// about Z; an identity transform and the rowed Matrix3D::Look_At 0x00712150
// with roll 0. Member meanings and the class name remain unresolved.
// Remaining residue (size-exact, 37 diff lines): retail loads offset.X into
// xmm2 right after the 0x0009AAA8 call, ahead of the x87 lerp, and adds
// [edi] at 0x0009B623; ours loads m_110.X and adds [ebp-0x10]. A separate
// eye variable for Look_At, a temporary, member-wise construction and
// Vector3 ctor spellings do not move it.
// Static Add keeps the original operand relationship across the member interpolation.
// Continuation evidence: reverse/attempt_support/0x0009b510-20261019.md (model=gpt-6.1-sol).
#include <math.h>

class Vector3
{
public:
    float X, Y, Z;
    Vector3() {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    __forceinline static void Add(const Vector3 &a, const Vector3 &b, Vector3 *r) { r->X = a.X + b.X; r->Y = a.Y + b.Y; r->Z = a.Z + b.Z; }
    __forceinline Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
    __forceinline Vector3 &operator-=(const Vector3 &v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
    __forceinline void Rotate_Z(float s, float c)
    {
        float tmp_x = X;
        float tmp_y = Y;
        X = c * tmp_x - s * tmp_y;
        Y = s * tmp_x + c * tmp_y;
    }
    __forceinline static void Lerp(const Vector3 &a, const Vector3 &b, float alpha, Vector3 *result)
    {
        result->X = (b.X - a.X) * alpha + a.X;
        result->Y = (b.Y - a.Y) * alpha + a.Y;
        result->Z = (b.Z - a.Z) * alpha + a.Z;
    }
};

class Vector4
{
public:
    float X, Y, Z, W;
    __forceinline float &operator[](int i) { return (&X)[i]; }
    __forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};
class Matrix3D
{
public:
    Matrix3D() {}
    __forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
    __forceinline void Make_Identity()
    {
        Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
        Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
        Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
    }
    __forceinline void Set_Translation(const Vector3 &t) { Row[0][3] = t.X; Row[1][3] = t.Y; Row[2][3] = t.Z; }
    void Look_At(const Vector3 &p, const Vector3 &t, float roll);
    Vector4 Row[3];
};
#define B510_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define B510_SLOTS16(p) B510_SLOTS4(p##0) B510_SLOTS4(p##1) B510_SLOTS4(p##2) B510_SLOTS4(p##3)
class Rva0009B510Object
{
public:
    B510_SLOTS16(s0) B510_SLOTS4(s1) virtual void s20();
    virtual void Set_Transform(const Matrix3D &m);	// slot 21
};
#undef B510_SLOTS16
#undef B510_SLOTS4

float __cdecl Rva0009AAA8Get(float x);

static inline float Rva0009B510Lerp(float a, float b, float t) { return (b - a) * t + a; }

// Layout view of the established factory product (see Rva0009D55BProductCtor.cpp).
class Rva0009C134Host
{
public:
    void rva0009B510(Matrix3D &tm, float distance, float pitch);

    char m_pad00[0x1C];
    float m_1C;
    float m_20;
    char m_pad24[0xF8 - 0x24];
    Vector3 m_F8;
    Vector3 m_104;
    Vector3 m_110;
    float m_11C;
    char m_pad120[0x134 - 0x120];
    float m_134;
    char m_pad138[0x188 - 0x138];
    Rva0009B510Object *m_188;
    char m_pad18C[0x198 - 0x18C];
    float m_198;
};

void Rva0009C134Host::rva0009B510(Matrix3D &tm, float distance, float pitch)
{
    float s = sin(pitch);
    float c = cos(pitch);
    Vector3 offset(0.0f, 0.0f - s * distance, c * distance);
    if (offset.Y == 0.0f)
        offset.Y = -0.5f;
    float ease = Rva0009AAA8Get(m_134);
    Vector3::Lerp(m_F8, m_104, ease, &m_110);
    m_110.X = Rva0009B510Lerp(m_110.X, m_1C, m_198);
    m_110.Y = Rva0009B510Lerp(m_110.Y, m_20, m_198);
    Vector3::Add(m_110, offset, &offset);
    if (m_188)
    {
        Matrix3D translate(true);
        translate.Set_Translation(Vector3(192.43f, 569.88f, (2.0f * distance) * ease));
        m_188->Set_Transform(translate);
    }
    offset -= m_110;
    float yaw = Rva0009B510Lerp(Rva0009B510Lerp(m_11C, 0.0f, ease), 0.0f, m_198);
    offset.Rotate_Z(sin(yaw), cos(yaw)); offset += m_110; tm.Make_Identity(); tm.Look_At(offset, m_110, 0.0f);
}
