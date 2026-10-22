// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord52: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord52 *> at 0x002B830A (stlport_asciistring_record_bodies.cpp),
// which also emits this same forwarder for BfmeAssignRecord52.
#include <vector>

struct BfmeAssignRecord52 { char m_bytes[52]; BfmeAssignRecord52 &operator=(const BfmeAssignRecord52 &); ~BfmeAssignRecord52(); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord52 *__copy_backward<BfmeAssignRecord52 *, BfmeAssignRecord52 *, int>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, BfmeAssignRecord52 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord52 *_STL::__copy_backward_ptrs<BfmeAssignRecord52 *, BfmeAssignRecord52 *>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, BfmeAssignRecord52 *, const _STL::__false_type &);
