// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE24CElement {Rva005FE24CElement();Rva005FE24CElement(const Rva005FE24CElement&);Rva005FE24CElement&operator=(const Rva005FE24CElement&);~Rva005FE24CElement(){}char bytes[12]; bool operator==(const Rva005FE24CElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE24CElement * _STL::__uninitialized_fill_n<Rva005FE24CElement *, unsigned int, Rva005FE24CElement>(Rva005FE24CElement *, unsigned int, Rva005FE24CElement const &, _STL::__false_type const &);

// Retail's call goes to the rowed _Construct at 0x005FE0F5; suppress this TU's own copy (which would
// call the element copy constructor, defined nowhere) and bind the template name to that row.
namespace _STL { template <> void _Construct<Rva005FE24CElement, Rva005FE24CElement>(Rva005FE24CElement *, const Rva005FE24CElement &); }
#pragma comment(linker, "/alternatename:??$_Construct@URva005FE24CElement@@U1@@_STL@@YAXPAURva005FE24CElement@@ABU1@@Z=?Rva005FE0F5Construct@@YAXPAUBfmeStringRecord005F93E3@@ABU1@@Z")
