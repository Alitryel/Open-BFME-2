// STLport 4.5.3 SelectionTranslator ID-membership map operations.
// Native translateGameMessage at 0x0043003C reads four-byte Object IDs,
// stores one-byte true values through subscript at 0x0042FE40 and calls
// the membership lookup at 0x002888D4.
// int/bool is the reconstruction's type choice; the target proves the
// key width, value width, identity hash and node traversal independently.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}


// Keep the canonical out-of-line bucket-vector providers. These same
// accessors are visible in Armor.cpp; native lookup inlines both reads.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void *>::size() const
{
    return size_t(this->_M_finish - this->_M_start);
}
template <> __declspec(dllimport) __forceinline void *const &
vector<void *>::operator[](size_t n) const
{
    return *(this->_M_start + n);
}
}

// The native initializer reads the vector end field and calls the canonical
// reserve/fill-insert providers. Keep those bodies in their owning units.
namespace _STL {
template <> void vector<void *>::reserve(size_t);
template <> void vector<void *>::_M_fill_insert(void **, size_t, void *const &);
template <> __declspec(dllimport) __forceinline void **vector<void *>::end()
{
    return this->_M_finish;
}
template <> __declspec(dllimport) __forceinline void
vector<void *>::insert(void **position, size_t count, void *const &value)
{
    _M_fill_insert(position, count, value);
}
}

typedef _STL::pair<const int,bool> SelectionIDValue;
typedef _STL::hashtable<SelectionIDValue,int,_STL::hash<int>,
    _STL::_Select1st<SelectionIDValue>,_STL::equal_to<int>,
    _STL::allocator<SelectionIDValue> > SelectionIDTable;
template _STL::_Hashtable_node<SelectionIDValue> *
    SelectionIDTable::_M_find<int>(const int &) const;

// Native selection records membership through this subscript. The key and
// Boolean value widths follow the caller's ID load and one-byte store.
template bool &_STL::hash_map<int,bool>::operator[](const int &);

// Constructor prerequisite: the same bucket count and zero-fill algorithm.
template void SelectionIDTable::_M_initialize_buckets(unsigned int);
