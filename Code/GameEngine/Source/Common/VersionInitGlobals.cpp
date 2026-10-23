// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// Extracted from VersionDestructor.cpp so the rest of the unit links cleanly.
#include "ascii_string.h"

void __cdecl destroyVersionRecords(void *first, void *last);
namespace _STL
{
extern "C" void __cdecl free(void *memory) throw(...);
}

struct VersionRecordBuffer
{
	~VersionRecordBuffer()
	{
		if (m_data)
			_STL::free(m_data);
	}
	void *m_data;
};

class VersionBlockParserInner
{
public:
	~VersionBlockParserInner()
	{
		destroyVersionRecords(m_start.m_data, m_finish);
	}
private:
	VersionRecordBuffer m_start;
	void *m_finish;
	void *m_alloc;
};

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
	~VersionBlockParser() {}
	const char *lookupVersionValue(const char *key, const char *defaultValue);
private:
	int m_unk0;
	VersionBlockParserInner m_inner;
};

extern int g_versionMajor;
extern int g_versionMinor;
extern int g_versionBuildNum;
extern int g_versionLocalBuildNum;
extern const char g_versionBlock[512];

int Rva00237D3DCheck();
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount(void);
extern "C" __declspec(dllimport) void __cdecl srand(unsigned int seed);
extern "C" __declspec(dllimport) int __cdecl rand(void);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buffer, const char *format, ...);

namespace _STL
{
template <class _CharT> class char_traits;
template <class _Tp> class allocator
{
public:
	allocator() {}
};
template <class _CharT, class _Traits, class _Alloc>
class basic_string
{
public:
	basic_string(const _CharT *s, const _Alloc &a = _Alloc());
	~basic_string()
	{
		if (_M_start)
			free(_M_start);
	}
	const _CharT *c_str() const { return _M_start; }
private:
	_CharT *_M_start;
	_CharT *_M_finish;
	_CharT *_M_end_of_storage;
};
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > VersionString;

int initVersionGlobals()
{
	VersionBlockParser parser(g_versionBlock);
	if (!Rva00237D3DCheck())
	{
		g_versionMajor = 0;
		srand(GetTickCount());
		g_versionMinor = rand();
		g_versionBuildNum = rand();
		g_versionLocalBuildNum = rand();
	}
	else
	{
		VersionString version(parser.lookupVersionValue("VERSION", "0.0.0.0"));
		sscanf(version.c_str(), "%d.%d.%d.%d", &g_versionMajor, &g_versionMinor, &g_versionBuildNum, &g_versionLocalBuildNum);
	}
	return 1;
}
