// ?rva00507D84@Made002CC5E1@@UAEXPAXPBUCoord3D@@@Z
// partial score=0.9404761904761905 date=2026-10-19
// cl: /O1 /arch:SSE /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// stlport
//
// ??0Made002CC5E1@@QAE@XZ retail 0x00507C2D 343B
// DamageNugget ctor over rowed base Rva00507823 0x0050775B (vtable 0x00864010
// then derived vtable 0x00864048). Derived floats at +0x128/+0x130/+0x134
// zero plus -1.0f at +0x12C/+0x140/+0x144 via 0x00BBB9AC plus pi at +0x138
// via 0x00BC7468 plus 1.0f at +0x150/+0x198 via 0x00BBB8D8 plus ints
// 0x16 at +0x158 and 0x1D at +0x160 plus vector at +0x168 via rowed
// Vector_base 0x00211E58 plus 0x1C member at +0x178 via rowed 0x0024C7B3
// plus filter at +0x19C via pinned 0x003623E5 plus duplicate memset 0x1C
// at +0x178 plus two FixedStorage temps from 0x009FEFA4 via rowed copy
// 0x0004543D consumed by pinned initFromStorages 0x00362087. Evidence:
// base rowed 0x0050775B plus derived vtables 0x00864048/0x00864C38/
// 0x008650B8 plus callers parseDamageNugget 0x002CC606 plus derived
// Made002CCA37 0x0050B1FF and Made002CCCF3 0x0050BF92 call here.
#include <vector>
#include <string.h>

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper() { clear80(); }
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

extern unsigned char g_00DFEFA4StoragePrototype[28];

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	BfmeFixedStorage0004543D(int,int,int);
private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
private:
	unsigned char m_data[0x1C];
};

#include "ascii_string.h"


// "DamageScalar" entries (Made002CC5E1DamageScalar.cpp): a filter handle
// plus a Real; the 8-byte stride is read off push_back 0x0050882B.
struct Made002CC5E1DamageScalar
{
	Rva003623E5Member filter;
	float scalar;
};

// Current canonical GameLogic view; no duplicate converged datum.
#include "GameLogicObjectLookupView.h"
typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x, y, z;
	Real length() const;
	void set(const Coord3D &a){x=a.x;y=a.y;z=a.z;}
	void sub(const Coord3D &p){x-=p.x;y-=p.y;z-=p.z;}
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real Length2() const { return X * X + Y * Y + Z * Z; }
	void Normalize();
	Real X, Y, Z;
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

__forceinline void Vector3::Normalize()
{
	Real len2 = Length2();
	if (len2 != 0.0f)
	{
		Real oolen = WWMath::Inv_Sqrt(len2);
		X *= oolen;
		Y *= oolen;
		Z *= oolen;
	}
}

inline Real Dot_Product(const Vector3 &a, const Vector3 &b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

Real Cos(Real angle);

class Rva00507D84TemplateView
{
public:
	unsigned char pad00[0x10A];
	unsigned char kind10A;
	unsigned char pad10B[0x11D - 0x10B];
	unsigned char kind11D;
};

class Thing
{
public:
 virtual Real calculateHeightAboveTerrain() const;
 Real getHeightAboveTerrain() const;
 Rva00507D84TemplateView *m_template;
 Real m_transform[3][4];
 Coord3D m_position;
 unsigned char pad44[0x54-0x44];
 mutable float m_cachedAltitudeAboveTerrain;
 float m_cachedAltitudeAboveTerrainOrWater;
 mutable int m_cacheFlags;
};
inline Real Thing::getHeightAboveTerrain() const
{
 if (!(m_cacheFlags & 2)) {
  m_cachedAltitudeAboveTerrain=calculateHeightAboveTerrain();
  m_cacheFlags|=2;
 }
 return m_cachedAltitudeAboveTerrain;
}
class Object : public Thing
{
public:
 const Coord3D *getPosition() const {return &m_position;}
 unsigned char pad60[0x250-0x60];
 void *m_contain;
};
extern GameLogic *TheGameLogic;
class GlobalData
{
public:
	unsigned char pad00[0xB40];
	Real m_singleTargetRadius;		// +0xB40
};
extern GlobalData *TheGlobalData;

class Rva000421C8
{
public:
	~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *m_next;
};

class Rva0006EE7A { public: Rva0006EE7A(int,int,int); private: unsigned char bytes[28]; };
static inline const BfmeFixedStorage0004543D &damageStorage(const Rva0006EE7A &v) {return reinterpret_cast<const BfmeFixedStorage0004543D &>(v);}
#include "RTS/XYDistanceCallView.h"
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &mustBeSet, const BfmeFixedStorage0004543D &mustBeClear);
	virtual bool allow(Object *obj);
