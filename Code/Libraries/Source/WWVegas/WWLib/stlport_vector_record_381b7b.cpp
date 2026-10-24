// cl: /Ireference/shims/stlport_stringrecord_5ddd40 /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The second retail vector over an 8-byte UnicodeString-plus-word record.
// Its push_back (0x00381C4B) and _M_insert_overflow (0x00381B7B) reach their
// own placement-copy helpers 0x003814A6/0x003814D3/0x003814F9, while
// vector<BfmeStringRecord005DDD40> (stlport_vector_stringrecord_5ddd40_allocate_copy.cpp)
// reaches 0x005DDD78/0x005DDDCA/0x005DDDA5 from its overflow at 0x005DE4BA:
// two same-layout element types whose helpers without exception state
// (_M_clear 0x00381B52, _Destroy 0x00381AC7) /OPT:ICF folded. Element identity is address-derived.
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
// The record's copy constructor and destructor are implicit: retail's
// _Construct 0x003814A6 calls the memberwise copy at 0x005DDD40 and _Destroy
// 0x00381AC7 the folded UnicodeString destructor at 0x005B804E.
struct Rva00381B7BRecord {
    UnicodeString text;
    unsigned int word;
};

template void _STL::vector<Rva00381B7BRecord, _STL::allocator<Rva00381B7BRecord> >::push_back(const Rva00381B7BRecord &);
template void _STL::vector<Rva00381B7BRecord, _STL::allocator<Rva00381B7BRecord> >::_M_insert_overflow(Rva00381B7BRecord *, const Rva00381B7BRecord &, const _STL::__false_type &, unsigned int, bool);
