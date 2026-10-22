// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 128-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod128 names only the 128-byte stride, matching the pod-vector TU convention.
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
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> vector<BfmePod128,allocator<BfmePod128> >::vector(vector<BfmePod128,allocator<BfmePod128> > const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@IAEXPAUB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> void vector<BfmePod128,allocator<BfmePod128> >::_M_insert_overflow(BfmePod128 *,BfmePod128 const &,__false_type const &,unsigned int,bool); }
struct BfmePod128 { int a[32]; };
template class _STL::vector<BfmePod128, _STL::allocator<BfmePod128> >;
