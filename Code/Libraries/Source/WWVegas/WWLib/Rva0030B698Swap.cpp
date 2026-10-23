// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x0030B698 (14B, cdecl): swap(x, y) calling x.swap(y) through the
// rowed, ICF-shared vector::swap 0x00567ECD -- STLport's free
// swap(vector&, vector&) (twin skeleton of __distance 0x002619A0). The
// element is a stand-in: BfmeE12 is the spelling stlport_vector_e12_o1.cpp
// compiles that swap under, and the vector members are element-size
// agnostic here. vector::swap is only declared so the call stays out of line.
#include <vector>

struct BfmeE12 { float x, y, z; };

namespace _STL {
template <> void vector<BfmeE12>::swap(vector<BfmeE12> &);
}

template void _STL::swap(_STL::vector<BfmeE12> &, _STL::vector<BfmeE12> &);
