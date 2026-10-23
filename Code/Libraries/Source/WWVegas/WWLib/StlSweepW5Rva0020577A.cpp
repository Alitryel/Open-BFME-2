// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

// Retail's loop calls _Construct<BfmeStringRecord00204A30> (0x002056DC,
// StringRecordInlineCopyBFME2.cpp), so the 20-byte element is that unit's record
// with its rowed copy ctor 0x00204A30.
struct BfmeStringRecord00204A30 { char bytes[20]; BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &source); };
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeStringRecord00204A30, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 const &); }
// bfme link decl-only end

// Instantiate the recovered operation and its required template dependencies.
template BfmeStringRecord00204A30 * _STL::__uninitialized_fill_n<BfmeStringRecord00204A30 *, unsigned int, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, unsigned int, BfmeStringRecord00204A30 const &, _STL::__false_type const &);
