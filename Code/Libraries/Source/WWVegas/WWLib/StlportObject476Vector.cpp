// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target object view; original type and member fields are unknown.
// Copy construction writes vptrs and cleanup dispatches a virtual destructor.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct BfmeObject476
{
    virtual ~BfmeObject476();
    unsigned char opaque[472];
    BfmeObject476();
    BfmeObject476(const BfmeObject476&);
    BfmeObject476 &operator=(const BfmeObject476&);
};
// bfme link decl-only BfmeObject476
namespace _STL { template <> BfmeObject476 * vector<BfmeObject476, allocator<BfmeObject476> >::erase(BfmeObject476 *, BfmeObject476 *); }

template void _STL::vector<BfmeObject476>::push_back(const BfmeObject476&);
template void _STL::vector<BfmeObject476>::_M_clear();
template BfmeObject476& _STL::vector<BfmeObject476>::operator[](unsigned int);
template BfmeObject476* _STL::__copy<BfmeObject476*,BfmeObject476*,int>(BfmeObject476*,BfmeObject476*,BfmeObject476*,const _STL::random_access_iterator_tag&,int*);


template BfmeObject476* _STL::__uninitialized_copy<const BfmeObject476*,BfmeObject476*>(const BfmeObject476*,const BfmeObject476*,BfmeObject476*,const _STL::__false_type&);
