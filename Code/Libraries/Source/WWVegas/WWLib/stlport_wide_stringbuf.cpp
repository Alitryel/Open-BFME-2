// cl: /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <sstream>
// bfme link decl-only begin
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end

template class _STL::basic_stringbuf<wchar_t, _STL::char_traits<wchar_t>, _STL::allocator<wchar_t> >;
