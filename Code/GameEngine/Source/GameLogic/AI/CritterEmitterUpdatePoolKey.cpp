// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@CritterEmitterUpdate@@UBE?AW4NameKeyType@@XZ @0x4C8D41
// (69B): cached pool-name key for CritterEmitterUpdate. The class
// identity comes from the pool-name string the body pushes
// ("CritterEmitterUpdate"); the body guards a function-local static
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

class CritterEmitterUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CritterEmitterUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType CritterEmitterUpdate::getModuleNameKey() const
{
	static NameKeyType TheCritterEmitterUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("CritterEmitterUpdate");
	return TheCritterEmitterUpdatePoolKey;
}
