// cl: /DNDEBUG /MD /GX
//
// ??1FireWeaponWhenDamagedBehavior@@UAE@XZ, retail 0x00482551 (234 bytes).
// Behavior-side dtor completing the FireWeaponWhenDamagedBehavior file-unit
// (ctor rowed at 0x00482803 over the same model; deleting dtor at 0x00482A4D
// calls this body). Restores the five vptrs (+0 +0xC +0x10 +0x20 +0x28) then
// releases the eight Weapon slots at +0x2C..+0x48 through the virtual
// deleteInstance slot0 with 0 return-fed to the rowed operator delete at
// 0x0002FD60 then calls the pinned UpdateModule base dtor at 0x0024A797.
// Layout from the rowed ctor TU at 0x00482803 (UpdateModule 0x20 plus
// UpgradeMux at +0x20 plus DamageModuleInterface at +0x28 plus eight Weapon
// slots). Shape follows FireWeaponUpdateDtor at 0x0048BD11 (tracked-pointer
// virtual release slot0 with 0 return-fed operator delete) over the
// PoisonedBehaviorDtor MI precedent.
#include "FireWeaponWhenDamagedView.h"

FireWeaponWhenDamagedBehavior::~FireWeaponWhenDamagedBehavior()
{
	if (m_reactionWeaponPristine != 0) {
		::operator delete(m_reactionWeaponPristine->deleteInstance(0));
	}
	if (m_reactionWeaponDamaged != 0) {
		::operator delete(m_reactionWeaponDamaged->deleteInstance(0));
	}
	if (m_reactionWeaponReallyDamaged != 0) {
		::operator delete(m_reactionWeaponReallyDamaged->deleteInstance(0));
	}
	if (m_reactionWeaponRubble != 0) {
		::operator delete(m_reactionWeaponRubble->deleteInstance(0));
	}
	if (m_continuousWeaponPristine != 0) {
		::operator delete(m_continuousWeaponPristine->deleteInstance(0));
	}
	if (m_continuousWeaponDamaged != 0) {
		::operator delete(m_continuousWeaponDamaged->deleteInstance(0));
	}
	if (m_continuousWeaponReallyDamaged != 0) {
		::operator delete(m_continuousWeaponReallyDamaged->deleteInstance(0));
	}
	if (m_continuousWeaponRubble != 0) {
		::operator delete(m_continuousWeaponRubble->deleteInstance(0));
	}
}
