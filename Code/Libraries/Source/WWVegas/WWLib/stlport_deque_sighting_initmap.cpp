// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<SightingInfo*>: _M_initialize_map 189B at
// 0x006203D0 plus the (alloc n) base ctor 76B at 0x00620690 which calls it.
// Real element type is SightingInfo* (PAVSightingInfo: class pointer 4B).
// Same noexc split-TU rationale as stlport_deque_e8_initmap.cpp: retail carries
// no exception-handling frame (the _STLP_TRY/_STLP_UNWIND rollback in
// vendor/stlport/stl/_deque.c compiles to nothing once _STLP_USE_EXCEPTIONS
// is off). /O2 inlines _M_create_nodes into _M_initialize_map; the node stride
// is 0x80 with shr-5 sizing (128/4 = 32 per node) and tail and-0x1f lea *4.
// Callers: deque ctor 0x006209D0 at 0x6209F3 and base ctor 0x00620690 at 0x6206D0.
// Donor: vendor/stlport/stl/_deque.c _M_initialize_map.
#include <deque>
// bfme link decl-only begin
namespace _STL { template <> void deque<int, allocator<int> >::_M_reallocate_map(unsigned int, bool); }
// Preserve the allocator header's inline operations without emitting separate
// int allocator copies. The initializer passes bytes to the shared allocator;
// deallocation remains the same null-guarded free.
namespace _STL {
template <> __declspec(dllimport) __forceinline
int *allocator<int>::allocate(size_t n, const void *) const
{ return n != 0 ? reinterpret_cast<int *>(allocator<char>::allocate(n * sizeof(int), 0)) : 0; }
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int *p, size_t) const
{ if (p != 0) ::free((void *)p); }
}
// bfme link decl-only end
class SightingInfo;
template class _STL::deque<SightingInfo*, _STL::allocator<SightingInfo* > >;

// AssetManagerImpl's seven 40-byte deques are constructed by the native
// default-argument closure620D80. Emit its four-byte int storage view here,
// under the same established no-exception settings. The constructor and map
// initializer may share the SightingInfo* owners only after pin_admission's
// full-body and relocation fold proof; the element spelling is an ABI view.
// Emit only the shared initializer and the default allocator constructor;
// the other int-deque members are owned by their existing provider units.
template void _STL::_Deque_base<int, _STL::allocator<int> >::_M_initialize_map(size_t);
template _STL::deque<int, _STL::allocator<int> >::deque(const _STL::allocator<int> &);
