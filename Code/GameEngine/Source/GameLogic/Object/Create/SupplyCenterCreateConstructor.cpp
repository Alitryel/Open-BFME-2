// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModuleInterface
{
public:
	virtual void createModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModule : public BehaviorModule,
	public CreateModuleInterface,
	public ModuleInterface
{
public:
	CreateModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~CreateModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterCreate.h
class SupplyCenterCreate : public CreateModule
{
public:
	SupplyCenterCreate( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~SupplyCenterCreate();
};

SupplyCenterCreate::SupplyCenterCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}

// ??1SupplyCenterCreate@@MAE@XZ present-unmatched
SupplyCenterCreate::~SupplyCenterCreate()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?createModuleInterfaceAnchor@CreateModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
