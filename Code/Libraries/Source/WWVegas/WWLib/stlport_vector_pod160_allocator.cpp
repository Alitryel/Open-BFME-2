// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BFME2's 160-byte Pod vector allocator at RVA 0x003A44ED (28B: imul-0xa0
// size computation plus the shared byte-allocator call). The home TU
// (stlport_pod_vector_bodies.cpp) compiles its allocators under /O1, which
// strength-reduces n*160 to lea+shl; retail keeps the imul, which this
// toolchain emits only under /G7 P4 tuning (probe-proven on the B9534 and
// Pod144 allocator precedents). Same-TU visibility and flag-split rules
// require a shard: flipping the home TU's flags would break its landed /O1
// bodies. Size-carrying body, so the BfmePod160 placeholder name is honest
// per the POD-PLACEHOLDER LAW (element construction never passes through
// here). The BfmePod160 layout mirrors the home TU declaration.
struct BfmePod160 { int a[40]; };
#include <memory>
// allocator::construct would otherwise emit a second copy of _Construct<BfmePod160>, whose
// body is the pinned copy construct at 0x003A454E; declare it as the home TU does.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod160, BfmePod160>(BfmePod160 *__p, const BfmePod160 &__val); }
template class _STL::allocator<BfmePod160>;

// The retail call in this body reads 0x003A454E, an address the ledger already
// carries as ??$_Construct@UBfmeContainerRecord003A451B@@U1@@_STL@@YAXPAUBfmeContainerRecord003A451B@@ABU1@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??$_Construct@UBfmePod160@@U1@@_STL@@YAXPAUBfmePod160@@ABU1@@Z=??$_Construct@UBfmeContainerRecord003A451B@@U1@@_STL@@YAXPAUBfmeContainerRecord003A451B@@ABU1@@Z")
