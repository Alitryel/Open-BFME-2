// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEXI@Z retail 0x00057E02 104B.
// Real STLport 4.5.3 vector<AsciiString> reserve. Same 104B shape as the landed
// vector<UnicodeString> reserve at 0x0005A27E in stlport_vector_unicode_reserve.cpp.
// Calls _M_allocate_and_copy at 0x000BBCA7 and _M_clear at 0x0002CD53 plus the
// folded allocator at 0x00068E15. Five callers 0x0005A211 0x00061DA1 0x001DEC13
// 0x0032D775 0x0057A0C8 operate on AsciiString vectors.
#include <vector>

#include "ascii_string.h"

// Already rowed at 0x00142CC0 in AsciiStringConstruct.cpp; declaration prevents
// a different local copy-constructor view from replacing that established helper.
// _Destroy stays a call through the rowed range at 0x0002CB64 via _M_clear at
// 0x0002CD53; declaring it keeps the TU from emitting a local copy.
namespace _STL {
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *);
}

template <>
void _STL::vector<AsciiString, _STL::allocator<AsciiString> >::reserve(size_type __n)
{
  if (capacity() < __n) {
    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, (const_pointer)this->_M_start, (const_pointer)this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}
