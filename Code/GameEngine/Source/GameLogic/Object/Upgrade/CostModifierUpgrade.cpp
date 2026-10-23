// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();

private:
	unsigned int m_state;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpgradeModuleInterface,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *, const ModuleData * );
};

// The base at +0x1C. Retail's constructor stores 0x00C4EF80 there, a table of
// four __purecall slots that seven abstract classes fold onto, and m_enabled
// follows at +0x20, so this base holds no data. The UpgradeMux constructor at
// 0x004CE2A3 installs 0x00C5FF10 and clears a flag at +4 instead, so this view
// keeps a neutral name: spelled UpgradeMux, it emitted a wrong
// ??0UpgradeMux@@QAE@XZ copy that, first in link order, displaced retail's.
class CostModifierUpgradeInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CostModifierUpgrade.h
class CostModifierUpgrade : public UpgradeModule, public CostModifierUpgradeInterface
{
public:
	CostModifierUpgrade( Thing *, const ModuleData * );

private:
	bool m_enabled;
};

CostModifierUpgrade::CostModifierUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData ),
	  m_enabled( true )
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?upgradeModuleInterfaceAnchor@UpgradeModuleInterface@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
