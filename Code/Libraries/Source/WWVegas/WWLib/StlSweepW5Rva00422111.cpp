// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

// 12-byte element without teardown: retail's deque destroy 0x00421E7E steps by 0x0C
// and only advances the iterator.
struct Rva00422111Element { float x, y, z; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, Rva00422111Element>(_STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, _STL::_Deque_iterator<Rva00422111Element, _STL::_Nonconst_traits<Rva00422111Element> >, Rva00422111Element *);
