// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 resize; native char-pointer keys and integer offsets.
// The prior basic_string attribution was not established by its masked placement.
#define _STLP_BFME_LOWER_BOUND_EXTERN
#include <hash_map>
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}
// Pointer keys and four-byte offsets are native facts; signedness and the
// concrete template spelling remain reconstruction choices.
typedef _STL::pair<const char *, int> XferKeyOffsetPair;
typedef _STL::hashtable<XferKeyOffsetPair, const char *, _STL::hash<const char *>, _STL::_Select1st<XferKeyOffsetPair>, _STL::equal_to<const char *>, _STL::allocator<XferKeyOffsetPair> > XferKeyOffsetTable;
template void XferKeyOffsetTable::resize(unsigned int);
