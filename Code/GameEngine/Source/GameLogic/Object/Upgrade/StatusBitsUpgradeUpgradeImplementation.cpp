// cl: /DNDEBUG /MD
//
// StatusBitsUpgrade::upgradeImplementation and upgradeRemovalImplementation,
// retail 0x004B49AD and 0x004B49E2 (53 bytes each). The BFME1 donor confirms
// the two inverse StatusToSet/StatusToClear operations. BFME2 target evidence
// supplies the ModuleData offsets (+0x118 and +0x128, from the matched
// StatusBitsUpgrade parse table at 0x004B493E and module-data constructor),
// the Object mask setter at 0x0028CDEB, and the apply/remove wrappers at
// 0x004CE4A0/0x004CE4A8. The module's +0x10 UpgradeMux view gives these
// implementations their negative offsets to ModuleData and Object.

#include "StatusBitsUpgradeView.h"

void StatusBitsUpgrade::upgradeImplementation()
{
	Object *object = getObject();
	const StatusBitsUpgradeModuleData *data =
		(const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToSet, true);
	data = (const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToClear, false);
	rva004CE4A0();
}

void StatusBitsUpgrade::upgradeRemovalImplementation()
{
	Object *object = getObject();
	const StatusBitsUpgradeModuleData *data =
		(const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToSet, false);
	data = (const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToClear, true);
	rva004CE4A8();
}
