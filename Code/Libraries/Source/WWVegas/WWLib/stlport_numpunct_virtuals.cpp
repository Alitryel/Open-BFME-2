// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// The five virtuals behind numpunct<char>'s vftable at 0x007BBB78 and
// numpunct<wchar_t>'s at 0x007BBB94. No search was needed to identify these -
// the vftable slot IS the identity, and the ledger already holds slot 0 of
// both, so slots 1..5 are do_decimal_point, do_thousands_sep, do_grouping,
// do_truename and do_falsename in declaration order.

#include <locale>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t) const; }
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

namespace _STL
{

char numpunct<char>::do_decimal_point() const
{
	return '.';
}

char numpunct<char>::do_thousands_sep() const
{
	return ',';
}

string numpunct<char>::do_grouping() const
{
	return string();
}

string numpunct<char>::do_truename() const
{
	return _M_truename;
}

string numpunct<char>::do_falsename() const
{
	return _M_falsename;
}

wchar_t numpunct<wchar_t>::do_decimal_point() const
{
	return L'.';
}

wchar_t numpunct<wchar_t>::do_thousands_sep() const
{
	return L',';
}

string numpunct<wchar_t>::do_grouping() const
{
	return string();
}

wstring numpunct<wchar_t>::do_truename() const
{
	return _M_truename;
}

wstring numpunct<wchar_t>::do_falsename() const
{
	return _M_falsename;
}

}
