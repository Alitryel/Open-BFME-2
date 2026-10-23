// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::_M_insert_overflow at target boundary 0x00361680/191.
// The matched vector::push_back at 0x00361756 calls this helper. Retail uses a
// 0x94-byte element stride and calls the separately matched vector clear at
// 0x00361657; its copy/fill/allocation helpers are pinned from their own target
// call sites. The complete application element type/layout is not known.
//
// BfmeStringHeadRecord148 is only an emitter view: 148-byte size and a
// non-trivial copy trait. Its historical AsciiString-plus-padding declaration
// does not describe the native record, which owns six vectors; destruction
// is explicitly routed to the verified Rva00360F55 owner below.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"


struct BfmeStringHeadRecord148 { AsciiString s; int a[36]; };

// Native record teardown is the independently recovered 0x00360FDB owner.
// This emitter view supplies stride and copy traits only; destruction must
// call that owner instead of synthesizing an AsciiString-only destructor.
class Rva00360F55
{
public:
    ~Rva00360F55();
};
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Destroy<BfmeStringHeadRecord148>(BfmeStringHeadRecord148 *p)
{
    ((Rva00360F55 *)p)->~Rva00360F55();
}
}

namespace _STL {
template <> void _Construct<BfmeStringHeadRecord148, BfmeStringHeadRecord148>(
	BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &);
}

template void _STL::vector<BfmeStringHeadRecord148>::_M_insert_overflow(
	BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &,
	const _STL::__false_type &, unsigned int, bool);
