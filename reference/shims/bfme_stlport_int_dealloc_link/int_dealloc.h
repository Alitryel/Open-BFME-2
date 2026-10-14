// TU-scoped STLport 4.5.3 allocator<int> deallocate view, same body as
// reference/shims/bfmealloc/stl/_alloc.h (free when non-null). The int
// instantiations have no retail address of their own (the /O1 shape folds
// with allocator<char> at 0x0046264A, the /O2 one with alloc_proxy<char> at
// 0x006892B0); consumers inline them entirely and only left orphan COMDATs
// the link census rejects under the first-copy rule.
#ifndef BFME_INT_DEALLOC_LINK_H
#define BFME_INT_DEALLOC_LINK_H
#include <vector>
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int *__p, size_t) const
{
    if (__p != 0) ::free((void *)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *__p, size_t __n)
{
    static_cast<allocator<int> &>(*this).deallocate(__p, __n);
}
}
#endif
