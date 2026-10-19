// ?rva0028F326@Rva0028F326Owner@@QAEEIM@Z
// partial score=0.97 date=2026-10-19
// ?rva0028F326@Rva0028F326Owner@@QAEEIM@Z
// partial score=0.9438 date=2026-10-18
// ?rva0028F326@Rva0028F326Owner@@QAEEIM@Z
// partial score=0.9432 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 28F326..28F44C 294B RET8; complete WB CE75F0 twin.
// 2026-10-19 seat12: WB's MathCoord3D.h calls (copy-constructed delta,
// operator-= 0x41F630, dot 0x41FB90 = x*r.x+y*r.y+z*r.z) via
// Lib/Coord3DCtorView.h + an inline Coord3D::operator*(Coord3DBase): 294B,
// 8 -> 3 differing lines; only retail's visionAngle movss sits after the
// first dot fmul (ours before it). Inert: visionAngle local before/after
// the dot, 3.141f/360 form, Bool result, dot operand orders, /G5-/G7,
// 3-arg or set() facing (worse), data-> re-read (worse).
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
#include "Coord3DBase.h"
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

inline float Coord3D::operator*(const Coord3DBase &r) const { return x*r.x+y*r.y+z*r.z; }
struct Vec2 {float x,y;};
extern bool Rva004DF8D8Test(const Vec2*,const Vec2*,const Vec2*,float,float,float,float);
extern float Cos(float),Sin(float);
class Thing {public:const Coord3D*getUnitDirectionVector2D()const;};
class Object {public:float getVisionRange()const;};
struct RangeTemplate {char pad[0x53C];float visionAngle;};
struct FacingVector {float x,y,z;FacingVector():x(0),y(0),z(0){}
 float dot(const Coord3D&a)const{return a.x*x+a.y*y+a.z*z;}};
class Rva0028F326Owner {public:unsigned char rva0028F326(unsigned,float);
 char pad00[4];const RangeTemplate*data;char pad08[0x38-8];Coord3D position;char pad44[0xB8-0x44];float radius;char padBC[0x1C0-0xBC];float angle;};
unsigned char Rva0028F326Owner::rva0028F326(unsigned targetWord,float range)
{
 const RangeTemplate*type=data;
 if(range<0.0f)range=((const Object*)this)->getVisionRange();
 const Rva0028F326Owner*target=(const Rva0028F326Owner*)targetWord;
 float sourceRadius=radius;float targetRadius=target->radius;
 const Coord3D*sourcePos=&position;
 const Coord3D*targetPos=&target->position;
 if(!Rva004DF8D8Test((const Vec2*)targetPos,(const Vec2*)sourcePos,
    (const Vec2*)((const Thing*)this)->getUnitDirectionVector2D(),range,1.0f,1.0f,sourceRadius+targetRadius))return 0;
 if(type->visionAngle>=360.0f)return 1;
 Coord3D delta=*targetPos;
 delta-=*sourcePos;
 delta.z=0.0f;
 delta.Normalize();
 Coord3D facing;
 facing.x=Cos(angle);
 facing.y=Sin(angle);
 facing.z=0.0f;
 range=delta*asBase(facing);
 return range>=Cos(type->visionAngle*0.008725001f);
}
