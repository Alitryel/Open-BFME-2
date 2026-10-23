// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 340-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod340 names only the 340-byte stride, matching the pod-vector TU convention.
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
struct BfmePod340 { int a[85]; };
// The rowed _Construct owner is 0x004D9B98. Instantiating only this member
// avoids unrelated vector members and their incompatible whole-class copies.
namespace _STL {
template <> void _Construct<BfmePod340, BfmePod340>(BfmePod340 *, const BfmePod340 &);
}
template BfmePod340 *_STL::vector<BfmePod340, _STL::allocator<BfmePod340> >::_M_allocate_and_copy<const BfmePod340 *>(unsigned int, const BfmePod340 *, const BfmePod340 *);
