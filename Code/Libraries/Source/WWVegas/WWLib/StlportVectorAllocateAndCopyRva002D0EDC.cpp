// Target boundary 0x002D0EDC/45 is STLport vector::_M_allocate_and_copy.
// The caller at 0x002D0F65 supplies element count and source-range pointers;
// this helper allocates through the vector allocator and returns the copied
// buffer. Retail advances the source/destination by the witnessed 0x5C stride.
//
// Rva002D0EDCElement is an address-derived 92-byte non-trivial emitter view.
// Its target Construct chain reaches the matched GeometryInfo copy constructor
// at 0x000929E8, but no complete element layout is claimed by this TU.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002D0EDCElement {
	char opaque[92];
	Rva002D0EDCElement(const Rva002D0EDCElement &);
	~Rva002D0EDCElement();
};

template Rva002D0EDCElement *
_STL::vector<Rva002D0EDCElement>::_M_allocate_and_copy(
	unsigned int, const Rva002D0EDCElement *, const Rva002D0EDCElement *);

// Retail's call goes to the rowed _Construct at 0x002D0BEA; suppress this TU's own copy (which would
// call the element copy constructor, defined nowhere) and bind the template name to that row.
namespace _STL { template <> void _Construct<Rva002D0EDCElement, Rva002D0EDCElement>(Rva002D0EDCElement *, const Rva002D0EDCElement &); }
#pragma comment(linker, "/alternatename:??$_Construct@URva002D0EDCElement@@U1@@_STL@@YAXPAURva002D0EDCElement@@ABU1@@Z=??$_Construct@VGeometryInfo@@V1@@_STL@@YAXPAVGeometryInfo@@ABV1@@Z")
