// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// Retail's /O1 _Bit_reference::operator= (0x00066099): in-class inline members take the optimize state of their definition.
#pragma optimize("s", on)
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> __copy<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, int>(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, random_access_iterator_tag const &, int *); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> __copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>, int>(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>, random_access_iterator_tag const &, int *); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> __copy_aux<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, __false_type const &); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> __copy_aux<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>, __false_type const &); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> __copy_backward<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, int>(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, random_access_iterator_tag const &, int *); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> void fill<_Bit_iter<_Bit_reference, _Bit_reference *>, bool>(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, bool const &); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> fill_n<_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool>(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool const &); }
namespace _STL { template <> vector<bool, allocator<bool> >::vector(vector<bool, allocator<bool> > const &); }
namespace _STL { template <> vector<bool, allocator<bool> >::vector(allocator<bool> const &); }
namespace _STL { template <> vector<bool, allocator<bool> >::vector(unsigned int, bool, allocator<bool> const &); }
namespace _STL { template <> vector<bool, allocator<bool> > & vector<bool, allocator<bool> >::operator=(vector<bool, allocator<bool> > const &); }
namespace _STL { template <> _Bit_reference vector<bool, allocator<bool> >::operator[](unsigned int); }
namespace _STL { template <> bool vector<bool, allocator<bool> >::operator[](unsigned int) const; }
namespace _STL { template <> _Bit_reference _Bit_iter<_Bit_reference, _Bit_reference *>::operator*() const; }
namespace _STL { template <> bool _Bit_iter<bool, bool const *>::operator*() const; }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> _Bit_iter<_Bit_reference, _Bit_reference *>::operator++(int); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> & _Bit_iter<_Bit_reference, _Bit_reference *>::operator++(); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> & _Bit_iter<_Bit_reference, _Bit_reference *>::operator--(); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> _Bit_iter<_Bit_reference, _Bit_reference *>::operator+(int) const; }
namespace _STL { template <> _Bit_iter<bool, bool const *> _Bit_iter<bool, bool const *>::operator+(int) const; }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> & _Bit_iter<_Bit_reference, _Bit_reference *>::operator+=(int); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_initialize(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *>, bool); }
namespace _STL { template <> bool vector<bool, allocator<bool> >::empty() const; }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> vector<bool, allocator<bool> >::erase(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> void vector<bool, allocator<bool> >::insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
namespace _STL { template <> void vector<bool, allocator<bool> >::push_back(bool); }
namespace _STL { template <> void vector<bool, allocator<bool> >::reserve(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::resize(unsigned int, bool); }
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *, unsigned int) const; }
// bfme link decl-only end
#pragma optimize("", on)

// RVA6D52A has a verified external provider; do not offer a wrong incidental copy.
namespace _STL { template<> void vector<bool>::clear(); }

template class _STL::vector<bool, _STL::allocator<bool> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Gen_dtor_007f6d20@@QAE@XZ=??0?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?m@Gen_00800280@@QAEPAXXZ=??0?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@QAE@XZ")
