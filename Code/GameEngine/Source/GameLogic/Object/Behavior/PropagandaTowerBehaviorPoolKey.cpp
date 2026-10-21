// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@PropagandaTowerBehavior@@UBE?AW4NameKeyType@@XZ @0x48191a
// (69B): cached pool-name key for PropagandaTowerBehavior. The class
// identity comes from the pool-name string the body pushes
// ("PropagandaTowerBehavior"); the body guards a function-local static
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

class PropagandaTowerBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PropagandaTowerBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType PropagandaTowerBehavior::getModuleNameKey() const
{
	static NameKeyType ThePropagandaTowerBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("PropagandaTowerBehavior");
	return ThePropagandaTowerBehaviorPoolKey;
}

