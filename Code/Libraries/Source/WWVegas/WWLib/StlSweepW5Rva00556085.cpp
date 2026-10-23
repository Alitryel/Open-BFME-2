// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

// 1432-byte element: retail's deque destroy 0x00555D32 steps by 0x598 and calls the
// destructor 0x0038A1F2, reached here by a qualified call.
struct BfmeOpaqueOwnedRecord1432 { ~BfmeOpaqueOwnedRecord1432(); };
struct Rva00556085Element
{
	__forceinline ~Rva00556085Element() { ((BfmeOpaqueOwnedRecord1432 *)this)->BfmeOpaqueOwnedRecord1432::~BfmeOpaqueOwnedRecord1432(); }
	char bytes[1432];
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva00556085Element, _STL::_Nonconst_traits<Rva00556085Element> >, Rva00556085Element>(_STL::_Deque_iterator<Rva00556085Element, _STL::_Nonconst_traits<Rva00556085Element> >, _STL::_Deque_iterator<Rva00556085Element, _STL::_Nonconst_traits<Rva00556085Element> >, Rva00556085Element *);
