// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::clear() = erase(begin(), end()) for the two
// element types whose range erase StlportVectorEraseNoDestroyFamily.cpp
// rows; both copies are unreferenced in retail and call the rowed erase out
// of line, so erase is only declared here.
//
//   clear       erase
//   0x0007C500  0x0007C2F0  Region2D
//   0x0008B4F8  0x0008B4D2  BfmeStringRecord000B9534
namespace _STL
{
template <class _Tp>
class allocator
{
};
template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	typedef _Tp *iterator;
	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	iterator erase(iterator __first, iterator __last);
	void clear() { erase(begin(), end()); }
protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}
struct Region2D;
struct BfmeStringRecord000B9534;
template void _STL::vector<Region2D >::clear();
template void _STL::vector<BfmeStringRecord000B9534 >::clear();
