// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CostModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002502DE, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5A06. Class identity is the
// "CostModifierUpgrade" literal ModuleFactory registers alongside this stub and the
// CostModifierUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CostModifierUpgrade
{
public:
	CostModifierUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@CostModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *CostModifierUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CostModifierUpgrade(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitCostModifierUpgradeFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitCostModifierUpgradeFriendNew(Thing *thing, const ModuleData *moduleData)
{
	CostModifierUpgrade::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
