// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 24-byte StringRecord vector allocation/copy helper at RVA 0xBBCEF.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
#include "../../../../../reference/shims/bfme2_ascii/string_base.h"
__forceinline AsciiString::AsciiString(const AsciiString &that) { ((::StringBase<char> *)this)->StringBase<char>::StringBase(*(const ::StringBase<char> *)&that); }
__forceinline AsciiString::~AsciiString() { ((::StringBase<char> *)this)->releaseBuffer(); }
struct BfmeStringRecord000B9534 {
    // Use the existing shared record destructor instead of this private copy.
    ~BfmeStringRecord000B9534();
    AsciiString text;
    unsigned char flag;
    unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534();
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &other)
      : text(other.text), flag(other.flag), word0(other.word0), word1(other.word1), word2(other.word2), word3(other.word3) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000B9534,BfmeStringRecord000B9534>(BfmeStringRecord000B9534*,const BfmeStringRecord000B9534&);
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> BfmeStringRecord000B9534 * vector<BfmeStringRecord000B9534,_STL::allocator<BfmeStringRecord000B9534> >::erase(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *); }
// bfme link decl-only end
template class _STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >;
