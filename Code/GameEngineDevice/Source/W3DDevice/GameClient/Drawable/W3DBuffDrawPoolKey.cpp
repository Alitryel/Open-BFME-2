// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DBuffDraw@@UBE?AW4NameKeyType@@XZ @0xCEE07
// (69B): cached pool-name key for W3DBuffDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DBuffDraw"); the body guards a function-local static
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

class W3DBuffDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DBuffDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DBuffDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DBuffDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DBuffDraw");
	return TheW3DBuffDrawPoolKey;
}
