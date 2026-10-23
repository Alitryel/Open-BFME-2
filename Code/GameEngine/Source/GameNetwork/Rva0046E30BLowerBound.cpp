// cl: /O1 /G7 /arch:SSE /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
//
// Rva0046E30B::rva0046E30B @0x0046E30B 20B: a container-level lower_bound
// returning the iterator built from the folded _M_lower_bound body at
// 0x0046A9AB (ConnectionManager.cpp's map<unsigned short, unsigned char>
// spelling, the alias row's object symbol) through the hidden result slot.
// Skeleton twin of the STLport find wrapper 0x004D7546. The folded callee
// does not prove the key/value types, and the owner is not recovered (no
// direct caller), so the view is address-named. The worker is declared, not
// defined, so the call stays out of line as in retail.
#include <map>

typedef _STL::map<unsigned short, unsigned char> Rva0046E30BMap;

namespace _STL {
template <> _Rb_tree_node<pair<unsigned short const, unsigned char> > *
_Rb_tree<unsigned short, pair<unsigned short const, unsigned char>,
	_Select1st<pair<unsigned short const, unsigned char> >, less<unsigned short>,
	allocator<pair<unsigned short const, unsigned char> > >::_M_lower_bound(const unsigned short &) const;
}

class Rva0046E30B
{
public:
	Rva0046E30BMap::iterator rva0046E30B(const unsigned short &key);
private:
	Rva0046E30BMap m_map;
};

Rva0046E30BMap::iterator Rva0046E30B::rva0046E30B(const unsigned short &key)
{
	return m_map.lower_bound(key);
}
