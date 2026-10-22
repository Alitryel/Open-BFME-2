// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}






// The element is Rva005EFD53Element: this copy loop's only call goes to the rowed
// _Construct<Rva005EFD53Element> at 0x005F09FF (Rva005EFD53ElementConstruct.cpp),
// declared only here.
#include "../../../../GameEngine/Source/Common/RegionIconSlotReferenceView.h"
namespace _STL { template <> void _Construct<Rva005EFD53Element, Rva005EFD53Element>(Rva005EFD53Element *, const Rva005EFD53Element &); }

template Rva005EFD53Element * _STL::__uninitialized_copy<Rva005EFD53Element const *, Rva005EFD53Element *>(Rva005EFD53Element const *, Rva005EFD53Element const *, Rva005EFD53Element *, _STL::__false_type const &);
