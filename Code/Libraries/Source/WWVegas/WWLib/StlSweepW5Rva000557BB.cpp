// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

// vector<void*> begin/size/operator[] otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void *>::operator[](size_t __n) { return *(begin() + __n); }
}

struct Rva000557BBElement {Rva000557BBElement();Rva000557BBElement(const Rva000557BBElement&);Rva000557BBElement&operator=(const Rva000557BBElement&);~Rva000557BBElement(){}char bytes[8]; bool operator==(const Rva000557BBElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::hashtable<_STL::pair<int const, Rva000557BBElement>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva000557BBElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva000557BBElement> > >::erase(_STL::_Ht_iterator<_STL::pair<int const, Rva000557BBElement>, _STL::_Const_traits<_STL::pair<int const, Rva000557BBElement> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva000557BBElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva000557BBElement> > > const &);
