// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include /I. /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// TeleportToCasterSpecialPower::teleportList: WB12777E0 assertion84 establishes name; native4CD51B..4CD68D RET8 establishes extent370 and layout/calls.
// No applicable clean BF1/ZH TeleportToCaster source at donor9cbfb551 (rechecked at0bef414b). Data+CC/D0 ring radii, Object44 orientation/258 AI; native vector element IDs use shared lookup enum.
#include <vector>
#include <string.h>
#include <math.h>
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern GameLogic *TheGameLogic;
enum CommandSourceType{COMMANDSOURCE_SCRIPT=2};
class AICommandInterface{public:void aiIdle(CommandSourceType);};
struct TeleportAI{char pad[0x20];AICommandInterface commands;};
class Player;
struct TeleportThingTemplate{char pad[0x115];unsigned char kind115;};
enum ObjectStatusTypes{STATUS_UNK=-1};
class Object{public:char pad[4];TeleportThingTemplate *thingTemplate;char pad08[0x38-8];Coord3D position;float orientation;char pad48[0x74-0x48];ObjectID id,storedByID;char pad7C[0x258-0x7C];TeleportAI *ai;
 void teleportTo(const Coord3D*,bool);Player *getControllingPlayer()const;bool testStatus(ObjectStatusTypes)const;};
class Thing{public:void setOrientation(float);};
class FXList;
struct TeleportData{char pad[0xC8];float radius,minRadius,maxRadius;const FXList *endFX;};
struct FindPositionOptions{
 FindPositionOptions():flags(0),minRadius(0),maxRadius(0),startAngle(-99999.9f),maxZDelta(1e10f),ignoreObject(0),sourceToPathToDest(0),relationshipObject(0){}
 unsigned flags;float minRadius,maxRadius,startAngle,maxZDelta;const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
};
class SpecialAbilityUpdate{public:virtual void triggerAbilityEffect();};	// base trigger 0x0045108D
class TeleportToCasterSpecialPower:public SpecialAbilityUpdate{public:virtual void triggerAbilityEffect();const TeleportData *data;Object *owner;char pad0C[0x44-0x0C];Coord3D targetPosition;
 void teleportList(const _STL::vector<ObjectID>*,const Coord3D*);void rva004CD4DC(Object*);};
void TeleportToCasterSpecialPower::teleportList(const _STL::vector<ObjectID>*ids,const Coord3D*center){
 const TeleportData *moduleData=data;
 FindPositionOptions options;options.minRadius=moduleData->minRadius;options.maxRadius=moduleData->maxRadius;
 int count=ids->size();float angleSpacing=6.28318530718f/count;float angle=0;
 for(_STL::vector<ObjectID>::const_iterator it=ids->begin();it!=ids->end();++it,angle+=angleSpacing){
  Object *object=TheGameLogic->findObjectByID(*it);
  if(object){
   rva004CD4DC(object);
   float orientation=object->orientation;options.startAngle=angle;Coord3D position;
   if(PartitionManager::findPositionAround(center,&options,&position)){double dx=(double)position.x-center->x;float dy=(float)((double)position.y-center->y);orientation=atan2f(dy,(float)dx);}
   else position=*center;
   if(object->ai)object->ai->commands.aiIdle(COMMANDSOURCE_SCRIPT);
   ((Thing*)object)->setOrientation(orientation);object->teleportTo(&position,false);
   rva004CD4DC(object);
  }
 }
}

// StoreObjectsSpecialPower lookup: target128B proves owner+8 object, object244 module list and slot4 name-key query; store+88 vector uses ObjectID-width unsigned slots.
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004CD45CItem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual NameKeyType getKey();
	unsigned char m_pad[0x88 - 4];
	unsigned int *m_vecBeg;
	unsigned int *m_vecEnd;
};

struct Rva004CD45CMid
{
	unsigned char m_pad[0x244];
	Rva004CD45CItem **m_list;
};

class Rva004CD45C
{
public:
	unsigned char m_pad0[8];
	Rva004CD45CMid *m_mid;
	void *rva004CD45C();
};

