// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00311B70@Rva00311DD9@@QAEXXZ, retail 0x00311B70 (617 B), ends where draw 0x00311DD9 begins.
// Spline end-point extension (WB twin 0xEB38C0): the first and last control points of the
// 184-byte records at +0x2C are pushed outward along the end directions by the length of the
// neighbouring segment. WB-literal separate locals; canonical Coord3D with set/scale and the
// coord3d.cpp length/normalize bodies visible inline (/O1 still calls 0x3571/0x35B6), plus a
// by-reference subtract like WB MathCoord3D.h Coord3D::Sub. Kept apart from the draw unit so its
// non-retail inline helper COMDAT copies do not cost that unit its link. Address-derived name.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
extern "C" double __cdecl fabs(double);
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"
struct SplineRecord {float duration;float steps[10];Coord3D samples[10];Coord3D point;unsigned tail[2];};
struct SplineState {char pad[0x18];float time,segmentBegin;unsigned segment;bool enabled;char pad25[7];_STL::vector<SplineRecord> records;unsigned pad38;float sampleBegin;int sample;unsigned pad44;Coord3D result;};
class View;extern View *TheTacticalView;
struct SplineViewCalls {virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void draw(const Coord3D*,const Coord3D*,unsigned);virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual void p40();virtual void p44();virtual void p48();virtual void p4c();virtual void p50();virtual void p54();virtual void p58();virtual void p5c();virtual void p60();virtual void p64();virtual void p68();virtual void p6c();virtual void visit(unsigned);};
class Rva0022B3F6Subsystem {public:bool rva00311974(SplineState*,bool,float*);};
extern Rva0022B3F6Subsystem *TheSplineService;
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
struct SplineTerrainCalls {virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual float height(float,float,void*);};
float Rva000930C0(float,float);
class Rva00311DD9:public SplineState {public:void rva00311B70();void draw(float);};

// Out-of-line rowed owners (coord3d.cpp 0x00003571/0x000035B6); visible here as
// the inline header bodies, which /O1 keeps as calls.
inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

inline void Coord3D::set(const Coord3DBase *that)
{
    x = that->x;
    y = that->y;
    z = that->z;
}

inline void Coord3D::scale(float s)
{
    x *= s;
    y *= s;
    z *= s;
}

// Coord3D::Sub(const Coord3DBase &) of the BFME 2 math header, which the canonical Coord3D lacks.
// ?subtract absent-from-retail
inline Coord3D &subtract(Coord3D &that, const Coord3D &other)
{
    that.x -= other.x;
    that.y -= other.y;
    that.z -= other.z;
    return that;
}

// Extends the curve's end segments: the first and last control points are
// pushed out along the end directions by the length of the neighbouring segment.
void Rva00311DD9::rva00311B70()
{
    Coord3D point;
    point.set(&asBase(records[1].point));
    Coord3D second;
    second.set(&asBase(records[2].point));
    Coord3D delta;
    delta.set(&asBase(point));
    subtract(delta, second);
    float length = delta.length();
    Coord3D first;
    first.set(&asBase(records[0].point));
    delta = point;
    subtract(delta, first);
    delta.normalize();
    delta.scale(length);
    subtract(point, delta);
    records[0].point = point;

    int count = records.size();
    Coord3D endPoint;
    endPoint.set(&asBase(records[count - 2].point));
    Coord3D beforeLast;
    beforeLast.set(&asBase(records[count - 3].point));
    delta = endPoint;
    subtract(delta, beforeLast);
    float endLength = delta.length();
    Coord3D last;
    last.set(&asBase(records[count - 1].point));
    delta = endPoint;
    subtract(delta, last);
    delta.normalize();
    delta.scale(endLength);
    subtract(endPoint, delta);
    records[count - 1].point = endPoint;
}
