// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// These two rowed destructors still select mismatched range-worker copies.
// Keep them apart from the independently bound and linking destructor family.
#include <vector>
// ??1?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@QAE@XZ @0x3b904b (_Destroy at 0x3b8e13)
struct BfmeAssignRecord104 { public: ~BfmeAssignRecord104(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<BfmeAssignRecord104 *>(BfmeAssignRecord104 *, BfmeAssignRecord104 *); }
template _STL::vector<BfmeAssignRecord104>::~vector();

// ??1?$vector@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@QAE@XZ @0x005EB28A (_Destroy at 0x005EAA83)
struct GeometryShape { public: ~GeometryShape(); };
// The size-only view must not provide the range helper.
namespace _STL { template <> void _Destroy<GeometryShape *>(GeometryShape *, GeometryShape *); }
template _STL::vector<GeometryShape>::~vector();
