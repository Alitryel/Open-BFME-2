// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord84: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord84 *> at 0x00586D5C (stlport_asciistring_record_bodies.cpp).
#include <vector>

struct BfmeAssignRecord84 { char m_bytes[84]; BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord84 *__copy_backward<BfmeAssignRecord84 *, BfmeAssignRecord84 *, int>(BfmeAssignRecord84 *, BfmeAssignRecord84 *, BfmeAssignRecord84 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord84 *_STL::__copy_backward_ptrs<BfmeAssignRecord84 *, BfmeAssignRecord84 *>(BfmeAssignRecord84 *, BfmeAssignRecord84 *, BfmeAssignRecord84 *, const _STL::__false_type &);
