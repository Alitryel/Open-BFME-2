// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyWarehouseDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EFF4, 59 bytes. Dedicated TU: the ZH header sizes the class at
// 0x88 but retail news 0x8C (4-byte growth; the rowed (Thing*,ModuleData*)
// ctor at 0x4A7DEA is placed). TU-local 0x8C-byte class plus the
// declared-only ctor reproduces the factory stub; operator new and __EH_prolog
// resolve via their rows. Recipe: DozerAIUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyWarehouseDockUpdate
{
public:
	SupplyWarehouseDockUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@SupplyWarehouseDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyWarehouseDockUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyWarehouseDockUpdate(thing, moduleData));
}
