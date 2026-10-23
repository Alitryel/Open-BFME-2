// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@CombineHordeSpecialPower@@UBE?AW4NameKeyType@@XZ @0x004C880D
// (69B): cached pool-name key for CombineHordeSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("CombineHordeSpecialPower"); the body guards a function-local static
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

class CombineHordeSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CombineHordeSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType CombineHordeSpecialPower::getModuleNameKey() const
{
	static NameKeyType TheCombineHordeSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("CombineHordeSpecialPower");
	return TheCombineHordeSpecialPowerPoolKey;
}
