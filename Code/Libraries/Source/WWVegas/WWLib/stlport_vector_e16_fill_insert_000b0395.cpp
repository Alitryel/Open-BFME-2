// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAEXPAUBfmeE16@@IABU3@@Z @0x000B0395 227B. vector<BfmeE16> fill-insert POD false_type path.
// Evidence: rowed BfmeE16 helpers 0x000ADE67 0x005B2B1E 0x004218D5 0x000ADE8D plus overflow 0x005B3970; /Ob0 keeps copy-backward wrapper and /G7 fixes registers vs o1 sibling.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<BfmeE16,allocator<BfmeE16> >::_M_clear(); }
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeE16, BfmeE16>(BfmeE16 *, BfmeE16 const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmeE16@@U1@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAEPAUBf:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> BfmeE16 *_STLP_alloc_proxy<BfmeE16 *, BfmeE16, allocator<BfmeE16> >::allocate(size_t); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}
// _M_insert_overflow is stlport_vector_e16_noexc.cpp's row 0x005B3970, whose
// body inlines size(), max, the proxy allocate, _M_clear and _M_set. /Ob0 keeps
// those calls out of line, so the stock body is spelled with them expanded.
namespace _STL {
template <> inline void vector<BfmeE16, allocator<BfmeE16> >::_M_insert_overflow(
	BfmeE16 *__position, const BfmeE16 &__x, const __false_type &,
	size_type __fill_len, bool __atend)
{
	const size_type __old_size = this->_M_finish - this->_M_start;
	const size_type __len = __old_size + *(__old_size < __fill_len ? &__fill_len : &__old_size);

	BfmeE16 *__new_start = this->_M_end_of_storage.allocator<BfmeE16>::allocate(__len, 0);
	BfmeE16 *__new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
	if (__fill_len == 1) {
		_Construct(__new_finish, __x);
		++__new_finish;
	} else
		__new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
	if (!__atend)
		__new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
	if (this->_M_start != 0)
		::free((void *)this->_M_start);
	this->_M_start = __new_start;
	this->_M_finish = __new_finish;
	this->_M_end_of_storage._M_data = __new_start + __len;
}
}
template void _STL::vector<BfmeE16>::_M_fill_insert(
	BfmeE16 *, unsigned int, const BfmeE16 &);
