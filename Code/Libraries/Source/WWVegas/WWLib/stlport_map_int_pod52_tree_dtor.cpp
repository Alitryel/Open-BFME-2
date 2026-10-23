// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod52@@@_STL@@@2@@_STL@@QAE@XZ
// retail 0x00425FB4, 56 bytes. Tree dtor for the int->BfmePod52 map: clears
// through the rowed 0x00425F69 body, then frees the header node through
// rowed _free at 0x00030830 when non-null. Evidence: chain lane (calls
// 0x00425F69 just landed); same 56B EH shell as the rowed int-int tree dtor
// 0x0021B775 and color-tree dtor 0x0038103F. Shard, not graft: the /EHs flag
// the EH state store needs would perturb the /EHsc erase/clear home TU.
// Companion to stlport_map_int_pod52_o1.cpp.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod52@@@_STL@@@_STL@@@_STL@@QBEPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> _Rb_tree_node<pair<int const ,BfmePod52> > * allocator<_Rb_tree_node<pair<int const ,BfmePod52> > >::allocate(unsigned int,void const *) const; }

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod52 { int a[13]; };
// _M_create_node and insert_unique have retail copies in stlport_rb_tree_create_nodes.cpp;
// map::insert reaches insert_unique out of line, so this unit only declares them.
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod52>, _STL::_Select1st<_STL::pair<const int, BfmePod52> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > > BfmePod52Tree;
template <> BfmePod52Tree::_Link_type BfmePod52Tree::_M_create_node(const BfmePod52Tree::value_type &);
template <> _STL::pair<BfmePod52Tree::iterator, bool> BfmePod52Tree::insert_unique(const BfmePod52Tree::value_type &);
template class _STL::map<int, BfmePod52, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > >;
