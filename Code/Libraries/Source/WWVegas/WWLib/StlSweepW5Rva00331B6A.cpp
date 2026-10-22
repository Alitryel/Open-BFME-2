// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeStringRecord00331962: this fill_n's construct call goes to
// the rowed _Construct<BfmeStringRecord00331962> at 0x00331B3D
// (StringRecordCopyBFME2.cpp), which is declared only here.
#include <vector>

struct BfmeStringRecord00331962
{
	BfmeStringRecord00331962(const BfmeStringRecord00331962 &source);
	char bytes[12];
};

namespace _STL { template <> void _Construct<BfmeStringRecord00331962, BfmeStringRecord00331962>(BfmeStringRecord00331962 *, const BfmeStringRecord00331962 &); }

template BfmeStringRecord00331962 *_STL::__uninitialized_fill_n<BfmeStringRecord00331962 *, unsigned int, BfmeStringRecord00331962>(BfmeStringRecord00331962 *, unsigned int, const BfmeStringRecord00331962 &, const _STL::__false_type &);
