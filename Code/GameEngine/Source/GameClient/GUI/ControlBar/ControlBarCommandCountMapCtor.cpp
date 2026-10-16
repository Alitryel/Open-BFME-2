// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// STLport4.5.3 count-map storage ABI already established by the canonical
// ThingTemplateCountMap.cpp key/subscript owner. Native populateCommand uses
// a local pointer-key/int-count map. These are genuine emitted helper twins
// of its constructor and cleanup providers; they recover no unique bytes.
namespace _STL { void __cdecl free(void *); }
#include <map>
class ThingTemplate;
struct TemplateCountKey {
 const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {}
 __forceinline TemplateCountKey(const ThingTemplate *p):pointer(p){}
 __forceinline bool operator<(const TemplateCountKey &other) const{return pointer<other.pointer;}
};
typedef _STL::pair<const TemplateCountKey,int> CountValue;
typedef _STL::map<TemplateCountKey,int> CountMap;
typedef _STL::_Rb_tree<TemplateCountKey,CountValue,_STL::_Select1st<CountValue>,_STL::less<TemplateCountKey>,_STL::allocator<CountValue> > CountTree;



// bfme link decl-only begin
// Retail's tree dtor (0x0053BCED, with the extra unwind-state store) is
// ControlBarCommandCountMap.cpp's row; this unit never calls it.
namespace _STL { template <> CountTree::~_Rb_tree(); }
// bfme link decl-only end

template CountMap::map();



