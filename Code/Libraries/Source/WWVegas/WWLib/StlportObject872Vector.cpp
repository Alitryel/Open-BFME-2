// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 operations for the target fixed-storage object view.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "Object872.h"
// bfme link decl-only begin
namespace _STL { template <> BfmeObject872 * vector<BfmeObject872, allocator<BfmeObject872> >::erase(BfmeObject872 *, BfmeObject872 *); }
// bfme link decl-only end
// bfme link decl-only: retail's operator= is StlportObject872Assign.cpp's
// 0x002CFF66; this unit's /O2 copy differs and sorted first in link order.
namespace _STL {
template <> vector<BfmeObject872, allocator<BfmeObject872> > &
vector<BfmeObject872, allocator<BfmeObject872> >::operator=(const vector<BfmeObject872, allocator<BfmeObject872> > &);
}
template class _STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> >;
// operator= was the only user of the const-pointer _M_allocate_and_copy row.
template BfmeObject872 *_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> >::_M_allocate_and_copy<const BfmeObject872 *>(size_t, const BfmeObject872 *, const BfmeObject872 *);
