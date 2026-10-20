// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// _List_base clear @0x00243119, 49B.
#include <list>
// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
class Rva0024076D {
public:
	~Rva0024076D();
private:
	char m_pad[0x50];
};
template void _STL::_List_base<Rva0024076D, _STL::allocator<Rva0024076D> >::clear();
