// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is Rva0051FC54Element: this forwarder's only call goes to the rowed
// __copy_backward<Rva0051FC54Element *> at 0x0051F9E1 (stlport_asciistring_record_bodies.cpp).
#include <vector>

struct Rva0051FC54Element { char m_bytes[80]; Rva0051FC54Element &operator=(const Rva0051FC54Element &); ~Rva0051FC54Element(); };

// Declared only: the rowed copy serves the call.
namespace _STL { template <> Rva0051FC54Element *__copy_backward<Rva0051FC54Element *, Rva0051FC54Element *, int>(Rva0051FC54Element *, Rva0051FC54Element *, Rva0051FC54Element *, const random_access_iterator_tag &, int *); }

template Rva0051FC54Element *_STL::__copy_backward_ptrs<Rva0051FC54Element *, Rva0051FC54Element *>(Rva0051FC54Element *, Rva0051FC54Element *, Rva0051FC54Element *, const _STL::__false_type &);
