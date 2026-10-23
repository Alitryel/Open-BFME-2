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

#include <list>



// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
// Its copy constructor is the rowed out-of-line 0x002419E2 (Rva0024314ARecordCopy.cpp),
// which retail's _Construct 0x0024314A calls.
class Rva0024076D { public: Rva0024076D(const Rva0024076D &); ~Rva0024076D(); bool operator==(const Rva0024076D&) const; bool operator<(const Rva0024076D&) const; private: unsigned char bytes[80]; };


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_List_node<Rva0024076D> * _STL::list<Rva0024076D, _STL::allocator<Rva0024076D> >::_M_create_node(Rva0024076D const &);
