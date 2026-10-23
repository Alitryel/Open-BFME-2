// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DeployStyleAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D1E6, 59 bytes. Dedicated TU: retail news 0x4D8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x48E983. Class identity is the
// "DeployStyleAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DeployStyleAIUpdate
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4D8];
};

// ?friend_newModuleInstance@DeployStyleAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *DeployStyleAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DeployStyleAIUpdate(thing, moduleData));
}

// friend_newModuleInstance is a header inline in retail: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitDeployStyleAIUpdateFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitDeployStyleAIUpdateFriendNew(Thing *thing, const ModuleData *moduleData)
{
	DeployStyleAIUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
