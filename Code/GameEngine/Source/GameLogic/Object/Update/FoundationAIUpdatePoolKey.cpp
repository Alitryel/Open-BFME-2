// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@FoundationAIUpdate@@UBE?AW4NameKeyType@@XZ @0x455167
// (69B): cached pool-name key for FoundationAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("FoundationAIUpdate"); the body guards a function-local static
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

class FoundationAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FoundationAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType FoundationAIUpdate::getModuleNameKey() const
{
	static NameKeyType TheFoundationAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("FoundationAIUpdate");
	return TheFoundationAIUpdatePoolKey;
}

