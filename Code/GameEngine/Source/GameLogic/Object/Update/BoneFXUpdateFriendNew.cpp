// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BoneFXUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CC49, 59 bytes. Dedicated TU: retail news 0x638 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4878E6. Class identity is the
// "BoneFXUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BoneFXUpdate
{
public:
	BoneFXUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x638];
};

// ?friend_newModuleInstance@BoneFXUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *BoneFXUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BoneFXUpdate(thing, moduleData));
}
#pragma inline_depth(0)
// ?bfmeEmitBoneFXUpdateFriendNew@@YAXPAVBoneFXUpdate@@@Z present-unmatched
void bfmeEmitBoneFXUpdateFriendNew(BoneFXUpdate *boneFXUpdate)
{
	boneFXUpdate->friend_newModuleInstance(0, 0);
}
#pragma inline_depth()
