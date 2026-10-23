// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@UBfmeVectorRecord0002154F3@@V?$allocator@UBfmeVectorRecord0002154F3@@@_STL@@@_STL@@QAEPAUBfmeVectorRecord0002154F3@@PAU3@0@Z @0x002157DB 51B range erase.
// Evidence: retail 4-push plus 2-push shape with tag at [ebp+0xb] same as BfmeStringRecord erase 0x00381B1F; callees __copy_ptrs twin at 0x0021570D and Destroy 0x00215783; caller 0x00215AB7.
struct BfmeVectorRecord0002154F3;
namespace _STL {
struct __false_type {
};
struct random_access_iterator_tag {
};
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
// Match STLport's distance template parameter so the call binds the rowed worker.
template <class InputIter, class OutputIter, class Distance> OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *distance);
template <class T> class allocator {
};
template <class T, class A> class vector {
public:
	typedef T *iterator;
	iterator erase(iterator first, iterator last);
private:
	iterator _M_start;
	iterator _M_finish;
	iterator _M_end;
};
template <class ForwardIter> void _Destroy(ForwardIter first, ForwardIter last);
}
// ??$__copy_ptrs@PAUBfmeVectorRecord0002154F3@@PAU1@@_STL@@YAPAUBfmeVectorRecord0002154F3@@PAU1@00ABU__false_type@0@@Z present-unmatched
template <> __declspec(noinline) BfmeVectorRecord0002154F3 *_STL::__copy_ptrs<BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *>(BfmeVectorRecord0002154F3 *first, BfmeVectorRecord0002154F3 *last, BfmeVectorRecord0002154F3 *result, const _STL::__false_type &tag)
{
	// Retail forwards an uninitialized empty tag local, as in Rva0021570DCopy.
	_STL::random_access_iterator_tag category;
	return _STL::__copy(first, last, result, category, (int *)0);
}
_STL::vector<BfmeVectorRecord0002154F3, _STL::allocator<BfmeVectorRecord0002154F3> >::iterator _STL::vector<BfmeVectorRecord0002154F3, _STL::allocator<BfmeVectorRecord0002154F3> >::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, _M_finish, first, _STL::__false_type());
	_STL::_Destroy(result, _M_finish);
	_M_finish = result;
	return first;
}
