// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }
// bfme link decl-only begin
namespace _STL { template <> basic_ifstream<unsigned short, char_traits<unsigned short> >::basic_ifstream(char const *, int); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(char const *, int); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(const locale &); }
// bfme link decl-only end
// ?bfmeAnchorWideIfstreamAssign absent-from-retail
void bfmeAnchorWideIfstreamAssign(_STL::string &s, char *first, char *last)
{
	s.assign(first, last);
}
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
template class _STL::basic_ifstream<wchar_t, _STL::char_traits<wchar_t> >;
