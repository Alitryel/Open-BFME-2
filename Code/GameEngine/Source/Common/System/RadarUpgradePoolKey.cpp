// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@RadarUpgrade@@UBE?AW4NameKeyType@@XZ @0x4B4727
// (69B): cached pool-name key for RadarUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("RadarUpgrade"); the body guards a function-local static
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

class RadarUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RadarUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType RadarUpgrade::getModuleNameKey() const
{
	static NameKeyType TheRadarUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("RadarUpgrade");
	return TheRadarUpgradePoolKey;
}
