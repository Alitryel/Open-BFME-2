// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target object view; original type and member fields are unknown.
// Target copy construction and nonvirtual destruction visit owned subobjects.
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

struct BfmeObject544
{
    unsigned char opaque[544];
    ~BfmeObject544();
    BfmeObject544();
    BfmeObject544(const BfmeObject544&);
};

// Instantiate the recovered operations and their helpers. Whole-class
// instantiation also emitted an unrelated vector destructor and assignment.
template void _STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> >::push_back(const BfmeObject544 &);
template void _STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> >::_M_clear();
template void _STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> >::_M_insert_overflow(BfmeObject544 *, const BfmeObject544 &, const _STL::__false_type &, unsigned int, bool);
template BfmeObject544 *_STL::__uninitialized_copy(const BfmeObject544 *, const BfmeObject544 *, BfmeObject544 *, const _STL::__false_type &);
