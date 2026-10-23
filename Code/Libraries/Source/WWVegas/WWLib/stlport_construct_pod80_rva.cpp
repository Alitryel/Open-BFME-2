// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@UBfmePod80@@U1@@_STL@@YAXPAUBfmePod80@@ABU1@@Z @0x0051F920 45B: placement copy of 80B element via rowed Rva0051F87B copy ctor 0x0051F87B. Callers in stlport_pod_vector_bodies.cpp (__uninitialized_copy/fill_n) plus StlportVectorOverflowRva00520211.cpp (twin-pinned as Rva00520211Element). Precedent stlport_construct_pod172.cpp.
#include <new>
#include <vector>
struct BfmePod80 { int a[20]; };
class Rva0051F87B
{
public:
	Rva0051F87B(const Rva0051F87B &o);
};
namespace _STL {
template <> inline void _Construct<BfmePod80, BfmePod80>(BfmePod80 *__p, const BfmePod80 &__val)
{
	new ((void *)__p) Rva0051F87B((const Rva0051F87B &)__val);
}
}

// This specialization is a header inline in the copier units; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeStlportConstructPod80InlineAnchor@@YAXXZ absent-from-retail
void _bfmeStlportConstructPod80InlineAnchor()
{
	_STL::_Construct<BfmePod80, BfmePod80>(
		static_cast<BfmePod80 *>(0), *static_cast<const BfmePod80 *>(0));
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@URva00520211Element@@U1@@_STL@@YAXPAURva00520211Element@@ABU1@@Z=??$_Construct@UBfmePod80@@U1@@_STL@@YAXPAUBfmePod80@@ABU1@@Z")

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??$_Construct@URva00520211Element@@U1@@_STL@@YAXPAURva00520211Element@@ABU1@@Z=??$_Construct@UBfmePod80@@U1@@_STL@@YAXPAUBfmePod80@@ABU1@@Z")
