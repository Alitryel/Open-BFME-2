// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<28-byte POD>::~vector at 0x002E4F50 (64 B gap
// claimed by its shape: element count via the 0x92492493 magic divide, buffers
// over 0x80 bytes go to operator delete, smaller ones to the node allocator).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
struct Rva002E4F50Elem { int m_v[7]; };
template class _STL::vector<Rva002E4F50Elem>;
