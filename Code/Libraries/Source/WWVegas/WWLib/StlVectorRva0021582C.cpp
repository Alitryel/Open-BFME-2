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



struct Rva0021582CRecord { Rva0021582CRecord(); Rva0021582CRecord(const Rva0021582CRecord&); ~Rva0021582CRecord(); Rva0021582CRecord&operator=(const Rva0021582CRecord&); private: char bytes[16]; };
namespace _STL {template<> void _Construct<Rva0021582CRecord,Rva0021582CRecord>(Rva0021582CRecord*,const Rva0021582CRecord&);}
template void _STL::vector<Rva0021582CRecord>::reserve(unsigned int);

// Retail's reserve (0x0021582C) reaches the element copy worker 0x0021559C and element destructor 0x002154BE through
// its rowed _M_allocate_and_copy / _M_clear; those rows name the same 16-byte record BfmeVectorRecord002154F3.
#pragma comment(linker, "/alternatename:??$_Construct@URva0021582CRecord@@U1@@_STL@@YAXPAURva0021582CRecord@@ABU1@@Z=??$_Construct@UBfmeVectorRecord002154F3@@U1@@_STL@@YAXPAUBfmeVectorRecord002154F3@@ABU1@@Z")
#pragma comment(linker, "/alternatename:??1Rva0021582CRecord@@QAE@XZ=??1BfmeVectorRecord0002154F3@@QAE@XZ")
