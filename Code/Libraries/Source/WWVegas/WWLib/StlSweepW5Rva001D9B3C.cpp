// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva001D9B3CElement { char bytes[8]; bool operator<(const Rva001D9B3CElement&)const; bool operator==(const Rva001D9B3CElement&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<Rva001D9B3CElement, Rva001D9B3CElement>(Rva001D9B3CElement *, const Rva001D9B3CElement &); }

// Instantiate the recovered operation and its required template dependencies.
template Rva001D9B3CElement * _STL::__uninitialized_copy<Rva001D9B3CElement const *, Rva001D9B3CElement *>(Rva001D9B3CElement const *, Rva001D9B3CElement const *, Rva001D9B3CElement *, _STL::__false_type const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@URva001D9B3CElement@@U1@@_STL@@YAXPAURva001D9B3CElement@@ABU1@@Z=?Rva001D9B0FConstruct@@YAXPAXPBX@Z")
