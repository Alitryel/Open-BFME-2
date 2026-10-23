// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Semantic donor: BF1 f98983a7d3 AIPathfind.cpp computeNormalRadialOffset
// and circleClipsTallBuilding, with ZH pathfinding as the underlying guide.
// Native BF2 002E7A62..002E7B02 RET and callers 002E9BE5/002F3392 prove
// the offset helper's purpose, scalar position +38 and radius +B8. WB names
// the helper ComputeNormalRadialOffset and caller CircleClipsTallBuilding;
// retain neutral ABI spellings because exact source signatures remain inferred.
// Static C++ lets cl choose the measured EAX/ECX/EBX plus two-stack-arg ABI.
// Scalar position copy through canonical Coord3D makes all160 helper bytes exact.
// The normalize leaf's native no-throw callgraph supports helper throw();
// without it the caller has an extra EH state store after the second temporary.
// Native caller292 RET20 independently measures two kind66 filter temporaries
// and first-object/success lifetime. Its four-arg partition query and 28-byte
// masks use established providers; inline destruction resets base BC26E0.
typedef float Real;
#include "Coord3D.h"
#include "Coord2D.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva002E7A62Position : Coord3D
{
	Rva002E7A62Position(const Coord3D &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
	}
};
class Object
{
  public:
	unsigned char pad[0x38];
	Coord3D position;
	unsigned char pad44[0xB8 - 0x44];
	float radius;
	const Coord3D *getPosition() const
	{
		return &position;
	}
	float getRadius() const
	{
		return radius;
	}
};
// WorldBuilder ComputeNormalRadialOffset, WB VA 0x00D4E940 (callgraph lead, score 3.0).
static void ComputeNormalRadialOffset(const Coord3D &from, Coord3D &insert, const Coord3D &to, Object *obj, Real radius) throw()
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Rva002E7A62Position objPos(*obj->getPosition());
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real crossProduct = dx * objDy - dy * objDx;
	Coord3D fromToNormal;
	fromToNormal.z = 0;
	if (crossProduct > 0)
	{
		fromToNormal.x = dy;
		fromToNormal.y = -dx;
	}
	else
	{
		fromToNormal.x = -dy;
		fromToNormal.y = dx;
	}
	fromToNormal.normalize();
	insert = *obj->getPosition();
	insert.x += fromToNormal.x * radius;
	insert.y += fromToNormal.y * radius;
}

class BfmeFixedStorage0004543D
{
	unsigned char bytes[28];
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int, int) throw();
	unsigned int bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];
class Rva000421C8
{
  public:
	Rva000421C8() : next(0)
	{
	}
	virtual ~Rva000421C8()
	{
	}
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *next;
};
class Rva0004584D : public Rva000421C8
{
  public:
	Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
	virtual bool allow(Object *);
	BfmeFixedStorage0004543D a, b;
};
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
// Native 0x002F3392 uses a two-word callback context and PathNode +0x0C position.
// The layer value is witnessed as 1; its original enumerator spelling is unknown.
enum PathfindLayerEnum { PathfindLayerNativeOne = 1 };
struct Rva002F1BD5Info { Object *theTallBuilding; unsigned int ignoreBuilding; };
class PathNode {
public:
 const Coord3D *getPosition() const { return &pos; }
 void setPosition(const Coord3D *p) { pos = *p; }
private:
 unsigned char pad[0x0C];
 Coord3D pos;
};
class Pathfinder
{
  public:
	int iterateCellsAlongLine(const Coord3D *, const Coord3D *, PathfindLayerEnum, Rva002F1BD5Info *);
	bool rva002F3392(PathNode *, PathNode *, unsigned int, Coord3D *, Coord3D *, Coord3D *);
	bool CircleClipsTallBuilding(const Coord3D *, const Coord3D *, float, unsigned int, Coord3D *);
};
bool Pathfinder::CircleClipsTallBuilding(const Coord3D *from, const Coord3D *to, float circleRadius, unsigned int ignoreBuilding,
							 Coord3D *adjustTo)
{
	Object *tallBuilding =
		ThePartitionManager->getClosestObject(to, circleRadius, 1,
											  &Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 66),
														   *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype));
	if (tallBuilding)
	{
		float radius = tallBuilding->getRadius() + 20.0f;
		ComputeNormalRadialOffset(*from, *adjustTo, *to, tallBuilding, circleRadius + radius);
		Object *otherTallBuilding = ThePartitionManager->getClosestObject(
			adjustTo, circleRadius, 1,
			&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 66),
						 *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype));
		if (otherTallBuilding && otherTallBuilding != tallBuilding)
		{
			radius = otherTallBuilding->getRadius() + 20.0f;
			Rva002E7A62Position tmpTo(*adjustTo);
			ComputeNormalRadialOffset(*from, *adjustTo, tmpTo, otherTallBuilding, circleRadius + radius);
		}
		return true;
	}
	return false;
}

