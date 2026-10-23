// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DelayedLuaEventUpdateModuleData constructor lifted from retail.

class DelayedLuaEventUpdateModuleData
{
public:
	DelayedLuaEventUpdateModuleData();
	// Empty destructor: retail's vtable 0x0084ED70 slot 0 0x004A10FD calls
	// 0x0049B47C, which only stores the vtable.
	virtual ~DelayedLuaEventUpdateModuleData() {}
};

// ??0DelayedLuaEventUpdateModuleData@@QAE@XZ
DelayedLuaEventUpdateModuleData::DelayedLuaEventUpdateModuleData()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0DelayedWeaponSetUpgradeUpdateModuleData@@QAE@XZ=??0DelayedLuaEventUpdateModuleData@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0HordeTransportContainDamageModuleData@@QAE@XZ=??0DelayedLuaEventUpdateModuleData@@QAE@XZ")
