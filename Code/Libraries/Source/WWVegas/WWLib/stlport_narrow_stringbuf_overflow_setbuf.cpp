// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 narrow basic_stringbuf members that retail compiled with /O1
// (EBP frames, uninlined push_back): overflow (0x1F95C4) and setbuf
// (0x1F9889). Sibling TU stlport_narrow_ostringstream.cpp keeps the base flags.
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

#include <sstream>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> fpos<int>::fpos(long); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::~basic_stringbuf(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> fpos<int> fpos<int>::operator-(long); }
namespace _STL { template <> fpos<int> & fpos<int>::operator-=(long); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_xsputnc(char, int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
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
template class _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> >;