private:
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeWideResult
{
	~BfmeWideResult();
	Object *next();
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, Real radius, Int mode, Rva000421C8 *filter, Int flags);
};
extern PartitionManager *ThePartitionManager;

struct Rva00507D84WeaponView
{
	unsigned char pad00[8];
	ObjectID sourceID08;
};


class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	Rva001EAE6FHelper m_bits04;
	Rva001EAE6FHelper m_bits84;
	int m_104;
	_STL::vector<AsciiString> m_vec108;
	_STL::vector<AsciiString> m_vec114;
	Rva003623E5Member m_filter120;
	bool m_124;
};

class Made002CC5E1 : public Rva00507823
{
public:
	Made002CC5E1();
	virtual Bool v1(void *weapon, Object *target);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void rva00507D84(void *weapon, const Coord3D *position);
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual Bool v14(void *weapon, Object *target, const Coord3D *position);

private:
	float m_128;
	float m_12C;
	float m_130;
	float m_134;
	float m_138;
	bool m_13C;
	char m_pad13D[3];
	float m_140;
	float m_144;
	bool m_148;
	char m_pad149[3];
	float m_14C;
	float m_150;
	int m_154;
	int m_158;
	int m_15C;
	int m_160;
	int m_164;
	_STL::vector<Made002CC5E1DamageScalar> m_vec168;
	float m_174;
	Rva0024C7B3Member m_178;
	bool m_194;
	char m_pad195[3];
	float m_198;
	Rva003623E5Member m_19C;
	bool m_1A0;
};

Made002CC5E1::Made002CC5E1()
	: m_128(0.0f)
	, m_12C(-1.0f)
	, m_130(0.0f)
	, m_134(0.0f)
	, m_138(3.1415927f)
	, m_13C(false)
	, m_140(-1.0f)
	, m_144(-1.0f)
	, m_148(true)
	, m_14C(0.0f)
	, m_150(1.0f)
	, m_154(0)
	, m_158(0x16)
	, m_15C(0)
	, m_160(0x1D)
	, m_164(0)
	, m_174(0.0f)
	, m_194(false)
	, m_198(1.0f)
	, m_1A0(false)
{
	memset(&m_178, 0, 0x1C);
	m_19C.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
}

void Made002CC5E1::rva00507D84(void *weapon, const Coord3D *position)
{
	Real radius = m_130;
	if (1.0f > radius)
		radius = 1.0f;
	Object *source = TheGameLogic->findObjectByID(static_cast<Rva00507D84WeaponView *>(weapon)->sourceID08);
	Int mode = 3;
	if (m_1A0)
		mode = 1;
	else if (radius >= 10.0f)
	{
		if (!(source->m_template->kind11D & 8) || !(source->m_template->kind10A & 0x20) || !source->m_contain)
			mode = 4;
	}
	Rva0004584D filter(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype), damageStorage(Rva0006EE7A(0, 0x59, 0x36)));
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(position, radius, mode, &filter, 0);
	Object *obj;
	while ((obj = iter.next()) != 0)
	{
		if (m_138 < 3.14159265359f)
		{
			Coord3D toObj; toObj.set(obj->m_position); toObj.sub(*position);
			Coord3D delta; delta.set(*position); delta.sub(source->m_position);
			Vector3 facing(delta.x, delta.y, delta.z);
			if (delta.length() == 0.0f)
				facing = Vector3(source->m_transform[0][0], source->m_transform[1][0], source->m_transform[2][0]);
			Vector3 dir(toObj.x, toObj.y, toObj.z);
			facing.Normalize();
			dir.Normalize();
			Real dot = Dot_Product(dir, facing);
			if (!(dot >= Cos(m_138)))
			{
				if (!m_13C)
					continue;
			}
			else if (m_13C)
				continue;
		}
		if (!v1(weapon, obj))
			continue;
		if (m_140 != -1.0f)
		{
			Real sourceZ = source->getPosition()->z;

			Real objectZ = obj->getPosition()->z;
			if ((objectZ - sourceZ) > m_140)
				continue;
		}
		if (m_144 != -1.0f)
		{
			obj->getHeightAboveTerrain();
			if (obj->getHeightAboveTerrain() > m_144)
				continue;
		}
		if (m_134 > 0.0f)
		{
			Real minRange = m_134;
			if (reinterpret_cast<Rva000CBA20 *>(obj)->distSq(reinterpret_cast<const Rva000CBA20Point *>(position)) < minRange * minRange)
				continue;
		}
		if (!v14(weapon, obj, position))
			continue;
		if (TheGlobalData->m_singleTargetRadius >= radius)
			break;
	}
}
