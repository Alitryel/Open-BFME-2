// cl: /MD
// stlport
// ?rva00398E4A@CastleBehavior@@QAEXPAURva00398E4AArg@@@Z @0x00398E4A 80B evidence: this CastleBehavior via caller 0x0039922D findModule CastleBehavior then call; map at this+0xa0 via insert_unique rowed 0x001E6F5F map-int-int; bits at arg+0xc loop test-shr-inc; value TheGameLogic+0x40 via global 0x009FE78C.
// Honest address-derived method on proven class (Object-rva precedent).
#include <map>
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, pair<int const, int> const &, _Rb_tree_node_base *); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// bfme link decl-only end

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};
extern GameLogic *TheGameLogic;

struct Rva00398E4AArg
{
	char m_pad00[0xc];
	unsigned int m_bits;
};

class CastleBehavior
{
public:
	virtual ~CastleBehavior();
	void rva00398E4A(Rva00398E4AArg *arg);
private:
	char m_pad04[0x9c];
	_STL::map<int, int> m_map;
};

void CastleBehavior::rva00398E4A(Rva00398E4AArg *arg)
{
	unsigned int bits = arg->m_bits;
	int idx = 0;
	while (bits != 0) {
		if ((bits & 1) != 0) {
			m_map.insert(_STL::map<int, int>::value_type(idx, 0)).first->second = TheGameLogic->m_40;
		}
		bits >>= 1;
		++idx;
	}
}
