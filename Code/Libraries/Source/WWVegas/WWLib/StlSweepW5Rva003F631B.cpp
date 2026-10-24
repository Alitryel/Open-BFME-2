// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct EvaMessageInfo { char m_unported[28]; EvaMessageInfo(const EvaMessageInfo &); };

namespace _STL {
template <> void _Construct<EvaMessageInfo, EvaMessageInfo>(EvaMessageInfo *, const EvaMessageInfo &);
}

// Instantiate the recovered operation and its required template dependencies.
template EvaMessageInfo * _STL::__uninitialized_fill_n<EvaMessageInfo *, unsigned int, EvaMessageInfo>(EvaMessageInfo *, unsigned int, EvaMessageInfo const &, _STL::__false_type const &);
