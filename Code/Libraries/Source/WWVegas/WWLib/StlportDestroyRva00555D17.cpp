// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// STLport 4.5.3 _Destroy(T*) instantiations, three 9-byte bodies at retail
// 0x00555D17, 0x00555D20 and 0x00555D29: load the pointer into ecx and
// tail-jump to the element's rowed destructor (0x0038A1F2
// ~BfmeOpaqueOwnedRecord1432, 0x00555ADF ~BfmeOpaqueOwnedRecord1408,
// 0x00555B79 ~Rva00555B79). The element spellings are those rows'
// address-derived or opaque names; their layouts are not needed here.
#include <memory>

struct BfmeOpaqueOwnedRecord1432 { ~BfmeOpaqueOwnedRecord1432(); };
struct BfmeOpaqueOwnedRecord1408 { ~BfmeOpaqueOwnedRecord1408(); };
class Rva00555B79 { public: ~Rva00555B79(); };

template void _STL::_Destroy(BfmeOpaqueOwnedRecord1432 *);
template void _STL::_Destroy(BfmeOpaqueOwnedRecord1408 *);
template void _STL::_Destroy(Rva00555B79 *);
