// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <string>
#include <utility>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::_STLP_alloc_proxy(const _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

struct Rva00056BFEElement { char bytes[1]; Rva00056BFEElement();Rva00056BFEElement(const Rva00056BFEElement&);~Rva00056BFEElement();Rva00056BFEElement& operator=(const Rva00056BFEElement&); bool operator<(const Rva00056BFEElement&)const; bool operator==(const Rva00056BFEElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::hashtable<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement>, _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, _STL::hash<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::_Select1st<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement> >, _STL::equal_to<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::allocator<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement> > >::resize(unsigned int);