// Native 002F3392..002F35AF, 541B; BF1/ZH tall-building segment detour semantics.
// Target field accesses and all three insertion points are measured from retail.
// Keep building-X/radius/endpoint-X reads in the native order; the first fence
// retains the object web while textual volatile accesses order the scalar reads.
bool Pathfinder::rva002F3392(PathNode *curNode, PathNode *nextNode, unsigned int ignoreBuilding,
                            Coord3D *insertPos1, Coord3D *insertPos2, Coord3D *insertPos3)
{
    Rva002F1BD5Info info;
    info.theTallBuilding = 0;
    info.ignoreBuilding = ignoreBuilding;
    Rva002E7A62Position fromPos(*curNode->getPosition());
    Rva002E7A62Position toPos(*nextNode->getPosition());
    for (int i = 0; i < 2; i++) {
        int ret = iterateCellsAlongLine(&fromPos, &toPos, PathfindLayerNativeOne, &info);
        if (ret != 0 && info.theTallBuilding) {
            Object *tallBuilding = info.theTallBuilding;
            _ReadWriteBarrier();
            Coord3D bldgPos;
            Coord2D delta;
            float radius;
            float tx, ty;
            bldgPos.x = *(const volatile float *)&tallBuilding->position.x;
            radius = *(const volatile float *)&tallBuilding->radius + 20.0f;
            tx = *(const volatile float *)&toPos.x;
            ty = toPos.y;
            bldgPos.y = *(const volatile float *)&tallBuilding->position.y;
            delta.x = tx - bldgPos.x;
            delta.y = ty - bldgPos.y;
            if (delta.length() <= radius * 0.98) {
                if (delta.length() < 0.1) delta.x = 1;
                delta.normalize();
                float dx = ((const volatile Coord2D *)&delta)->x;
                float dy = ((const volatile Coord2D *)&delta)->y;
                dx *= radius;
                dy *= radius;
                toPos.x = bldgPos.x + dx;
                toPos.y = bldgPos.y + dy;
                nextNode->setPosition(&toPos);
                continue;
            }
            delta.x = fromPos.x - bldgPos.x;
            delta.y = fromPos.y - bldgPos.y;
            if (delta.length() <= radius * 0.98) {
                if (delta.length() < 0.1) delta.x = 1;
                delta.normalize();
                float dx = ((const volatile Coord2D *)&delta)->x;
                float dy = ((const volatile Coord2D *)&delta)->y;
                dx *= radius;
                dy *= radius;
                fromPos.x = bldgPos.x + dx;
                fromPos.y = bldgPos.y + dy;
            }
            ComputeNormalRadialOffset(fromPos, *insertPos2, toPos, tallBuilding, radius);
            ComputeNormalRadialOffset(fromPos, *insertPos1, *insertPos2, tallBuilding, radius);
            ComputeNormalRadialOffset(*insertPos2, *insertPos3, toPos, tallBuilding, radius);
            return true;
        }
    }
    return false;
}
