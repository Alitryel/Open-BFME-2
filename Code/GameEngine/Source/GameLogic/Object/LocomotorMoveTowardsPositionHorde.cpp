// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
//
// Locomotor's horde portal movement, retail 0x001E7389 (484 bytes), the
// per-frame movement dispatch 0x001E9083 (2429 bytes), and the path getter
// both call.
//
// ?Rva001E3FFDGet@@YAPAXPAURva001E3FFDOuter@@@Z, retail 0x001E3FFD (24 bytes):
// the Object's +0x258 AI and that AI's +0x140 path, else null. Defined here,
// ahead of its Locomotor callers, because retail cleans up the calls to it
// with `add esp,4` after moving the result out of eax; cl 7.1 emits that
// shape (rather than `pop ecx`) only when the callee body is in the same
// unit and known to leave ecx alone. Callers: 0x001E6007 0x001E7389
// 0x001E756D 0x001E9083 (all Locomotor).
//
// ?moveTowardsPositionHordeOnClimbPortal@Locomotor@@QAE_NPAVObject@@PAVWaypoint@@@Z,
// retail 0x001E7389 (484 bytes, ret 8). Name from the WorldBuilder twin
// 0x00AE58F0 (Locomotor.cpp asserts 1963..2010); called from 0x001E764E in
// 0x001E756D (WB moveTowardsPositionHorde) when the path's next waypoint
// (TheTerrainLogic slot 35, type at +0x60) is type 3. Requires the
// waypoint's +0xB0 object to exist and the Object's +0x250 contain to hand
// out a horde contain interface (slot +0x7C). Peeks the climb position past
// the portal and takes the 16-byte path point (0x00364521); while the Object
// is farther than 10 from the climb position it is moved there (rowed
// Thing::setPosition), the transform matrix at +0x68 gets the translation,
// the layer is applied (rowed Object 0x0028B4CE), the horde interface slot
// +0x1BC gets the goal, the point's position, waypoint and layer, the frame
// deadline at +0x64 becomes TheGameLogic's frame plus 12 times the global
// 0x009BA4E4, and the result is true. Otherwise it stays true until the
// members reached the end of their path (slot +0x1CC) or the deadline
// passed, then advances the path past the portal (rowed 0x0036617B) with a
// temporary vector and returns false.
// Retail evidence: EH frame for the vector only, SSE distance test against
// 100.0f (0x00BC292C), the waypoint argument slot reused for the path.
// Callee rows: 0x00049DC5 0x00363DF9 0x00364521 0x0030AA80 0x001E34FA
// 0x0028B4CE 0x001E3511 0x001E34B2 (Rva001E34B2.cpp) 0x0036617B; the vector's
// base ctor is the ICF-folded 0x00211E58.
// Facts from retail: offsets slots and types; names of the method and the
// waypoint come from the WorldBuilder twin; the point and node views are
// address-named because their real types are unproven.
//
// ?rva001E9083@Locomotor@@QAEXPAVObject@@PBUCoord3D@@MM@Z, retail 0x001E9083
// (2429 bytes plus the 40-byte case table at 0x001E99D8, ret 0x10). Called
// from AIUpdateInterface::doLocomotor 0x0026A3A0 and quickHordeUpdate
// 0x0026C4EB. Clears flag 4 at +0x44, copies the Object's transform into
// +0x68, clamps the desired speed to the timed limit (+0x5C until frame
// +0x60) and to getMaxSpeed, then returns early when 0x001E4194 holds or the
// Object has status 0x25. Records the path's 0x001E3557 test at +0x99. For
// a wall climber (template +0x150, kindof 0xB8 and not 0x6D, not status 0x26,
// not contained by a kindof-0x6D container) it probes the step ahead (the
// unit direction times min(speed, 7)): a kindof-0xC9 wall found by the
// pathfinder (0x001E4461) there is climbed when the step lies inside its
// major radius and below its top (rising 0.6 per unit speed with status
// 0x67, otherwise turned to the wall's facing and clamped to its radius in
// wall space, with Eva event 15 for an enemy-owned local wall); without a
// wall the Object descends towards the ground (status 0x69). Climbing,
// descending and landing set the position, the 0x67/0x69 status bits, the
// drawable flag (0x00272A02) and reveal a stealthed Object; otherwise the
// bits are cleared and the template's appearance (+0x74) selects the worker:
// 0/4/7 0x001E6B8B, 6 moveTowardsPositionHorde 0x001E756D, 2 0x001E7C4C,
// 8 0x001E9045, 9 0x001E68D7, 3 0x001E7C2B, 1 0x001E8C1B, 5 none, else
// 0x001E7053; then 0x001E7ECA unless the path's 0x001E3591 test holds, and
// the transform is written back. The WorldBuilder twin 0x00ADF140 has the
// same statement shapes (wall top as height plus wall z, the clamp and bias
// ternaries); its name is not recovered, so the method keeps an address name
// (ZH's analogue is Locomotor::locoUpdate_moveTowardsPosition). Codegen: the
// bit-flag, kindof and status helpers are forceinline; the Coord3D helpers
// are field-wise so the direction vectors stay out of block copies, which
// is what gives retail's register assignment.
#include <vector>
#include <math.h>
#include "Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
// always.h (via matrix3d.h) redeclares operator new[]/delete[], which the
// STLport <new> above already provides.
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"

typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum Relationship
{
	ENEMIES = 0
};

enum EvaEventID
{
	EVA_INVALID = -1
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<ScienceType>::deallocate(ScienceType* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ScienceType*,ScienceType,allocator<ScienceType> >::deallocate(ScienceType* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<ScienceType>&>(*this),(ScienceType*)0).deallocate(__p,__n);
}
template <> __declspec(dllimport) __forceinline
_Vector_base<ScienceType,allocator<ScienceType> >::~_Vector_base() {
 if (_M_start != 0) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start);
}
}


// The float triple 0x001E34B2 returns by value (see Rva001E34B2.cpp).
struct Rva001E34B2Point
{
	Real x;
	Real y;
	Real z;
	Rva001E34B2Point(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
	Rva001E34B2Point(const Rva001E34B2Point &o) { x = o.x; y = o.y; z = o.z; }
};

// What 0x00364521 returns by value (16 bytes): a node and a position.
struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};

class Rva001E34FA
{
public:
	int rva001E34FA(); // 0x001E34FA, the node's layer
};

class Rva001E3511
{
public:
	int rva001E3511(); // 0x001E3511, the node's waypoint (0x7FFFFFFF without one)
};

class Rva001E34B2
{
public:
	Rva001E34B2Point rva001E34B2(); // 0x001E34B2, the node's position
};

class Rva0008BB38FloatField;

class Path
{
public:
	Coord3D *PeekPastClimbPortal(Coord3D *out);
	Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);
	void AdvancePastPortal(ScienceType st, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *vec);
};

struct Rva001E3FFDInner
{
	char m_pad00[0x140];
	void *m_p140; // +0x140
};

struct Rva001E3FFDOuter
{
	char m_pad00[0x258];
	Rva001E3FFDInner *m_p258; // +0x258
};

void *__cdecl Rva001E3FFDGet(Rva001E3FFDOuter *p)
{
	Rva001E3FFDInner *q = p->m_p258;
	return q ? q->m_p140 : 0;
}

// The horde interface getHordeContainInterface hands out (retail vtable
// 0x00C44C58: +0x1BC is 0x0046ECDE, +0x1CC is 0x0046A677).
class HordeContainInterface
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009();
	virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029();
	virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049();
	virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069();
	virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083(); virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087(); virtual void s088(); virtual void s089();
	virtual void s090(); virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095(); virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103(); virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107(); virtual void s108(); virtual void s109();
	virtual void s110();
	virtual void slot111(const Coord3D *goal, const Rva001E34B2Point *pos, int waypointID, int layer); // +0x1BC
	virtual void s112(); virtual void s113(); virtual void s114();
	virtual bool haveMembersReachedEndOfPath(); // +0x1CC (WB assert text)
};

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30();
	virtual HordeContainInterface *getHordeContainInterface(); // +0x7C
};

