// ?update@DualWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9 date=2026-10-17
// cl: /GX /MD /DNDEBUG
//
// ??0DualWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z at retail
// 0x0045AE55, 88 bytes. Behavior-side ctor in the DualWeapon file-unit:
// pool key 0x45ADE0 (DualWeaponBehavior string) ends where the ModuleData
// ctor 0x45AE25 begins, proc 0x45AE44 (SwitchWeapon table) ends where this
// ctor begins, and ??_G 0x45AEAD starts where this ctor ends. The rowed
// UpdateModule base ctor (0x253390) plus the setWakeFrame pin (0x44DF71)
// carry the frame; the derived class re-stores the inherited +0x0C/+0x10
// slots, zeroes its close-range flag and switch timer through one shared
// zero register, then keeps itself awake with setWakeFrame(obj, 1).
// Shape follows AimWeaponBehaviorCtor.cpp: the real UpdateModule hierarchy
// (BehaviorModule pair plus UpdateModuleInterface), so the ctor and the dtor
// store the three vtables themselves. Member names are inferred from the
// SwitchWeapon table (MinimumSwitchTime, UseCloseRangeWhileMounted).

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DualWeaponBehavior : public UpdateModule
{
public:
	DualWeaponBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~DualWeaponBehavior();
	virtual UpdateSleepTime update();
private:
	Object *getObject() const { return m_object; }
	bool m_closeRangeActive; // +0x20
	int m_switchTimer; // +0x24
};

// ??0DualWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x45AE55
DualWeaponBehavior::DualWeaponBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_closeRangeActive = false;
	m_switchTimer = 0;
	setWakeFrame(const_cast<Object*>(getObject()), UPDATE_SLEEP_NONE);
}

// ??1DualWeaponBehavior@@UAE@XZ @0x0045ADC1: vftable 0x008417A4 slot 0 is its
// deleting dtor 0x0045AEAD (formerly the placeholder Rva0045ADC1 in
// Rva0024A797Derived.cpp).
DualWeaponBehavior::~DualWeaponBehavior()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Native527B 45AF14..45B123; corrected native guards and shared set/clear paths.
#include <math.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
template<class T> __forceinline volatile T &r1_vwrite(T &value)
{
 return *(volatile T *)&value;

}
enum WeaponSetType

{
 WEAPONSET_CLOSE = 7

}
;
enum KindOfType

{
 KIND_UNKNOWN = 0

}
;
class Object;
class AIUpdateInterface

{
 public: Object *getCurrentVictim() const;

}
;
class Rva0028B7AELeaGetter

{
 public: void *get() const;

}
;
struct DualWeaponFlags

{
 unsigned int words[4];
 __forceinline bool test(unsigned i) const

 {
  return (words[i>>5] >> (i&31)) & 1;

 }

}
;
struct DualWeaponConditions

{
 unsigned int words[19];
 __forceinline unsigned test(unsigned i) const

 {
  return words[i>>5] & (1u<<(i&31));

 }
 __forceinline void set(unsigned i)

 {
  words[i>>5] |= 1u<<(i&31);

 }
 __forceinline void clear(unsigned i)

 {
  words[i>>5] &= ~(1u<<(i&31));

 }

}
;
struct DualWeaponTemplateView

{
 unsigned char pad[0x114];
 unsigned int kindWord;

}
;
class Object

{
 public:
 bool isKindOf(KindOfType) const;
 void setWeaponSetFlag(WeaponSetType);
 void clearWeaponSetFlag(WeaponSetType);
 void rva0028AE6D();
 __forceinline const DualWeaponFlags *getWeaponSetFlags() const

 {
  return (const DualWeaponFlags *)((const Rva0028B7AELeaGetter *)this)->get();

 }
 __forceinline const Coord3D *getPosition() const

 {
  return &position;

 }
 __forceinline const DualWeaponTemplateView *getTemplate() const

 {
  return tmplate;

 }
 __forceinline void setCloseCondition()

 {
  if (!conditions.test(160))

  {
   conditions.set(160);
   rva0028AE6D();

  }

 }
 __forceinline void clearCloseCondition()

 {
  if (conditions.test(160))

  {
   conditions.clear(160);
   rva0028AE6D();

  }

 }
 __forceinline AIUpdateInterface *getAIUpdateInterface() const

 {
  return ai;

 }
 __forceinline Object *getContainer() const

 {
  return container;

 }
 __forceinline bool isEffectivelyDead() const

