// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2
// stlport
// ??1Rva0042FCE6@@QAE@XZ, retail 0x0042FCE6, 54 bytes.
// Dtor stores derived vtable 0x0083C960 destroys tree at +0x28 via rowed 0x00357C6A stores base vtable 0x007DBA74. Evidence: caller 0x0042FE1F deleting dtor base vtable matches BfmeOwnVVD base.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<unsigned int, pair<unsigned int const, void *>, _Select1st<pair<unsigned int const, void *> >, less<unsigned int>, allocator<pair<unsigned int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<unsigned int, pair<unsigned int const, void *>, _Select1st<pair<unsigned int const, void *> >, less<unsigned int>, allocator<pair<unsigned int const, void *> > >::_M_erase(_Rb_tree_node<pair<unsigned int const, void *> > *); }
// bfme link decl-only end

typedef _STL::pair<const unsigned int, void *> Rva0042FCE6Pair;
typedef _STL::_Rb_tree<unsigned int, Rva0042FCE6Pair, _STL::_Select1st<Rva0042FCE6Pair>, _STL::less<unsigned int>, _STL::allocator<Rva0042FCE6Pair> > Rva0042FCE6Tree;

class Rva0042FCE6Base
{
public:
	Rva0042FCE6Base() { }
	~Rva0042FCE6Base() { }
	virtual void rvaSlot0();
};

class Rva0042FCE6 : public Rva0042FCE6Base
{
public:
	~Rva0042FCE6();
private:
	char m_pad04[0x24];
	Rva0042FCE6Tree m_map28;
};

Rva0042FCE6::~Rva0042FCE6()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rvaSlot0@Rva0042FCE6Base@@UAEXXZ=__purecall")
