// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_set>
#include <memory>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _STL::_OKToMemCpy<void *,void *> _IsOKToMemCpy<void *,void *>(void * *,void * *); }
namespace _STL { template <> template <> void * * vector<void *,_STL::allocator<void *> >::_M_allocate_and_copy<void * *>(unsigned int,void * *,void * *); }
namespace _STL { template <> void swap<_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > >(_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > &,_STL::_STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(_STL::allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::_Vector_base(unsigned int,_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(_STL::allocator<void *> const &); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::vector(unsigned int,void * const &,_STL::allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *,_STL::allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> vector<void *,_STL::allocator<void *> >::~vector(); }
namespace _STL { template <> void * const & vector<void *,_STL::allocator<void *> >::operator[](unsigned int) const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_fill_insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_insert_overflow(void * *,void * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::_M_set(void * *,void * *,void * *); }
namespace _STL { template <> _STL::__true_type _OKToMemCpy<void *,void *>::_Ret(); }
namespace _STL { template <> void * * _STLP_alloc_proxy<void * *,void *,_STL::allocator<void *> >::allocate(unsigned int); }
namespace _STL { template <> void * * allocator<void *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> unsigned int vector<void *,_STL::allocator<void *> >::capacity() const; }
namespace _STL { template <> _STL::allocator<void *> vector<void *,_STL::allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::insert(void * *,unsigned int,void * const &); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<void *,_STL::allocator<void *> >::swap(_STL::vector<void *,_STL::allocator<void *> > &); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

struct Rva001F4325Element { unsigned words[1];operator unsigned() const {return words[0];}bool operator<(const Rva001F4325Element& b)const{return words[0]<b.words[0];}bool operator==(const Rva001F4325Element& b)const{return words[0]==b.words[0];} };
template class _STL::hash_set<Rva001F4325Element,_STL::hash<unsigned> >;
