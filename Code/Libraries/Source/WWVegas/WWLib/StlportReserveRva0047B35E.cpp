// Target boundary 0x0047B35E/125: the body reserves storage for a vector
// (start/finish/end at +0/+4/+8) with 24-byte elements. The target calls the
// matched allocate/copy helper at 0x0047A6C0 and the shared 24-byte allocator
// at 0x00395944. The element's application type and payload are not established.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_MEMBER_TEMPLATES /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native allocation/copy 0x0047A6C0 has no exception frame or cleanup.
// Match that STLport configuration here as in its existing Pod24 owner;
// otherwise this unit emits a non-retail EH copy of the called helper.
#include <vector>

// Address-derived codegen view; only the 24-byte stride is witnessed.
struct Rva0047B35EElement { int opaque[6]; };

template void _STL::vector<Rva0047B35EElement,
                            _STL::allocator<Rva0047B35EElement> >::reserve(unsigned int);
