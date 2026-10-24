// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva000BBBF3Element { char bytes[8]; bool operator<(const Rva000BBBF3Element&)const; bool operator==(const Rva000BBBF3Element&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<Rva000BBBF3Element, Rva000BBBF3Element>(Rva000BBBF3Element *, const Rva000BBBF3Element &); }

// Instantiate the recovered operation and its required template dependencies.
template Rva000BBBF3Element * _STL::__uninitialized_copy<Rva000BBBF3Element const *, Rva000BBBF3Element *>(Rva000BBBF3Element const *, Rva000BBBF3Element const *, Rva000BBBF3Element *, _STL::__false_type const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@URva000BBBF3Element@@U1@@_STL@@YAXPAURva000BBBF3Element@@ABU1@@Z=?Rva000BBA47Construct@@YAXPAUTreeKey00242F5E@@ABU1@@Z")
