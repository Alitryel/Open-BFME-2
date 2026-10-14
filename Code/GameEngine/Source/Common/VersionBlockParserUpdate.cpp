// cl: /O1 /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00428B27@VersionBlockParser@@QAEXPBD0@Z @0x00428B27 201B.
// Version-block record update (retail 0x00428B27, WorldBuilder twin 0x0146BC50): finds the key in the
// sorted record table; a missing key with a value appends a new record and re-sorts, a present key
// takes the new value or is erased when the value is empty/null.
// Evidence: target bytes and the WorldBuilder debug body; callees all rowed (equal-range search
// 0x00427EB9 returns {first,last} through its output slot and takes the one-byte flag read back as
// a dword, the trick of lookupVersionValue 0x00427EDA; push_back 0x00428678, sort 0x00428972,
// range erase 0x004286AF). Views follow VersionBlockParserParse.cpp.
// Codegen: /EHs-c- /EHs drops the extern-C no-throw assumption so the inline
// ~basic_string free keeps retail's unwind state store.
#include <vector>
#include <string>
#include <algorithm>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" void *__cdecl memset(void *, int, unsigned);
#pragma intrinsic(memset)
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// The vector instance retail links is the one rowed for the 0x18-byte record
// named BfmeNarrowRecord00427F75; the parser's local entry derives from it.
struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
};

struct VersionBlockEntry : public BfmeNarrowRecord00427F75
{
	VersionBlockEntry();
	~VersionBlockEntry();
};

class VersionBlockKeyCompare
{
public:
	bool operator()(const VersionBlockEntry &a, const VersionBlockEntry &b) const
	{
		return a.m_key < b.m_key;
	}
};

class VersionBlockParser
{
public:
	void rva00428B27(const char *key, const char *value);
	static const void *findEntry(const void *found, const void *first, const void *last, const char *const *key, const void *match);
private:
	int m_size;
	_STL::vector<BfmeNarrowRecord00427F75> m_records;
};

void VersionBlockParser::rva00428B27(const char *key, const char *value)
{
	const void *found;
	volatile char match;
	memset((void *)&match, 0, 1);
	findEntry(&found, &*m_records.begin(), &*m_records.end(), &key, (const void *)(unsigned)*(volatile unsigned *)&match);
	if (found == (const void *)(unsigned)*(volatile unsigned *)&match)
	{
		if (value != 0)
		{
			VersionBlockEntry e;
			e.m_key = key;
			e.m_value = value;
			m_records.push_back(e);
			_STL::sort((VersionBlockEntry *)&*m_records.begin(), (VersionBlockEntry *)&*m_records.end(), VersionBlockKeyCompare());
		}
	}
	else if (value != 0 && *value != 0)
	{
		((BfmeNarrowRecord00427F75 *)found)->m_value = value;
	}
	else
	{
		m_records.erase((_STL::vector<BfmeNarrowRecord00427F75>::iterator)found, (_STL::vector<BfmeNarrowRecord00427F75>::iterator)(unsigned)*(volatile unsigned *)&match);
	}
}
