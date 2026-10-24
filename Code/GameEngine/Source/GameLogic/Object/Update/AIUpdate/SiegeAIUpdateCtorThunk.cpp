// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

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

class SiegeAIUpdateIface1
{
public:
	virtual void siegeAIUpdateIface1Anchor();
};

class SiegeAIUpdateIface2
{
public:
	virtual void siegeAIUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class SiegeAIUpdateIface3
{
public:
	virtual void siegeAIUpdateIface3Anchor();
};

class SiegeAIUpdateIface4
{
public:
	virtual void siegeAIUpdateIface4Anchor();
};

class AIUpdateInterface : public BehaviorModule,
	public SiegeAIUpdateIface1,
	public SiegeAIUpdateIface2,
	public SiegeAIUpdateIface3,
	public SiegeAIUpdateIface4
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
};

class SiegeAIUpdate : public AIUpdateInterface
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0SiegeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeAIUpdate::SiegeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x0026E9BD -> ??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z (defined by Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceCtor.cpp)
#pragma comment(linker, "/alternatename:??0SiegeAIUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z=??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z")
