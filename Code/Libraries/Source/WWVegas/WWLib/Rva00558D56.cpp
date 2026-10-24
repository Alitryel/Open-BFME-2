// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0BFMENetworkQueue1@@QAE@XZ @0x00558D56 21B: Default ctor wraps DequeBase E16 with temp allocator plus 0 then returns this. Evidence: unlock lane calls rowed DequeBase 0x0055334A plus caller 0x00558F07 plus push0 lea-b shape.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include "../../../Include/Lib/BfmeE16.h"
class BFMENetworkQueue1
{
	_STL::_Deque_base<BfmeE16, _STL::allocator<BfmeE16> > m_base;
public:
	BFMENetworkQueue1();
};
BFMENetworkQueue1::BFMENetworkQueue1() : m_base(_STL::allocator<BfmeE16>(), 0)
{
}
