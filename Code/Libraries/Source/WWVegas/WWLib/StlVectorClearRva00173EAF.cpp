// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport vector<Rva0017341BWords>::clear(), retail 0x00173EAF (11 bytes):
// erase(begin(), end()) through the matched range erase 0x00173DF8
// (StlRangeEraseRva00173DF8.cpp), which is declared here so this unit calls
// retail's copy instead of inlining its own. Same shape as the matched
// vector<BfmeFixedObject60>::clear (StlportFixedObject60Vector.cpp). No
// direct caller found.
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include <vector>
#include "StlRecordRva0017341B.h"
namespace _STL {
template <> Rva0017341BWords *vector<Rva0017341BWords>::erase(Rva0017341BWords *, Rva0017341BWords *);
}
template void _STL::vector<Rva0017341BWords, _STL::allocator<Rva0017341BWords> >::clear();
