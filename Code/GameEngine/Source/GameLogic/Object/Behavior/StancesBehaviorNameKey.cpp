// cl: /O1 /DNDEBUG /MD
//
// ?Rva0045EE2CGet@@YA?AW4NameKeyType@@XZ, retail 0x0045EE2C, 43 bytes.
// Lazily-cached StancesBehavior name key via the rowed Cache::get at
// 0x00148F5E. Evidence: body stores the "StancesBehavior" string
// (VA 0x007F5A4C) into a static cache and tail-jmps to Cache::get;
// 12+ callers push eax into the rowed Object::findModule at 0x0028B6D6
// (e.g. 0x0036E27E 0x005D71C7); neighbours StancesBehaviorXfer/Ctor share
// // cl: /O1 /DNDEBUG /MD.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Rva00148F5ECache
{
public:
	Rva00148F5ECache(const char *n);
	NameKeyType get();
private:
	NameKeyType m_key;
	const char *m_name;
};

// ??0Rva00148F5ECache@@QAE@PBD@Z present-unmatched
inline Rva00148F5ECache::Rva00148F5ECache(const char *n) : m_key(NK_UNKNOWN), m_name(n)
{
}

NameKeyType Rva0045EE2CGet()
{
	static Rva00148F5ECache cache("StancesBehavior");
	return cache.get();
}
