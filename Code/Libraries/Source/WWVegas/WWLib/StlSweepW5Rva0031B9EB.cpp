// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// Retail's allocate (0x00068E15, shl 2) and copy loop (0x001DD10D, one dword per element)
// prove a 4-byte element copied by value; the copy constructor is that inline dword copy.
struct Rva0031B9EBElement { int value;Rva0031B9EBElement();Rva0031B9EBElement(const Rva0031B9EBElement&o):value(o.value){}~Rva0031B9EBElement();Rva0031B9EBElement&operator=(const Rva0031B9EBElement&); bool operator<(const Rva0031B9EBElement&)const; bool operator==(const Rva0031B9EBElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0031B9EBElement * _STL::vector<Rva0031B9EBElement, _STL::allocator<Rva0031B9EBElement> >::_M_allocate_and_copy<Rva0031B9EBElement const *>(unsigned int, Rva0031B9EBElement const *, Rva0031B9EBElement const *);
