// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
class Rva00467DB3Obj;
// Declared only: retail's node allocation is the separately rowed 34-byte body
// at this name's pinned address; this TU's copy is not retail's.
template <> _STL::_List_node<Rva00467DB3Obj *> *_STL::list<Rva00467DB3Obj *>::_M_create_node(Rva00467DB3Obj *const &);
template void _STL::list<Rva00467DB3Obj *>::push_back(Rva00467DB3Obj *const &);
// The declared node allocation binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?_M_create_node@?$list@PAVRva00467DB3Obj@@V?$allocator@PAVRva00467DB3Obj@@@_STL@@@_STL@@IAEPAU?$_List_node@PAVRva00467DB3Obj@@@2@ABQAVRva00467DB3Obj@@@Z=?Rva004677FDCreateNode@@YGPAXPBX@Z")
