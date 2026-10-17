char g_00C5FF10;

// cl: /O1 /DNDEBUG /MD
//
// ??0UpgradeMux@@QAE@XZ, retail 0x004CE2A3, 13 bytes. UpgradeMux root
// ctor (frameless leaf: installs vtable (void *)&g_00C5FF10 explicitly over the
// novtable model plus clears the executed flag at +4). Called this-direct
// with no adjustment by 12 behavior-ctor sites (0x4525B8/0x45F5C5/
// 0x460B12/0x48282B/0x482DA6/0x48424E/0x49B586/0x49C12C/0x4A3454/
// 0x4B40AA/0x4B7CE2/0x4C1CAB) as a shared member/base, and declared with
// this exact spelling in the AudioLoopUpgrade/FireWeaponWhenDamaged/
// RadiateFear/AttributeModifierAura behavior TUs (bool m_upgradeExecuted
// at +4); donor ZH UpgradeModule.h backs the UpgradeMux name. Row
// supersedes the same-name pin; the TU-local ALU_UpgradeMux alias pin
// stands for its own TU.

class __declspec(novtable) UpgradeMux
{
public:
	UpgradeMux();

private:
	void *m_vtable; // +0
	bool m_executed; // +4, upgrade-executed flag
};

// ??0UpgradeMux@@QAE@XZ @0x4CE2A3
inline UpgradeMux::UpgradeMux()
	: m_vtable(reinterpret_cast<void *>((void *)&g_00C5FF10)),
	  m_executed(false)
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeUpgradeMuxInlineAnchor@@YAXPAVUpgradeMux@@@Z absent-from-retail
void _bfmeUpgradeMuxInlineAnchor(UpgradeMux *p)
{
    p->UpgradeMux::UpgradeMux();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0ALU_UpgradeMux@@QAE@XZ=??0UpgradeMux@@QAE@XZ")
