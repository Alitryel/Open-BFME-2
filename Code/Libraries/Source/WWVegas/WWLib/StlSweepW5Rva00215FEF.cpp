// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <algorithm>
#include <memory>

struct Rva00215FEFElement { char bytes[28]; bool operator<(const Rva00215FEFElement&)const; bool operator==(const Rva00215FEFElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00215FEFElement * _STL::__copy<Rva00215FEFElement *, Rva00215FEFElement *, int>(Rva00215FEFElement *, Rva00215FEFElement *, Rva00215FEFElement *, _STL::random_access_iterator_tag const &, int *);

// 0x002161A5 forwards (first, last, result) here with a random_access_iterator_tag and a
// null distance pointer: the __false_type __copy_ptrs dispatcher over this 28-byte element.
template Rva00215FEFElement * _STL::__copy_ptrs<Rva00215FEFElement *, Rva00215FEFElement *>(Rva00215FEFElement *, Rva00215FEFElement *, Rva00215FEFElement *, _STL::__false_type const &);
