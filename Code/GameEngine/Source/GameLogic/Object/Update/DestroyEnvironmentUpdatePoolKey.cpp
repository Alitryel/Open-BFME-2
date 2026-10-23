// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@DestroyEnvironmentUpdate@@UBE?AW4NameKeyType@@XZ @0x4AC686
// (69B): cached pool-name key for DestroyEnvironmentUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DestroyEnvironmentUpdate"); the body guards a function-local static
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

class DestroyEnvironmentUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DestroyEnvironmentUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DestroyEnvironmentUpdate::getModuleNameKey() const
{
	static NameKeyType TheDestroyEnvironmentUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DestroyEnvironmentUpdate");
	return TheDestroyEnvironmentUpdatePoolKey;
}
