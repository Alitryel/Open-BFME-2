// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@MoneyCrateCollide@@UBE?AW4NameKeyType@@XZ @0x4BC988
// (69B): cached pool-name key for MoneyCrateCollide. The class
// identity comes from the pool-name string the body pushes
// ("MoneyCrateCollide"); the body guards a function-local static
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

class MoneyCrateCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@MoneyCrateCollide@@UBE?AW4NameKeyType@@XZ
NameKeyType MoneyCrateCollide::getModuleNameKey() const
{
	static NameKeyType TheMoneyCrateCollidePoolKey =
		TheNameKeyGenerator->nameToKey("MoneyCrateCollide");
	return TheMoneyCrateCollidePoolKey;
}
