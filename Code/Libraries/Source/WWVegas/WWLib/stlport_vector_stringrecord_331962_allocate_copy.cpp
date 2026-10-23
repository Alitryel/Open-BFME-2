// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeStringRecord000331962 vector allocation/copy helper at RVA 0x331CE3.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
struct BfmeStringRecord000331962 {
    unsigned int word;
    AsciiString text;
    unsigned char flag;
    BfmeStringRecord000331962();
    BfmeStringRecord000331962(const BfmeStringRecord000331962 &other) : word(other.word), text(other.text), flag(other.flag) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000331962,BfmeStringRecord000331962>(BfmeStringRecord000331962*,const BfmeStringRecord000331962&);
#include <vector>
typedef _STL::vector<BfmeStringRecord000331962> StringRecordVector;
template BfmeStringRecord000331962 *StringRecordVector::_M_allocate_and_copy(
    unsigned int, const BfmeStringRecord000331962 *, const BfmeStringRecord000331962 *);
template void StringRecordVector::push_back(const BfmeStringRecord000331962 &);
template StringRecordVector::vector(const StringRecordVector &);
template void _STL::fill(BfmeStringRecord000331962 *, BfmeStringRecord000331962 *, const BfmeStringRecord000331962 &);
