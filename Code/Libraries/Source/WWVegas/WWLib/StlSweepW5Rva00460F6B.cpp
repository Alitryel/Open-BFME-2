// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00460F6BElement {Rva00460F6BElement();Rva00460F6BElement(const Rva00460F6BElement&);Rva00460F6BElement&operator=(const Rva00460F6BElement&);~Rva00460F6BElement(){}char bytes[12]; bool operator==(const Rva00460F6BElement&)const;};

// Retail's loop calls the rowed two-pointer cdecl placement-copy owner
// Rva00460F18Construct 0x00460F18 (stlport_construct_stl_types.cpp).
void __cdecl Rva00460F18Construct(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00460F6BElement, Rva00460F6BElement>(Rva00460F6BElement *__p, const Rva00460F6BElement &__val)
{ Rva00460F18Construct(__p, &__val); }
}

// Instantiate the recovered operation and its required template dependencies.
template Rva00460F6BElement * _STL::__uninitialized_fill_n<Rva00460F6BElement *, unsigned int, Rva00460F6BElement>(Rva00460F6BElement *, unsigned int, Rva00460F6BElement const &, _STL::__false_type const &);

// Retail's call goes to the rowed _Construct at 0x00460F18; suppress this TU's own copy (which would
// call the element copy constructor, defined nowhere) and bind the template name to that row.
namespace _STL { template <> void _Construct<Rva00460F6BElement, Rva00460F6BElement>(Rva00460F6BElement *, const Rva00460F6BElement &); }
#pragma comment(linker, "/alternatename:??$_Construct@URva00460F6BElement@@U1@@_STL@@YAXPAURva00460F6BElement@@ABU1@@Z=?Rva00460F18Construct@@YAXPAXPBX@Z")
