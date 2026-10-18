// cl: /ICode/Libraries/Source/WWVegas/WWLib/TimeInfoLink /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <string>
// Use the rowed 14-byte string destructor at RVA 0x00142D70.
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
// bfme link decl-only end
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
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > time_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, const tm *, char, char) const; }
template class _STL::time_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
