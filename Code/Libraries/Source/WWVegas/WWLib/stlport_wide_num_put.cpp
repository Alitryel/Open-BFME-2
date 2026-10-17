// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <stl/_alloc.h>
// Public malloc release uses retail's unoptimized import entry; callers keep the header inline body.
namespace _STL {
#pragma optimize("", off)
template <> __forceinline void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
#pragma optimize("", on)
}

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// The 64-bit integer writers are owned by stlport_write_integer_backward_64.cpp,
// stlport_write_integer_backward_int64.cpp and stlport_write_decimal_backward_u64.cpp.
// This unit's copies are not retail's; declare their instantiations only.
namespace _STL { template <> char * __write_integer_backward<__int64>(char *, int, __int64); }
namespace _STL { template <> char * __write_integer_backward<unsigned __int64>(char *, int, unsigned __int64); }
namespace _STL { template <> char * __write_decimal_backward<unsigned __int64>(char *, unsigned __int64, int, __false_type const &); }

#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
