// cl: /DNDEBUG /MD /EHsc
// stlport

// _STL::__introsort_loop<S4SortElem8 *, S4SortElem8, int, S4Cmp00625C10>,
// retail 0x00626860, 224 bytes.  Descending twin: inline median, the matched
// __unguarded_partition at 0x00625E30, the matched __partial_sort at
// 0x006265B0, self-recursion.  All callees are matched rows (no new pins).

#include <algorithm>

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4Cmp00625C10
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template<> __declspec(dllimport) __forceinline void iter_swap<S4SortElem8*,S4SortElem8*>(S4SortElem8* left,S4SortElem8* right) {
 S4SortElem8 temporary=*left; *left=*right; *right=temporary;
}

template void __introsort_loop<S4SortElem8 *, S4SortElem8, int,
	S4Cmp00625C10>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *, int,
	S4Cmp00625C10);

}
