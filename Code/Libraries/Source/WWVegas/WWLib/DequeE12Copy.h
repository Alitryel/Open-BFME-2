#pragma once
// Include after the existing BfmeE12 POD view and <deque>.
// Native584E0E copies twelve-byte elements through construction2CA82C;
// increment421B1E proves stride12 and a120-byte deque node payload.
// This POD construction has no throwing subobjects, so no rollback is needed.
// The original element identity remains unknown. Evidence:
// reverse/attempt_support/deque-e12-link-20261024/readme.md
void rva002CA82C(BfmeE12 *, const BfmeE12 &) throw();

namespace _STL {
typedef _Deque_iterator<BfmeE12, _Nonconst_traits<BfmeE12> > E12CopyCursor;
typedef _Deque_iterator<BfmeE12, _Const_traits<BfmeE12> > E12ConstCopyCursor;

template<> inline E12CopyCursor
__uninitialized_copy<E12CopyCursor, E12CopyCursor>(
    E12CopyCursor first, E12CopyCursor last, E12CopyCursor out,
    const __false_type &)
{
    E12CopyCursor cur = out;
    for (; first != last; ++first, ++cur)
        rva002CA82C(&*cur, *first);
    return cur;
}

template<> inline E12CopyCursor
__uninitialized_copy<E12ConstCopyCursor, E12CopyCursor>(
    E12ConstCopyCursor first, E12ConstCopyCursor last, E12CopyCursor out,
    const __false_type &)
{
    E12CopyCursor cur = out;
    for (; first != last; ++first, ++cur)
        rva002CA82C(&*cur, *first);
    return cur;
}
}
