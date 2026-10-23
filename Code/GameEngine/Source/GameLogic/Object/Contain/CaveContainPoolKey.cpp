// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@CaveContain@@UBE?AW4NameKeyType@@XZ @0x4663ff
// (69B): cached pool-name key for CaveContain. The class
// identity comes from the pool-name string the body pushes
// ("CaveContain"); the body guards a function-local static
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

class CaveContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CaveContain@@UBE?AW4NameKeyType@@XZ
NameKeyType CaveContain::getModuleNameKey() const
{
	static NameKeyType TheCaveContainPoolKey =
		TheNameKeyGenerator->nameToKey("CaveContain");
	return TheCaveContainPoolKey;
}

