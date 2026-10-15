// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Int specialization of _STL::__introsort_loop. Needs /G7 (Pentium 4
// tuning): /O1 emits the threshold mask as dword `and eax,0xfc` where
// retail has the byte form `and al,0xfc` (VID/BVID/StepTDB precedent).
// Shard, not graft: the home TU verifies its 18 rows under /O1 and a flag
// flip would perturb them. Drivers only make the compiler emit the helper
// and carry no rows.
#include <algorithm>

namespace _STL {
template<> __declspec(dllimport) __forceinline _OKToMemCpy<int,int> _IsOKToMemCpy<int,int>(int*,int*) { return _OKToMemCpy<int,int>(); }
template<> __declspec(dllimport) __forceinline __true_type _OKToMemCpy<int,int>::_Ret() { return __true_type(); }
template<> __declspec(dllimport) __forceinline __true_type _BothPtrType<int*,int*>::_Ret() {return __true_type();}
template<> __declspec(dllimport) __forceinline int* __copy_backward_ptrs<int*,int*>(int* first,int* last,int* result,const __true_type&) { return (int*)__copy_trivial_backward(first,last,result); }
template<> void __linear_insert<int*,int,less<int> >(int*,int*,int,less<int>);
}
#include <functional>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

void bfmeEmitIntIntroSortLoop(int *first, int *last)
{
	_STL::sort(first, last);
	_STL::partial_sort(first, last, last, _STL::less<int>());
}
