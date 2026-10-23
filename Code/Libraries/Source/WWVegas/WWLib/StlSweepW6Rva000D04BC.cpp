// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// The native loop proves an eight-byte stride and calls the already verified
// placement-copy owner directly. Keep only that neutral footprint here;
// original element identity and the provider's inherited type view are unknown.
struct Rva000D04BCElement { unsigned words[2]; };
struct TreeKey00242F5E;
void Rva000D0469Construct(TreeKey00242F5E *, const TreeKey00242F5E &);

namespace _STL {
// TU-local forwarding glue; its discardable out-of-line copy has no retail entry.
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva000D04BCElement *destination,
                                    const Rva000D04BCElement &value)
{
    Rva000D0469Construct(reinterpret_cast<TreeKey00242F5E *>(destination),
        *reinterpret_cast<const TreeKey00242F5E *>(&value));
}
}

// Expose the local overload when the reference template is parsed.
#include <vector>

// Instantiate the recovered operation and its required template dependencies.
template Rva000D04BCElement * _STL::__uninitialized_fill_n<Rva000D04BCElement *, unsigned int, Rva000D04BCElement>(Rva000D04BCElement *, unsigned int, Rva000D04BCElement const &, _STL::__false_type const &);
