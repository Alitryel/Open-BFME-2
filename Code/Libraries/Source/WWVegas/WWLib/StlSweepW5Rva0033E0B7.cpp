// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

class ProductionPrerequisite { public: ProductionPrerequisite(const ProductionPrerequisite &); private: void *m_unreconstructed[9]; };

namespace _STL {
template <> void _Construct<ProductionPrerequisite, ProductionPrerequisite>(ProductionPrerequisite *, const ProductionPrerequisite &);
}

// Instantiate the recovered operation and its required template dependencies.
template ProductionPrerequisite * _STL::__uninitialized_copy<ProductionPrerequisite const *, ProductionPrerequisite *>(ProductionPrerequisite const *, ProductionPrerequisite const *, ProductionPrerequisite *, _STL::__false_type const &);
