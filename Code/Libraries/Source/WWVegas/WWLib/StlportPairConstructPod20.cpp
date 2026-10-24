// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 placement-copy view, retained from StlportPairConstructFamily.cpp.
// Native 0x004192A4 is the complete 45-byte EH-guarded placement operation.
// Its callee 0x0041922E is independently recovered as the string-aware
// Rva0041922E copy constructor. The old BfmePod20 spelling remains a
// placement-only opaque view, not a claim about that callee's actual layout.
// Keep this unresolved binding out of the other placement-copy families.
#include <memory>
#include <utility>

struct BfmePod20 { int a[5]; BfmePod20(const BfmePod20 &); };
typedef _STL::pair<const int, BfmePod20> IntPod20Pair;

// Retail's placement copy calls 0x0041922E, rowed as Rva0041922E's copy
// constructor (Rva0041922ECopy.cpp), not a trivial pair copy: construct
// through that name.
struct Rva0041922E { Rva0041922E(const Rva0041922E &); };
template <> void _STL::_Construct<IntPod20Pair, IntPod20Pair>(IntPod20Pair *p, const IntPod20Pair &value)
{
	new (p) Rva0041922E(*(const Rva0041922E *)&value);
}

// Native 0x0078671B: complete 14-byte placement-new failure cleanup.
// The exact parent and EH graph bind this action to the existing no-op
// placement delete; the original record identity stays unknown.
