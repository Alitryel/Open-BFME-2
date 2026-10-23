// Reference: pristine STLport4.5.3. Address-derived opaque ABI view.
// Target boundary and stride independently establish storage width; no game class identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <vector>



struct Rva005C84F1Record { Rva005C84F1Record(); Rva005C84F1Record(const Rva005C84F1Record&); ~Rva005C84F1Record(); Rva005C84F1Record&operator=(const Rva005C84F1Record&); private: char bytes[72]; };
namespace _STL {template<> void _Construct<Rva005C84F1Record,Rva005C84F1Record>(Rva005C84F1Record*,const Rva005C84F1Record&);}
template void _STL::vector<Rva005C84F1Record>::reserve(unsigned int);

// Bind this opaque element view to the existing native lifetime providers.
// reserve calls 5C8445 -> uninitialized_copy 5C83FA -> _Construct 5C83CD;
// its old storage cleanup calls 5C84D3 -> destroy range 5C847B -> 5C8FBD.
// Both loops step by 0x48, matching this view. The copy provider takes two
// cdecl pointers; the destructor takes this in ECX and has no stack arguments.
// These are the rowed owners, not new identities for the application record.
#pragma comment(linker, "/alternatename:??$_Construct@URva005C84F1Record@@U1@@_STL@@YAXPAURva005C84F1Record@@ABU1@@Z=??$_Construct@URva005C8624Element@@U1@@_STL@@YAXPAURva005C8624Element@@ABU1@@Z")
#pragma comment(linker, "/alternatename:??1Rva005C84F1Record@@QAE@XZ=??1Rva005C8FBD@@QAE@XZ")