 {
  return privateStatus & 1;

 }
 unsigned char pad0[4];
 const DualWeaponTemplateView *tmplate;
 unsigned char pad8[0x38-8];
 Coord3D position;
 unsigned char pad44[0x10c-0x44];
 DualWeaponConditions conditions;
 unsigned char pad158[0x258-0x158];
 AIUpdateInterface *ai;
 unsigned char pad25c[0x274-0x25c];
 Object *container;
 unsigned char pad278[0x438-0x278];
 unsigned char privateStatus;

}
;
class AttackPriorityInfo;
class PartitionFilter;
class AI

{
 public: Object *findClosestEnemy(const Object *, float, unsigned int,
 const AttackPriorityInfo *, PartitionFilter *, int);

}
;
extern AI *TheAI;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern const int g_009BA4E4;
struct DualWeaponBehaviorModuleData

{
 unsigned char pad[8];
 float switchDistance;
 bool useCloseWhileMounted;
 unsigned int minimumSwitchTime;
 bool useHordeRangeWeapon, useRealVictimRange;

}
;

UpdateSleepTime DualWeaponBehavior::update()

{
 const DualWeaponBehaviorModuleData *d = (const DualWeaponBehaviorModuleData *)m_moduleData;
 Object *obj = getObject();
 AIUpdateInterface *ai = obj->getAIUpdateInterface();
 if ((d ? (!ai || obj->isEffectivelyDead()) : (!ai || obj->isEffectivelyDead()))) return UPDATE_SLEEP_FOREVER;
 if (obj->getWeaponSetFlags()->test(8)) return (UpdateSleepTime)g_009BA4E4;
 Object *container = obj->getContainer();
 if (container && !(container->getTemplate()->kindWord & 0x2000))
 return (m_closeRangeActive ? ((UpdateSleepTime)g_009BA4E4) : ((UpdateSleepTime)g_009BA4E4));
 goto afterContainerRange;
 afterContainerRange:;
 if (d->useHordeRangeWeapon && container && (container->getTemplate()->kindWord & 0x2000))

 {
  if (container->getWeaponSetFlags()->test(7)) { obj->setWeaponSetFlag(WEAPONSET_CLOSE);
 obj->setCloseCondition();
 return (UpdateSleepTime)g_009BA4E4; }
 obj->clearWeaponSetFlag(WEAPONSET_CLOSE);
 obj->clearCloseCondition();
 return (UpdateSleepTime)g_009BA4E4;
 }
 if (!obj->isKindOf((KindOfType)0xcf)) { } else return (UpdateSleepTime)g_009BA4E4;
 if (!m_closeRangeActive)

 {
  float range = d->switchDistance;
  Object *victim = 0;
  if (d->useRealVictimRange && ai->getCurrentVictim())

  {
   victim = ai->getCurrentVictim();
   Coord3D delta;
   delta.x = obj->getPosition()->x - victim->getPosition()->x;
   delta.y = obj->getPosition()->y - victim->getPosition()->y;
   r1_vwrite(delta.z) = obj->getPosition()->z - victim->getPosition()->z;
   if (delta.x*delta.x + delta.y*delta.y + delta.z*delta.z > range*range) victim = 0;

  }
  else

  {
   victim = TheAI->findClosestEnemy(obj, range, 0x62, 0, 0, 0);

  }
  if (victim && fabs((double)(victim->getPosition()->z - obj->getPosition()->z)) > (double)(range * 0.5f))
  victim = 0;
  if (d->useCloseWhileMounted && obj->isKindOf((KindOfType)0xd6)) {
   if (!obj->getWeaponSetFlags()->test(7)) { obj->setWeaponSetFlag(WEAPONSET_CLOSE);
 obj->setCloseCondition();
 return (UpdateSleepTime)g_009BA4E4; }
   return (UpdateSleepTime)g_009BA4E4;
  }
  unsigned int now = TheGameLogic->getFrame();
  int remaining = (int)(m_switchTimer + d->minimumSwitchTime - now);
  if (remaining > 0) return (UpdateSleepTime)remaining;
  m_switchTimer = now;
  if (!victim || victim->isEffectivelyDead()) {
   if (!obj->getWeaponSetFlags()->test(7)) return (UpdateSleepTime)g_009BA4E4;
   obj->clearWeaponSetFlag(WEAPONSET_CLOSE);
 obj->clearCloseCondition();
 return (UpdateSleepTime)g_009BA4E4;
  }
 }
 if (!obj->getWeaponSetFlags()->test(7)) { obj->setWeaponSetFlag(WEAPONSET_CLOSE);
 obj->setCloseCondition();
 return (UpdateSleepTime)g_009BA4E4; }
 return (UpdateSleepTime)g_009BA4E4;
}
