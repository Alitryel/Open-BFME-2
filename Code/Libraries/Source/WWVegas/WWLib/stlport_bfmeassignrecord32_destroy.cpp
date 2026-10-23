// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@PAUBfmeAssignRecord32@@@_STL@@YAXPAUBfmeAssignRecord32@@0@Z
// @ 0x00173AE0 (25B): range destroy over 32-byte BfmeAssignRecord32 elements
// via the rowed dtor at 0x0017330A with 0x20 stride. Called by 0x00173E1E,
// 0x00173EBA and 0x00173FB6. The TU also emits the scalar deleting dtor
// ??_GBfmeAssignRecord32@@QAEPAXI@Z @ 0x00173500 (28B) which calls the same
// rowed dtor then the rowed operator delete at 0x0002FD60.
#include <vector>

struct BfmeAssignRecord32 {
	~BfmeAssignRecord32();
	unsigned char m_pad[32];
};

namespace _STL {
template <>
inline void _Destroy<BfmeAssignRecord32*>(BfmeAssignRecord32* __first, BfmeAssignRecord32* __last)
{
	for (; __first != __last; ++__first)
		__first->~BfmeAssignRecord32();
}
}

template void _STL::vector<BfmeAssignRecord32>::_M_clear();

// _Destroy<BfmeAssignRecord32*> is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStlportBfmeAssignRecord32Destroy@@YAXPAUBfmeAssignRecord32@@0@Z present-unmatched
void bfmeEmitStlportBfmeAssignRecord32Destroy(BfmeAssignRecord32 *__first, BfmeAssignRecord32 *__last)
{
	_STL::_Destroy(__first, __last);
}
#pragma inline_depth()
