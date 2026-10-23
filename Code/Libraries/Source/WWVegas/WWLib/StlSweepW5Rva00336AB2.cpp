// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "Object156.h"

// The element is BfmeOpaqueRecord156: retail push_back calls its rowed
// _Construct 0x00333283 (Object156Copy.cpp) and _M_insert_overflow 0x00336101
// (StlportObject156Vector.cpp).

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<BfmeOpaqueRecord156, _STL::allocator<BfmeOpaqueRecord156> >::push_back(BfmeOpaqueRecord156 const &);
