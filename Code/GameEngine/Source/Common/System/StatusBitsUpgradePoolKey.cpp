// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@StatusBitsUpgrade@@UBE?AW4NameKeyType@@XZ @0x4B48F9
// (69B): cached pool-name key for StatusBitsUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("StatusBitsUpgrade"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

#include "../../GameLogic/Object/Upgrade/StatusBitsUpgradeView.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@StatusBitsUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType StatusBitsUpgrade::getModuleNameKey() const
{
	static NameKeyType TheStatusBitsUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("StatusBitsUpgrade");
	return TheStatusBitsUpgradePoolKey;
}
