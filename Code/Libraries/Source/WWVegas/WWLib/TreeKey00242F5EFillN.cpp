// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// stlport
// Native37B523E27 fills mutable (int, AsciiString) pairs through Construct523DD4.
// Apt adder524845 and the vector's erase chain establish pair/mutability;
// signedness retains the producer's source convention. Its sole named native
// caller is vector overflow5244DC at524547. Keep the generic definition in its
// genuine pair family; unrelated TreeKey vector instantiations remain separate.
#include "ascii_string.h"
#include <utility>
namespace _STL {
template<class T, class U> void _Construct(T *, const U &);
template<class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &) {
 ForwardIter cur=first;
 for(;n>0;--n,++cur)
  _STL::_Construct(cur,x);
 return cur;
}
}
typedef _STL::pair<int, AsciiString> MutableAsciiPair;
template MutableAsciiPair *_STL::__uninitialized_fill_n(MutableAsciiPair *, unsigned int, const MutableAsciiPair &, const _STL::__false_type &);
