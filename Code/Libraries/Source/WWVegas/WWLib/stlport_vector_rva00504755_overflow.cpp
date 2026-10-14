// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00504755Record>::_M_insert_overflow, retail 0x005049E8, 186 bytes.
// Masked-identical to landed BfmeE16 overflow at 0x005B3970 (16-byte stride,
// inline free). Same no-EH recipe as stlport_vector_e16_noexc.cpp.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Same view as StlHelperRva00504755.cpp: retail copies the first float, then
// the other three words as an aggregate.
struct Rva00504755Record {
    float x;
    struct Tail { float y, z, w; } tail;
    Rva00504755Record() {}
    Rva00504755Record(const Rva00504755Record& v): x(v.x), tail(v.tail) {}
};
// Retail's placement copy 0x0041360E, which StlHelperRva00504755.cpp calls.
template void _STL::_Construct<Rva00504755Record, Rva00504755Record>(Rva00504755Record *, const Rva00504755Record &);
// Only the rowed member: a whole-class instantiation also emitted this TU's
// insert(pos, x), which differs from retail's.
template void _STL::vector<Rva00504755Record, _STL::allocator<Rva00504755Record> >::_M_insert_overflow(Rva00504755Record *, const Rva00504755Record &, const _STL::__false_type &, unsigned int, bool);
