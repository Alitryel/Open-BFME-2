// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAVUnicodeString@@IV1@@_STL@@YAPAVUnicodeString@@PAV1@IABV1@ABU__false_type@0@@Z retail 0x00054E66 37B
// Evidence: same 37B count-loop plus _Construct shape as other vector fill_n rows; here fills UnicodeString via rowed _Construct 0x00054DF6;
// element and flags match stlport_vector_unicode_reserve.cpp; caller 0x0005B5A3.
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

#include "unicode_string.h"
// bfme link decl-only/import-inline begin: stop this unit emitting non-retail STL copies
namespace _STL { template <> __declspec(dllimport) __forceinline void allocator<UnicodeString>::deallocate(UnicodeString * __a0, unsigned int __a1) const { if (__a0 != 0) ::free((void*)__a0); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<UnicodeString *,UnicodeString,allocator<UnicodeString> >::deallocate(UnicodeString * __a0, unsigned int __a1) { __stl_alloc_rebind(static_cast<allocator<UnicodeString>&>(*this), (UnicodeString*)0).deallocate(__a0, __a1); } }
namespace _STL { template <> _Vector_base<UnicodeString,allocator<UnicodeString> >::~_Vector_base(); }
// bfme link decl-only/import-inline end
// bfme link decl-only begin
namespace _STL { template <> UnicodeString * vector<UnicodeString, allocator<UnicodeString> >::erase(UnicodeString *, UnicodeString *); }
namespace _STL { template <> vector<UnicodeString, allocator<UnicodeString> >::~vector(); }
// bfme link decl-only end
namespace _STL {
template <> void _Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
}

template class _STL::vector<UnicodeString, _STL::allocator<UnicodeString> >;
