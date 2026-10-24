// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>



// Instantiate the recovered operation and its required template dependencies.
template void _STL::__pop_heap<int *, int, _STL::greater<int>, int>(int *, int *, int *, int, _STL::greater<int>, int *);
