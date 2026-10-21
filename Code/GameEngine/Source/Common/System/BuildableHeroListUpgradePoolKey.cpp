// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@BuildableHeroListUpgrade@@UBE?AW4NameKeyType@@XZ @0x4B82CB
// (69B): cached pool-name key for BuildableHeroListUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("BuildableHeroListUpgrade"); the body guards a function-local static
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

class BuildableHeroListUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BuildableHeroListUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType BuildableHeroListUpgrade::getModuleNameKey() const
{
	static NameKeyType TheBuildableHeroListUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("BuildableHeroListUpgrade");
	return TheBuildableHeroListUpgradePoolKey;
}

struct FieldParse;
extern const int g_emptyFieldParseTable[4];
class MultiIniFieldParse
{
public:
	void add(const FieldParse *f, unsigned int extraOffset);
};
int Rva004CE29DGet(void);

class BuildableHeroListUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// ?buildFieldParse@BuildableHeroListUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004B8310 (34B)
void BuildableHeroListUpgradeModuleData::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	multiIniFieldParse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

