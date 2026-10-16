// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// _List_base clear @0x00243119, 49B.
#include <list>
struct Rva00240831Dtor {
	~Rva00240831Dtor();
	char m_pad[1];
};
template void _STL::_List_base<Rva00240831Dtor, _STL::allocator<Rva00240831Dtor> >::clear();

// The retail call in this body reads 0x00240831, an address the ledger already
// carries as ??1WorkerAIUpdateModuleData@@UAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Rva00240831Dtor@@QAE@XZ=??1WorkerAIUpdateModuleData@@UAE@XZ")
