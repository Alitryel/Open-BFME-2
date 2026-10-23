// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ??0AABoxRenderObjClass@@QAE@ABUW3dBoxStruct@@@Z @ 0x00175C40 (39B).
// Dedicated TU: boxrobj.cpp cannot take another row (bulk import left defs
// without rows or markers, failing find_declared_unmatched on any staging).
// Same headers as the landed Box/OBBox ctor TUs. Verbatim BFME1 body.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"
#include "boxrobj.h"

// matrix3d.h's Matrix3D::Get_Translation() under a unit-local name: called as the
// Matrix3D member, this unit emitted an external copy that differs from the kept
// retail one. Body unchanged (Matrix3D::Get_Translation view, 96f26b7c4d pattern).
class AABoxTranslationView : public Matrix3D
{
public:
	WWINLINE Vector3 Get_Translation(void) const { return Vector3(Row[0][3],Row[1][3],Row[2][3]); }
};

// Defined here (verbatim BFME1) so the ctor inlines it: retail's 143B body
// carries the cached-box refresh as SSE loads/adds/stores, not a call.
inline void AABoxRenderObjClass::update_cached_box(void)
{
	CachedBox.Center = ((const AABoxTranslationView &)Transform).Get_Translation() + ObjSpaceCenter;
	CachedBox.Extent = ObjSpaceExtent;
}

// ??0AABoxRenderObjClass@@QAE@ABUW3dBoxStruct@@@Z
AABoxRenderObjClass::AABoxRenderObjClass(const W3dBoxStruct & def) :
	BoxRenderObjClass(def)
{
	update_cached_box();
}
