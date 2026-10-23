// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord40: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord40 *> at 0x005400FF (stlport_asciistring_record_bodies.cpp),
// which also emits this same forwarder for BfmeAssignRecord40.
#include <vector>

struct BfmeAssignRecord40 { char m_bytes[40]; };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord40 *__copy_backward<BfmeAssignRecord40 *, BfmeAssignRecord40 *, int>(BfmeAssignRecord40 *, BfmeAssignRecord40 *, BfmeAssignRecord40 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord40 *_STL::__copy_backward_ptrs<BfmeAssignRecord40 *, BfmeAssignRecord40 *>(BfmeAssignRecord40 *, BfmeAssignRecord40 *, BfmeAssignRecord40 *, const _STL::__false_type &);
