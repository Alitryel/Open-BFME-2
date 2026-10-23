// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

#include <algorithm>
#include <deque>

class LightPoint;

struct Rva00425B75Deleter
{
	void operator()(LightPoint *p) const;
};

template Rva00425B75Deleter _STL::for_each(_STL::deque<LightPoint *>::iterator, _STL::deque<LightPoint *>::iterator, Rva00425B75Deleter);

// The retail call in this body reads 0x00425B75, an address the ledger already
// carries as ?Rva00425B75Delete@@YGXPAVLightPoint@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??RRva00425B75Deleter@@QBEXPAVLightPoint@@@Z=?Rva00425B75Delete@@YGXPAVLightPoint@@@Z")
