// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <cstddef>
// _M_find (retail's 47-byte body, folded at 0x002888D4) inlines the bucket
// count and the bucket read; declaration-only const begin()/size() made this
// TU's copy call them. Bind to the kept retail copies instead of emitting them.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Suppress this TU's non-retail non-const vector<void*> begin/end copies:
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const { return *(begin() + __n); }
}

struct Rva00148B27Element {Rva00148B27Element();Rva00148B27Element(const Rva00148B27Element&);Rva00148B27Element&operator=(const Rva00148B27Element&);~Rva00148B27Element(){}char bytes[8]; bool operator==(const Rva00148B27Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Ht_iterator<_STL::pair<int const, Rva00148B27Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00148B27Element> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00148B27Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00148B27Element> > > _STL::hashtable<_STL::pair<int const, Rva00148B27Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00148B27Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00148B27Element> > >::find<int>(int const &);
