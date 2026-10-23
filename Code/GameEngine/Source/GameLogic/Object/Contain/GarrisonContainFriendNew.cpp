// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GarrisonContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BA5B, 59 bytes. Dedicated TU: retail news 0x9E0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x477F06. Class identity is the
// "GarrisonContain" literal ModuleFactory registers alongside this stub and the
// GarrisonContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GarrisonContain
{
public:
	GarrisonContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9E0];
};

// ?friend_newModuleInstance@GarrisonContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *GarrisonContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GarrisonContain(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitGarrisonContainFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitGarrisonContainFriendNew(Thing *thing, const ModuleData *moduleData)
{
	GarrisonContain::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
