// cl: /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <sstream>
// fill_n stays inline here: retail's out-of-line copy is the vector unit's (stlport_vector_word_o1.cpp).
namespace _STL {
template <> __declspec(dllimport) __forceinline
unsigned short *fill_n<unsigned short *, unsigned int, unsigned short>(unsigned short *__first, unsigned int __n, const unsigned short &__val)
{ for ( ; __n > 0; --__n, ++__first) *__first = __val; return __first; }
}
// bfme link decl-only begin
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAGGV?$allocator@G@_STL@@@_STL@@QAEPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short *_STLP_alloc_proxy<unsigned short *, unsigned short, allocator<unsigned short> >::allocate(size_t); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAGPAG@_STL@@YAPAGPAG00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short *__uninitialized_copy<unsigned short *, unsigned short *>(unsigned short *, unsigned short *, unsigned short *, const __true_type &); }
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t) const; }

template class _STL::basic_stringbuf<wchar_t, _STL::char_traits<wchar_t>, _STL::allocator<wchar_t> >;
