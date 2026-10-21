// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 8-byte BfmeStringRecord000B94D2 vector allocation/copy helper at RVA 0xBC72B.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BfmeStringRecord000B94D2 {
    AsciiString text0, text1;
    BfmeStringRecord000B94D2();
    BfmeStringRecord000B94D2(const BfmeStringRecord000B94D2 &other) : text0(other.text0), text1(other.text1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000B94D2,BfmeStringRecord000B94D2>(BfmeStringRecord000B94D2*,const BfmeStringRecord000B94D2&);
#include <vector>
// Only the rowed members: a whole-class instantiation also emitted this
// TU's operator= and resize, which differ from retail and, first in link
// order, were kept over stlport_vector_stringrecord_b94d2_assign.cpp's copy.
typedef _STL::vector<BfmeStringRecord000B94D2, _STL::allocator<BfmeStringRecord000B94D2> > BfmeStringRecord000B94D2Vector;
template BfmeStringRecord000B94D2Vector::vector(const BfmeStringRecord000B94D2Vector &);
template void BfmeStringRecord000B94D2Vector::push_back(const BfmeStringRecord000B94D2 &);
template void BfmeStringRecord000B94D2Vector::_M_insert_overflow(BfmeStringRecord000B94D2 *, const BfmeStringRecord000B94D2 &, const _STL::__false_type &, unsigned int, bool);
template void BfmeStringRecord000B94D2Vector::_M_clear();
template BfmeStringRecord000B94D2 *BfmeStringRecord000B94D2Vector::_M_allocate_and_copy<const BfmeStringRecord000B94D2 *>(unsigned int, const BfmeStringRecord000B94D2 *, const BfmeStringRecord000B94D2 *);
