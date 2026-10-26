// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the radius-decal update constructor to clean C++.

#include "RadiusDecalUpdateView.h"

// ??0RadiusDecalUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RadiusDecalUpdate::RadiusDecalUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_deliveryDecal.clear();
	m_killWhenNoLongerAttacking = false;
	setWakeFrame(getObject(), (UpdateSleepTime)0x3FFFFFFF);
}

// ??1RadiusDecalUpdate@@UAE@XZ, retail 0x003913E4, 91 bytes. Dtor clears the
// delivery decal then tears it down through the rowed 0x330DBA/0x330DD6
// bodies then the UpdateModule base through the pinned 0x24A797 dtor.
// Compiler emits the three vtable stores (0xC1A018 at +0 plus 0xBEFF90 at
// +0xC plus 0xC1A00C at +0x10). Donor is BFME1
// RadiusDecalUpdateDestructor.cpp. Caller is the slot-0 ??_G at 0x3914F9.

RadiusDecalUpdate::~RadiusDecalUpdate()
{
	m_deliveryDecal.clear();
}
