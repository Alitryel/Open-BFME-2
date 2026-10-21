// cl: /Ireference/shims/stlport_stringrecord_5ddd40 /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2 8-byte BfmeStringRecord005DDD40 vector copy_backward helpers.
// ??$__copy_backward@PAUBfmeStringRecord005DDD40@@PAU1@H@_STL@@YAPAUBfmeStringRecord005DDD40@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x005DD743 47B via operator= 0x005DD6B6 plus word copy; caller 0x005DDD5B.
// ??$__copy_backward_ptrs@PAUBfmeStringRecord005DDD40@@PAU1@@_STL@@YAPAUBfmeStringRecord005DDD40@@PAU1@00ABU__false_type@0@@Z @0x005DDD5B 29B wrapper via rowed 0x005DD743; gap between 0x005DDD40 and 0x005DDD78 in StringRecordInlineCopyBFME2.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "unicode_string.h"
#include <vector>
struct BfmeStringRecord005DDD40 {
    UnicodeString text;
    unsigned int word;
    BfmeStringRecord005DDD40();
    BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &);
    BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &);
public:
	~BfmeStringRecord005DDD40();
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
// The range-erase specialization is byte-verified in the separate erase unit.
// Keep this explicit vector instantiation from emitting a competing body.
template <> BfmeStringRecord005DDD40 *vector<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >::erase(BfmeStringRecord005DDD40 *, BfmeStringRecord005DDD40 *);
}
// The chat-history copy uses the distinct native placement-copy entry at
// 0x003814A6; the generic record helpers use the other copy at 0x005DDD78.
void Rva003814A6Construct(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
namespace _STL {
template <> void vector<BfmeStringRecord005DDD40>::push_back(const BfmeStringRecord005DDD40 &value)
{
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
        Rva003814A6Construct(this->_M_finish, value);
        ++this->_M_finish;
    } else {
        _M_insert_overflow(this->_M_finish, value, _IsPODType(), 1UL, true);
    }
}
}
template class _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >;
