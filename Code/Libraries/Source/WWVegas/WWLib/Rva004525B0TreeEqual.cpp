// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

#include "string_base.h"

// The set's key is an AsciiString: its compare is StringBase<char>'s
// (retail 0x000069D6, rowed in string_base.cpp), reached through the base.
class Rva004525B0String : public StringBase<char>
{
};

inline bool operator==(const Rva004525B0String &left,
	const Rva004525B0String &right)
{
	return left.compare(right) == 0;
}

typedef _STL::_Rb_tree_iterator<Rva004525B0String,
	_STL::_Const_traits<Rva004525B0String> > Rva004525B0Iterator;

char __cdecl Rva004525B0Equal(Rva004525B0Iterator first,
	Rva004525B0Iterator last, Rva004525B0Iterator second)
{
	return _STL::equal(first, last, second);
}
