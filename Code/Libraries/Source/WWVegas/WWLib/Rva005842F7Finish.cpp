// ?erase@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEPAUBfmePod28@@PAU3@0@Z
// partial score=0.97 date=2026-09-24
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport range erase over a 28-byte POD. The prvalue __false_type tag is the
// sibling stlport_vector_record_2154f3_erase shape: it keeps the tag at
// [ebp+0xb] under /O1 instead of the [ebp+0xf] a named local produces.
struct BfmePod28 { int a[7]; };

namespace _STL {
struct __false_type {};
struct random_access_iterator_tag {};
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter> OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, int *distance);
template <class T> class allocator {};
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator erase(iterator first, iterator last);
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end;
};
}
// ??$__copy_ptrs@PAUBfmePod28@@PAU1@@_STL@@YAPAUBfmePod28@@PAU1@00ABU__false_type@0@@Z present-unmatched
template <> __declspec(noinline) BfmePod28 *_STL::__copy_ptrs<BfmePod28 *, BfmePod28 *>(BfmePod28 *first, BfmePod28 *last, BfmePod28 *result, const _STL::__false_type &tag)
{
	return _STL::__copy(first, last, result, _STL::random_access_iterator_tag(), (int *)0);
}

_STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::iterator _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, _M_finish, first, _STL::__false_type());
	_M_finish = result;
	return first;
}
