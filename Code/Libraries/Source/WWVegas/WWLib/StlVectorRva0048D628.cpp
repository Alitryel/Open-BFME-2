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



struct Rva0048D628Record { Rva0048D628Record(); Rva0048D628Record(const Rva0048D628Record&); ~Rva0048D628Record(); Rva0048D628Record&operator=(const Rva0048D628Record&); private: char bytes[8]; };
namespace _STL {template<> void _Construct<Rva0048D628Record,Rva0048D628Record>(Rva0048D628Record*,const Rva0048D628Record&);}
namespace _STL {template<> void _Destroy<Rva0048D628Record*>(Rva0048D628Record*,Rva0048D628Record*);}
template void _STL::vector<Rva0048D628Record>::push_back(const Rva0048D628Record&);

// Bind lifetime operations to the existing rowed native providers.
// push_back and overflow 48D48F call the cdecl copy provider 48C81F.
// Native cleanup C060A calls range destructor 48CE25, whose loop steps 8.
// These bindings identify operations on an ABI view, not a new game type.
#pragma comment(linker, "/alternatename:??$_Construct@URva0048D628Record@@U1@@_STL@@YAXPAURva0048D628Record@@ABU1@@Z=?Rva0048C81FConstruct@@YAXPAUTreeKey00242F5E@@ABU1@@Z")
#pragma comment(linker, "/alternatename:??$_Destroy@PAURva0048D628Record@@@_STL@@YAXPAURva0048D628Record@@0@Z=??$_Destroy@PAVCameraMarker@@@_STL@@YAXPAVCameraMarker@@0@Z")
