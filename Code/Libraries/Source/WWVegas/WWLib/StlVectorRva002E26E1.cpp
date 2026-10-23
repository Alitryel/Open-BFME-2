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



struct Rva002E26E1Record { Rva002E26E1Record(); Rva002E26E1Record(const Rva002E26E1Record&); ~Rva002E26E1Record(); Rva002E26E1Record&operator=(const Rva002E26E1Record&); private: char bytes[216]; };
namespace _STL {template<> void _Construct<Rva002E26E1Record,Rva002E26E1Record>(Rva002E26E1Record*,const Rva002E26E1Record&);}
namespace _STL {template<> void _Destroy<Rva002E26E1Record*>(Rva002E26E1Record*,Rva002E26E1Record*);}
template void _STL::vector<Rva002E26E1Record>::reserve(unsigned int);

// Native allocate/copy 2E1693 calls 2E163C -> cdecl placement copy 2E160F.
// Clear 2E26C3 calls range wrapper 2AF4ED -> 2AE5CF. The copy and destroy
// loops both advance 0xD8; bind operations without naming the game record.
#pragma comment(linker, "/alternatename:??$_Construct@URva002E26E1Record@@U1@@_STL@@YAXPAURva002E26E1Record@@ABU1@@Z=??$_Construct@URva002E160FElement@@U1@@_STL@@YAXPAURva002E160FElement@@ABU1@@Z")
#pragma comment(linker, "/alternatename:??$_Destroy@PAURva002E26E1Record@@@_STL@@YAXPAURva002E26E1Record@@0@Z=??$_Destroy@PAURva002E2690Element@@@_STL@@YAXPAURva002E2690Element@@0@Z")
