// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ @0x4543eb
// (69B): cached pool-name key for GettingBuiltBehavior. The class
// identity comes from the pool-name string the body pushes
// ("GettingBuiltBehavior"); the body guards a function-local static
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

class GettingBuiltBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType GettingBuiltBehavior::getModuleNameKey() const
{
	static NameKeyType TheGettingBuiltBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("GettingBuiltBehavior");
	return TheGettingBuiltBehaviorPoolKey;
}

