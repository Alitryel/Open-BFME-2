// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeAssignRecord80: this forwarder's only call goes to the rowed
// __copy_backward<BfmeAssignRecord80 *> at 0x0051F9E1 (stlport_asciistring_record_bodies.cpp).
#include <vector>

struct BfmeAssignRecord80 { char m_bytes[80]; BfmeAssignRecord80 &operator=(const BfmeAssignRecord80 &); ~BfmeAssignRecord80(); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeAssignRecord80 *__copy_backward<BfmeAssignRecord80 *, BfmeAssignRecord80 *, int>(BfmeAssignRecord80 *, BfmeAssignRecord80 *, BfmeAssignRecord80 *, const random_access_iterator_tag &, int *); }

template BfmeAssignRecord80 *_STL::__copy_backward_ptrs<BfmeAssignRecord80 *, BfmeAssignRecord80 *>(BfmeAssignRecord80 *, BfmeAssignRecord80 *, BfmeAssignRecord80 *, const _STL::__false_type &);
