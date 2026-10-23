// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

// 1408-byte element: retail's deque destroy 0x00555D53 steps by 0x580 and calls the
// destructor 0x00555ADF, reached here by a qualified call.
struct BfmeOpaqueOwnedRecord1408 { ~BfmeOpaqueOwnedRecord1408(); };
struct Rva005560B2Element
{
	__forceinline ~Rva005560B2Element() { ((BfmeOpaqueOwnedRecord1408 *)this)->BfmeOpaqueOwnedRecord1408::~BfmeOpaqueOwnedRecord1408(); }
	char bytes[1408];
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, Rva005560B2Element>(_STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, _STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, Rva005560B2Element *);
