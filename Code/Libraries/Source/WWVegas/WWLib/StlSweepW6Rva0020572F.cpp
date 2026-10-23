// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// The native loop proves an eight-byte stride and calls the already verified
// placement-copy owner directly. Keep only that neutral footprint here;
// original element identity and the provider's inherited type view are unknown.
struct Rva0020572FElement { unsigned words[2]; };
void Rva0020596AConstruct(void *, const void *);

namespace _STL {
// TU-local forwarding glue; its discardable out-of-line copy has no retail entry.
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0020572FElement *destination,
                                    const Rva0020572FElement &value)
{
    Rva0020596AConstruct(destination, &value);
}
}

// Expose the local overload when the reference template is parsed.
#include <vector>

// Instantiate the recovered operation and its required template dependencies.
template Rva0020572FElement * _STL::__uninitialized_fill_n<Rva0020572FElement *, unsigned int, Rva0020572FElement>(Rva0020572FElement *, unsigned int, Rva0020572FElement const &, _STL::__false_type const &);
