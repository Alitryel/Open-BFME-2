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
struct BfmeE8 { int a, b; };
// Retail's growth path is the no-EH provider 0x00057C80; spell its
// algorithm out so this TU's copy is that provider instead of an EH copy.
namespace _STL {
template<> inline void vector<BfmeE8>::_M_insert_overflow(
    pointer position, const BfmeE8 &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}
// The copy constructor is the no-EH body 0x004334D7: call it, emit no EH copy.
// _M_allocate_and_copy is spelled without EH like retail's 0x001D9AD9.
namespace _STL { template <> vector<BfmeE8>::vector(const vector<BfmeE8> &); }
namespace _STL {
template <> template <> inline BfmeE8 *vector<BfmeE8>::_M_allocate_and_copy<BfmeE8 *>(size_t n, BfmeE8 *first, BfmeE8 *last)
{
    pointer result = this->_M_end_of_storage.allocate(n);
    __uninitialized_copy(first, last, result, __false_type());
    return result;
}
}
// insert(pos, x) is AreaPolygon's /O1 body 0x0030B9F3; call it, emit no copy.
namespace _STL { template <> vector<BfmeE8>::iterator vector<BfmeE8>::insert(iterator, const BfmeE8 &); }
template class _STL::vector<BfmeE8, _STL::allocator<BfmeE8 > >;
