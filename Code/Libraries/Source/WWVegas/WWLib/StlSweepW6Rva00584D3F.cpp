// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <algorithm>
#include <memory>
#include <utility>

struct Rva00584D3FElement { unsigned char words[1];bool operator<(const Rva00584D3FElement&)const;bool operator==(const Rva00584D3FElement&)const; };
// Emit the matched trait directly. Whole sort/heap instantiations also emitted
// unrelated operations needing the provisional element's undefined comparison.
template struct _STL::_OKToMemCpy<Rva00584D3FElement, Rva00584D3FElement>;
