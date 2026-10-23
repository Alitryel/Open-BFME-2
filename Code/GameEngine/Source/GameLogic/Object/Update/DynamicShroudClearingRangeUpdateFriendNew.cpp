// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DynamicShroudClearingRangeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "DynamicShroudClearingRangeUpdate"
// (addModule pairs the name with it). news 0x230 and runs the declared-only
// module ctor, pinned at 0x0048B067.

class Thing;
class ModuleData;
class Module;

class DynamicShroudClearingRangeUpdate
{
public:
	DynamicShroudClearingRangeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x230];
};

// ?friend_newModuleInstance@DynamicShroudClearingRangeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
inline Module *DynamicShroudClearingRangeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DynamicShroudClearingRangeUpdate(thing, moduleData));
}

#pragma inline_depth(0)
// ?bfmeEmitDynamicShroudClearingRangeUpdateFriendNew@@YAXPAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitDynamicShroudClearingRangeUpdateFriendNew(Thing *thing, const ModuleData *moduleData)
{
	DynamicShroudClearingRangeUpdate::friend_newModuleInstance(thing, moduleData);
}
#pragma inline_depth()
