// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::_STLP_alloc_proxy(const _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_map>
#include <string>
#include <utility>
// Bind to the kept retail copy instead of emitting this unit's own.
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__less@I@_STL@@YA?AU?$less@I@0@PAI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> less<unsigned int> __less<unsigned int>(unsigned int *); }
// Suppress this TU's non-retail copy of ??0?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

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
