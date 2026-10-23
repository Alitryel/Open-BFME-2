// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?push_back@?$vector@UTreeKey00242F5E@@V?$allocator@UTreeKey00242F5E@@@_STL@@@_STL@@QAEXABUTreeKey00242F5E@@@Z @0x0052480E 55B.
// Existing STLport vector view: genuine mutable-pair Construct523DD4 and
// growth5244DC. Native Apt adder524845 passes std::make_pair; erase writes
// its first word. The int spelling follows the existing producer's source
// view, not a recovered original signature.
// Sibling of StlportVectorPushBackSiblings 55B push_backs; flags mirror
// TreeKey00242F5EVectorOverflow plus bfme2_ascii for AsciiString member.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

struct TreeKey00242F5E
{
	int m_id;
	AsciiString m_name;
	TreeKey00242F5E(const TreeKey00242F5E &other);
	~TreeKey00242F5E();
};

extern template void _STL::_Construct<_STL::pair<int, AsciiString>, _STL::pair<int, AsciiString> >(_STL::pair<int, AsciiString> *, const _STL::pair<int, AsciiString> &);

namespace _STL
{
// ?_Construct typed placement adapter absent-from-retail
__forceinline void _Construct(TreeKey00242F5E *p, const TreeKey00242F5E &x)
{
	_STL::_Construct((_STL::pair<int, AsciiString> *)p, *(const _STL::pair<int, AsciiString> *)&x);
}
}


// The native fill worker belongs to the mutable pair family, not every legacy
// TreeKey vector view. Keep this layout-only bridge inline in the caller.
namespace _STL {
// ?MutablePairFillView absent-from-retail
__forceinline TreeKey00242F5E *__uninitialized_fill_n(TreeKey00242F5E *first, unsigned int n,
 const TreeKey00242F5E &x, const __false_type &tag) {
 return (TreeKey00242F5E *)_STL::__uninitialized_fill_n(
  (_STL::pair<int, AsciiString> *)first,n,*(const _STL::pair<int, AsciiString> *)&x,tag);
}
}
template void _STL::vector<TreeKey00242F5E>::push_back(const TreeKey00242F5E &);
