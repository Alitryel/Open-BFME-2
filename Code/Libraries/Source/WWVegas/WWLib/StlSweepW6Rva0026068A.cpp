// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0026068AElement {Rva0026068AElement();Rva0026068AElement(const Rva0026068AElement&);Rva0026068AElement&operator=(const Rva0026068AElement&);virtual void slot0();virtual ~Rva0026068AElement();char bytes[4]; bool operator==(const Rva0026068AElement&)const;};

// The native placement copy at 0x0026061A owns its UnicodeString field.
// Retain the address-derived stride view but call the existing typed owner.
struct BfmeStringRecord005DDD40;
void Rva0026061AConstruct(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<Rva0026068AElement, Rva0026068AElement>(Rva0026068AElement *dest, const Rva0026068AElement &source)
{
 Rva0026061AConstruct((BfmeStringRecord005DDD40 *)dest, (const BfmeStringRecord005DDD40 &)source);
}
}

// Instantiate the recovered operation and its required template dependencies.
template Rva0026068AElement * _STL::__uninitialized_fill_n<Rva0026068AElement *, unsigned int, Rva0026068AElement>(Rva0026068AElement *, unsigned int, Rva0026068AElement const &, _STL::__false_type const &);
