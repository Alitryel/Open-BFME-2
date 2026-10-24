// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// LivingWorldAutoResolveReinforcementSchedule::getRoundForArmyNumber (WorldBuilder name, lines 32..43: find or extrapolate from the last entry by +0x0C).
// stlport
// was ?rva00413BC5@Rva00413BC5@@QAEHH@Z @0x00413BC5 61B: map<int,int> find with stride extension.
// Evidence: unlock lane, rowed _M_find 0x00388F63 and rowed _M_decrement 0x000242C0, found returns +0x14, miss with size!=0 uses (key-last_key)*stride+last_value, caller at 0x002BCA37.
#include <map>
// map<int,int> empty, tree-iterator ++/-- and != are expanded inline here; their
// out-of-line copies differ from retail's. Declared imported and force-inlined,
// they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::empty() const { return _M_node_count == 0; }
template <> __declspec(dllimport) __forceinline
bool map<int, int, less<int>, allocator<pair<const int, int> > >::empty() const { return _M_t.empty(); }
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{ _M_node = _Rb_global_inst::_M_increment(_M_node); return *this; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator--()
{ _M_node = _Rb_global_inst::_M_decrement(_M_node); return *this; }
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits> &a, const _Rb_tree_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class LivingWorldAutoResolveReinforcementSchedule
{
public:
  int getRoundForArmyNumber(int key);
private:
  _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > m_map00;
  int m_stride0C;
};
int LivingWorldAutoResolveReinforcementSchedule::getRoundForArmyNumber(int key)
{
  _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator it = m_map00.find(key);
  if (it == m_map00.end()) {
    if (m_map00.empty())
      return 0;
    _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator last = m_map00.end();
    --last;
    return (key - last->first) * m_stride0C + last->second;
  }
  return it->second;
}
