// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector<DynamicPortalLink>::_M_insert_overflow, false_type
// growth path (12-byte Patch-owned portal Link records) and its push_back, emitted by
// explicit instantiation of those two members of the real vendor template; retail 0x0046152F
// is exactly this body, the _M_insert_overflow reachable from the DynamicPortalBehaviour list.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

// Native placement-copy calls 0x460F18, whose complete provider delegates to
// the rowed scalar-vector copy at 0x2CFAB9. The old opaque copy constructor has
// no independent definition. Forward inline to that verified provider.
class DynamicPortalLink;
void Rva00460F18Construct(void *, const void *);
namespace _STL {
static __forceinline void _Construct(DynamicPortalLink *p,
    const DynamicPortalLink &value) { Rva00460F18Construct(p, &value); }
}
#include <vector>

class DynamicPortalLink
{
public:
	DynamicPortalLink();
	DynamicPortalLink(const DynamicPortalLink &other);
	DynamicPortalLink &operator=(const DynamicPortalLink &other);
	~DynamicPortalLink();
	void *m_owned;
	int m_second;
	int m_third;
};

typedef _STL::vector<DynamicPortalLink, _STL::allocator<DynamicPortalLink> > DynamicPortalLinkVector;
template void DynamicPortalLinkVector::_M_insert_overflow(DynamicPortalLink *, const DynamicPortalLink &,
	const _STL::__false_type &, size_t, bool);
template void DynamicPortalLinkVector::push_back(const DynamicPortalLink &);
