// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003079C1Element { char bytes[9];Rva003079C1Element();Rva003079C1Element(const Rva003079C1Element&);~Rva003079C1Element();Rva003079C1Element&operator=(const Rva003079C1Element&); bool operator<(const Rva003079C1Element&)const; bool operator==(const Rva003079C1Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> void swap<_STL::_STLP_alloc_proxy<Rva003079C1Element *,Rva003079C1Element,_STL::allocator<Rva003079C1Element> > >(_STL::_STLP_alloc_proxy<Rva003079C1Element *,Rva003079C1Element,_STL::allocator<Rva003079C1Element> > &,_STL::_STLP_alloc_proxy<Rva003079C1Element *,Rva003079C1Element,_STL::allocator<Rva003079C1Element> > &); }
template void _STL::vector<Rva003079C1Element, _STL::allocator<Rva003079C1Element> >::swap(_STL::vector<Rva003079C1Element, _STL::allocator<Rva003079C1Element> > &);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$swap@V?$_STLP_alloc_proxy@PAURva003079C1Element@@U1@V?$allocator@URva003079C1Element@@@_STL@@@_STL@@@_STL@@YAXAAV?$_STLP_alloc_proxy@PAURva003079C1Element@@U1@V?$allocator@URva003079C1Element@@@_STL@@@0@0@Z=??$swap@V?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@@_STL@@YAXAAV?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@0@0@Z")
