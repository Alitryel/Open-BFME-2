// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <string>
// Inline uses here keep the stock body (with its length_error path), but this unit,
// the first in link order to spell it, must not emit an out-of-line copy: retail's
// _String_base<char>::_M_allocate_block is the 0x00007460 body without that path,
// which stlport_narrow_string_allocate_block.cpp emits. dllimport + forceinline: no __imp_.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _String_base<char, allocator<char> >::_M_allocate_block(size_t __n)
{
	if ((__n <= (max_size() + 1)) && (__n > 0)) {
		_M_start = _M_end_of_storage.allocate(__n);
		_M_finish = _M_start;
		_M_end_of_storage._M_data = _M_start + __n;
	}
	else
		_M_throw_length_error();
}
}
// Native 0x00025AD0 is supplied by stlport_vector_voidptr.cpp.
// Keep this profile from emitting a competing allocator-proxy swap.
namespace _STL {
template <> void swap(_STLP_alloc_proxy<char *, char, allocator<char> > &,
                     _STLP_alloc_proxy<char *, char, allocator<char> > &);
}
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }

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
// Retail's insert(iterator, n, c) at 0x00029530 is emitted by
// stlport_string_insert_fill.cpp; this unit's copy precedes it in link order.
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::insert(char *, size_t, char); }
// bfme link decl-only end

template class _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeFillV14@@YAPADPADID@Z=?assign@?$char_traits@D@_STL@@SAPADPADID@Z")
#pragma comment(linker, "/alternatename:?rva0082ADB0Fill@@YAXPAD0ABD@Z=?fill@_STL@@YAXPAD0ABD@Z")
#pragma comment(linker, "/alternatename:?bfmeCallVMC@@YAXHHH@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAssignPL@BfmeThingPL@@QAEXPAD0@Z=?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z")
#pragma comment(linker, "/alternatename:?rva0082C6E0CopyValues@@YAPAURva0082C6E0Value@@PAU1@00@Z=?__copy_trivial@_STL@@YAPAXPBX0PAX@Z")

// Row 0x000199E0 (_Construct<char,char>) was previously instantiated through _M_insert_aux.
template void _STL::_Construct<char, char>(char *, const char &);

// Retail money_put<wchar_t>::do_put(string), 0x0000DF20+0x449, calls
// the same allocator-base constructor as char strings at 0x00689600.
// Both emitted bodies are 37 bytes and call the folded 11-byte proxy
// constructor at 0x00007410. Keep the wide body available for fold proof.
template _STL::_String_base<wchar_t, _STL::allocator<wchar_t> >::_String_base(
        const _STL::allocator<wchar_t>&);


namespace _STL
{
// The char-range destruction overload in stl/_construct.h is empty.
// Native string insertion calls the shared RET at 0x0069E440 through this
// existing neutral binding; no exclusive original identity is claimed.
void Rva0069E440Destroy(char *, char *) {}
}

namespace _STL
{
// The /Od string-replace and conversion units call this char* copy out of line;
// retail folds it onto __copy_trivial (0x000179B0, pinned there). Supply that
// retail-proven copy of the name.
template <class _InputIter, class _ForwardIter>
inline _ForwardIter Rva000179B0UninitializedCopy(_InputIter __first, _InputIter __last, _ForwardIter __result)
{
	return (_ForwardIter)__copy_trivial(__first, __last, __result);
}
template char *Rva000179B0UninitializedCopy<char *, char *>(char *, char *, char *);
}
