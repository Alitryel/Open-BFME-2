#pragma once

// Shared accessed module-data prefix. Offsets and the zero-block helper are
// preserved from the byte-verified constructor and update views.
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

class DemoTrapUpdateModuleData
{
public:
	DemoTrapUpdateModuleData();

public:
	const void *m_vtable;
	unsigned int m_unused04;
	unsigned int m_detonationWeapon;			// +0x08
	Rva0024C7B3Member m_zeroBlock;			// +0x0C
	unsigned int m_manualModeWeaponSlot;		// +0x28
	unsigned int m_detonationWeaponSlot;		// +0x2C
	unsigned int m_proximityModeWeaponSlot;		// +0x30
	float m_triggerDetonationRange;			// +0x34
	unsigned int m_scanRate;				// +0x38
	bool m_defaultsToProximityMode;			// +0x3C
	bool m_autoDetonationWithFriends;		// +0x3D
	bool m_detonateWhenKilled;				// +0x3E
};

