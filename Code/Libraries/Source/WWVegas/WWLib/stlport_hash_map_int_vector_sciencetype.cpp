// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// hash_map<int, vector<ScienceType>>: its pair copy (0x0041E7D5) calls the rowed vector<ScienceType> copy constructor (ProductionPrerequisiteCopyCtor.cpp) for the value, and its node constructor (0x0041EA07) zeroes the next link and places the pair at +4.
// The key is a 32-bit int-hashed type; int stands in, as in
// stlport_pod_hash_bodies.cpp, whose whole-class instantiation this follows.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
#include <vector>
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

enum ScienceType
{
	SCIENCE_NONE = 0
};

// The separate subscript unit owns the byte-verified 0x0041EB1A body.
// Whole-class instantiation here must use it rather than emit another copy.
namespace _STL {
template <> vector<ScienceType> &hash_map<int, vector<ScienceType> >::operator[](const int &);
}

template class _STL::hash_map<int, _STL::vector<ScienceType>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::vector<ScienceType> > > >;

// These rowed helpers were otherwise emitted only through operator[].
template _STL::pair<const int, _STL::vector<ScienceType> >::pair(const int &, const _STL::vector<ScienceType> &);
template _STL::pair<const int, _STL::vector<ScienceType> > &_STL::hashtable<_STL::pair<const int, _STL::vector<ScienceType> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<const int, _STL::vector<ScienceType> > >, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::vector<ScienceType> > > >::_M_insert(const _STL::pair<const int, _STL::vector<ScienceType> > &);

template bool _STL::operator!=(const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &, const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &);
