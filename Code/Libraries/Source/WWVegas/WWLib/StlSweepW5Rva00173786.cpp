// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord32: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord32 *> at 0x001734D1 (stlport_asciistring_record_bodies.cpp),
// which also emits this same forwarder for BfmeAssignRecord32.
#include <vector>

struct BfmeAssignRecord32 { char m_bytes[32]; BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &); ~BfmeAssignRecord32(); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord32 *__copy_backward<BfmeAssignRecord32 *, BfmeAssignRecord32 *, int>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord32 *_STL::__copy_backward_ptrs<BfmeAssignRecord32 *, BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const _STL::__false_type &);
