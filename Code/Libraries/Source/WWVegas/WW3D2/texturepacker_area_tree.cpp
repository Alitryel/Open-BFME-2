// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The destructor of texturepacker.cpp's area multimap<unsigned,AssetReference>
// tree, retail 0x00170D7F (56 B). Target evidence: TexturePacker::
// UpdateResultTexture (0x001711A6) calls it on its AreaMap, and its /EHs shape
// (the EH state reset before the header is freed) differs from the /EHsc copy
// texturepacker.cpp would emit. Its clear (0x00170BD6), node erase (0x00170B19)
// and out-of-line value destructor (0x00151DAB) compile to retail's bytes here.
#include <map>

class TextureClass {
public:
    void Release_Ref();
};
class AssetReference {
public:
    TextureClass *object;
    ~AssetReference() { if(object) object->Release_Ref(); }
};

// ??1?$_Rb_tree@IU?$pair@$$CBIVAssetReference@@@_STL@@U?$_Select1st@U?$pair@$$CBIVAssetReference@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIVAssetReference@@@_STL@@@2@@_STL@@QAE@XZ
template _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, AssetReference>, _STL::_Select1st<_STL::pair<const unsigned int, AssetReference> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, AssetReference> > >::~_Rb_tree();
