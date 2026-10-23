// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <vector>

// The native pair cleanup frees the mapped vector's storage at pair+4.
// Its three-word footprint also agrees with the existing container owner.
struct Rva00079995Element { _STL::vector<unsigned int> m_values; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva00079995Element>, _STL::_Select1st<_STL::pair<int const, Rva00079995Element> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00079995Element> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00079995Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00079995Element> > >);
