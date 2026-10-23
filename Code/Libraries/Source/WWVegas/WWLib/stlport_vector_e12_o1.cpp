// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmeE12 { float x, y, z; };
namespace _STL { template<> vector<BfmeE12> &vector<BfmeE12>::operator=(const vector<BfmeE12> &); }

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?swap@SidesInfoStringVector@@QAEXAAV1@@Z=?swap@?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEXAAV12@@Z")
// Explicitly instantiate the retail helpers; no synthetic callers are needed.
namespace _STL {
template BfmeE12 *__copy<const BfmeE12 *, BfmeE12 *, int>(const BfmeE12 *, const BfmeE12 *, BfmeE12 *, const random_access_iterator_tag &, int *);
template BfmeE12 *__copy_backward<BfmeE12 *, BfmeE12 *, int>(BfmeE12 *, BfmeE12 *, BfmeE12 *, const random_access_iterator_tag &, int *);
template BfmeE12 *__uninitialized_copy<const BfmeE12 *, BfmeE12 *>(const BfmeE12 *, const BfmeE12 *, BfmeE12 *, const __false_type &);
template BfmeE12 *__uninitialized_fill_n<BfmeE12 *, unsigned int, BfmeE12>(BfmeE12 *, unsigned int, const BfmeE12 &, const __false_type &);
template void fill<BfmeE12 *, BfmeE12>(BfmeE12 *, BfmeE12 *, const BfmeE12 &);
template unsigned int vector<BfmeE12>::size() const;
template void vector<BfmeE12>::swap(vector<BfmeE12> &);
template void vector<BfmeE12>::pop_back();
template _Vector_base<BfmeE12, allocator<BfmeE12> >::_Vector_base(const allocator<BfmeE12> &);
template BfmeE12 *__copy_backward_ptrs<BfmeE12 *, BfmeE12 *>(BfmeE12 *, BfmeE12 *, BfmeE12 *, const __false_type &);
}
