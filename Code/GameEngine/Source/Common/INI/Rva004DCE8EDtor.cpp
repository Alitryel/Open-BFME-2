// cl: /MD /EHsc /DNDEBUG
// stlport
// ??1Rva004DCE8E@@QAE@XZ @0x004DCE8E 54B: dtor destroying two Rb_tree maps at +0x14 and +0x20.
// Evidence: retail lea ecx [esi+0x20] calls rowed 0x004DCE51 then lea ecx [esi+0x14] calls rowed 0x004636FE with EH prolog table 0x00B916EC; pin ??1Rva004DCE8E@@QAE@XZ; caller deleting dtor in FamilyDeletingDtors11.cpp.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::_M_erase(_Rb_tree_node<pair<unsigned short const, int> > *); }
namespace _STL { template <> void _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, less<unsigned short>, allocator<pair<unsigned short const, int> > >::clear(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva00462D35Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00462D35Mapped;
namespace _STL { template <> void _Rb_tree<int,pair<int const ,Rva00462D35Mapped>,_Select1st<pair<int const ,Rva00462D35Mapped> >,less<int>,allocator<pair<int const ,Rva00462D35Mapped> > >::_M_erase(_Rb_tree_node<pair<int const ,Rva00462D35Mapped> > *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@V?$allocator@U?$pair@$$CBHURva0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00462D35Mapped;
namespace _STL { template <> _Rb_tree_base<pair<int const ,Rva00462D35Mapped>,allocator<pair<int const ,Rva00462D35Mapped> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@_STL@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00462D35Mapped;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const ,Rva00462D35Mapped> > >::deallocate(_Rb_tree_node<pair<int const ,Rva00462D35Mapped> > *,unsigned int) const; }

struct Rva00462D35Mapped
{
	unsigned int m_bits;
};

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > Rva004DCE8ETree20;
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00462D35Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00462D35Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00462D35Mapped> > > Rva004DCE8ETree14;

// The +0x14 tree's destructor is rowed at 0x004636FE (the call at 0x004DCEB2); declared only
// so this unit emits no non-retail copy of it.
namespace _STL { template <> Rva004DCE8ETree14::~_Rb_tree(); }
class Rva004DCE8E
{
public:
	~Rva004DCE8E();
private:
	char m_pad00[0x14];
	Rva004DCE8ETree14 m_tree14;
	Rva004DCE8ETree20 m_tree20;
};

Rva004DCE8E::~Rva004DCE8E()
{
}
