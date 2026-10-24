// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva000CF503Element { char bytes[8]; bool operator<(const Rva000CF503Element&)const; bool operator==(const Rva000CF503Element&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<Rva000CF503Element, Rva000CF503Element>(Rva000CF503Element *, const Rva000CF503Element &); }

// Instantiate the recovered operation and its required template dependencies.
template Rva000CF503Element * _STL::__uninitialized_copy<Rva000CF503Element const *, Rva000CF503Element *>(Rva000CF503Element const *, Rva000CF503Element const *, Rva000CF503Element *, _STL::__false_type const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@URva000CF503Element@@U1@@_STL@@YAXPAURva000CF503Element@@ABU1@@Z=?Rva000CF4D6Construct@@YAXPAUTreeKey00242F5E@@ABU1@@Z")
