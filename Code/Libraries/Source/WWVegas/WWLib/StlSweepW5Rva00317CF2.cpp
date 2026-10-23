// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00317CF2Element { char bytes[8]; bool operator<(const Rva00317CF2Element&)const; bool operator==(const Rva00317CF2Element&)const; };

// Retail's loop calls the rowed two-pointer cdecl placement-copy owner
// Rva00317CA0Construct 0x00317CA0 (stlport_construct_stl_types.cpp), as the
// StlportVectorPushBackFamily.cpp element at the same owner does.
void __cdecl Rva00317CA0Construct(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00317CF2Element, Rva00317CF2Element>(Rva00317CF2Element *__p, const Rva00317CF2Element &__val)
{ Rva00317CA0Construct(__p, &__val); }
}

// Instantiate the recovered operation and its required template dependencies.
template Rva00317CF2Element * _STL::__uninitialized_copy<Rva00317CF2Element const *, Rva00317CF2Element *>(Rva00317CF2Element const *, Rva00317CF2Element const *, Rva00317CF2Element *, _STL::__false_type const &);
