// cl: /DNDEBUG /MD /EHsc
//
// ??1GiveOrRestoreUpgradeSpecialPower@@UAE@XZ, retail 0x004CD166, 83 bytes.
// Dtor restoring four vptrs (+0 +0x0C +0x10 +0x20) then destroying AsciiString
// at +0x8C via pinned ??1 StringBase at 0x00036410 and calling pinned base
// ??1Rva0044EF5E at 0x00451F45. Layout from rowed ctor 0x4CD0DC (Rva0044EF5E
// base size 0x20, +0x20 secondary, byte +0x88, string +0x8C). Vtable 0x0085FA40
// with slot 0 ??_G at 0x004CD332. Model follows FlammableUpdateDtor (4 vptrs).

class Thing;
class ModuleData;
class Object;

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

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

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class Rva0044EF5E : public BehaviorModule, public UpdateModuleInterface
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class SpecialPowerTemplate;
class Waypoint;
struct Coord3D;

class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);
};

// The dtor tail-calls the rowed ??1SpecialAbilityUpdate (0x00451F45), and
// retail's +0x10 and +0x20 tables (0x0084DEE8, 0x008552A4) keep
// SpecialAbilityUpdate::update (0x00451FA2) and
// SpecialAbilityUpdate::initiateIntentToDoSpecialPower (0x004500A3) in slot 0.
class SpecialAbilityUpdate : public Rva0044EF5E, public SpecialPowerUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();
	virtual UpdateSleepTime update();
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);
};

class GiveOrRestoreUpgradeSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual ~GiveOrRestoreUpgradeSpecialPower();

private:
	unsigned char m_pad24[0x88 - 0x24];
	unsigned char m_88;
	unsigned char m_pad89[3];
	StringBase<char> m_8C;
};

GiveOrRestoreUpgradeSpecialPower::~GiveOrRestoreUpgradeSpecialPower()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
