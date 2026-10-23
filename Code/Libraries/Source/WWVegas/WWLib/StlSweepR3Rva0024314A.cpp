// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <algorithm>
#include <memory>



// The 0x50-byte record whose copy ctor is 0x002419E2 (Rva0024314ARecordCopy.cpp).
class Rva0024076D { public: Rva0024076D(); Rva0024076D(const Rva0024076D&); ~Rva0024076D(); Rva0024076D&operator=(const Rva0024076D&); bool operator<(const Rva0024076D&)const; private: char bytes[0x50]; };
template Rva0024076D* _STL::uninitialized_fill_n(Rva0024076D*,unsigned int,const Rva0024076D&);
