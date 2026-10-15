// ?bfmeDoInsertQX@BfmeThingQX@@QAEXPADIE@Z
// partial score=0.75 date=2026-10-15
// ?bfmeDoInsertQX@BfmeThingQX@@QAEXPADIE@Z (this bank compiles the char-parameter
// spelling ?bfmeDoInsertQX@BfmeThingQX@@QAEXPADID@Z)
// STLport 4.5.3 basic_string<char>::insert(iterator, size_t, char) (_string.c), retail
// 0x00029530 662B, compiled /Od /Ob1 without EH. This private view is SIZE-EXACT (662/662)
// and every instruction matches except [ebp-x] frame offsets (retail frame 0x70, this at
// -0x64; here 0x54 / -0x48) and the one unresolved call to the empty _Destroy(char*,char*).
// - Retail passes &c straight to fill (lea [ebp+0x10]), so the parameter is char, not the
//   unsigned char of the existing BfmeThingQX pin: an unsigned char adds a conversion temp.
// - Frame slots: retail reserves 7 extra dwords, 2 at each uninitialized_copy call in the
//   in-place paths (before the move temps and after the fill_n temps) and 1 per copy in the
//   reallocation path. Compiling the REAL vendor <string> (/Od /Ob1 /GX- /D_CRTIMP=
//   /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc, _STLP_BFME_COPY_TRIVIAL_EXTERN, explicit
//   instantiation of insert) shows /Ob1 DECLINES ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z
//   (it is called out of line) while keeping retail-size slots: retail's 0x000179B0 is that
//   template folded by ICF with __copy_trivial. Calling __copy_trivial directly (below) gives
//   the right pushes but not the reserved slots; a two-level template chain is inlined, not
//   declined. Next lever: the full vendor chain (uninitialized_copy -> __uninitialized_copy ->
//   __copy_aux -> __copy_ptrs with the _IS_POD_ITER / _BothPtrType / _IsOKToMemCpy tags) so
//   /Ob1 declines it the way the real header does; that call then needs a fold pin at 0x179B0.
// - Hard wall: the empty _Destroy(char*,char*) is called out of line and lands on the shared
//   1-byte ret 0x0069E440; pin_admission refuses a fold pin there (< MIN_LIB_CONCRETE bytes,
//   address already named). The sibling inserts 0x000284D0 and 0x00028820 share it.
// cl: /Od /Ob1 /DNDEBUG /MD
#include <string.h>

namespace _STL
{
void *__copy_trivial(const void *__first, const void *__last, void *__result);
void fill(char *__first, char *__last, const char &__val);
void free(void *);
void _Destroy(char *, char *);

template <class _Tp>
class allocator;

template <>
class allocator<char>
{
public:
	static char *allocate(unsigned int __n, const void *);
};

template <class CharT>
class char_traits;

template <>
class char_traits<char>
{
public:
	static char *assign(char *__s, unsigned int __n, char __c);
	static char *move(char *__s1, const char *__s2, unsigned int __n)
	{
		return __n == 0 ? __s1 : (char *)memmove(__s1, __s2, __n);
	}
};

struct __true_type
{
};


template <class _Size>
inline char *fill_n(char *__first, _Size __n, const char &__val)
{
	fill(__first, __first + __n, __val);
	return __first + __n;
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter __uninitialized_fill_n(_ForwardIter __first, _Size __n,
	const _Tp &__x, const __true_type &)
{
	return fill_n(__first, __n, __x);
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __true_type());
}

template <class _Tp>
inline const _Tp &(max)(const _Tp &__a, const _Tp &__b)
{
	return __a < __b ? __b : __a;
}
}

struct BfmeThingQX
{
	typedef _STL::char_traits<char> _Traits;

	void bfmeDoInsertQX(char *__position, unsigned int __n, char __c);

	unsigned int size() const { return m_finish - m_start; }
	char *allocate(unsigned int __n) { return __n != 0 ? _STL::allocator<char>::allocate(__n, 0) : 0; }
	void deallocate(char *__p, unsigned int) { if (__p != 0) _STL::free(__p); }
	void _M_deallocate_block() { deallocate(m_start, m_end_of_storage - m_start); }
	void _M_construct_null_aux(char *__p, const _STL::__true_type &) { *__p = 0; }
	void _M_construct_null(char *__p) { _M_construct_null_aux(__p, _STL::__true_type()); }

	char *m_start;
	char *m_finish;
	char *m_end_of_storage;
};

void BfmeThingQX::bfmeDoInsertQX(char *__position, unsigned int __n, char __c)
{
	if (__n != 0) {
		if ((unsigned int)(m_end_of_storage - m_finish) >= __n + 1) {
			const unsigned int __elems_after = m_finish - __position;
			char *__old_finish = m_finish;
			if (__elems_after >= __n) {
				(char *)_STL::__copy_trivial((m_finish - __n) + 1, m_finish + 1, m_finish + 1);
				m_finish += __n;
				_Traits::move(__position + __n, __position, (__elems_after - __n) + 1);
				_Traits::assign(__position, __n, __c);
			}
			else {
				_STL::uninitialized_fill_n(m_finish + 1, __n - __elems_after - 1, __c);
				m_finish += __n - __elems_after;
				(char *)_STL::__copy_trivial(__position, __old_finish + 1, m_finish);
				m_finish += __elems_after;
				_Traits::assign(__position, __elems_after + 1, __c);
			}
		}
		else {
			const unsigned int __old_size = size();
			const unsigned int __len = __old_size + (_STL::max)(__old_size, __n) + 1;
			char *__new_start = allocate(__len);
			char *__new_finish = __new_start;
			__new_finish = (char *)_STL::__copy_trivial(m_start, __position, __new_start);
			__new_finish = _STL::uninitialized_fill_n(__new_finish, __n, __c);
			__new_finish = (char *)_STL::__copy_trivial(__position, m_finish, __new_finish);
			_M_construct_null(__new_finish);
			_STL::_Destroy(m_start, m_finish + 1);
			_M_deallocate_block();
			m_start = __new_start;
			m_finish = __new_finish;
			m_end_of_storage = __new_start + __len;
		}
	}
}
