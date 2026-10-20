// STLport 4.5.3 SelectionTranslator ID-membership map destruction.
// Native translateGameMessage 0x0043003C destroys its local table through
// 0x0042FD1C; the table stores four-byte keys and one-byte Boolean values.
// int/bool remains a structural type inference from that caller, as in
// SelectionIDMap.cpp. The destructor and its shared clear worker are the
// unmodified official STLport templates, including the /GX EH frame.
// cl: /O1 /G7 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN
#include <hash_map>
typedef _STL::pair<const int,bool> SelectionIDValue;
typedef _STL::hashtable<SelectionIDValue,int,_STL::hash<int>,_STL::_Select1st<SelectionIDValue>,_STL::equal_to<int>,_STL::allocator<SelectionIDValue> > SelectionIDTable;
template SelectionIDTable::~hashtable();
