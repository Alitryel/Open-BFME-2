// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 104-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod104 names only the 104-byte stride, matching the pod-vector TU convention.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmePod104 { int a[26]; };
// Call the rowed placement-copy owner at 0x003B8AD8 from the native loop.
namespace _STL { template <> void _Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &); }
// Emit the rowed allocation/copy member without unrelated whole-class copies.
template BfmePod104 *_STL::vector<BfmePod104, _STL::allocator<BfmePod104> >::_M_allocate_and_copy<const BfmePod104 *>(unsigned int, const BfmePod104 *, const BfmePod104 *);
