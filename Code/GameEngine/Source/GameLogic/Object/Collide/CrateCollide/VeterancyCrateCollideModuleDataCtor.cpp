// cl: /O1 /MD /GX /DNDEBUG
//
// ??0VeterancyCrateCollideModuleData@@QAE@XZ, retail 0x00255B09 (36 bytes).
// Frameless ctor over the rowed CrateCollide base (0x4BC657): zeroes
// m_rangeOfEffect at +0x5C plus m_addsOwnerVeterancy at +0x60 plus m_isPilot
// at +0x61 through one xor-shared zero, installs the folded vtable 0x00BF3AC0
// mid-body through the ??_7 pin (Devastate precedent: virtual classes with
// declared-only virtual dtors and no source store), then stores
// m_affectsUpToLevel 10 at +0x64. Field identity is the chained
// buildFieldParse table 0x00BEFB60 (EffectRange plus AddsOwnerVeterancy plus
// IsPilot plus AffectsUpToLevel) joined to the ZH VeterancyCrateCollide.h
// donor (BFME2 adds AffectsUpToLevel). Sole raw caller is the ModuleData
// factory 0x255B2D which news 0x68.

// The table is defined (as g_00BF3AC0) by MoneyCrateCollideModuleDataCtor.cpp.
extern const void *const g_00BF3AC0[];

class __declspec(novtable) CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();

private:
	unsigned char m_pad[0x5C - 4];
};

class __declspec(novtable) VeterancyCrateCollideModuleData : public CrateCollideModuleData
{
public:
	VeterancyCrateCollideModuleData();

private:
	unsigned int m_rangeOfEffect;		// +0x5C
	bool m_addsOwnerVeterancy;		// +0x60
	bool m_isPilot;				// +0x61
	unsigned int m_affectsUpToLevel;	// +0x64
};

inline VeterancyCrateCollideModuleData::VeterancyCrateCollideModuleData()
{
	*(unsigned int *)this = ((unsigned int)g_00BF3AC0);
	m_rangeOfEffect = 0;
	m_addsOwnerVeterancy = false;
	m_isPilot = false;
	m_affectsUpToLevel = 10;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeVeterancyCrateCollideModuleDataInlineAnchor@@YAXPAVVeterancyCrateCollideModuleData@@@Z absent-from-retail
void _bfmeVeterancyCrateCollideModuleDataInlineAnchor(VeterancyCrateCollideModuleData *p)
{
    p->VeterancyCrateCollideModuleData::VeterancyCrateCollideModuleData();
}
#pragma inline_depth()
