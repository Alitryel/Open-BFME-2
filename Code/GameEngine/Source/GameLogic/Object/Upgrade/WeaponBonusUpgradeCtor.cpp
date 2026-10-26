// cl: /DNDEBUG /MD
//
// ??0WeaponBonusUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B5633, 49 bytes.
// WeaponBonusUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x18 secondary slots (address-of TU-local dummies,
// DIR32-masked). The pool-key proc at 0x4B55EE (nameToKey("WeaponBonusUpgrade"))
// ends exactly where this ctor begins, and the rowed instance factory
// 0x2501E2 (registered under "WeaponBonusUpgrade") is the sole raw caller.
// Row supersedes the ctor pin.

#include "WeaponBonusUpgradeView.h"

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary18;

// ??0WeaponBonusUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B5633
WeaponBonusUpgrade::WeaponBonusUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	*reinterpret_cast<const void **>(this) = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p18 = &s_secondary18;
}
