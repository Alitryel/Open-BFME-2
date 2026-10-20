// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// list<Rva0024076D> construction: _List_base ctor @0x0023E83A (41B, sentinel
// node of 0x58 bytes through the 0x0014F3C4 alloc proxy ctor) and the list
// ctor @0x00247072 (18B) that calls it. 0x0024877A builds its record list
// through 0x0023E83A. Flags as stlport_pod_list_bodies.cpp, which compiled
// these two bodies under a BfmePod80 placeholder before.
#include <list>
// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
class Rva0024076D {
public:
	~Rva0024076D();
private:
	char m_pad[0x50];
};
template _STL::_List_base<Rva0024076D, _STL::allocator<Rva0024076D> >::_List_base(const _STL::allocator<Rva0024076D> &);
template _STL::list<Rva0024076D, _STL::allocator<Rva0024076D> >::list(const _STL::allocator<Rva0024076D> &);
