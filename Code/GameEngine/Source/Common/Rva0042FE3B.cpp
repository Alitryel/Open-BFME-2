// cl: /O1 /G7 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0x0042FE3B is a standalone cleanup JMP to the local selection-table
// destructor 0x0042FD1C. It preserves the table receiver in ECX; the previous
// free-function alias hid that contract. The original wrapper identity and
// enclosing lifetime remain unknown. The target's key/value widths support
// int/bool as a structural reconstruction, as in SelectionIDMap.cpp.
#include <hash_map>
typedef _STL::pair<const int,bool> SelectionIDValue;
typedef _STL::hashtable<SelectionIDValue,int,_STL::hash<int>,
    _STL::_Select1st<SelectionIDValue>,_STL::equal_to<int>,
    _STL::allocator<SelectionIDValue> > SelectionIDTable;
namespace _STL { template <> SelectionIDTable::~hashtable(); }
struct Rva0042FE3BSelectionIDCleanup { void cleanup(); };
void Rva0042FE3BSelectionIDCleanup::cleanup()
{
    reinterpret_cast<SelectionIDTable *>(this)->~SelectionIDTable();
}
