// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RebuildHoleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C3FB, 56 bytes. Dedicated TU: retail news 0x48 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x483271. Class identity is the
// "RebuildHoleBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RebuildHoleBehavior
{
public:
	RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@RebuildHoleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *RebuildHoleBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RebuildHoleBehavior(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRebuildHoleBehaviorFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitRebuildHoleBehaviorFriendNew(Thing *thing, const ModuleData *moduleData)
{
	RebuildHoleBehavior::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
