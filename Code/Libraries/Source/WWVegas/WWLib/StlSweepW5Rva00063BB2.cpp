// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

struct Rva00063BB2Element {Rva00063BB2Element();Rva00063BB2Element(const Rva00063BB2Element&);Rva00063BB2Element&operator=(const Rva00063BB2Element&);~Rva00063BB2Element(){}char bytes[36]; bool operator==(const Rva00063BB2Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00063BB2Element * _STL::__copy<Rva00063BB2Element *, Rva00063BB2Element *, int>(Rva00063BB2Element *, Rva00063BB2Element *, Rva00063BB2Element *, _STL::random_access_iterator_tag const &, int *);

// 0x00063C72 forwards (first, last, result) here with a random_access_iterator_tag and a
// null distance pointer: the __false_type __copy_ptrs dispatcher over this element.
template Rva00063BB2Element * _STL::__copy_ptrs<Rva00063BB2Element *, Rva00063BB2Element *>(Rva00063BB2Element *, Rva00063BB2Element *, Rva00063BB2Element *, _STL::__false_type const &);
