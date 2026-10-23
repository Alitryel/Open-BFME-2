// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

// Retail's loop calls _Construct<BfmePod104> (0x003B8AD8, StlportConstructFamily.cpp),
// so the element is that 104-byte record with its out-of-line copy ctor.
struct BfmePod104 { char m_pad[104]; BfmePod104(const BfmePod104 &); ~BfmePod104(); };

// Instantiate the recovered operation and its required template dependencies.
template BfmePod104 * _STL::__uninitialized_fill_n<BfmePod104 *, unsigned int, BfmePod104>(BfmePod104 *, unsigned int, BfmePod104 const &, _STL::__false_type const &);

// 0x003F4163 calls this fill through the out-of-line uninitialized_fill_n wrapper
// (three arguments plus the __false_type tag at [ebp-1]).
template BfmePod104 * _STL::uninitialized_fill_n<BfmePod104 *, unsigned int, BfmePod104>(BfmePod104 *, unsigned int, BfmePod104 const &);
