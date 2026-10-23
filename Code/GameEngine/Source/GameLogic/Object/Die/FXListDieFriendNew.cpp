// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FXListDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CAA8, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4865DD. Class identity is the
// "FXListDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FXListDie
{
public:
	FXListDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@FXListDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *FXListDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FXListDie(thing, moduleData));
}

#pragma inline_depth(0)
// ?bfmeEmitFXListDieFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitFXListDieFriendNew(Thing *thing, const ModuleData *moduleData)
{
	FXListDie::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
