// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?preprocessMacro@INI@@SAPBDPBD@Z, retail 0x0002D0A9, 156 bytes.
// INI macro expansion: a token starting with a digit is returned as-is
// (high bound tested first; the '-' test is reachable-but-dead, as in BFME 1);
// otherwise it is looked up in the INI macro hash_map (VA 0x00DDF58C,
// BfmeINIMacroTableStorage, owned by INI_loadFile.cpp). On a hit the current
// INI filename (BfmeINICurrentFilename, VA 0x00DDF5B4) is recorded in the
// no-case set at +0x14 when non-empty, and the macro's text is returned.
//
// Target evidence: calls the rowed hashtable::_M_find<AsciiString> 0x0002C9E7
// (ECX = table) and the rowed set::insert 0x0002CA26 (ECX = table+0x14); the
// pair<iterator,bool> it returns shares the 8-byte frame with the find
// iterator. Retail stores the iterator's _M_ht half (mov [ebp-0x10],esi):
// binding find()'s iterator to a const_iterator local is what keeps that
// store and homes the table address in ESI (a plain iterator local folds
// the store away and gives 151 bytes). WorldBuilder twin 0x006D00A0 has the
// same shape (iterator _M_ht stored to its frame, value at node+8 read as an
// AsciiString through str()/peek()).
// Mapped type: the WB twin and the hash_map ctor row 0x0002DC1D show an
// AsciiString; the rowed _M_find 0x0002C9E7 spells it Rva0002C9E7Value, which
// this TU reuses so the call binds that row (here with its AsciiString member).
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
	template <class T> struct equal_to
	{
	};
	template <> struct equal_to<AsciiString>
	{
		bool operator()(const AsciiString &a, const AsciiString &b) const
		{
			return a.compareNoCase(b) == 0;
		}
	};
}

#include <hash_map>
#include <set>

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

struct Rva0002C9E7Value
{
	AsciiString m_text;
};

typedef _STL::hash_map<AsciiString, Rva0002C9E7Value, rts::hash<AsciiString>, rts::equal_to<AsciiString> > MacroMap;
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> NoCaseStringSet;

struct INIMacroTable
{
	MacroMap m_macros;
	NoCaseStringSet m_used;
};

class INI
{
public:
	static const char *preprocessMacro(const char *token);
};

extern AsciiString BfmeINICurrentFilename;
extern unsigned BfmeINIMacroTableStorage[8];
#define TheINIMacroTable (*(INIMacroTable *)BfmeINIMacroTableStorage)

// ?preprocessMacro@INI@@SAPBDPBD@Z
const char *INI::preprocessMacro(const char *token)
{
	char c = token[0];
	if (c <= '9' && c >= '0' && c != '-')
		return token;

	MacroMap::const_iterator it = TheINIMacroTable.m_macros.find(token);
	if (it != TheINIMacroTable.m_macros.end())
	{
		if (BfmeINICurrentFilename != AsciiString::TheEmptyString)
			TheINIMacroTable.m_used.insert(BfmeINICurrentFilename);
		return (*it).second.m_text.str();
	}
	return token;
}
