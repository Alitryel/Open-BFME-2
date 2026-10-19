// cl: /O1 /DNDEBUG /MD
//
// UpdateModule::UpdateModule, retail 0x00253390, 61 bytes. Dedicated TU so
// CreateModule.cpp cannot see this body. BehaviorModule ctor stays at 0x253330.

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

template <int N> class BitFlags;

// The interface table as the other UpdateModule views (first in link order:
// DumbProjectileBehavior.cpp) spell it: update stays pure in UpdateModule and the
// second slot is UpdateModule's getDisabledTypesToProcess.
class UpdateModuleInterface
{
public:
	virtual void update() = 0;
	virtual BitFlags<13> getDisabledTypesToProcess() const = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual BitFlags<13> getDisabledTypesToProcess() const;
};

inline UpdateModule::UpdateModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData),
	  m_nextCallFrameAndPhase(0),
	  m_indexInLogic(-1),
	  m_bfmeReserved(-1)
{
}

// LINK-OWNER anchor: this unit owns ??0UpdateModule; other units emit
// it inline, so the owner must also emit a select-any (inline) copy.
#pragma inline_depth(0)
// ?bfmeEmitUpdateModuleCtor@@YAXPAVUpdateModule@@PAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitUpdateModuleCtor(UpdateModule *p, Thing *thing, const ModuleData *moduleData)
{
	p->UpdateModule::UpdateModule(thing, moduleData);
}
#pragma inline_depth()

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
