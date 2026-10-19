// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 four-byte vector constructors. The former unsigned-short
// owners at2339F3/511E1C called n*4 allocation and DWORD fill; that width is
// independently visible in retail and WB. Existing uint/HKL/ScienceType
// providers establish the four-byte family. uint is a storage view here;
// no otherwise unknown original application element type is asserted.
#include <vector>

template _STL::vector<unsigned int, _STL::allocator<unsigned int> >::vector(
	unsigned int, const unsigned int &, const _STL::allocator<unsigned int> &);

template _STL::vector<unsigned int, _STL::allocator<unsigned int> >::vector(unsigned int);
