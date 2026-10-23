// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00317CCDElement {Rva00317CCDElement();Rva00317CCDElement(const Rva00317CCDElement&);Rva00317CCDElement&operator=(const Rva00317CCDElement&);virtual void slot0();virtual ~Rva00317CCDElement();char bytes[4]; bool operator==(const Rva00317CCDElement&)const;};

// Retail's loop calls the rowed two-pointer cdecl placement-copy owner
// Rva00317CA0Construct 0x00317CA0 (stlport_construct_stl_types.cpp), as the
// StlportVectorPushBackFamily.cpp element at the same owner does.
void __cdecl Rva00317CA0Construct(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00317CCDElement, Rva00317CCDElement>(Rva00317CCDElement *__p, const Rva00317CCDElement &__val)
{ Rva00317CA0Construct(__p, &__val); }
}

// Instantiate the recovered operation and its required template dependencies.
template Rva00317CCDElement * _STL::__uninitialized_fill_n<Rva00317CCDElement *, unsigned int, Rva00317CCDElement>(Rva00317CCDElement *, unsigned int, Rva00317CCDElement const &, _STL::__false_type const &);
