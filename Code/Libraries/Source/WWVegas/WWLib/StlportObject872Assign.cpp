// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// STLport 4.5.3 operations for the target fixed-storage object view.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "Object872.h"
// bfme link decl-only begin
namespace _STL { template <> void vector<BfmeObject872, allocator<BfmeObject872> >::_M_insert_overflow(BfmeObject872 *, BfmeObject872 const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> BfmeObject872 * allocator<BfmeObject872>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> BfmeObject872 * vector<BfmeObject872, allocator<BfmeObject872> >::erase(BfmeObject872 *, BfmeObject872 *); }
// bfme link decl-only end
namespace _STL {
// Retail inlines free here; retain that call without emitting a competing helper.
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
}
// Emit the rowed assignment and clear operations without unrelated T() users.
typedef _STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> > BfmeObject872Vector;
template BfmeObject872Vector & BfmeObject872Vector::operator=(const BfmeObject872Vector &);
template void BfmeObject872Vector::clear();
