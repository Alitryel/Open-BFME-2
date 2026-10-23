// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TunnelContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BCED, 59 bytes. Dedicated TU: retail news 0x9E8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47DBF7. Class identity is the
// "TunnelContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TunnelContain
{
public:
	TunnelContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9E8];
};

// ?friend_newModuleInstance@TunnelContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *TunnelContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TunnelContain(thing, moduleData));
}

// Select-any anchor: this unit owns the row above while other TUs emit it as
// an inline copy. The anchor keeps this unit emitting its copy for the ledger;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitTunnelContainFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitTunnelContainFriendNew(Thing *thing, const ModuleData *moduleData)
{
	TunnelContain::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
