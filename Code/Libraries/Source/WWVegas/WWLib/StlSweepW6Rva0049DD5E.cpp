// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// The fill loop's construct call goes to 0x0049DD0B, pinned as
// _Construct<QuantityModifier> (the REL32 target of the rowed
// vector<QuantityModifier> overflow 0x0049F729), so the element is
// QuantityModifier (AsciiString plus int, 8 bytes; opaque here).
struct QuantityModifier
{
	QuantityModifier(const QuantityModifier &);
	char m_opaque[8];
};

namespace _STL {
template <> void _Construct<QuantityModifier, QuantityModifier>(QuantityModifier *, const QuantityModifier &);
}

template QuantityModifier * _STL::__uninitialized_fill_n<QuantityModifier *, unsigned int, QuantityModifier>(QuantityModifier *, unsigned int, QuantityModifier const &, _STL::__false_type const &);
