// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Native boundaries 6C6A3..6C6E2 and6C6E2..6C721 are separate RET8 bodies,
// after Cast_Ray's terminal true branch at6C69F. WorldBuilder's saved extent
// incorrectly merges these into Cast_Ray. The reference showAsVisibleCliff
// (BF1 a7c38d3b BaseHeightMap.cpp) guides the bounds/index operation only:
// native adds four coordinate checks and reads bit-vectors at37EC/3800.
// Native data/callee evidence proves the layouts; original getter names are
// not asserted. The const bool subscript provider is rowed at0006BE55.
#include <vector>
struct HeightMapDimensions {
 char pad0[8];int width,height;
};
class BaseHeightMapRenderObjClass {
public:
 bool rva0006C6A3(int x,int y) const;
 bool rva0006C6E2(int x,int y) const;
private:
 char pad0[0x37C0];HeightMapDimensions *map;
 char pad37C4[0x28];std::vector<bool> cliffBits;
 std::vector<bool> impassableBits;
};
bool BaseHeightMapRenderObjClass::rva0006C6A3(int x,int y) const {
 int width=map->width;
 if(x<0 || y<0 || y>=map->height || x>=width)return false;
 return cliffBits[x+y*width];
}
