// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@AutoAbilityBehavior@@UBE?AW4NameKeyType@@XZ @0x45A3CE
// (69B): cached pool-name key for AutoAbilityBehavior. The class
// identity comes from the pool-name string the body pushes
// ("AutoAbilityBehavior"); the body guards a function-local static
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

class AutoAbilityBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AutoAbilityBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType AutoAbilityBehavior::getModuleNameKey() const
{
	static NameKeyType TheAutoAbilityBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	return TheAutoAbilityBehaviorPoolKey;
}
