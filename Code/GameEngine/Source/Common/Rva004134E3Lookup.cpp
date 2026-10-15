// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?rva004134E3@Rva004134E3@@QAEPAHH@Z @0x004134E3 102B
// Map lookup with lazy static defaults: tree root at map+4 set goes straight
// to _M_lower_bound on the map<int,int> at +0x0C (rowed 0x00382A92); empty
// once-flags the single statics block (int 0 plus three 1.0f from shared
// literal 0x7BB8D8 plus dword flag) and returns the block itself: retail
// loads 0x00E03044, the block start, not a field past the flag. End result
// decrements to predecessor (rowed 0x000242C0); both paths return value
// pointer at node+0x14. Evidence: unlock lane; caller 0x002BC971; statics
// 0x00A03044-58; sibling map recipe.
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
struct Rva004134E3Statics
{
	int m_count;
	float m_f0;
	float m_f1;
	float m_f2;
	int m_flag;
};
static Rva004134E3Statics s_block;
class Rva004134E3
{
public:
	int *rva004134E3(int key);
private:
	unsigned char m_pad00[0x0C];
	_STL::map<int, int> m_map0C;
};
// ?rva004134E3@Rva004134E3@@QAEPAHH@Z
int *Rva004134E3::rva004134E3(int key)
{
	if (((void **)&m_map0C)[1] == 0)
	{
		if ((s_block.m_flag & 1) == 0)
		{
			s_block.m_f0 = 1.0f;
			s_block.m_flag |= 1;
			s_block.m_count = 0;
			s_block.m_f1 = 1.0f;
			s_block.m_f2 = 1.0f;
		}
		return &s_block.m_count;
	}
	_STL::map<int, int>::iterator it = m_map0C.lower_bound(key);
	if (it == m_map0C.end())
		--it;
	return &it->second;
}
