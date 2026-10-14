// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva002A463B@Rva002A463B@@QAEXXZ, retail 0x002A463B (11B).
// Target evidence: adjusts the receiver by +0x750 and tail-jumps the rowed
// _Rb_tree<Rva002A1B9DElement, pair<const Rva002A1B9DElement, int>>::clear
// 0x002A1B9D -- an owner clearing its map member (STLport map::clear
// forwards to the tree's). The tree's clear is only declared so the call
// stays out of line; key type and owner are the ledger's stand-ins /
// unresolved.
#include <map>

struct Rva002A1B9DElement { short words[1]; bool operator<(const Rva002A1B9DElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002A1B9DElement&b)const {return words[0]==b.words[0];} };

typedef _STL::map<Rva002A1B9DElement, int> Rva002A463BMap;
namespace _STL {
template <> void _Rb_tree<Rva002A1B9DElement, pair<const Rva002A1B9DElement, int>, _Select1st<pair<const Rva002A1B9DElement, int> >, less<Rva002A1B9DElement>, allocator<pair<const Rva002A1B9DElement, int> > >::clear();
}

class Rva002A463B
{
public:
	void rva002A463B();
private:
	char m_pad000[0x750];
	Rva002A463BMap m_map;
};

void Rva002A463B::rva002A463B()
{
	m_map.clear();
}
