// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@MV?$allocator@M@_STL@@@_STL@@QAEXABM@Z: STLport
// vector<float>::push_back, which retail folds into the 4-byte-element body
// at 0x004DFCB0 (rowed as the vector<const ModuleData *> instance in
// stlport_moduledatavector_push.cpp). INI::Rva00289228_ParseRealList calls it.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

template void _STL::vector<float>::push_back(const float &);
