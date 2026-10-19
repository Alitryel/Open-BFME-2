// ?bfmeImplV21@BfmeStrV21@@QAEXPAD000@Z
// partial score=0.8 date=2026-10-19
// cl: /DNDEBUG /MD /Od /Ob1 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// 0x00028820 (740 B, RET 0x10): STLport 4.5.3 basic_string<char>::insert<const char *>(iterator,
// first, last, const forward_iterator_tag &) (vendor stl/_string.h:741), /Od with inlining.
// Placeholders bfmeImplV21/V22/V44/VMF/VMR pin this address. This bank writes the vendor body as
// an explicit specialization so retail's out-of-line copies are expressed: every
// uninitialized_copy is a direct call to the rowed __copy_trivial 0x179B0 (retail pushes the
// three arguments straight, so nothing was inlined there), _M_copy moves (memmove import
// 0xBBA688), allocate is `len != 0 ? byte allocate(len, 0) : 0` (0x307F0), deallocate keeps
// its named size. Instruction stream equals retail through the new_finish copies and the
// null terminator; left: (1) retail calls the empty _Destroy(start, finish + 1) out of line
// (0x0069E440, a 1-byte shared RET: no admissible real-name pin; placement delete is inline
// in <new>), (2) retail's frame is 0x14 larger: one extra dword below -0x24, one below -0x40
// and three between -0x58 and the -0x67 char temp (this at -0x74 vs our -0x60) - probably
// empty tag temporaries of inline helpers retail kept (distance/advance/uninitialized_copy
// dispatch) that this body does not reproduce.
#include <string>
namespace _STL {
// Retail's _M_copy for a const char range moves (memmove import), not memcpy.
inline void __bfme_string_copy(const char *__first, const char *__last, char *__result)
{
	char_traits<char>::move(__result, __first, __last - __first);
}
template <> template <>
void basic_string<char, char_traits<char>, allocator<char> >::insert<const char *>(char *__position, const char *__first, const char *__last, const forward_iterator_tag &)
{
	if (__first != __last) {
		difference_type __n = distance(__first, __last);
		if (this->_M_end_of_storage._M_data - this->_M_finish >= __n + 1) {
			const difference_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after >= __n) {
				__copy_trivial((this->_M_finish - __n) + 1, this->_M_finish + 1, this->_M_finish + 1);
				this->_M_finish += __n;
				char_traits<char>::move(__position + __n, __position, (__elems_after - __n) + 1);
				__bfme_string_copy(__first, __last, __position);
			}
			else {
				const char *__mid = __first;
				advance(__mid, __elems_after + 1);
				__copy_trivial(__mid, __last, this->_M_finish + 1);
				this->_M_finish += __n - __elems_after;
				__copy_trivial(__position, __old_finish + 1, this->_M_finish);
				this->_M_finish += __elems_after;
				__bfme_string_copy(__first, __mid, __position);
			}
		}
		else {
			const size_type __old_size = size();
			const size_type __len = __old_size + (max)(__old_size, __STATIC_CAST(size_type, __n)) + 1;
			pointer __new_start = __len != 0 ? (pointer)allocator<char>::allocate(__len, 0) : 0;
			pointer __new_finish = __new_start;
			__new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
			__new_finish = (pointer)__copy_trivial(__first, __last, __new_finish);
			__new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish);
			_M_construct_null(__new_finish);
			::operator delete(this->_M_start, this->_M_finish + 1);
			this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
			this->_M_start = __new_start;
			this->_M_finish = __new_finish;
			this->_M_end_of_storage._M_data = __new_start + __len;
		}
	}
}
}
