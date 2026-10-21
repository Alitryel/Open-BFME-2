// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@UntamedAllegianceSpecialPower@@UBE?AW4NameKeyType@@XZ @0x004C7B4F
// (69B): cached pool-name key for UntamedAllegianceSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("UntamedAllegianceSpecialPower"); the body guards a function-local static
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

class UntamedAllegianceSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@UntamedAllegianceSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType UntamedAllegianceSpecialPower::getModuleNameKey() const
{
	static NameKeyType TheUntamedAllegianceSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("UntamedAllegianceSpecialPower");
	return TheUntamedAllegianceSpecialPowerPoolKey;
}
