// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva005EA9E1Element { char bytes[36]; bool operator<(const Rva005EA9E1Element&)const; bool operator==(const Rva005EA9E1Element&)const; };

// Link: the element copy is retail's 0x005EA9A9, the rowed
// _Construct<GeometryShape> (GeometryShapeConstruct005EA9A9.cpp); an inline
// forwarder reaches it with the same pushes instead of emitting a
// non-retail copy.
struct GeometryShape;
namespace _STL {
template <> void _Construct<GeometryShape, GeometryShape>(GeometryShape *, const GeometryShape &);
template <> __declspec(dllimport) __forceinline void _Construct<Rva005EA9E1Element, Rva005EA9E1Element>(Rva005EA9E1Element *__p, const Rva005EA9E1Element &__val)
{ _Construct((GeometryShape *)__p, *(const GeometryShape *)&__val); }
}

// Instantiate the recovered operation and its required template dependencies.
template Rva005EA9E1Element * _STL::__uninitialized_fill_n<Rva005EA9E1Element *, unsigned int, Rva005EA9E1Element>(Rva005EA9E1Element *, unsigned int, Rva005EA9E1Element const &, _STL::__false_type const &);
