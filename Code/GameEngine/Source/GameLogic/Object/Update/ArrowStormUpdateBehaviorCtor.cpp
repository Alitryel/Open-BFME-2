// cl: /DNDEBUG /MD /GX
//
// ??0ArrowStormUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004909D7,
// 129 bytes. Behavior-side ctor (rowed instance factory news 0x9C with this
// pinned 2-arg ctor as its sole raw caller; poolkey rowed).
//
// Shape: opaque Rva0044EF5E base (declared-only dtor arms the single EH
// state) plus explicit derived vtable installs plus freelist-node member at
// +0x88 via pinned 0x29FB3B init plus pool reset via 0x26549E alias pin plus
// zero tail. The init context is the address of the last byte of the
// incoming ModuleData slot (framework idiom, shared by all 6 callers).

extern "C" const void *const vtbl_00C4D640[];  // folded, 11 classes; via ??_7LevelGrantSpecialPower@@6BSpecialPowerModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4D640=??_7LevelGrantSpecialPower@@6BSpecialPowerModuleInterface@@@")
extern "C" const void *const vtbl_00C4DEE8[];  // folded, 4 classes; via ??_7GiveOrRestoreUpgradeSpecialPower@@6BRva0044EF5E@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4DEE8=??_7GiveOrRestoreUpgradeSpecialPower@@6BRva0044EF5E@@@")

extern char g_00C4D61C;
extern char g_00C4D700;

class Thing;
class ModuleData;

// Retail's unwind of the base subobject calls the rowed
// ~SpecialAbilityUpdate 0x00451F45 (the dtor of the 0x0044EF5E base).
class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
};

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	~Rva0044EF5E() { ((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::~SpecialAbilityUpdate(); }
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class ArrowStormUpdate : public Rva0044EF5E
{
public:
	ArrowStormUpdate(Thing *thing, const ModuleData *moduleData);
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	int m_90;
	int m_94;
	unsigned char m_98;
};

// ??0ArrowStormUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004909D7
ArrowStormUpdate::ArrowStormUpdate(Thing *thing, const ModuleData *moduleData) :
	Rva0044EF5E(thing, moduleData)
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	void *context = (void *)((char *)&moduleData + 3);
	*(const void **)this = (const void *)(unsigned int)&g_00C4D700;
	*(const void **)((char *)this + 0x0C) = (const void *)((unsigned int)vtbl_00C4D640);
	*(const void **)((char *)this + 0x10) = (const void *)((unsigned int)vtbl_00C4DEE8);
	*(const void **)((char *)this + 0x20) = (const void *)(unsigned int)&g_00C4D61C;
	member->init(context);
	member->reset();
	m_8C = 0;
	m_90 = 0;
	m_94 = 0;
	m_98 = 0;
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1Rva0044EF5E@@QAE@XZ=??1Rva00383D71@@QAE@XZ")
