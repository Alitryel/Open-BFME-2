// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 28-byte BfmeStringRecord00111ACF vector allocation/copy helper at RVA 0x101F5C.
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
#include <vector>
// Suppress this TU's non-retail copy of ??$__copy@PBUBfmeStringRecord00111ACF@@PAU1@H@_STL@@YAPAUBfmeStringRecord00111ACF@@PBU1@0P:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord00111ACF;
namespace _STL { template <> BfmeStringRecord00111ACF * __copy<BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF *,int>(BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF const *,BfmeStringRecord00111ACF *,random_access_iterator_tag const &,int *); }
struct BfmeStringRecord00111ACF {
    AsciiString first;
    unsigned int word4;
    struct FloatStorage { float values[4]; } middle;
    AsciiString second;
    BfmeStringRecord00111ACF();
    BfmeStringRecord00111ACF(const BfmeStringRecord00111ACF &);
    ~BfmeStringRecord00111ACF();
};
namespace _STL {
template <> void _Construct<BfmeStringRecord00111ACF, BfmeStringRecord00111ACF>(BfmeStringRecord00111ACF *, const BfmeStringRecord00111ACF &);
}
// The mutable-range uninitialized copy (0x003F62F5) and push_back (0x003F6CF9)
// construct through 0x003F62C8, rowed as _Construct<EvaMessageInfo>, while
// the const-range copy and fill rows here use 0x000AD77B; spell those two.
struct EvaMessageInfo;
namespace _STL {
template <> void _Construct<EvaMessageInfo, EvaMessageInfo>(EvaMessageInfo *, const EvaMessageInfo &);
template <> inline BfmeStringRecord00111ACF *
__uninitialized_copy<BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *>(BfmeStringRecord00111ACF *first,
    BfmeStringRecord00111ACF *last, BfmeStringRecord00111ACF *result, const __false_type &)
{
    BfmeStringRecord00111ACF *cur = result;
    for ( ; first != last; ++first, ++cur)
        _Construct((EvaMessageInfo *)cur, *(const EvaMessageInfo *)first);
    return cur;
}
template <> inline void vector<BfmeStringRecord00111ACF>::push_back(const BfmeStringRecord00111ACF &x)
{
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
        _Construct((EvaMessageInfo *)this->_M_finish, (const EvaMessageInfo &)x);
        ++this->_M_finish;
    }
    else
        _M_insert_overflow(this->_M_finish, x, __false_type(), 1UL, true);
}
}
template class _STL::vector<BfmeStringRecord00111ACF, _STL::allocator<BfmeStringRecord00111ACF> >;
