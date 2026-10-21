// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@AimWeaponBehavior@@UBE?AW4NameKeyType@@XZ @0x45b198
// (69B): cached pool-name key for AimWeaponBehavior. The class
// identity comes from the pool-name string the body pushes
// ("AimWeaponBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AimWeaponBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AimWeaponBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType AimWeaponBehavior::getModuleNameKey() const
{
	static NameKeyType TheAimWeaponBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("AimWeaponBehavior");
	return TheAimWeaponBehaviorPoolKey;
}

