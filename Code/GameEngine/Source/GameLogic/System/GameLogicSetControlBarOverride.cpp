// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// GameLogic::setControlBarOverride, retail 0x0024792F (79 B; WB 0x00D08DA0).
// Zero Hour's body, m_controlBarOverrides[make_pair(name, slot)] = button,
// with BFME 2's key order (slot, name): the make_pair<int, AsciiString> call
// 0x0023FC23 and the map subscript 0x00246FF6 on this+0x24 (the map the rowed
// lookup 0x00246F8E searches). The name is the one the rowed caller
// doRemoveCommandBarButton binds (0x003C5D5E). The map keeps the ledger's
// structural key and mapped-value names.
#include "ascii_string.h"
#include <map>
#include "../../Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@UTreeKey00242F5E@@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapp:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct TreeKey00242F5E; struct TreeOpaqueMapped242F5E;
namespace _STL { template <> _Rb_tree_node<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > * _Rb_tree<TreeKey00242F5E,pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Select1st<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> >,less<TreeKey00242F5E>,allocator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >::_M_create_node(pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> const &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@UTreeKey00242F5E@@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMappe:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct TreeKey00242F5E; struct TreeOpaqueMapped242F5E;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Nonconst_traits<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >,bool> _Rb_tree<TreeKey00242F5E,pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E>,_Select1st<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> >,less<TreeKey00242F5E>,allocator<pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> > >::insert_unique(pair<TreeKey00242F5E const ,TreeOpaqueMapped242F5E> const &); }

struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);

typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

// The shared GameLogic view leaves +0x24 unmodelled; the override map lives there.
struct GameLogicControlBarOverrides
{
	unsigned char m_pad00[0x24];
	ControlBarOverrideMap m_controlBarOverrides;	// +0x24
};

void GameLogic::setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton)
{
	((GameLogicControlBarOverrides *)this)->m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, commandSetName)].m_bits = (unsigned int)commandButton;
}
