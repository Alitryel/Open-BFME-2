// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 32-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod32 names only the 32-byte stride, matching the pod-vector TU convention.
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
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod32;
class Gen_005e9a20;
namespace _STL {
template <> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *, const Gen_005e9a20 &);
// 0x00421D16
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod32, BfmePod32>(BfmePod32 *p, const BfmePod32 &v)
{ _Construct((Gen_005e9a20 *)p, (const Gen_005e9a20 &)v); }
}
struct BfmePod32 { int a[8]; };
// bfme link decl-only BfmePod32
namespace _STL { template <> vector<BfmePod32, allocator<BfmePod32> >::~vector(); }
template BfmePod32 *_STL::vector<BfmePod32>::_M_allocate_and_copy<const BfmePod32 *>(unsigned int, const BfmePod32 *, const BfmePod32 *);
