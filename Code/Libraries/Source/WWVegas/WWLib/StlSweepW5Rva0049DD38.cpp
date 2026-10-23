// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

// The element is QuantityModifier (8 bytes, AsciiString plus int): retail's
// vector<QuantityModifier>::_M_insert_overflow 0x0049F729 calls this body twice
// as __uninitialized_copy<QuantityModifier *, QuantityModifier *>, and its copy
// loop calls 0x0049DD0B, _Construct<QuantityModifier> (emitted by
// stlport_vector_quantitymodifier_insert_overflow_49F729.cpp). Declared only here.
struct QuantityModifier
{
	QuantityModifier(const QuantityModifier &);
	~QuantityModifier();
	char bytes[8];
};
namespace _STL { template <> void _Construct<QuantityModifier, QuantityModifier>(QuantityModifier *, const QuantityModifier &); }

// Instantiate the recovered operation and its required template dependencies.
template QuantityModifier * _STL::__uninitialized_copy<QuantityModifier *, QuantityModifier *>(QuantityModifier *, QuantityModifier *, QuantityModifier *, _STL::__false_type const &);
