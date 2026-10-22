// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WWLib/RvaTreeInsertUniqueGenP12pod009282C0.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.
// ?insert_unique@?$_Rb_tree@UGen_p12pod@@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Select1st@U?$pair@$$CBUGen_p12pod@@H@_STL@@@3@U?$less@UGen_p12pod@@@3@V?$allocator@U?$pair@$$CBUGen_p12pod@@H@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUGen_p12pod@@H@_STL@@@2@@2@U32@ABU?$pair@$$CBUGen_p12pod@@H@2@@Z
// Open-BFME: STLport hinted _Rb_tree::insert_unique for Gen_p12pod, retail
// RVA 0x009282C0, 718 bytes. Identity is independently pinned by the
// Gen_p12pod map operator[] caller at 0x00928690 and the insertion callee
// symbol above. The redundant bool assignment is intentional: it reproduces
// the retail adjacent materialization order in MSVC 7.1 without a byte lift.
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@UGen_p12pod@@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Select1st@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_p12pod;
namespace _STL { template <> _Rb_tree_node<pair<Gen_p12pod const ,int> > * _Rb_tree<Gen_p12pod,pair<Gen_p12pod const ,int>,_Select1st<pair<Gen_p12pod const ,int> >,less<Gen_p12pod>,allocator<pair<Gen_p12pod const ,int> > >::_M_create_node(pair<Gen_p12pod const ,int> const &); }
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

struct Gen_p12pod
{
	int a[3];
	// Retail 16CC80 copies the key words individually, then the mapped int.
	Gen_p12pod(const Gen_p12pod &source)
	{ a[0] = source.a[0]; a[1] = source.a[1]; a[2] = source.a[2]; }
};

inline bool compare_tail(const Gen_p12pod &gen_p12pod, const Gen_p12pod &b)
{
	const int a1 = gen_p12pod.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && gen_p12pod.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

#include "GenP12TreeInsertUnique.h"

template GenP12Tree::iterator
GenP12Tree::insert_unique(GenP12Tree::iterator, const GenP12Pair &);