// ?rva004CD45C@Rva004CD45C@@QAEPAXXZ @0x004CD45C128B
void *Rva004CD45C::rva004CD45C()
{
	static NameKeyType s_key = TheNameKeyGenerator->nameToKey("StoreObjectsSpecialPower");
	Rva004CD45CMid *mid = m_mid;
	Rva004CD45CItem **pp = mid->m_list;
	for (;;) {
		Rva004CD45CItem *cur = *pp;
		if (cur == 0)
			return 0;
		if (cur->getKey() != s_key) {
			pp++;
			continue;
		}
		cur = *pp;
		if (cur == 0) {
			pp++;
			continue;
		}
		unsigned int **vec = (unsigned int **)((char *)cur + 0x88);
		unsigned int diff = vec[1] - vec[0];
		if (diff > 0)
			return cur;
		pp++;
	}
}

class Rva004CDA35
{
public:
	void rva004CDA35();
};

class Rva0044E633
{
public:
	void *rva0044E633();
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

// The +0x60 object filter is read through the final override (Zero Hour SpecialPower.h getFO() idiom).
class SpecialPowerTemplate : public Overridable
{
public:
	const void *getObjectFilter() const { return &getFO()->m_objectFilter; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	char m_pad00[0x60];
	int m_objectFilter;
};

// What 0x0044E633 returns: slot 6 is the special power template.
class TeleportPowerModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);
	Rva000421C8 *m_next;
};

class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match) : m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(Object *o) : m_object(o) {}
	virtual bool allow(Object *obj);
	Object *m_object;
};

class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(Object *o, int flags, bool inverse) : m_object(o), m_flags(flags), m_inverse(inverse) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Object *m_object;
	int m_flags;
	bool m_inverse;
};

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(Object *o) : m_object(o) {}
	virtual bool allow(Object *obj);
	Object *m_object;
};

class BfmeFixedStorage0004543D
{
public:
	char bits[28];
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &) throw();
};

class Rva0006EE7A
{
public:
	Rva0006EE7A(int, int, int) throw();
	unsigned bits[7];
};

template<int N> class BitFlags
{
public:
	unsigned bits[7];
};

extern BitFlags<116> KINDOFMASK_NONE;

class PartitionFilterRejectByKindOf : public Rva000421C8
{
public:
	PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D a, b;
};

class BfmeObject872Header
{
public:
	__forceinline BfmeObject872Header() { memset(bits, 0, sizeof(bits)); }
	BfmeObject872Header(const BfmeObject872Header &);
	unsigned bits[4];
};

class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int, int);
	unsigned bits[4];
};

class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &, const BfmeObject872Header &);
	virtual bool allow(Object *obj);
	BfmeObject872Header a, b;
};

class Matrix3D;

class FXList
{
public:
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
};

extern PartitionManager *ThePartitionManager;

// Target622B virtual override: WB1277B60 directly calls SpecialAbility base trigger, then teleports stored IDs or a filtered range and plays endFX.
void TeleportToCasterSpecialPower::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	Object *object = owner;
	const TeleportData *moduleData = data;
	Rva004CD45CItem *stored = (Rva004CD45CItem *)((Rva004CD45C *)this)->rva004CD45C();
	if (stored) {
		teleportList((const _STL::vector<ObjectID> *)&stored->m_vecBeg, &targetPosition);
		((Rva004CDA35 *)stored)->rva004CDA35();
	} else {
		const void *what = ((TeleportPowerModule *)((Rva0044E633 *)this)->rva0044E633())->getSpecialPowerTemplate()->getObjectFilter();
		Rva0023DA79 statusMask;
		BfmeWideResult result = ThePartitionManager->iterateObjectsInRange(&targetPosition, moduleData->radius, 0,
			Rva002614DFFilter(object).link(Rva0026119DFilter().link(PartitionFilterRejectByKindOf(*(const BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 7, 0x86), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(
			Rva00260EB1Filter(object, 4, false).link(Rva002611BFFilter(object).link(&Rva002614ECFilter(what, object->getControllingPlayer(), true))->link(
			&Rva002FDF1C(*(BfmeObject872Header *)statusMask.rva0023DA79(0, 0x26), BfmeObject872Header())))))), 1);
		_STL::vector<ObjectID> ids;
		Object *item;
		while ((item = result.next()) != 0) {
			Object *caster = TheGameLogic->findObjectByID(item->storedByID);
			if (caster && (caster->thingTemplate->kind115 & 0x20))
				continue;
			if (item->testStatus((ObjectStatusTypes)3) || item->testStatus((ObjectStatusTypes)2))
				continue;
			ObjectID id = item->id;
			ids.push_back(id);
		}
		teleportList(&ids, &object->position);
	}
	FXList::doFXPos(moduleData->endFX, &targetPosition, 0, 0.0f, 0);
}
