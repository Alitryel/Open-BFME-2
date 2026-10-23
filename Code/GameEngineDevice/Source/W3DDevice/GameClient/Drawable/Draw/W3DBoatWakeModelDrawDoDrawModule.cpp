// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// ?doDrawModule@W3DBoatWakeModelDraw@@UAEXPBVMatrix3D@@@Z, retail
// 0x000D0D24..0x000D100A (742 bytes), thiscall RET 4; vtable entry
// 0x007CDD9C of the rowed W3DBoatWakeModelDraw module (deleting dtor
// 0x000D0D08 two slots before its name getters). WB 0x0095EF10 is the debug
// twin (Locomotor::getMaxSpeed, Matrix3D::Get_Z_Rotation, cos, sin).
// Target facts: module data +0x04 (wake offset +0x0C), drawable +0x08 whose
// object is at +0xFC, last speed ratio +0x0C and render object +0x14 (slot
// 21, Set_Transform). The speed ratio steps toward the locomotor's current
// over maximum speed by at most the .data float at VA 0x00DB52E8 (0.005);
// the wake transform is identity, moved to the drawable, turned to its Z
// rotation, offset and scaled by the ratio. Matrix3D/Vector3 inlines are the
// real Zero Hour WWMath headers. Locomotor and render object views keep the
// rowed address-derived spellings.
//
// The speed-ratio test calls fabsf directly. The C++ fabs(float) overload
// inlines through fabsf to the same call, but its extra inline level makes
// cl issue the first argument pop after the fxch instead of before it.
#include "always.h"
#include "vector3.h"
#include "matrix3d.h"
#include <math.h>

typedef float Real;

// Native writable speed-ratio step; retail RVA 0x009B52E8 is 0A D7 A3 3B.
Real g_Va00DB52E8 = 0.005f;

class Object;
struct Rva0028AC4EEntry;
class Rva0008BB38FloatField { public: Real get() const; };
class Locomotor { public: Real getMaxSpeed(Object *obj) const; };

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	char m_pad00[0xFC];
	Object *m_object;					// +0xFC
};

class RenderObjClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual void Set_Transform(const Matrix3D &m);	// +0x54
};

class W3DBoatWakeModelDrawModuleData
{
public:
	char m_pad00[0x0C];
	Vector3 m_wakeOffset;				// +0x0C
};

class W3DBoatWakeModelDraw
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);

private:
	const W3DBoatWakeModelDrawModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;				// +0x08
	Real m_speedRatio;					// +0x0C
	int m_10;
	RenderObjClass *m_renderObject;		// +0x14
};

static __forceinline void translateWake(Matrix3D &mtx,float x,float y,float z){mtx[0][3]+=(mtx[0][0]*x)+((mtx[0][1]*y)+((*(const volatile float *)&(mtx[0][2]))*z));
mtx[1][3]+=mtx[1][0]*x+mtx[1][1]*y+mtx[1][2]*z;
mtx[2][3]+=mtx[2][0]*x+mtx[2][1]*y+mtx[2][2]*z;}
void W3DBoatWakeModelDraw::doDrawModule(const Matrix3D *transformMtx)
{
	Vector3 offset = m_moduleData->m_wakeOffset;
	Object *obj = m_drawable->getObject();
	const Rva0028AC4EEntry *locomotor = obj->rva0028AC4E();
	Real speedRatio = ((const Rva0008BB38FloatField *)locomotor)->get()
		/ ((const Locomotor *)locomotor)->getMaxSpeed(obj);
	if (fabsf(speedRatio - m_speedRatio) > g_Va00DB52E8)
	{
		if (speedRatio > m_speedRatio)
			speedRatio = m_speedRatio + g_Va00DB52E8;
		else
			speedRatio = m_speedRatio - g_Va00DB52E8;
	}
	Matrix3D mtx(true);
	mtx.Translate(transformMtx->Get_Translation());
	mtx.Rotate_Z(transformMtx->Get_Z_Rotation());
	translateWake(mtx,offset.X,offset.Y,offset.Z);
	mtx.Scale(speedRatio);
	m_speedRatio = speedRatio;
	if (m_renderObject)
		m_renderObject->Set_Transform(mtx);
}
