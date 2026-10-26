// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0022DCDARecord { ~Rva0022DCDARecord(); char bytes[1]; };

// Retail's destructor calls the rowed 25-byte range destroy at 0x0022D941,
// ?Rva0022D941Destroy@@YAXPAURva0022CD2A@@0@Z (Rva0022D941Destroy.cpp), over
// 0x18-byte elements. Spell STLport's ~vector body against that owner instead
// of emitting a competing _Destroy<Rva0022DCDARecord *> copy.
struct Rva0022CD2A;
void __cdecl Rva0022D941Destroy(Rva0022CD2A *first, Rva0022CD2A *last);
namespace _STL {
template <> vector<Rva0022DCDARecord>::~vector()
{ Rva0022D941Destroy(reinterpret_cast<Rva0022CD2A *>(this->_M_start), reinterpret_cast<Rva0022CD2A *>(this->_M_finish)); }
}

template _STL::vector<Rva0022DCDARecord>::~vector();
