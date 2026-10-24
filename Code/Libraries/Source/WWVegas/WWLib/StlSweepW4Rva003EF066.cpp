// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva003EF066Element { char bytes[1]; bool operator<(const Rva003EF066Element&)const; bool operator==(const Rva003EF066Element&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const int, Rva003EF066Element> , pair<const int, Rva003EF066Element> >(pair<const int, Rva003EF066Element>  *, const pair<const int, Rva003EF066Element>  &); }
namespace _STL {template<> struct hash<Rva003EF066Element> { unsigned operator()(const Rva003EF066Element&) const; };}

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Hashtable_node<_STL::pair<int const, Rva003EF066Element> > * _STL::hashtable<_STL::pair<int const, Rva003EF066Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva003EF066Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva003EF066Element> > >::_M_new_node(_STL::pair<int const, Rva003EF066Element> const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@U?$pair@$$CBHURva003EF066Element@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHURva003EF066Element@@@0@ABU10@@Z=?Rva003EEFDBConstruct@@YAXPAXPBX@Z")
