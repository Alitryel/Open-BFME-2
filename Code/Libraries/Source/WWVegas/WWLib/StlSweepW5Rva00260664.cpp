// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00260664Element { char bytes[8]; bool operator<(const Rva00260664Element&)const; bool operator==(const Rva00260664Element&)const; };

// The native placement copy at 0x0026061A owns its UnicodeString field.
// Retain the address-derived stride view but call the existing typed owner.
struct BfmeStringRecord005DDD40;
void Rva0026061AConstruct(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<Rva00260664Element, Rva00260664Element>(Rva00260664Element *dest, const Rva00260664Element &source)
{
 Rva0026061AConstruct((BfmeStringRecord005DDD40 *)dest, (const BfmeStringRecord005DDD40 &)source);
}
}

// Instantiate the recovered operation and its required template dependencies.
template Rva00260664Element * _STL::__uninitialized_copy<Rva00260664Element const *, Rva00260664Element *>(Rva00260664Element const *, Rva00260664Element const *, Rva00260664Element *, _STL::__false_type const &);
