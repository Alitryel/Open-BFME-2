// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
// The element is Object::xfer's 8-byte unresolved-trigger pair; its list
// node allocation is the rowed _M_create_node at 0x00293486 (the only caller
// is this unit's insert at 0x002947F0), whose opaque record spelling it shares.
struct Rva00293486Record { unsigned char bytes[8]; bool operator==(const Rva00293486Record&) const; bool operator<(const Rva00293486Record&) const; };
template void _STL::list<Rva00293486Record>::push_back(const Rva00293486Record &);
