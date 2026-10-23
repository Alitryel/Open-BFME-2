// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmePod40: back()'s only call goes to the rowed
// _Deque_iterator_base<BfmePod40>::_M_decrement at 0x00421B68 (stlport_pod_deque_bodies.cpp).
#include <deque>

struct BfmePod40 { int a[10]; };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> void _Deque_iterator_base<BfmePod40>::_M_decrement(); }

template BfmePod40 &_STL::deque<BfmePod40, _STL::allocator<BfmePod40> >::back(void);
