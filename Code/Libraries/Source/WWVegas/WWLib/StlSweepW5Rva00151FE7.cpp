// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord36: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord36 *> at 0x00151E7F (stlport_asciistring_record_bodies.cpp).
#include <vector>

struct BfmeAssignRecord36 { char m_bytes[36]; BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord36 *__copy_backward<BfmeAssignRecord36 *, BfmeAssignRecord36 *, int>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, BfmeAssignRecord36 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord36 *_STL::__copy_backward_ptrs<BfmeAssignRecord36 *, BfmeAssignRecord36 *>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, BfmeAssignRecord36 *, const _STL::__false_type &);
