// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist
// stlport

#include <list>
// bfme link decl-only begin
namespace _STL { template <> list<int, allocator<int> >::list(list<int, allocator<int> > const &); }
namespace _STL { template <> list<int, allocator<int> >::list(allocator<int> const &); }
namespace _STL { template <> list<int, allocator<int> > & list<int, allocator<int> >::operator=(list<int, allocator<int> > const &); }
namespace _STL { template <> _List_iterator<int, _Nonconst_traits<int> > & _List_iterator<int, _Nonconst_traits<int> >::operator++(); }
namespace _STL { template <> _List_iterator<int, _Const_traits<int> > & _List_iterator<int, _Const_traits<int> >::operator--(); }
namespace _STL { template <> _List_node<int> * list<int, allocator<int> >::_M_create_node(int const &); }
namespace _STL { template <> _List_iterator<int, _Nonconst_traits<int> > list<int, allocator<int> >::erase(_List_iterator<int, _Nonconst_traits<int> >, _List_iterator<int, _Nonconst_traits<int> >); }
namespace _STL { template <> void list<int, allocator<int> >::push_back(int const &); }
namespace _STL { template <> void list<int, allocator<int> >::push_back(); }
namespace _STL { template <> void list<int, allocator<int> >::push_front(int const &); }
namespace _STL { template <> void list<int, allocator<int> >::splice(_List_iterator<int, _Nonconst_traits<int> >, list<int, allocator<int> > &, _List_iterator<int, _Nonconst_traits<int> >); }
namespace _STL { template <> void list<int, allocator<int> >::splice(_List_iterator<int, _Nonconst_traits<int> >, list<int, allocator<int> > &); }
// bfme link decl-only end
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

template class _STL::list<int, _STL::allocator<int> >;
