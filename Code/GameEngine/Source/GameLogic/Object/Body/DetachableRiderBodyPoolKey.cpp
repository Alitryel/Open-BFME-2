// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@DetachableRiderBody@@UBE?AW4NameKeyType@@XZ @0x4C1BE4
// (69B): cached pool-name key for DetachableRiderBody. The class
// identity comes from the pool-name string the body pushes
// ("DetachableRiderBody"); the body guards a function-local static
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

class DetachableRiderBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DetachableRiderBody@@UBE?AW4NameKeyType@@XZ
NameKeyType DetachableRiderBody::getModuleNameKey() const
{
	static NameKeyType TheDetachableRiderBodyPoolKey =
		TheNameKeyGenerator->nameToKey("DetachableRiderBody");
	return TheDetachableRiderBodyPoolKey;
}
