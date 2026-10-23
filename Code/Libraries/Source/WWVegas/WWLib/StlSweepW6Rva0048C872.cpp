// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// The native loop proves an eight-byte stride and calls the already verified
// placement-copy owner directly. Keep only that neutral footprint here;
// original element identity and the provider's inherited type view are unknown.
struct Rva0048C872Element { unsigned words[2]; };
struct TreeKey00242F5E;
void Rva0048C81FConstruct(TreeKey00242F5E *, const TreeKey00242F5E &);

namespace _STL {
// TU-local forwarding glue; its discardable out-of-line copy has no retail entry.
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0048C872Element *destination,
                                    const Rva0048C872Element &value)
{
    Rva0048C81FConstruct(reinterpret_cast<TreeKey00242F5E *>(destination),
        *reinterpret_cast<const TreeKey00242F5E *>(&value));
}
}

// Expose the local overload when the reference template is parsed.
#include <vector>

// Instantiate the recovered operation and its required template dependencies.
template Rva0048C872Element * _STL::__uninitialized_fill_n<Rva0048C872Element *, unsigned int, Rva0048C872Element>(Rva0048C872Element *, unsigned int, Rva0048C872Element const &, _STL::__false_type const &);
