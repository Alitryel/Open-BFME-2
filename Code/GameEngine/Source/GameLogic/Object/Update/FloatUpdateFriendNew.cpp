// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FloatUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D0B9, 56 bytes. Dedicated TU: the factory news 0x24; TU-local
// 0x24-byte class plus the declared-only ctor (rowed at 0x48D7C4) reproduces
// the factory stub; operator new and __EH_prolog resolve via their rows.
// Recipe: POWTruckAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FloatUpdate
{
public:
	FloatUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@FloatUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FloatUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FloatUpdate(thing, moduleData));
}
