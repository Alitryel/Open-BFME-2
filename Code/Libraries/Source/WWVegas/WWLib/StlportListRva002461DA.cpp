// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /DNDEBUG /MD /EHs-c- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// _List_base<Rva0024076D> dtor @0x002461DA (23B): clear 0x00243119, then free
// the sentinel through 0x00030830. Callers: 0x0024877A's record list
// (0x00248CA4) and the jmp at 0x00247084.
#include <list>
// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
class Rva0024076D {
public:
	~Rva0024076D();
private:
	char m_pad[0x50];
};
namespace _STL {
// clear is rowed in stlport_list_rva00243119_clear.cpp.
template <> void _List_base<Rva0024076D, allocator<Rva0024076D> >::clear();
}
template _STL::_List_base<Rva0024076D, _STL::allocator<Rva0024076D> >::~_List_base();
