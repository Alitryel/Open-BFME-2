// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The copy is trivial: retail's element construct (the BfmeE16 _Construct
// 0x0059CE9E reached through 0x000ADE67) is four movsd, so no copy ctor is
// declared.
struct Rva0022118FElement {Rva0022118FElement();Rva0022118FElement&operator=(const Rva0022118FElement&);~Rva0022118FElement(){}char bytes[16]; bool operator==(const Rva0022118FElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0022118FElement, _STL::allocator<Rva0022118FElement> >::reserve(unsigned int);