template <int NUMBITS>
class BitFlagsView
{
public:
	__forceinline Bool test(unsigned int bit) const { return (m_bits[bit >> 5] & (1 << (bit & 0x1f))) != 0; }
	__forceinline void set(unsigned int bit) { m_bits[bit >> 5] |= 1 << (bit & 0x1f); }
	__forceinline void clear(unsigned int bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1f)); }
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

class ThingTemplate
{
public:
	__forceinline Bool hasKindOf(KindOfType k) const { return m_kindof.test(k); }
private:
	char m_pad00[0x108];
	BitFlagsView<218> m_kindof; // +0x108
};

class Drawable
{
public:
	void rva00272A02(Bool b);
};
class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	Real getMajorRadius() const { return m_majorRadius; }
private:
	char m_pad00[0x24];
	Real m_majorRadius; // +0x24
};
class AIUpdateInterface
{
public:
	void destroyPath();
};
class Rva00373EC6;

class StealthUpdate
{
public:
	void markAsDetected(unsigned int frames, int a, Object *by, Bool b);
	Bool rva3c() const { return m_p3c != 0; }
private:
	char m_pad00[0x3c];
	void *m_p3c; // +0x3c
};
class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getUnitDirectionVector2D() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	void setTransformMatrix(const Matrix3D *mx);
	Drawable *getDrawable() const;
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	Coord3D m_pos; // +0x38
	Real m_angle; // +0x44
};
class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes s) const;
	Bool isKindOf(KindOfType k) const;
	int rva0028B511() const;
	void rva0028AE6D();
	void rva0028B4CE(PathfindLayerEnum layer);
	Rva00373EC6 *rva0028F4BC(); // the StealthUpdate, or null
	Bool isLocallyControlled() const;
	ObjectID getContainedByID() const { return m_containedByID; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Bool has274() const { return m_p274 != 0; }
	__forceinline void setStatusBit(int bit)
	{
		if (!m_status.test(bit))
		{
			m_status.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearStatusBit(int bit)
	{
		if (m_status.test(bit))
		{
			m_status.clear(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearAndSetStatusBit(int clr, int set)
	{
		if (m_status.test(clr) || !m_status.test(set))
		{
			m_status.clear(clr);
			m_status.set(set);
			rva0028AE6D();
		}
	}
private:
	char m_pad48[0x78 - 0x48];
	ObjectID m_containedByID; // +0x78
	char m_pad7c[0xa8 - 0x7c];
	GeometryInfo m_geometryInfo; // +0xa8
	char m_padd0[0x10c - 0xa8 - sizeof(GeometryInfo)];
	BitFlagsView<128> m_status; // +0x10c
	char m_pad11c[0x250 - 0x11c];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25c[0x274 - 0x25c];
	void *m_p274; // +0x274
};
class Waypoint
{
public:
	ObjectID getClimbObjectID() const { return m_climbObjectID; }

private:
	char m_pad00[0xB0];
	ObjectID m_climbObjectID; // +0xB0
};

extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
	virtual Real getLayerHeight(Real x, Real y, int layer, Coord3D *normal, Bool clip) const; // +0x1c
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder
{
public:
	void *rva001E4461(int layer, int pos); // 0x001E4461: the wall object's ID at a position
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;
class Player
{
public:
	Relationship getRelationship(const Object *that) const;
};
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	char m_pad00[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;
class Eva
{
public:
	Bool reportEvaEvent(EvaEventID id, const Coord3D *pos, const Coord3D *pos2);
};
extern Eva *TheEva;
class Rva001E3557
{
public:
	Bool rva001E3557();
};
class Rva001E3591
{
public:
	Bool rva001E3591();
};
Real normalizeAngle(Real angle);

class LocomotorTemplate
{
public:
	char m_pad00[0x74];
	int m_appearance; // +0x74
	char m_pad78[0x150 - 0x78];
	Bool m_150; // +0x150
};

static __forceinline void CoordCopy(Coord3D *d, const Coord3D *s) { d->x = s->x; d->y = s->y; d->z = s->z; }
static __forceinline void CoordScale(Coord3D *d, Real s) { d->x *= s; d->y *= s; d->z *= s; }
static __forceinline void CoordAdd(Coord3D *d, const Coord3D *s) { d->x += s->x; d->y += s->y; d->z += s->z; }
static __forceinline void CoordSub(Coord3D *d, const Coord3D *s) { d->x -= s->x; d->y -= s->y; d->z -= s->z; }

// Receivers of the appearance workers, named as their rows and pins are.
class Rva001E7C4C
{
public:
	void rva001E7C4C(Object *obj, unsigned int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E9045
{
public:
	void rva001E9045(int obj, int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E7C2B
{
public:
	void rva001E7C2B(int obj, int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E8C1B
{
public:
	void rva001E8C1B(int obj, int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E7053
{
public:
	void rva001e7053(unsigned int obj, unsigned int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E46E1
{
public:
	Bool rva001E7ECA(Object *obj, const Coord3D *goalPos); // 0x001E7ECA
};

class Locomotor
{
public:
	Real getMaxSpeed(Object *obj) const;
	Bool rva001E4194(Object *obj);
	bool moveTowardsPositionHordeOnClimbPortal(Object *obj, Waypoint *way);
	void moveTowardsPositionHorde(Object *obj, const Coord3D &goalPos, Real onPathDistToGoal, Real desiredSpeed);
	void rva001E68D7(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed);
	void rva001E6B8B(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed);
	void rva001E9083(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed);

private:
	void *m_vtbl;
	LocomotorTemplate *m_template; // +0x04
	char m_pad08[0x44 - 0x08];
	unsigned int m_flags; // +0x44
	char m_pad48[0x5c - 0x48];
	Real m_speedLimit; // +0x5c
	unsigned int m_speedLimitFrame; // +0x60
	unsigned int m_hordeClimbFrame; // +0x64
	Matrix3D m_transform; // +0x68
	Bool m_98; // +0x98
	Bool m_99; // +0x99
};

bool Locomotor::moveTowardsPositionHordeOnClimbPortal(Object *obj, Waypoint *way)
{
	if (!way->getClimbObjectID())
		return false;
	Object *climbObj = TheGameLogic->findObjectByID(way->getClimbObjectID());
	if (!climbObj)
		return false;
	ContainModuleInterface *contain = obj->getContain();
	if (!contain || !contain->getHordeContainInterface())
		return false;
	HordeContainInterface *hordeContain = contain->getHordeContainInterface();
	Path *aPath = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
	if (!aPath)
		return false;
	Coord3D climbPos;
	aPath->PeekPastClimbPortal(&climbPos);
	Rva003642DFResult result = aPath->rva00364521((const Rva0008BB38FloatField *)this);
	Coord3D goalPos;
	goalPos.x = result.m_pos.x;
	goalPos.y = result.m_pos.y;
	goalPos.z = result.m_pos.z;
	const Coord3D *pos = obj->getPosition();
	Coord3D delta;
	delta.x = pos->x - climbPos.x;
	delta.y = pos->y - climbPos.y;
	delta.z = pos->z - climbPos.z;
	if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > 10.0f * 10.0f)
	{
		obj->setPosition(&climbPos);
		m_transform.Set_Translation(Vector3(climbPos.x, climbPos.y, climbPos.z));
		obj->rva0028B4CE((PathfindLayerEnum)((Rva001E34FA *)&result)->rva001E34FA());
		hordeContain->slot111(&goalPos, &((Rva001E34B2 *)&result)->rva001E34B2(),
			((Rva001E3511 *)&result)->rva001E3511(), ((Rva001E34FA *)&result)->rva001E34FA());
		m_hordeClimbFrame = TheGameLogic->getFrame() + BfmeLogicFramesPerSecond * 12;
		return true;
	}
	if (!hordeContain->haveMembersReachedEndOfPath() && TheGameLogic->getFrame() <= m_hordeClimbFrame)
		return true;
	aPath = (Path *)Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
	if (!aPath)
		return false;
	_STL::vector<ScienceType> portals;
	aPath->AdvancePastPortal((ScienceType)((Rva001E3511 *)&result)->rva001E3511(), &portals);
	return false;
}

void Locomotor::rva001E9083(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed)
{
	m_flags &= ~4;
	m_transform = *obj->getTransformMatrix();
	if (TheGameLogic->getFrame() <= m_speedLimitFrame && desiredSpeed > m_speedLimit)
		desiredSpeed = m_speedLimit;
	Real maxSpeed = getMaxSpeed(obj);
	if (desiredSpeed > maxSpeed)
		desiredSpeed = maxSpeed;
	if (rva001E4194(obj))
		return;
	if (obj->testStatus((ObjectStatusTypes)0x25))
		return;
	m_99 = false;
	void *path = Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
	if (path)
		m_99 = ((Rva001E3557 *)path)->rva001E3557();
	Bool skip = obj->testStatus((ObjectStatusTypes)0x26);
	if (!skip)
	{
		skip = obj->has274();
		if (!skip && obj->getContainedByID())
		{
			Object *container = TheGameLogic->findObjectByID(obj->getContainedByID());
			skip = container && container->getTemplate()->hasKindOf((KindOfType)0x6d);
		}
	}
	if (!skip && m_template->m_150 && !obj->getTemplate()->hasKindOf((KindOfType)0x6d) && obj->getTemplate()->hasKindOf((KindOfType)0xb8))
	{
		Coord3D pos;
		CoordCopy(&pos, obj->getPosition());
		Real height = TheTerrainLogic->getLayerHeight(pos.x, pos.y, obj->rva0028B511(), NULL, true);
		Coord3D dir;
		CoordCopy(&dir, obj->getUnitDirectionVector2D());
		CoordScale(&dir, desiredSpeed < 7.0f ? desiredSpeed : 7.0f);
		CoordAdd(&pos, &dir);
		Real nextHeight = TheTerrainLogic->getLayerHeight(pos.x, pos.y, obj->rva0028B511(), NULL, true);
		Real bias = (height - nextHeight + 0.1f < 0.0f) ? 0.0f : height - nextHeight + 0.1f;
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &pos);
		ObjectID wallID = (ObjectID)(int)TheAI->pathfinder()->rva001E4461(layer, (int)&pos);
		Object *wall = TheGameLogic->findObjectByID(wallID);
		Bool climbing = false;
		Bool descending = false;
		Bool landed = false;
		if (wall && wall->getTemplate()->hasKindOf((KindOfType)0xc9))
		{
			Vector3 local(pos.x, pos.y, pos.z);
			Matrix3D inverse;
			wall->getTransformMatrix()->Get_Orthogonal_Inverse(inverse);
			inverse.mulVector3(local);
			const GeometryInfo &geom = wall->getGeometryInfo();
			Bool inside = fabs(local.X) <= geom.getMajorRadius() && local.Z <= geom.getMaxHeightAbovePosition();
			if (inside)
			{
				Real maxH = geom.getMaxHeightAbovePosition();
				Real top = wall->getPosition()->z + maxH;
				if (pos.z < top)
				{
					CoordSub(&pos, &dir);
					climbing = true;
					if (obj->isKindOf((KindOfType)0x67))
					{
						pos.z += desiredSpeed * 0.6f;
						if (pos.z > top)
							pos.z = top;
					}
					else
					{
						Coord3D myDir;
						CoordCopy(&myDir, obj->getUnitDirectionVector2D());
						Coord3D wallDir;
						CoordCopy(&wallDir, wall->getUnitDirectionVector2D());
						Real dot = myDir.x * wallDir.x + myDir.y * wallDir.y + myDir.z * wallDir.z;
						if (dot >= 0.0f)
							obj->setOrientation(wall->getOrientation());
						else
							obj->setOrientation(normalizeAngle(wall->getOrientation() + 3.1415927f));
						Vector3 moved(pos.x, pos.y, pos.z);
						inverse.mulVector3(moved);
						if (moved.X > geom.getMajorRadius())
							moved.X = geom.getMajorRadius();
						else if (-geom.getMajorRadius() > moved.X)
							moved.X = -geom.getMajorRadius();
						wall->getTransformMatrix()->mulVector3(moved);
						pos.x = moved.X;
						pos.y = moved.Y;
						pos.z = moved.Z;
						if (wall->isLocallyControlled() && ThePlayerList->getLocalPlayer()->getRelationship(obj) == ENEMIES)
							TheEva->reportEvaEvent((EvaEventID)15, wall->getPosition(), NULL);
					}
				}
				else
				{
					landed = true;
				}
			}
		}
		else
		{
			Real groundHeight = TheTerrainLogic->getLayerHeight(pos.x, pos.y, obj->rva0028B511(), NULL, true);
			if (pos.z > groundHeight + bias)
			{
				CoordSub(&pos, &dir);
				descending = true;
				if (obj->isKindOf((KindOfType)0x69))
				{
					pos.z -= desiredSpeed * 0.6f;
					if (groundHeight + 1.0f >= pos.z)
					{
						pos.z = groundHeight;
						if (obj->getAI())
							obj->getAI()->destroyPath();
						obj->setStatusBit(0x3d);
						landed = true;
					}
				}
			}
		}
		if (descending || climbing || landed)
		{
			obj->setPosition(&pos);
			if (descending)
			{
				if (obj->getDrawable())
					obj->getDrawable()->rva00272A02(false);
				obj->clearAndSetStatusBit(0x67, 0x69);
				StealthUpdate *stealth = (StealthUpdate *)obj->rva0028F4BC();
				if (stealth && stealth->rva3c())
					stealth->markAsDetected(0, 1, NULL, true);
			}
			else if (climbing)
			{
				if (obj->getDrawable())
					obj->getDrawable()->rva00272A02(false);
				obj->clearAndSetStatusBit(0x69, 0x67);
				StealthUpdate *stealth = (StealthUpdate *)obj->rva0028F4BC();
				if (stealth && stealth->rva3c())
					stealth->markAsDetected(0, 1, NULL, true);
			}
			else
			{
				obj->clearStatusBit(0x67);
				obj->clearStatusBit(0x69);
				if (obj->getDrawable())
					obj->getDrawable()->rva00272A02(true);
			}
			return;
		}
		obj->clearStatusBit(0x67);
		obj->clearStatusBit(0x69);
		if (obj->getDrawable())
			obj->getDrawable()->rva00272A02(true);
	}
	switch (m_template->m_appearance)
	{
		case 0:
		case 4:
		case 7:
			rva001E6B8B(obj, goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 6:
			moveTowardsPositionHorde(obj, *goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 2:
			((Rva001E7C4C *)this)->rva001E7C4C(obj, (unsigned int)goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 8:
			((Rva001E9045 *)this)->rva001E9045((int)obj, (int)goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 9:
			rva001E68D7(obj, goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 3:
			((Rva001E7C2B *)this)->rva001E7C2B((int)obj, (int)goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 1:
			((Rva001E8C1B *)this)->rva001E8C1B((int)obj, (int)goalPos, onPathDistToGoal, desiredSpeed);
			break;
		case 5:
			break;
		default:
			((Rva001E7053 *)this)->rva001e7053((unsigned int)obj, (unsigned int)goalPos, onPathDistToGoal, desiredSpeed);
			break;
	}
	path = Rva001E3FFDGet((Rva001E3FFDOuter *)obj);
	if (!path || !((Rva001E3591 *)path)->rva001E3591())
		((Rva001E46E1 *)this)->rva001E7ECA(obj, goalPos);
	obj->setTransformMatrix(&m_transform);
	m_99 = false;
}
