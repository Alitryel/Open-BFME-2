// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// INI::parseAsciiStringVector (retail 0x002F196, 36 bytes). Shared vector
// parser behind the AnimationName, RequiredUpgrades, ForbiddenUpgrades and
// ObjectNames table entries: clears the store through the rowed
// vector<AsciiString>::erase at 0x002CCFC (callee-cleaned, so no caller
// add), then reuses the macro-expanding append at 0x002E896 with the same
// four arguments. Mirrors the BFME1 donor shape (erase plus append reuse).

#include "ascii_string.h"
#include <vector>

// The rowed out-of-line erase: an explicit specialization declaration keeps
// the call instead of inlining STLport's in-class body.
namespace _STL
{
template <> vector<AsciiString, allocator<AsciiString> >::iterator
vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last);
}

class INI
{
public:
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiStringVectorAppend(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAsciiStringVector(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	_STL::vector<AsciiString> *vec = (_STL::vector<AsciiString> *)store;
	vec->erase(vec->begin(), vec->end());
	INI::parseAsciiStringVectorAppend(ini, 0, vec, 0);
}
