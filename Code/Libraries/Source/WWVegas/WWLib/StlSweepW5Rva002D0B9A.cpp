// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva002D0B9AElement { short words[1]; bool operator<(const Rva002D0B9AElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002D0B9AElement&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<Rva002D0B9AElement const,int> > * _Rb_tree<Rva002D0B9AElement,_STL::pair<Rva002D0B9AElement const,int>,_STL::_Select1st<_STL::pair<Rva002D0B9AElement const,int> >,_STL::less<Rva002D0B9AElement>,_STL::allocator<_STL::pair<Rva002D0B9AElement const,int> > >::_M_create_node(_STL::pair<Rva002D0B9AElement const,int> const &); }
template _STL::_Rb_tree_node<_STL::pair<Rva002D0B9AElement const, int> > * _STL::_Rb_tree<Rva002D0B9AElement, _STL::pair<Rva002D0B9AElement const, int>, _STL::_Select1st<_STL::pair<Rva002D0B9AElement const, int> >, _STL::less<Rva002D0B9AElement>, _STL::allocator<_STL::pair<Rva002D0B9AElement const, int> > >::_M_clone_node(_STL::_Rb_tree_node<_STL::pair<Rva002D0B9AElement const, int> > *);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?_M_create_node@?$_Rb_tree@URva002D0B9AElement@@U?$pair@$$CBURva002D0B9AElement@@H@_STL@@U?$_Select1st@U?$pair@$$CBURva002D0B9AElement@@H@_STL@@@3@U?$less@URva002D0B9AElement@@@3@V?$allocator@U?$pair@$$CBURva002D0B9AElement@@H@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBURva002D0B9AElement@@H@_STL@@@2@ABU?$pair@$$CBURva002D0B9AElement@@H@2@@Z=?_M_create_node@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@ABU?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@2@@Z")
