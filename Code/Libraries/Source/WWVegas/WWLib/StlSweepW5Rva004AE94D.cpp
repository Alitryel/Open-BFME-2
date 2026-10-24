// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

class WeaponTemplateSet { public: WeaponTemplateSet(const WeaponTemplateSet &); private: char m_unreconstructed[84]; };

namespace _STL {
template <> void _Construct<WeaponTemplateSet, WeaponTemplateSet>(WeaponTemplateSet *, const WeaponTemplateSet &);
}

// Instantiate the recovered operation and its required template dependencies.
template WeaponTemplateSet * _STL::__uninitialized_fill_n<WeaponTemplateSet *, unsigned int, WeaponTemplateSet>(WeaponTemplateSet *, unsigned int, WeaponTemplateSet const &, _STL::__false_type const &);
