// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ToppleUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F080, 56 bytes. Dedicated TU: retail news 0x58 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A8201. Class identity is the
// "ToppleUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ToppleUpdate
{
public:
	ToppleUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x58];
};

// ?friend_newModuleInstance@ToppleUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *ToppleUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ToppleUpdate(thing, moduleData));
}

#pragma inline_depth(0)
// ?bfmeEmitToppleUpdateFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitToppleUpdateFriendNew(Thing *thing, const ModuleData *moduleData)
{
	ToppleUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
