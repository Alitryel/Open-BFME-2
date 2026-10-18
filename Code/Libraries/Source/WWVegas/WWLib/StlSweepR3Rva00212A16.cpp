// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end



struct Rva00212A16Record { Rva00212A16Record(); Rva00212A16Record(const Rva00212A16Record&); ~Rva00212A16Record(); Rva00212A16Record&operator=(const Rva00212A16Record&); char bytes[1]; bool operator==(const Rva00212A16Record&) const; bool operator<(const Rva00212A16Record&) const; };
namespace _STL {template<> void _Construct<Rva00212A16Record,Rva00212A16Record>(Rva00212A16Record*,const Rva00212A16Record&); template<>struct hash<Rva00212A16Record> { unsigned int operator()(const Rva00212A16Record&) const; };}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<Rva00212A16Record const, Rva00212A16Record> & _STL::hashtable<_STL::pair<Rva00212A16Record const, Rva00212A16Record>, Rva00212A16Record, _STL::hash<Rva00212A16Record>, _STL::_Select1st<_STL::pair<Rva00212A16Record const, Rva00212A16Record> >, _STL::equal_to<Rva00212A16Record>, _STL::allocator<_STL::pair<Rva00212A16Record const, Rva00212A16Record> > >::_M_insert(_STL::pair<Rva00212A16Record const, Rva00212A16Record> const &);
