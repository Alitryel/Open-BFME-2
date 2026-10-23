// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ArmorUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FDC7, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B3468. Class identity is the
// "ArmorUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ArmorUpgrade
{
public:
	ArmorUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@ArmorUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *ArmorUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ArmorUpgrade(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitArmorUpgradeFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitArmorUpgradeFriendNew(Thing *thing, const ModuleData *moduleData)
{
	ArmorUpgrade::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
