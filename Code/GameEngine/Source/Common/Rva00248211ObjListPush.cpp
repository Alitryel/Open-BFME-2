// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// list<Rva0024076D>::push_back @0x00248211 and its insert @0x00247089, which
// creates the node through _M_create_node 0x002461F1. 0x0024877A inserts into
// its record list through 0x00247089.
#include <list>
// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
class Rva0024076D {
public:
	~Rva0024076D();
private:
	char m_pad[0x50];
};
template void _STL::list<Rva0024076D>::push_back(const Rva0024076D &);
