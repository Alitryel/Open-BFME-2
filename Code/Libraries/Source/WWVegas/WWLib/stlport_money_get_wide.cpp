// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> bool __get_decimal_integer<unsigned short *, long double>(unsigned short *&, unsigned short *&, long double &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > money_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, bool, ios_base &, int &, long double &) const; }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t) const; }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
template class _STL::money_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
