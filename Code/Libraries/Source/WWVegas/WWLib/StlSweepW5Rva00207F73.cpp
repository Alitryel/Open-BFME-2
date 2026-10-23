// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The element is BfmeStringRecord00204A30: _M_clear's destroy call (0x00207F7B) goes to the
// rowed _Destroy<BfmeStringRecord00204A30 *> at 0x00206CBA
// (stlport_vector_stringrecord_00204a30_allocate_copy.cpp), declared only here.
struct BfmeStringRecord00204A30 { char m_pad[20]; BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &); ~BfmeStringRecord00204A30(); };
namespace _STL { template <> void _Destroy<BfmeStringRecord00204A30 *>(BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *); }

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::_M_clear(void);
