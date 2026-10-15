// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00417FBA@Rva00417FBA@@QAEPAHH@Z @0x00417FBA 54B. Floor lookup over
// map<int,int> at +8 via rowed lower_bound 0x00382A92 and rowed decrement
// 0x000242C0. No empty check (cf Rva0041530B 64B which has one). Caller
// 0x004F9FC4. Landing unblocks 0x004F9F39.
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

class Rva00417FBA
{
public:
	int *rva00417FBA(int key);
private:
	unsigned char m_pad[8];
	_STL::map<int, int> m_map;
};

int *Rva00417FBA::rva00417FBA(int key)
{
	_STL::map<int, int>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || it->first > key)
	{
		if (it == m_map.begin())
			return 0;
		--it;
	}
	return &it->second;
}
