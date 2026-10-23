// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@AttachUpdate@@UBE?AW4NameKeyType@@XZ @0x491912
// (69B): cached pool-name key for AttachUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AttachUpdate"); the body guards a function-local static
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

class AttachUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AttachUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AttachUpdate::getModuleNameKey() const
{
	static NameKeyType TheAttachUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AttachUpdate");
	return TheAttachUpdatePoolKey;
}

