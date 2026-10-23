// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@UBfmePod196@@U1@@_STL@@YAXPAUBfmePod196@@ABU1@@Z @ 0x00438E49 (18B).
// Null-guarded placement copy over the 196-byte element whose real copy ctor
// is the rowed Rva004382FC copy at 0x00438559 (twin-pinned as BfmePod196 copy).
// Same 18B throw-spec shape as rowed _Construct<BfmeObject872> at 0x002CF8A9.
// Caller is the rowed list node create at 0x00438F99.
#include <memory>
#include <new>

struct BfmePod196 {
    BfmePod196(const BfmePod196 &other);
    char m_body[196];
};

namespace _STL {
template<> inline void _Construct<BfmePod196, BfmePod196>(BfmePod196 *dest, const BfmePod196 &source) throw() { new (dest) BfmePod196(source); }
}

#pragma inline_depth(0)
// ?bfmeEmitPod196Construct@@YAXPAUBfmePod196@@ABU1@@Z present-unmatched
void bfmeEmitPod196Construct(BfmePod196 *p, const BfmePod196 &q)
{
	_STL::_Construct<BfmePod196, BfmePod196>(p, q);
}
#pragma inline_depth()
