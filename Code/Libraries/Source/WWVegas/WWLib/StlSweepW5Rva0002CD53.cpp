// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// 4-byte narrow-string slot: retail's range destroy 0x0002CB64 steps by 4 and calls
// the string destructor 0x0048BA39, reached here by a qualified call.
struct Rva0048BA39StringElement { ~Rva0048BA39StringElement(); };
struct Rva0002CD53Element
{
	__forceinline ~Rva0002CD53Element() { ((Rva0048BA39StringElement *)this)->Rva0048BA39StringElement::~Rva0048BA39StringElement(); }
	char bytes[4];
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0002CD53Element, _STL::allocator<Rva0002CD53Element> >::_M_clear(void);
