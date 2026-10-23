// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SwayClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025298F, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C908B. Class identity is the
// "SwayClientUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SwayClientUpdate
{
public:
	SwayClientUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@SwayClientUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *SwayClientUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SwayClientUpdate(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitSwayClientUpdateFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitSwayClientUpdateFriendNew(Thing *thing, const ModuleData *moduleData)
{
	SwayClientUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
