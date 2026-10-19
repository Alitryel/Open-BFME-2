// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t) const; }

struct Rva00422111Element { _STL::basic_string<wchar_t> strings[1]; bool operator<(const Rva00422111Element&)const; bool operator==(const Rva00422111Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, Rva00422111Element>(_STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, _STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, Rva00422111Element *);
