// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /Ivendor /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stlport/stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>


// Retail's helpers reach the element through rowed twins: _Construct 0x00063C8F (_Construct<BfmeStringRecord00063BE4>), ~ 0x00255D17 (~Rva00255D17) and operator= 0x00063627 (Rva00063BB2Element::operator=, via the copy dispatch 0x00063BB2): forward to them.
struct BfmeStringRecord00063BE4;
struct Rva00255D17 { ~Rva00255D17(); };
struct Rva00063BB2Element { Rva00063BB2Element&operator=(const Rva00063BB2Element&); };
struct Rva0006447DRecord { Rva0006447DRecord(); Rva0006447DRecord(const Rva0006447DRecord&);
 __declspec(dllimport) __forceinline ~Rva0006447DRecord() { reinterpret_cast<Rva00255D17*>(this)->~Rva00255D17(); }
 __declspec(dllimport) __forceinline Rva0006447DRecord&operator=(const Rva0006447DRecord&x) { reinterpret_cast<Rva00063BB2Element*>(this)->operator=(reinterpret_cast<const Rva00063BB2Element&>(x)); return *this; }
 char bytes[36]; };
namespace _STL {
template<> void _Construct<BfmeStringRecord00063BE4,BfmeStringRecord00063BE4>(BfmeStringRecord00063BE4*,const BfmeStringRecord00063BE4&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva0006447DRecord,Rva0006447DRecord>(Rva0006447DRecord*p,const Rva0006447DRecord&v)
{ _Construct(reinterpret_cast<BfmeStringRecord00063BE4*>(p),reinterpret_cast<const BfmeStringRecord00063BE4&>(v)); }
}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva0006447DRecord, _STL::allocator<Rva0006447DRecord> > & _STL::vector<Rva0006447DRecord, _STL::allocator<Rva0006447DRecord> >::operator=(_STL::vector<Rva0006447DRecord, _STL::allocator<Rva0006447DRecord> > const &);
