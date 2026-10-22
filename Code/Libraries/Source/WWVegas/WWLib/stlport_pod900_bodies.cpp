// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Isolated 900-byte placeholder view. The other large-element operations do
// not depend on its unresolved non-trivial owner. Preserve the original
// compiler settings and calls while the owner reconciliation is pending.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#include <vector>
struct BfmePod900 { int a[225]; };
// _Construct<BfmePod900> is the rowed non-trivial copy construct at 0x004CB8DE: declare it so this
// unit calls it rather than emitting its own trivial copy (as stlport_pod_vector_bodies.cpp does).
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod900, BfmePod900>(BfmePod900 *__p, const BfmePod900 &__val); }
template class _STL::vector<BfmePod900, _STL::allocator<BfmePod900 > >;
