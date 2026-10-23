// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/sweep
// Clean BFME1 CatmullRom003A14C0.cpp at revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, compiled O1/G7/SSE/MD.
// Target Ghidra311638+679: seven cdecl stack slots; either the PE-proven
// D3DXVec3CatmullRom thunk or the identical Catmull-Rom polynomial.
// Target EAX returns out on the polynomial path and the SDK pointer on the
// imported path. Original function name and reachability remain unknown;
// no direct E8/E9 caller was found. Inputs/output access three floats at0/4/8.
// TU-private value arithmetic preserves donor operation/copy ordering without
// exporting incompatible public Vector3 arithmetic or constructor COMDATs.
// These private helpers have no target identity or byte credit.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
#include "d3dx8math.h"
extern "C" D3DXVECTOR3 * __stdcall rva0062AFC8D3DXVec3CatmullRom(D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,const D3DXVECTOR3 *,float);
namespace {
class CurveValue {
public:
 float X,Y,Z;
 __forceinline CurveValue(const D3DXVECTOR3 &d3DXVECTOR3){X=d3DXVECTOR3.x;Y=d3DXVECTOR3.y;Z=d3DXVECTOR3.z;}
 __forceinline CurveValue(const CurveValue &curveValue){X=curveValue.X;Y=curveValue.Y;Z=curveValue.Z;}
 __forceinline CurveValue(float x,float y,float z){X=x;Y=y;Z=z;}
};
// ?operatorPlus present-unmatched
static __forceinline CurveValue operator+(const CurveValue &a,const CurveValue &b){return CurveValue(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
// ?operatorMinus present-unmatched
static __forceinline CurveValue operator-(const CurveValue &a,const CurveValue &b){return CurveValue(a.X-b.X,a.Y-b.Y,a.Z-b.Z);}
// ?operatorTimes present-unmatched
static __forceinline CurveValue operator*(const CurveValue &a,float k){return CurveValue(a.X*k,a.Y*k,a.Z*k);}
// ?operatorLeftTimes present-unmatched
static __forceinline CurveValue operator*(float k,const CurveValue &a){return CurveValue(a.X*k,a.Y*k,a.Z*k);}
}
D3DXVECTOR3 *rva00311638CatmullRom(D3DXVECTOR3 *out,const D3DXVECTOR3 *d3DXVECTOR3,const D3DXVECTOR3 *p1,const D3DXVECTOR3 *p2,const D3DXVECTOR3 *p3,float t,bool imported)
{
 if(imported) return rva0062AFC8D3DXVec3CatmullRom(out,d3DXVECTOR3,p1,p2,p3,t);
 float t2=t*t;
 float t3=t*t2;
 CurveValue a=*d3DXVECTOR3,b=*p1,c=*p2,d=*p3;
 CurveValue q0=2.0f*b;
 CurveValue q1=(c-a)*t;
 CurveValue q2=(2.0f*a-5.0f*b+4.0f*c-d)*t2;
 CurveValue q3=(3.0f*b-a-3.0f*c+d)*t3;
 CurveValue v=(q0+q1+q2+q3)*0.5f;
 out->x=v.X;out->y=v.Y;out->z=v.Z;
 return out;
}
