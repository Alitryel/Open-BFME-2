// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE@ABV01@@Z, retail 0x0052D25D, 165 bytes.
// _Rb_tree copy ctor for map<int AsciiString> (28B pair 44B node) caller of matched _M_copy 0x0050427F via WOLBuddyOverlay.
// Evidence: unlock lane unblocking 0x0052D477; callees get_allocator fold 0x0021983A and base 0x00417B55 and _M_copy 0x0050427F; EH_prolog with handler.
// Private 24B AsciiString (not shared 4B header): retail header-node is 0x2c/44B requiring 28B pair; shared 4B gives 8B pair/24B node so gate fails; size not in mangling so _M_copy name still matches.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
class AsciiString { public: unsigned char m_data[24]; };
// map<int, AsciiString>'s _M_clone_node is rowed in stlport_map_int_asciistring_clone.cpp
// (retail 0x005041D8); declare it so this unit emits no copy of its own.
namespace _STL { template <> _Rb_tree<int, pair<const int, AsciiString>, _Select1st<pair<const int, AsciiString> >, less<int>, allocator<pair<const int, AsciiString> > >::_Link_type
_Rb_tree<int, pair<const int, AsciiString>, _Select1st<pair<const int, AsciiString> >, less<int>, allocator<pair<const int, AsciiString> > >::_M_clone_node(_Link_type); }
typedef _STL::_Rb_tree<int, _STL::pair<const int, AsciiString>, _STL::_Select1st<_STL::pair<const int, AsciiString> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > HAsciiStringMapTree;
template HAsciiStringMapTree::_Rb_tree(const HAsciiStringMapTree &);
// The rowed _M_create_node (above) was emitted through _M_clone_node; keep it emitted.
template HAsciiStringMapTree::_Link_type HAsciiStringMapTree::_M_create_node(const HAsciiStringMapTree::value_type &);
