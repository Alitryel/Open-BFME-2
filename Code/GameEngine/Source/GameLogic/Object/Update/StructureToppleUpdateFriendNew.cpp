// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StructureToppleUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EE07, 56 bytes. Dedicated TU: retail news 0x58 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A5556. Class identity is the
// "StructureToppleUpdate" literal ModuleFactory registers alongside this stub and the
// StructureToppleUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StructureToppleUpdate
{
public:
	StructureToppleUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x58];
};

// ?friend_newModuleInstance@StructureToppleUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *StructureToppleUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StructureToppleUpdate(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStructureToppleUpdateFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitStructureToppleUpdateFriendNew(Thing *thing, const ModuleData *moduleData)
{
	StructureToppleUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
