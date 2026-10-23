// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// stlport
// The element is UnicodeString: this range erase's only call goes to the rowed
// list<UnicodeString>::erase(iterator) at 0x0043BEC9
// (stlport_list_unicodestring_create_node.cpp), and the list<UnicodeString>
// units emit this same range erase.
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "unicode_string.h"

typedef _STL::list<UnicodeString, _STL::allocator<UnicodeString> > UnicodeStringList0052223E;

// Declared only: the rowed single-node erase serves the call.
namespace _STL { template <> UnicodeStringList0052223E::iterator UnicodeStringList0052223E::erase(UnicodeStringList0052223E::iterator); }

template UnicodeStringList0052223E::iterator UnicodeStringList0052223E::erase(UnicodeStringList0052223E::iterator, UnicodeStringList0052223E::iterator);
