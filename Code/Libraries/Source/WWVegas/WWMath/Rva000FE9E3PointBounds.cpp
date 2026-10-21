// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep
// Clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76 donor:
// game/Libraries/Source/WWVegas/WWMath/AABoxClassPointsConstructor.cpp,
// compiled with its original header directory first under O1/G7/SSE/MD.
// Target Ghidra FE9E3+248 meets FEADB; RET8 and callers FF1FA/10CF3E
// establish a thiscall point-array/count ABI. The body reads 12B points and
// stores midpoint/half extent at this+0..14, returning this in EAX.
// Donor AABox purpose is preserved. Original target class/method names,
// constructor-versus-initializer identity and full object size are unknown:
// this address-labelled record models only the proven 24B storage prefix.
// Fresh full donor compilation resolves the old 214B scalar-shape refusal.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
#include "vector3.h"

namespace {
// TU-local three-float value temporaries preserve donor evaluation and copy
// semantics without exporting the incompatible public Vector3 arithmetic
// copies. These helpers have no target identity or byte credit.
class BoundsValue {
public:
 float X,Y,Z;
 __forceinline BoundsValue() {}
 __forceinline BoundsValue(const BoundsValue &boundsValue) { X=boundsValue.X;Y=boundsValue.Y;Z=boundsValue.Z; }
 __forceinline BoundsValue(float x,float y,float z) { X=x;Y=y;Z=z; }
 __forceinline BoundsValue &operator=(const BoundsValue &v) {X=v.X;Y=v.Y;Z=v.Z;return *this;}
};
// ?add present-unmatched
static __forceinline BoundsValue add(const Vector3 &lhs,const Vector3 &rhs){return BoundsValue(lhs.X+rhs.X,lhs.Y+rhs.Y,lhs.Z+rhs.Z);}
// ?sub present-unmatched
static __forceinline BoundsValue sub(const Vector3 &lhs,const Vector3 &rhs){return BoundsValue(lhs.X-rhs.X,lhs.Y-rhs.Y,lhs.Z-rhs.Z);}
// ?scale present-unmatched
static __forceinline BoundsValue scale(const BoundsValue &boundsValue,float k){return BoundsValue(boundsValue.X*k,boundsValue.Y*k,boundsValue.Z*k);}
}

class Rva000FE9E3PointBounds
{
public:
    Rva000FE9E3PointBounds *rva000FE9E3(Vector3 *points, int num);
    BoundsValue Center;
    BoundsValue Extent;
};

Rva000FE9E3PointBounds *Rva000FE9E3PointBounds::rva000FE9E3(Vector3 *points, int num)
{
    Vector3 Min = points[0];
    Vector3 Max = points[0];
    for (int i = 1; i < num; ++i) {
        if (Min.X > points[i].X) Min.X = points[i].X;
        if (Min.Y > points[i].Y) Min.Y = points[i].Y;
        if (Min.Z > points[i].Z) Min.Z = points[i].Z;
        if (Max.X < points[i].X) Max.X = points[i].X;
        if (Max.Y < points[i].Y) Max.Y = points[i].Y;
        if (Max.Z < points[i].Z) Max.Z = points[i].Z;
    }
    Center = scale(add(Max, Min), 0.5f);
    Extent = scale(sub(Max, Min), 0.5f);
    return this;
}
