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

// Do not instantiate a trivial copy for the native string-bearing payload.
template <> _STL::pair<const int, BfmePod20>::pair(const IntPod20Pair &);
template void _STL::_Construct<IntPod20Pair, IntPod20Pair>(IntPod20Pair *, const IntPod20Pair &);

// Native 0x0078671B: complete 14-byte placement-new failure cleanup.
// The exact parent and EH graph bind this action to the existing no-op
// placement delete; the original record identity stays unknown.
