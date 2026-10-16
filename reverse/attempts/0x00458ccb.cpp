// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.976837701698967 date=2026-10-16
// cl: /G7 /arch:SSE /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// stlport
// ??1RampageBehaviorModuleData@@UAE@XZ, RVA 0x00458C9B, size 48.
// Virtual dtor destroying RequiredUpgrade vector at +8 then restoring
// Snapshot base vtable 0xBBB554 with trivial base inlined (no base call).
// Evidence: EH state 0 single vector teardown 0x2CC70, vtable-last
// 0xBBB554 same shape as UpgradeModuleData 0x255A42, slot-0 deleter
// 0x458C7F calls here, ctor 0x458C0F owns class and table 0xC40E78.
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

class ModuleDataBase
{
public:
    virtual ~ModuleDataBase() {}
};

class RampageBehaviorModuleData : public ModuleDataBase
{
public:
    RampageBehaviorModuleData(int);
private:
    unsigned int m_unused04;
    _STL::vector<AsciiString> m_requiredUpgrade;
};

// ?dummyCtor@RampageBehaviorModuleData@@QAE@H@Z present-unmatched
RampageBehaviorModuleData::RampageBehaviorModuleData(int)
{
}

void deleteRampageBehaviorModuleData(RampageBehaviorModuleData *p)
{
    delete p;
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
enum UpdateSleepTime

{
 UPDATE_SLEEP_NONE = 1,
 UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
 
}
;
enum WeaponSetType

{
 WEAPONSET_7 = 7,
 WEAPONSET_8 = 8
 
}
;
enum CommandSourceType

{
 CMD_FROM_AI = 2
 
}
;
class Thing;
class ModuleData;
class Object;
class UpgradeTemplate;
class AsciiString;
class Drawable

{
 public:
 void rva00274176(Bool force);
 
}
;
class ObjectModuleBase

{
 public:
 virtual void objectModuleBaseAnchor();
 const ModuleData *m_moduleData;
 Object *m_object;
 
}
;
class BehaviorModuleInterface

{
 public:
 virtual void getBehaviorModuleInterface() = 0;
 
}
;
class BehaviorModule : public ObjectModuleBase, public BehaviorModuleInterface

{
 
}
;
class UpdateModuleInterface

{
 public:
 virtual UpdateSleepTime update() = 0;
 
}
;
class UpdateModule : public BehaviorModule, public UpdateModuleInterface

{
 public:
 virtual ~UpdateModule();
 private:
 UnsignedInt m_nextCallFrameAndPhase;
 Int m_indexInLogic;
 UnsignedInt m_updateState;
 
}
;
class RampageBehaviorModuleDataView

{
 public:
 unsigned char m_pad00[8];
 const unsigned char *m_requiredUpgradeStart;
 const unsigned char *m_requiredUpgradeFinish;
 const unsigned char *m_requiredUpgradeEnd;
 float m_healthThreshold;
 Int m_lifeTimer;
 Int m_angryLifeTimer;
 Int m_resetTimer;
 float m_enemyCheckRange;
 Int m_enemyThreshold;
 
}
;
class BodyModuleFloatInterface

{
 public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual float rva0048F64EGetA();
 virtual void slot14();
 virtual float rva0048F64EGetB();
 
}
;
class AICommandInterface

{
 public:
 void aiIdle(CommandSourceType source);
 void aiAttackPosition(const Coord3D *position, Int maxShots,
 CommandSourceType source);
 void rva0045003E(Int value, CommandSourceType source);
 
}
;
class AIUpdateInterfaceView

{
 public:
 unsigned char m_pad00[0x20];
 __forceinline AICommandInterface *commands() 
 {
  return (AICommandInterface *)((char *)this + 0x20);
  
 }
 
}
;
class Rva0028B7AELeaGetter

{
 public:
 void *get() const;
 
}
;
class Rva0028BD3AInterface

{
 public:
 virtual void slot00();
 virtual void slot04();
 virtual void set(Bool enabled);
 
}
;
class Thing

{
 public:
 Drawable *getDrawable() const;
 void *m_vtable;
 const void *m_template;
 unsigned char m_pad08[0x30];
 Coord3D m_position;
 unsigned char m_pad44[4];
 
}
;
class Object : public Thing

{
 public:
 Int rva0028B7C8() const;
 void rva0028AE6D();
 Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
 void clearWeaponSetFlag(WeaponSetType type);
 void setWeaponSetFlag(WeaponSetType type);
 void *rva0028BD3A() const;
 const UnsignedInt *getWeaponSetFlags() const
 
 {
  return (const UnsignedInt *)((const Rva0028B7AELeaGetter *)this)->get();
  
 }
 const Coord3D *getPosition() const 
 {
  return &m_position;
  
 }
 __forceinline void clearConditionWord5Bit2()
 
 {
  if (m_conditionWords[5] & 4) 
  {
   *(unsigned int *)((char *)this+0x120) &= ~4U;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void setConditionWord5Bit2()
 
 {
  if (!(m_conditionWords[5] & 4)) 
  {
   *(unsigned int *)((char *)this+0x120) |= 4;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void clearConditionWord5Bit0()
 
 {
  if (((const unsigned char *)&m_conditionWords[5])[0] & 1) 
  {
   m_conditionWords[5] &= ~1U;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void clearConditionWord5Byte1Bits()
 
 {
  const volatile unsigned char *testBytes = (const volatile unsigned char *)&m_conditionWords[5];
  unsigned char *bytes = (unsigned char *)&m_conditionWords[5];
  if (testBytes[1] & 0x10) 
  {
   bytes[1] &= (unsigned char)0xEF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x20) 
  {
   bytes[1] &= (unsigned char)0xDF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x40) 
  {
   bytes[1] &= (unsigned char)0xBF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x80) 
  {
   bytes[1] &= (unsigned char)0x7F;
   rva0028AE6D();
   
  }
  
 }
 __forceinline Bool hasStatusBit1() const 
 {
  return (m_status438 & 1) != 0;
  
 }
 __forceinline Bool hasWeaponSet(WeaponSetType type) const
 
 {
  unsigned char flags = (unsigned char)(*getWeaponSetFlags() >> type);
  return (flags & 1) != 0;
  
 }
 private:
 unsigned char m_pad48[0x10C - 0x48];
 UnsignedInt m_conditionWords[19];
 unsigned char m_pad158[0x254 - 0x158];
 public:
 BodyModuleFloatInterface *m_body;
 AIUpdateInterfaceView *m_ai;
 private:
 unsigned char m_pad25C[0x438 - 0x25C];
 unsigned char m_status438;
 
}
;
class UpgradeCenter

{
 public:
 const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
 
}
;
extern UpgradeCenter *TheUpgradeCenter;
__forceinline const float &rampageMax(const float &a, const float &b) 
{
 return a > b ? a : b;
 
}
class Rva00458BE1

{
 public:
 unsigned char rva00458BE1();
 
}
;
class RampageBehavior : public UpdateModule

{
 public:
 virtual UpdateSleepTime update();
 private:

 float m_10;
 Int m_14;
 Int m_18;
 
}
;
UpdateSleepTime RampageBehavior::update()

{
 Object *owner = m_object;
 AIUpdateInterfaceView *ai = owner->m_ai;
 BodyModuleFloatInterface *body = owner->m_body;
 Drawable *drawable = owner->getDrawable();
 if (!body || !ai || !drawable)
 return UPDATE_SLEEP_FOREVER;
 const RampageBehaviorModuleDataView *data =
 (const RampageBehaviorModuleDataView *)m_moduleData;
 for (const unsigned char *upgrade = data->m_requiredUpgradeStart;
 upgrade != data->m_requiredUpgradeFinish; upgrade += 4) 
 {
  const UpgradeTemplate *required = TheUpgradeCenter->findUpgrade(
  *(const AsciiString *)upgrade);
  if (!owner->rva00290D2B(required))
  return UPDATE_SLEEP_NONE;
  
 }
 float health = body->rva0048F64EGetA();
 float maxHealth = body->rva0048F64EGetB();
 float healthRatio = health / rampageMax(1.0f, maxHealth);
 if (m_14 > 0) 
 {
  --m_14;
  if (m_14 > 0 && !owner->hasStatusBit1() && !(unsigned char)owner->rva0028B7C8())
  goto updateResetTimer;
  if (owner->hasWeaponSet(WEAPONSET_8))
  owner->clearWeaponSetFlag(WEAPONSET_8);
  if (!owner->hasStatusBit1() && !(unsigned char)owner->rva0028B7C8())
  ai->commands()->aiIdle(CMD_FROM_AI);
  Int resetTime = data->m_resetTimer;
  m_18 = resetTime;
  m_14 = 0;
  _ReadWriteBarrier();
  owner->clearConditionWord5Bit2();
  drawable->rva00274176(false);
  goto updateResetTimer;
  
 }
 if (!(data->m_healthThreshold > healthRatio)
 || owner->hasStatusBit1()
 || owner->hasWeaponSet(WEAPONSET_8)
 || !(m_10 > health)
 || m_18 != 0)
 goto updateResetTimer;
 if (((Rva00458BE1 *)this)->rva00458BE1()) 
 {
  owner->clearWeaponSetFlag(WEAPONSET_7);
  owner->setWeaponSetFlag(WEAPONSET_8);
  ai->commands()->aiAttackPosition(owner->getPosition(), 0x0FFFFFFE,
  CMD_FROM_AI);
  m_14 = data->m_lifeTimer;
  
 }
 else 
 {
  owner->setConditionWord5Bit2();
  ai->commands()->rva0045003E(0, CMD_FROM_AI);
  m_14 = data->m_angryLifeTimer;
  
 }
 owner->clearConditionWord5Bit0();
 owner->clearConditionWord5Byte1Bits();
 Rva0028BD3AInterface *iface = (Rva0028BD3AInterface *)owner->rva0028BD3A();
 if (iface)
 iface->set(false);
 drawable->rva00274176(false);
 updateResetTimer:
 if (m_18 > 0) 
 {
  --m_18;
  if (m_18 <= 0)
  m_10 = health;
  
 }
 return UPDATE_SLEEP_NONE;
 
}

// The complete UpdateModule bases supply the +0x10 interface adjustment;
// source fields m_10/m_14/m_18 occupy complete-object +0x20/+0x24/+0x28.
