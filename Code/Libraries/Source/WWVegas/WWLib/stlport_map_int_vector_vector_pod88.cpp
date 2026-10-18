// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// The insert path of map<int, vector<vector<BfmePod88> >>: its pair copy (0x0050118D) calls the rowed vector<vector<BfmePod88>> copy constructor (VectorPod88CopyConstructor.cpp), after a
// one-word key copy. The key is a signed 32-bit type (the inserts compare it
// signed); int stands in, as in stlport_map_int_int_os.cpp. Recipe and flags
// are stlport_map_int_vector_pod128.cpp's.

#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>

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
#include <vector>

struct BfmePod88
{
	char m_body[88];
};
// Bind to the kept retail copies instead of emitting this unit's own.
namespace _STL { template <> void _Construct<BfmePod88,BfmePod88>(BfmePod88 *,BfmePod88 const &); }
namespace _STL { template <> vector<BfmePod88,allocator<BfmePod88> >::vector(vector<BfmePod88,allocator<BfmePod88> > const &); }
// bfme link decl-only BfmePod88
namespace _STL { template <> vector<BfmePod88, allocator<BfmePod88> >::~vector(); }

typedef _STL::map<int, _STL::vector<_STL::vector<BfmePod88> > > IntPod88VectorVectorMap;

template class _STL::map<int, _STL::vector<_STL::vector<BfmePod88> > >;
