// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
#include "Coord3D.h"
#include <list>
#include <map>
#include "Bfme/PlaceTerrainResourceClaimantFeedbackView.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int,_STL::pair<int const,void *>,_STL::_Select1st<_STL::pair<int const,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,void *> > >::~_Rb_tree(); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_List_node<Coord3D> *,_STL::_List_node<Coord3D>,_STL::allocator<_STL::_List_node<Coord3D> > >::deallocate(_STL::_List_node<Coord3D> *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_List_node<Coord3D> >::deallocate(_STL::_List_node<Coord3D> *,unsigned int) const; }
namespace _STL { template <> void _List_base<Coord3D,_STL::allocator<Coord3D> >::clear(); }
namespace _STL { template <> _List_base<Coord3D,_STL::allocator<Coord3D> >::~_List_base(); }
// bfme link decl-only end

// Native 4E6745..4E678B RET12 allocates its 32-byte Impl, passing this,
// the UI's feedback settings, its preview drawable and the resource module.
// The real new-expression caller is InGameUI::handleBuildPlacements at
// 2A2392..2A23A4; WB names the outer and nested constructors.
PlaceTerrainResourceClaimantFeedback::PlaceTerrainResourceClaimantFeedback(
    FeedbackParams *params, Drawable *drawable,
    const TerrainResourceBehaviorModuleData *data)
{
    m_impl = new Impl(this, params, drawable, data);
}

class Rva004E5610
{
public:
    Rva004E5610();
private:
    char m_pad[0x0C];
};

class Rva004E7D72
{
public:
	Rva004E7D72(void *parent);

private:
    void *m_parent;
    int m_04;
    AsciiString m_name;
    _STL::list<Coord3D> m_list0C;
    _STL::map<int, void *> m_map10;
    Rva004E5610 m_1C;
};

class Rva004E7F43
{
public:
	Rva004E7F43 *rva004E7F43();

private:
	Rva004E7D72 *m_00;
};

// ?rva004E7F43@Rva004E7F43@@QAEPAURva004E7F43@@XZ @0x004E7F43 59B.
Rva004E7F43 *Rva004E7F43::rva004E7F43()
{
	m_00 = new Rva004E7D72(this);
	return this;
}

// Native4E7D72..4E7DC8 RET4 and WB131C300 prove parent+0, scalar+4,
// string+8, list+C, map+10 and the 12-byte member+1C. Native unwind
// action792399 adjusts this by8 and jumps to rowed AsciiString::~AsciiString
// at48BA39; the old artificial-base model hid that real member lifetime.
Rva004E7D72::Rva004E7D72(void *parent)
    : m_parent(parent), m_04(0), m_name(), m_list0C(), m_map10(), m_1C()
{
}
