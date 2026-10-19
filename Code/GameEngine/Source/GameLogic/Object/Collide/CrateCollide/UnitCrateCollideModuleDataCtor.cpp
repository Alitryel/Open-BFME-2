// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0UnitCrateCollideModuleData@@QAE@XZ, retail 0x00255A72 (70 bytes). The
// module-data half of UnitCrateCollide: runs the rowed CrateCollideModuleData
// base ctor (0x004BC657), zeroes UnitCount, nulls the UnitName string slot
// and sets the name through StringBase::set (pinned at 0x55F5,
// GrantUpgradeCreateModuleDataCtor precedent for the null-plus-set string
// shape). Field identity is the chained buildFieldParse row (base table plus
// UnitCount/UnitName at 0x00BEFAF4) joined to the ZH UnitCrateCollide.h donor
// (UnsignedInt m_unitCount plus AsciiString m_unitType, both defaulted).
// Virtual classes (DevastateSpecialPowerModuleDataCtor precedent): the
// derived vtable store is compiler-emitted through the ??_7 pin at the true
// vtable 0x00BF39C0 (unique installer at 0x255A8D), which is what places it
// mid-init right after the base call; a source-written store can only land
// last. The base declared-only dtor is the unwindable arming state 0 and the
// string declared-only dtor advances state 1 ahead of the set call.

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const char *str);

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_pad[0x5C - 4];
};

class UnitCrateCollideModuleData : public CrateCollideModuleData
{
public:
	UnitCrateCollideModuleData();
	// Implicit destructor, as in ZH's UnitCrateCollide.h: retail folds it with
	// GrantScienceUpgradeModuleData's (0x0025637D, ??_G 0x00256361 in slot 0).

private:
	unsigned int m_unitCount;			// +0x5C
	AsciiString m_unitType;			// +0x60
};

inline UnitCrateCollideModuleData::UnitCrateCollideModuleData()
	: m_unitType()
{
	m_unitCount = 0;
	m_unitType.set("");
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeUnitCrateCollideModuleDataInlineAnchor@@YAXPAVUnitCrateCollideModuleData@@@Z absent-from-retail
void _bfmeUnitCrateCollideModuleDataInlineAnchor(UnitCrateCollideModuleData *p)
{
    p->UnitCrateCollideModuleData::UnitCrateCollideModuleData();
}
#pragma inline_depth()
