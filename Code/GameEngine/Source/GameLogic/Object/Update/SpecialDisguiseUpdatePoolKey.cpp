// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@SpecialDisguiseUpdate@@UBE?AW4NameKeyType@@XZ @0x004B018E
// (69B): cached pool-name key for SpecialDisguiseUpdate. The class
// identity comes from the pool-name string the body pushes
// ("SpecialDisguiseUpdate"); the body guards a function-local static
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

class SpecialDisguiseUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpecialDisguiseUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType SpecialDisguiseUpdate::getModuleNameKey() const
{
	static NameKeyType TheSpecialDisguiseUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
	return TheSpecialDisguiseUpdatePoolKey;
}
