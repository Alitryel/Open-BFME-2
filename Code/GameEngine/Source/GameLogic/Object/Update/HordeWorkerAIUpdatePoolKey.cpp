// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@HordeWorkerAIUpdate@@UBE?AW4NameKeyType@@XZ @0x49acd0
// (69B): cached pool-name key for HordeWorkerAIUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HordeWorkerAIUpdate"); the body guards a function-local static
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

class HordeWorkerAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeWorkerAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeWorkerAIUpdate::getModuleNameKey() const
{
	static NameKeyType TheHordeWorkerAIUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HordeWorkerAIUpdate");
	return TheHordeWorkerAIUpdatePoolKey;
}

