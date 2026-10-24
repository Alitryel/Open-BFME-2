// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva0048C84CElement { char bytes[8]; bool operator<(const Rva0048C84CElement&)const; bool operator==(const Rva0048C84CElement&)const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<Rva0048C84CElement, Rva0048C84CElement>(Rva0048C84CElement *, const Rva0048C84CElement &); }

// Instantiate the recovered operation and its required template dependencies.
template Rva0048C84CElement * _STL::__uninitialized_copy<Rva0048C84CElement const *, Rva0048C84CElement *>(Rva0048C84CElement const *, Rva0048C84CElement const *, Rva0048C84CElement *, _STL::__false_type const &);
// The declared element copy binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??$_Construct@URva0048C84CElement@@U1@@_STL@@YAXPAURva0048C84CElement@@ABU1@@Z=?Rva0048C81FConstruct@@YAXPAUTreeKey00242F5E@@ABU1@@Z")
