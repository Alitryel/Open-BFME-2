// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva000BBC89Element { short words[1]; bool operator<(const Rva000BBC89Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva000BBC89Element&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<Rva000BBC89Element const,int> > * _Rb_tree<Rva000BBC89Element,_STL::pair<Rva000BBC89Element const,int>,_STL::_Select1st<_STL::pair<Rva000BBC89Element const,int> >,_STL::less<Rva000BBC89Element>,_STL::allocator<_STL::pair<Rva000BBC89Element const,int> > >::_M_create_node(_STL::pair<Rva000BBC89Element const,int> const &); }
template _STL::_Rb_tree_node<_STL::pair<Rva000BBC89Element const, int> > * _STL::_Rb_tree<Rva000BBC89Element, _STL::pair<Rva000BBC89Element const, int>, _STL::_Select1st<_STL::pair<Rva000BBC89Element const, int> >, _STL::less<Rva000BBC89Element>, _STL::allocator<_STL::pair<Rva000BBC89Element const, int> > >::_M_clone_node(_STL::_Rb_tree_node<_STL::pair<Rva000BBC89Element const, int> > *);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?_M_create_node@?$_Rb_tree@URva000BBC89Element@@U?$pair@$$CBURva000BBC89Element@@H@_STL@@U?$_Select1st@U?$pair@$$CBURva000BBC89Element@@H@_STL@@@3@U?$less@URva000BBC89Element@@@3@V?$allocator@U?$pair@$$CBURva000BBC89Element@@H@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBURva000BBC89Element@@H@_STL@@@2@ABU?$pair@$$CBURva000BBC89Element@@H@2@@Z=?_M_create_node@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@2@ABU?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@2@@Z")
