// ?rva0050A4A2@Made002CC8A4@@UAEXPAXPBUCoord3D@@@Z
// partial score=0.995 date=2026-10-15
// cl: /O1 /MD /EHsc /DNDEBUG /arch:SSE /I.
//
// ?rva0050A4A2@Made002CC8A4@@UAEXPAXPBUCoord3D@@@Z, retail 0x0050A4A2..
// 0x0050A791 (751 bytes, RET 8): slot 6 of Made002CC8A4's (MetaImpactNugget)
// vtable 0x008649A0, reached from slot 5 (rowed 0x00509DF8) with the
// victim position. Gathers the objects within this nugget's +0x12C radius
// (at least 1) of the position through a reject-by-kindof filter (one-bit
// mask 0x59) and the partition query (3D bounding-sphere distance unless the
// +0x144 value is non-zero), and hands every object slot 1 (rowed
// 0x00509E43) accepts to slot 15 (rowed 0x0050A1E9). With a +0x130 cone
// angle below PI an object passes only when the normalised direction to it
// from the position lies inside the cone around the source object's
// position-to-impact direction (its transform Y column when that is zero),
// or outside it when the +0x134 flag is set.
#include "Code/Libraries/Include/Lib/Coord3DInline.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;

float Cos(float value);
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

struct Vector3
{
	float X, Y, Z;
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	static float Dot_Product(const Vector3 &a, const Vector3 &b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	unsigned char m_pad00[0x04];
	float m_transform[3][4]; // +0x04
	unsigned char m_pad34[0x38 - 0x34];
	Coord3D m_pos; // +0x38
};

// The weapon source record handed to the nugget: its source ObjectID at +0x08.
struct Rva0050A4A2Source
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};

// BFME 2's partition filter base (ctor 0x000421C8): a vptr and the +0x04 link.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *m_next;
};
// The 224-bit KindOf mask and the one-bit mask builder 0x00045411.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
struct Rva00045411BitSet : public BfmeFixedStorage0004543D
{
	Rva00045411BitSet(int unused, int bit) throw();
};
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
// The out-of-line constructor 0x00395A35.
class PartitionFilterRejectByKindOf : public Rva000421C8
{
public:
	PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &require, const BfmeFixedStorage0004543D &reject);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_require;
	BfmeFixedStorage0004543D m_reject;
};

class Made002CC8A4
{
public:
	virtual ~Made002CC8A4();
	virtual bool rva00509E43(int source, Object *obj);	// slot 1
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void rva0050A4A2(void *source, const Coord3D *pos);	// slot 6
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void rva0050A1E9(void *source, Object *obj);	// slot 15
private:
	unsigned char m_pad04[0x12C - 0x04];
	float m_radius; // +0x12C
	float m_coneAngle; // +0x130
	bool m_outsideCone; // +0x134
	unsigned char m_pad135[0x144 - 0x135];
	float m_144; // +0x144
};

void Made002CC8A4::rva0050A4A2(void *source, const Coord3D *pos)
{
	if (!source || !pos)
		return;
	float radius = m_radius;
	if (radius < 1.0f)
		radius = 1.0f;
	PartitionFilterRejectByKindOf filter(Rva00045411BitSet(0, 0x59), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE);
	bool centerDistance = m_144 != 0.0f;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(pos, radius, centerDistance ? 1 : 3, &filter, 0);
	Object *obj;
	while ((obj = iter.next()) != 0)
	{
		if (!rva00509E43((int)source, obj))
			continue;
		if (m_coneAngle < 3.14159265359f)
		{
			Coord3D toObj;
			toObj.set(obj->getPosition());
			toObj.sub(pos);
			Object *src = TheGameLogic->findObjectByID(((const Rva0050A4A2Source *)source)->m_sourceID);
			if (!src)
				continue;
			Coord3D diff;
			diff.set(pos);
			diff.sub(src->getPosition());
			Coord3D tmp;
			tmp.set(&diff);
			Vector3 dir(diff.x, diff.y, diff.z);
			if (tmp.length() == 0.0f)
				dir.Set(src->m_transform[0][1], src->m_transform[1][1], src->m_transform[2][1]);
			Vector3 toV(toObj.x, toObj.y, toObj.z);
			dir.Normalize();
			toV.Normalize();
			float dot = Vector3::Dot_Product(toV, dir);
			if (!(dot >= Cos(m_coneAngle)))
			{
				if (!m_outsideCone)
					continue;
			}
			else if (m_outsideCone)
				continue;
		}
		rva0050A1E9(source, obj);
	}
}
