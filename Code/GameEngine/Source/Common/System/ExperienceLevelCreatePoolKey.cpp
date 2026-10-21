// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@ExperienceLevelCreate@@UBE?AW4NameKeyType@@XZ @0x4B91AB
// (69B): cached pool-name key for ExperienceLevelCreate. The class
// identity comes from the pool-name string the body pushes
// ("ExperienceLevelCreate"); the body guards a function-local static
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

class ExperienceLevelCreate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ExperienceLevelCreate@@UBE?AW4NameKeyType@@XZ
NameKeyType ExperienceLevelCreate::getModuleNameKey() const
{
	static NameKeyType TheExperienceLevelCreatePoolKey =
		TheNameKeyGenerator->nameToKey("ExperienceLevelCreate");
	return TheExperienceLevelCreatePoolKey;
}
