// cl: /O1 /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Asset worker 00624130 searches its AssetList pointer-key set through the
// native 004D7546 wrapper and unsigned lower-bound worker 00357180.
// STLport 4.5.3 under the sibling AssetList cleanup flags emits both complete
// native bodies. Existing integer-map owners are their ICF counterparts;
// comparison is by the same unsigned 32-bit key representation.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva001408C0Target;
typedef Rva001408C0Target *AssetKey;
typedef _STL::set<AssetKey,_STL::less<AssetKey>,_STL::allocator<AssetKey> > AssetSet;
typedef _STL::_Rb_tree<AssetKey,AssetKey,_STL::_Identity<AssetKey>,_STL::less<AssetKey>,_STL::allocator<AssetKey> > AssetTree;

template AssetTree::const_iterator AssetTree::find<AssetKey>(const AssetKey &) const;
