// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PhysicsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "PhysicsBehavior"
// (addModule pairs the name with it). news 0x68 and runs the declared-only
// module ctor, pinned at 0x003907A6.

class Thing;
class ModuleData;
class Module;

class PhysicsBehavior
{
public:
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x68];
};

// ?friend_newModuleInstance@PhysicsBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *PhysicsBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PhysicsBehavior(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitPhysicsBehaviorFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitPhysicsBehaviorFriendNew(Thing *thing, const ModuleData *moduleData)
{
	PhysicsBehavior::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
