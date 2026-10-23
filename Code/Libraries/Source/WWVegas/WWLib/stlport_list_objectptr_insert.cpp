// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<Object*>::insert calls the out-of-line create_node (landed alongside
// at 0x5EB9AC), mirroring stlport_list_int_insert.cpp.
#include <list>

class Object;
// Native Object-pointer nodes use the dedicated freelist provider.
namespace _STL {
template <> _List_node<Object *> *list<Object *, allocator<Object *> >::_M_create_node(Object *const &);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Object;
template class _STL::list<Object *, _STL::allocator<Object *> >;
