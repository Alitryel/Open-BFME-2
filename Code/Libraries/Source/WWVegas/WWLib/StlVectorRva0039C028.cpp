// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
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



struct Rva0039C028Record { Rva0039C028Record(); Rva0039C028Record(const Rva0039C028Record&); ~Rva0039C028Record(); Rva0039C028Record&operator=(const Rva0039C028Record&); private: char bytes[20]; };
namespace _STL {template<> void _Construct<Rva0039C028Record,Rva0039C028Record>(Rva0039C028Record*,const Rva0039C028Record&);}
namespace _STL {template<> void _Destroy<Rva0039C028Record*>(Rva0039C028Record*,Rva0039C028Record*);}
template void _STL::vector<Rva0039C028Record>::reserve(unsigned int);

// Retail reserve calls allocate-and-copy 51ED51 -> uninitialized_copy 39BA22,
// whose 0x14-stride loop invokes copy constructor 39B893. Bind the unused
// out-of-line construction spelling to the rowed placement-copy wrapper.
// Cleanup is 565A42 -> 22C8E3 -> 52BF9B: that last loop calls the virtual
// deleting-destructor slot with flag zero and advances 0x14. Bind the whole
// two-pointer range operation; this opaque view does not identify its vtable.
#pragma comment(linker, "/alternatename:??$_Construct@URva0039C028Record@@U1@@_STL@@YAXPAURva0039C028Record@@ABU1@@Z=??$_Construct@VRva0039B893@@V1@@_STL@@YAXPAVRva0039B893@@ABV1@@Z")
#pragma comment(linker, "/alternatename:??$_Destroy@PAURva0039C028Record@@@_STL@@YAXPAURva0039C028Record@@0@Z=?Rva0022C8E3DestroyRange@@YAXPAURva0052BF9BElem@@0@Z")
