// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const { return *(begin() + __n); }
}



// The table is the case-insensitive AsciiString-keyed one: this find's only
// call goes to the rowed _M_find<AsciiString> at 0x0002C9E7
// (stlport_hashtable_nocase_asciistring_m_find.cpp, whose doc names this body
// 0x0002CB7D as its caller). Key, functors and placeholder value repeat that
// unit's view; _M_find is declared only so its row serves the call.
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
		bool operator()(const AsciiString &a, const AsciiString &b) const;
	};
}
struct Rva0002C9E7Value
{
	int m_value;
};
typedef _STL::pair<const AsciiString, Rva0002C9E7Value> NoCaseAsciiValue;
typedef _STL::hashtable<NoCaseAsciiValue, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<NoCaseAsciiValue>, rts::equal_to<AsciiString>,
	_STL::allocator<NoCaseAsciiValue> > NoCaseAsciiHashtable;
template NoCaseAsciiHashtable::iterator NoCaseAsciiHashtable::find<AsciiString>(const AsciiString &);
// The outer hash_map::find at retail 0x0002CCAF (20 bytes): forwards the
// result slot and the argument to the table member above.
typedef _STL::hash_map<AsciiString, Rva0002C9E7Value, rts::hash<AsciiString>, rts::equal_to<AsciiString>,
	_STL::allocator<NoCaseAsciiValue> > HM_0002CCAF;
template HM_0002CCAF::iterator HM_0002CCAF::find(const AsciiString &);
