// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <string>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
// bfme link decl-only end

// Native base cleanup is supplied by the independently verified B3C0 owner.
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
// The canonical default constructor is verified at retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }


namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);

template <>
basic_string<char, char_traits<char>, allocator<char> >&
basic_string<char, char_traits<char>, allocator<char> >::assign(
        const basic_string<char, char_traits<char>, allocator<char> >&);

// The retail-proven reserve body is emitted by stlport_narrow_string_reserve.cpp.
template <>
void basic_string<char, char_traits<char>, allocator<char> >::reserve(
        unsigned int);

// Owners emit these retail-proven bodies (stlport_narrow_string_copy.cpp,
// _erase_count.cpp); this unit's explicit instantiation must not.
template <>
basic_string<char, char_traits<char>, allocator<char> >::size_type
basic_string<char, char_traits<char>, allocator<char> >::copy(
        char*, size_type, size_type) const;

template <>
basic_string<char, char_traits<char>, allocator<char> >&
basic_string<char, char_traits<char>, allocator<char> >::erase(
        size_type, size_type);

// Retail's body is emitted by stlport_narrow_string_insert_aux.cpp.
template <>
char *basic_string<char, char_traits<char>, allocator<char> >::_M_insert_aux(char *, char);
}

// bfme link decl-only begin: members whose copies here are not retail's (owned or kept elsewhere)
namespace _STL { template <> char *__find_if(char *, char *, _Eq_char_bound<char_traits<char> >, const random_access_iterator_tag &); }
namespace _STL { template <> reverse_iterator<const char *> __find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >, const random_access_iterator_tag &); }
namespace _STL { template <> char *find_if(char *, char *, _Eq_char_bound<char_traits<char> >); }
namespace _STL { template <> reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const basic_string<char, char_traits<char>, allocator<char> > &, size_t, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(size_t, char, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const char *, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(_String_reserve_t, size_t, const allocator<char> &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::operator=(const basic_string<char, char_traits<char>, allocator<char> > &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(const basic_string<char, char_traits<char>, allocator<char> > &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(size_t, char); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::append(const char *); }
namespace _STL { template <> size_t basic_string<char, char_traits<char>, allocator<char> >::find(const char *, size_t) const; }
namespace _STL { template <> size_t basic_string<char, char_traits<char>, allocator<char> >::find_last_not_of(const char *, size_t, size_t) const; }
// bfme link decl-only end

template class _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFillV16@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?bfmeFillV14@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?rva0082ADB0Fill@@YAXPAD0ABD@Z=?fill@_STL@@YAXPAD0ABD@Z")
#pragma comment(linker, "/alternatename:?bfmeCallVMC@@YAXHHH@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAssignPL@BfmeThingPL@@QAEXPAD0@Z=?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z")
#pragma comment(linker, "/alternatename:?rva0082C6E0CopyValues@@YAPAURva0082C6E0Value@@PAU1@00@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")

// Row 0x000199E0 (_Construct<char,char>) was previously instantiated through _M_insert_aux.
template void _STL::_Construct<char, char>(char *, const char &);
