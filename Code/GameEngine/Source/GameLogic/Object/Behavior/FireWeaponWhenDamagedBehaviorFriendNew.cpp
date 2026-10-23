// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FireWeaponWhenDamagedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C2F5, 56 bytes. Dedicated TU: retail news 0x4C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x482803. Class identity is the
// "FireWeaponWhenDamagedBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FireWeaponWhenDamagedBehavior
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4C];
};

// ?friend_newModuleInstance@FireWeaponWhenDamagedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *FireWeaponWhenDamagedBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FireWeaponWhenDamagedBehavior(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitFireWeaponWhenDamagedBehaviorFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitFireWeaponWhenDamagedBehaviorFriendNew(Thing *thing, const ModuleData *moduleData)
{
	FireWeaponWhenDamagedBehavior::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
