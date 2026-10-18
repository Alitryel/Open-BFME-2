// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// The node path of hash_map<int, Rva0029E067>: its pair copy (0x0029E13C)
// copies one key word, then calls the rowed Rva0029E067 copy constructor
// (0x0029E067, Rva0029E067Ctor.cpp), and its node constructor (0x002A14D5)
// allocates 0x3C bytes, zeroes the next link and places the pair at +4: a
// 0x34-byte value, Rva0029E067's layout there. Only the value's copy
// constructor is used. Only the table's find_or_insert and _M_insert are
// instantiated: the whole class would need operator== on the value
// (_M_equal) and hash_map's operator[] a default-constructed one.

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
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
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

struct Rva0029E067
{
	Rva0029E067(const Rva0029E067 &src);
	char m_bytes[0x34];
};

typedef _STL::pair<const int, Rva0029E067> IntRva0029E067Value;

typedef _STL::hashtable<IntRva0029E067Value, int, _STL::hash<int>, _STL::_Select1st<IntRva0029E067Value>, _STL::equal_to<int>, _STL::allocator<IntRva0029E067Value> > IntRva0029E067Table;

template IntRva0029E067Table::reference IntRva0029E067Table::find_or_insert(const IntRva0029E067Value &);
template IntRva0029E067Table::reference IntRva0029E067Table::_M_insert(const IntRva0029E067Value &);
