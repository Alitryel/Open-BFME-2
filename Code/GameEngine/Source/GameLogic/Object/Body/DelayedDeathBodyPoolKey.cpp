// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@DelayedDeathBody@@UBE?AW4NameKeyType@@XZ @0x004C161D
// (69B): cached pool-name key for DelayedDeathBody. The class
// identity comes from the pool-name string the body pushes
// ("DelayedDeathBody"); the body guards a function-local static
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

class DelayedDeathBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DelayedDeathBody@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedDeathBody::getModuleNameKey() const
{
	static NameKeyType TheDelayedDeathBodyPoolKey =
		TheNameKeyGenerator->nameToKey("DelayedDeathBody");
	return TheDelayedDeathBodyPoolKey;
}
