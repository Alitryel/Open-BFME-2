// cl: /EHsc
// stlport
//
// ??0VersionBlockParser@@QAE@PBD@Z at retail 0x00428C04 (63B).
// Constructs the parser over the 512-byte version block: clears the header
// word, default-builds the 0x18-byte record vector at +4 through the
// Vector_base body pinned at 0x00211E58, then parses the block through the
// member pinned at 0x004289B8. Single EH state from the vector member.
// The parser destructor is unrowed so it stays declared-only here; the
// VersionDestructor TU keeps the buffer model that the rowed inner
// destructor (0x002385FF) verifies against.
#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// Retail stores 0x18-byte records with the key string at +0 and the value
// string at +0xC (VersionBlockSearch TU); spelled for readability, the
// constructor only needs the extent.
struct VersionBlockEntry
{
	const char *m_key; // +0
	char m_padAfterKey[8]; // +4, contents unproven
	const char *m_value; // +0xC
	char m_padTail[8]; // +0x10, contents unproven
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<VersionBlockEntry>(VersionBlockEntry *p) { typedef VersionBlockEntry BfmeDestroyT; p->~BfmeDestroyT(); } }

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
	~VersionBlockParser();
private:
	int m_unk0;
	_STL::vector<VersionBlockEntry> m_records;
	// The rowed parser at 0x004289B8 returns success in AL; this caller
	// intentionally discards it. Keep the declaration identical to its owner.
	bool parse(const char *versionBlock);
};

VersionBlockParser::VersionBlockParser(const char *versionBlock)
	: m_unk0(0), m_records()
{
	parse(versionBlock);
}
