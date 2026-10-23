// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RepairDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EA65, 59 bytes. Dedicated TU: retail news 0x90 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A118B. Class identity is the
// "RepairDockUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RepairDockUpdate
{
public:
	RepairDockUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x90];
};

// ?friend_newModuleInstance@RepairDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *RepairDockUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RepairDockUpdate(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRepairDockUpdateInstanceNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitRepairDockUpdateInstanceNew(Thing *thing, const ModuleData *moduleData)
{
	RepairDockUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
