// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// istreambuf_iterator<char>::equal is retail's 126-byte body at 0x0000FA00, owned by
// stlport_narrow_istreambuf_iterator_equal.cpp. This unit's copy (with _M_getc out of
// line) is not retail's and came before it in link order; the body still inlines
// here, imported, so the unit emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool istreambuf_iterator<char, char_traits<char> >::equal(const istreambuf_iterator<char, char_traits<char> >& __i) const {
  if (this->_M_buf)
    this->_M_getc();
  if (__i._M_buf)
    __i._M_getc();
  return this->_M_eof == __i._M_eof;
}
}

#include <cstddef>
// __get_monetary_value is retail 0x00011E30 (stlport_narrow_get_monetary_value.cpp); this unit only calls it.
// bfme link decl-only begin
namespace _STL { template <> bool __get_monetary_value<istreambuf_iterator<char, char_traits<char> >, back_insert_iterator<basic_string<char, char_traits<char>, allocator<char> > >, char>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> >, back_insert_iterator<basic_string<char, char_traits<char>, allocator<char> > >, ctype<char> const &, char, int, char, basic_string<char, char_traits<char>, allocator<char> > const &, bool &); }
// back_insert_iterator<string>::operator= (row 0x00019160) was emitted only through the removed copy above.
namespace _STL { typedef back_insert_iterator<basic_string<char, char_traits<char>, allocator<char> > > bfmeMoneyGetOutIt;
static bfmeMoneyGetOutIt &(bfmeMoneyGetOutIt::*bfmeMoneyGetOutAssign)(const char &) = &bfmeMoneyGetOutIt::operator=; }
// bfme link decl-only end
// bfme link decl-only begin
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::_M_insert_aux(char *, char); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
