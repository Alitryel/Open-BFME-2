// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@BeaconClientUpdate@@UBE?AW4NameKeyType@@XZ @0x004C9607
// (69B): cached pool-name key for BeaconClientUpdate. The class
// identity comes from the pool-name string the body pushes
// ("BeaconClientUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

#include "../../../GameClient/Drawable/Update/BeaconClientUpdateView.h"

// ?getModuleNameKey@BeaconClientUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType BeaconClientUpdate::getModuleNameKey() const
{
	static NameKeyType TheBeaconClientUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("BeaconClientUpdate");
	return TheBeaconClientUpdatePoolKey;
}
