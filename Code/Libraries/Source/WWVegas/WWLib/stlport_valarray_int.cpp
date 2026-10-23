// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <valarray>
// bfme link decl-only begin
namespace _STL { template <> int * fill_n<int *, unsigned int, int>(int *, unsigned int, int const &); }
// bfme link decl-only end

template class _STL::valarray<int>;
