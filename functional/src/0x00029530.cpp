// ?bfmeDoInsertQX@BfmeThingQX@@QAEXPADIE@Z
// partial score=0.903323 date=2026-10-16
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


template<class I, class O> struct _BothPtrType { static __true_type _Ret() { return __true_type(); } };
template<class A, class B> struct _OKToMemCpy { static __true_type _Ret() { return __true_type(); } };
template<class A, class B> inline _OKToMemCpy<A,B> _IsOKToMemCpy(A*, B*) { return _OKToMemCpy<A,B>(); }
template<class I, class O>
inline O __copy_ptrs(I first, I last, O result, const __true_type&) {
    return (O)__copy_trivial(first, last, result);
}
template<class I, class O>
inline O __copy_aux(I first, I last, O result, const __true_type&) {
    return __copy_ptrs(first, last, result, _IsOKToMemCpy((char*)0, (char*)0)._Ret());
}
template<class I, class O>
inline O __uninitialized_copy(I first, I last, O result, const __true_type&) {
    return __copy_aux(first, last, result, _BothPtrType<I,O>::_Ret());
}
template<class I, class O>
inline O uninitialized_copy(I first, I last, O result) {
    return __uninitialized_copy(first, last, result, __true_type());
}

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

	void bfmeDoInsertQX(char *__position, unsigned int __n, unsigned char __c);

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

void BfmeThingQX::bfmeDoInsertQX(char *__position, unsigned int __n, unsigned char __c)
{
	if (__n != 0) {
		if ((unsigned int)(m_end_of_storage - m_finish) >= __n + 1) {
			const unsigned int __elems_after = m_finish - __position;
			char *__old_finish = m_finish;
			if (__elems_after >= __n) {
				_STL::uninitialized_copy((m_finish - __n) + 1, m_finish + 1, m_finish + 1);
				m_finish += __n;
				_Traits::move(__position + __n, __position, (__elems_after - __n) + 1);
				_Traits::assign(__position, __n, *(char *)&__c);
			}
			else {
				_STL::uninitialized_fill_n(m_finish + 1, __n - __elems_after - 1, *(char *)&__c);
				m_finish += __n - __elems_after;
				_STL::uninitialized_copy(__position, __old_finish + 1, m_finish);
				m_finish += __elems_after;
				_Traits::assign(__position, __elems_after + 1, *(char *)&__c);
			}
		}
		else {
			const unsigned int __old_size = size();
			const unsigned int __len = __old_size + (_STL::max)(__old_size, __n) + 1;
			char *__new_start = allocate(__len);
			char *__new_finish = __new_start;
			__new_finish = _STL::uninitialized_copy(m_start, __position, __new_start);
			__new_finish = _STL::uninitialized_fill_n(__new_finish, __n, *(char *)&__c);
			__new_finish = _STL::uninitialized_copy(__position, m_finish, __new_finish);
			_M_construct_null(__new_finish);
			_STL::_Destroy(m_start, m_finish + 1);
			_M_deallocate_block();
			m_start = __new_start;
			m_finish = __new_finish;
			m_end_of_storage = __new_start + __len;
		}
	}
}
