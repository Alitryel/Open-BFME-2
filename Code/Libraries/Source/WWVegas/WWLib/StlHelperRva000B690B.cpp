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



struct Rva000B690BRecord { Rva000B690BRecord(); Rva000B690BRecord(const Rva000B690BRecord&); ~Rva000B690BRecord(); Rva000B690BRecord&operator=(const Rva000B690BRecord&); private: char bytes[24]; };
namespace _STL {template<> void _Construct<Rva000B690BRecord,Rva000B690BRecord>(Rva000B690BRecord*,const Rva000B690BRecord&);}
template Rva000B690BRecord *_STL::__copy(Rva000B690BRecord*,Rva000B690BRecord*,Rva000B690BRecord*,const _STL::random_access_iterator_tag&,int*);

// The retail call in this body reads 0x000B450B, an address the ledger already
// carries as ??0Rva000B450B@@QAE@ABV0@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??4Rva000B690BRecord@@QAEAAU0@ABU0@@Z=??0Rva000B450B@@QAE@ABV0@@Z")
