// ??0?$vector@UBfmeContainerRecord005FDEC7@@V?$allocator@UBfmeContainerRecord005FDEC7@@@_STL@@@_STL@@QAE@I@Z
// partial score=0.636 date=2026-10-15
// vector<BfmeContainerRecord005FDEC7>::vector(unsigned)
// partial score=0.8606223479490807 date=2026-10-14
// cl: /O1 /G7 /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport donor: reference/open-bfme-1/vendor/stlport/stl/_vector.h.
// Reference revision a7c38d3b2597121f178ab5190b3062478823257d.
// Full native 0x5FE409 is a count vector constructor with a zeroed12B temporary.
// Target assignment 0x5FDEC7 copies words +0/+4 and sets the wide string at +8.
// The destroy loop confirms a 12-byte stride; application identity is unknown.
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
struct BfmeContainerRecord005FDEC7 {
    unsigned int word0;
    unsigned int word4;
    UnicodeString text08;
    BfmeContainerRecord005FDEC7(): word0(0),word4(0) {}
    __declspec(nothrow) BfmeContainerRecord005FDEC7 &operator=(const BfmeContainerRecord005FDEC7 &other);
};
__declspec(nothrow) BfmeContainerRecord005FDEC7 &BfmeContainerRecord005FDEC7::operator=(const BfmeContainerRecord005FDEC7 &other) {
    word0 = other.word0;
    word4 = other.word4;
    text08 = other.text08;
    return *this;
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void vector<BfmeContainerRecord005FDEC7, allocator<BfmeContainerRecord005FDEC7> >::_M_fill_insert(BfmeContainerRecord005FDEC7 *, unsigned int, BfmeContainerRecord005FDEC7 const &); }
// bfme link decl-only end
template class _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> >;

void forceCountH(unsigned n) { _STL::vector<BfmeContainerRecord005FDEC7> v(n); }

// Remaining wall: compiled104 vs native99. _M_fill_initialize inlines the
// public uninitialized_fill_n into a four-argument __uninitialized_fill_n call;
// retail keeps the public three-argument wrapper at0x5FE3C1 out of line.
// Current5FE3C1 owner is named copy_backward_aux despite its actual call to
// the uninitialized-fill worker5FE24C; reconcile the owner/recursive fold proof
// rather than use that pointer-specialization name with a count argument.
// Count _Vector_base specialization at5C8C37 also needs full fold proof.
