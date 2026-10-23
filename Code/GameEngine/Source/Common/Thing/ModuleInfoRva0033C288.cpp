// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033C288@ModuleInfo@@QBEPBHH@Z @0x0033C288 43B: map<int int> find at +0x3AC guarded by flag at +0x3B0 returns mapped int* else 0.
// Evidence: calls rowed map _M_find at 0x00388F63; node+0x14 value (0x18 node via stlport_map_int_int_os); caller 0x00268A46; neighbours ModuleInfo rows.
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
class ModuleInfo
{
public:
	const int *rva0033C288(int key) const;
private:
	char m_pad[0x3AC];
	_STL::map<int, int> m_map3AC;
};
const int *ModuleInfo::rva0033C288(int key) const
{
	if (m_map3AC.empty())
		return 0;
	else
	{
		_STL::map<int, int>::const_iterator it = m_map3AC.find(key);
		if (it == m_map3AC.end())
			return 0;
		return &it->second;
	}
}
