// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ??1TerrainResourceBehaviorModuleData@@UAE@XZ @ 0x00482275 48B
// Implicit virtual dtor restoring base vtable 0x00BBB554 with no base call.
// Member at +0x18 via pinned 0x00360D26. Layout from ctor TU 0x0048202F
// (base 8 radius +8 maxIncome +0xC interval +0x10 highPri +0x14 visible +0x15
// pad +0x16 member +0x18). Vtable 0x00849440 slot 0 is ??_G 0x00482259.
// ShareExperienceBehaviorModuleDataDtor precedent.
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// Native teardown restores Snapshot; the intermediate data base adds +4 only.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
class TerrainResourceBehaviorModuleData : public ModuleData
{
public:
	TerrainResourceBehaviorModuleData(); // rowed in TerrainResourceBehaviorModuleDataCtor.cpp
	// Native table C49440 slot24 is 47A6A9: return this.
	virtual const void *slot24() const { return this; }
// Implicit virtual dtor (never declared, never defined)
private:
	int m_gap04;
	float m_radius;
	int m_maxIncome;
	int m_incomeInterval;
	bool m_highPriority;
	bool m_visible;
	unsigned char m_pad16[2];
	Rva003623E5Filter m_member18;
	int m_upgrade;
	float m_upgradeBonusPercent;
};
// Emit the native implicit destructor without a synthetic constructor/vtable.
void destroyTerrainResourceBehaviorModuleData(TerrainResourceBehaviorModuleData *terrainResourceBehaviorModuleData)
{
	terrainResourceBehaviorModuleData->TerrainResourceBehaviorModuleData::~TerrainResourceBehaviorModuleData();
}
