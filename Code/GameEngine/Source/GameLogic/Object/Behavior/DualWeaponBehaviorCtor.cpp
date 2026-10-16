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

class UpdateModuleInterface
{
public:
	virtual void update();
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
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
private:
	const Object *getObject() const { return m_object; }
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
