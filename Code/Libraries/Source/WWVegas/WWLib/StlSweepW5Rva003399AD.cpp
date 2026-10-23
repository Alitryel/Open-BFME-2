// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is Rva002390CB: 0x003399AD copies 8-byte elements through the
// rowed _Construct<Rva002390CB> (0x0031B4A8, a tail call into Rva002390CB's copy
// constructor 0x002390CB), like its neighbour fill_n<Rva002390CB> at 0x003399D3;
// vector<Rva002390CB>'s copy and allocate_and_copy call this address too.
#include <algorithm>
#include <memory>

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
private:
	char m_bytes[8];
};

// Declared only: the rowed copy in stlport_construct_throw_spec.cpp serves the call.
namespace _STL { template <> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &); }

template Rva002390CB *_STL::__uninitialized_copy<const Rva002390CB *, Rva002390CB *>(const Rva002390CB *, const Rva002390CB *, Rva002390CB *, const _STL::__false_type &);
