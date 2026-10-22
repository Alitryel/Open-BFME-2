// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
//
// Dedicated TU for hashtable<int,int>::resize. The shared hash_map_int
// unit is built with /EHsc and emits an EH prologue retail does not have.

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$hash_map@HHU?$hash@H@_STL@@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hash_map<int,int,hash<int>,equal_to<int>,allocator<pair<int const ,int> > >::hash_map(); }
// Suppress this TU's non-retail copy of ??$__advance@PBIH@_STL@@YAXAAPBIHABUrandom_access_iterator_tag@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,random_access_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??0?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::hashtable(size_t, const hash<int> &, const equal_to<int> &, const allocator<pair<const int, int> > &); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }

template class _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > >;
