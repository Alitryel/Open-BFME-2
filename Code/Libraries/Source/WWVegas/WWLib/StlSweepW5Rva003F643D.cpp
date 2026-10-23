// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is Rva003F63B3Element: this forwarder's only call goes to the rowed
// __copy_backward<Rva003F63B3Element *> at 0x003F63B3 (StlSweepW5Rva003F63B3.cpp).
#include <vector>

struct Rva003F63B3Element {Rva003F63B3Element();Rva003F63B3Element(const Rva003F63B3Element&);Rva003F63B3Element&operator=(const Rva003F63B3Element&);~Rva003F63B3Element(){}char bytes[28]; bool operator==(const Rva003F63B3Element&)const;};

// Declared only: the rowed copy serves the call.
namespace _STL { template <> Rva003F63B3Element *__copy_backward<Rva003F63B3Element *, Rva003F63B3Element *, int>(Rva003F63B3Element *, Rva003F63B3Element *, Rva003F63B3Element *, const random_access_iterator_tag &, int *); }

template Rva003F63B3Element * _STL::__copy_backward_ptrs<Rva003F63B3Element *, Rva003F63B3Element *>(Rva003F63B3Element *, Rva003F63B3Element *, Rva003F63B3Element *, _STL::__false_type const &);
