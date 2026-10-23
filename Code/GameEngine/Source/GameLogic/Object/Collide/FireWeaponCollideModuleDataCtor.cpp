// cl: /O1 /DNDEBUG /MD /GX-
//
// ??0FireWeaponCollideModuleData@@QAE@XZ, retail 0x00254A36 (68 bytes).
// Frameless ModuleData ctor: installs vtable 0x00C4ED70 explicitly (standalone,
// no base: the real Behavior/Collide hierarchy lives in the ZH headers with
// different bytes, so a private novtable view emitted differing COMDAT copies)
// ahead of the two 128-bit status-mask resets through the rowed
// bitset<128>::reset at 0x0024CA24, clears the +0x08 word, zeroes both mask
// structs with the CRT memset import, and clears the fire-once flag. No base
// call is emitted (retail is frameless here). /GX- keeps the post-store calls
// frameless (no __EH_prolog). Class size 0x30 proven by the data factory 0x00254A7A
// (sole caller, news 0x30). Donor: BFME1 FireWeaponCollide.cpp (ZH header
// keeps UnsignedInt masks; BFME2 widens both to 128-bit masks and drops the
// template NULL init, leaving +0x04 unstored).

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

#include <string.h>

namespace _STL
{

template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
	bitset<_Bits> &reset();
};

}

class FireWeaponCollideModuleData
{
public:
	FireWeaponCollideModuleData();

private:
	const void *m_vtable;	// +0x00 explicit; no virtuals declared, so no vtable is emitted
	void *m_unsourced04;	// +0x04, retail never stores it
	int m_zeroed08;	// +0x08, and-zeroed by the ctor
	_STL::bitset<128> m_requiredStatus;	// +0x0C
	_STL::bitset<128> m_forbiddenStatus;	// +0x1C
	bool m_fireOnce;	// +0x2C
};

inline FireWeaponCollideModuleData::FireWeaponCollideModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C4ED70);
	m_requiredStatus.reset();
	m_forbiddenStatus.reset();
	m_zeroed08 = 0;
	memset(&m_requiredStatus, 0, sizeof(m_requiredStatus));
	memset(&m_forbiddenStatus, 0, sizeof(m_forbiddenStatus));
	m_fireOnce = false;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFireWeaponCollideModuleDataInlineAnchor@@YAXPAVFireWeaponCollideModuleData@@@Z absent-from-retail
void _bfmeFireWeaponCollideModuleDataInlineAnchor(FireWeaponCollideModuleData *fireWeaponCollideModuleData)
{
    fireWeaponCollideModuleData->FireWeaponCollideModuleData::FireWeaponCollideModuleData();
}
#pragma inline_depth()
