// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@PoisonedBehavior@@UBE?AW4NameKeyType@@XZ @0x482f27
// (69B): cached pool-name key for PoisonedBehavior. The class
// identity comes from the pool-name string the body pushes
// ("PoisonedBehavior"); the body guards a function-local static
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

class PoisonedBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PoisonedBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType PoisonedBehavior::getModuleNameKey() const
{
	static NameKeyType ThePoisonedBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("PoisonedBehavior");
	return ThePoisonedBehaviorPoolKey;
}

