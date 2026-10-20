// STLport 4.5.3 SelectionTranslator ID-membership lookup.
// Native translateGameMessage at 0x0043003C reads four-byte Object IDs,
// stores one-byte true values and calls this whole body at 0x002888D4.
// int/bool is the reconstruction's type choice; the target proves the
// key width, value width, identity hash and node traversal independently.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

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

typedef _STL::pair<const int,bool> SelectionIDValue;
typedef _STL::hashtable<SelectionIDValue,int,_STL::hash<int>,
    _STL::_Select1st<SelectionIDValue>,_STL::equal_to<int>,
    _STL::allocator<SelectionIDValue> > SelectionIDTable;
template _STL::_Hashtable_node<SelectionIDValue> *
    SelectionIDTable::_M_find<int>(const int &) const;
