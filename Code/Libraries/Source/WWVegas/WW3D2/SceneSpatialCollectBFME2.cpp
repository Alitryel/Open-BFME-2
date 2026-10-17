// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// Target [142330,142407) maps a floating rectangle to spatial cells and
// calls the recursive tree query at142170. Its node stride is 28 bytes.
// Original function names are unknown; no donor name is asserted.
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
// bfmeHeadersForSize: the headers' out-of-line inline copies that retail keeps are
// the size-optimised bodies (decalsys.cpp pattern); the rows below keep the unit's flags.
#pragma optimize("s", on)
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#include "camera.h"
#include "plane.h"
#pragma optimize("", on)
struct Gen_00943CF0_Node { Gen_00943CF0_Node *m_next; void *m_value; };
struct SceneCollectCell { unsigned count; MultiListClass<RenderObjClass> objects; };
typedef char SceneCollectCellSize[(sizeof(SceneCollectCell)==28)?1:-1];
class Gen_009431F0 { public: int map_x(float); int map_y(float); };
struct SceneCollectPair { float X,Y; };
struct SceneCollectRect {
 SceneCollectPair min,max;
 __forceinline void Add_Point(const Vector2 &p)
 {
  if (p.X < min.X) min.X = p.X;
  else if (p.X > max.X) max.X = p.X;
  if (p.Y < min.Y) min.Y = p.Y;
  else if (p.Y > max.Y) max.Y = p.Y;
 }
};
class BfmeSceneVector {
public:
 void rva00142170(Gen_00943CF0_Node **out,SceneCollectCell *node,unsigned n,int xmin,int ymin,int xmax,int ymax,int ox,int oy,int extent);
 void rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin);
 void rva00142410(Gen_00943CF0_Node **out,CameraClass *camera,const float *margin);
 float bounds[6]; SceneCollectCell *vector; int vector_max; float scale; unsigned level_mask;
};
typedef char SceneCollectIndexMatches[(sizeof(BfmeSceneVector)==sizeof(BFME2SceneSpatialIndex))?1:-1];
typedef char SceneCollectCellMatches[(sizeof(SceneCollectCell)==sizeof(BFME2SceneSpatialNode))?1:-1];

void BfmeSceneVector::rva00142330(Gen_00943CF0_Node **out,const SceneCollectRect &rect,const float *margin)
{
 int x0=((Gen_009431F0*)this)->map_x(rect.min.X-(margin ? margin[0] : 0.0f));
 int x1=((Gen_009431F0*)this)->map_x(rect.max.X+(margin ? margin[0] : 0.0f));
 int y0=((Gen_009431F0*)this)->map_y(rect.min.Y-(margin ? margin[1] : 0.0f));
 int y1=((Gen_009431F0*)this)->map_y(rect.max.Y+(margin ? margin[1] : 0.0f));
 rva00142170(out,vector,(unsigned)vector_max>>2,x0,y0,x1,y1,0,0,level_mask);
}


// rva00142410, retail 0x00142410 (662 bytes, RET12; Ghidra's 655 truncates the
// epilogue): the camera-frustum collect. Frustum corners 0..3 (camera +0x190)
// seed an x/y rectangle; each of the four corner rays (i to i+4) is then cut
// by the z=0 plane (z=800 when the camera's Z-axis Z component, transform +0x40,
// is negative), the cut point (clamped to t=1) widens the rectangle, and the
// sibling rva00142330 maps it to cells. Shape from WWMath: PlaneClass default
// plane, Compute_Intersection and Vector3::Lerp; the unrolled corner updates are
// the rectangle's Add_Point. Original function names are unknown.
void BfmeSceneVector::rva00142410(Gen_00943CF0_Node **out, CameraClass *camera, const float *margin)
{
	const Vector3 *corners = camera->Get_Frustum_Corners();
	SceneCollectRect rect;
	rect.max.X = corners[0].X;
	rect.max.Y = corners[0].Y;
	rect.min = rect.max;
	if (corners[1].X < rect.min.X) rect.min.X = corners[1].X;
	else if (corners[1].X > rect.max.X) rect.max.X = corners[1].X;
	if (corners[1].Y < rect.min.Y) rect.min.Y = corners[1].Y;
	else if (corners[1].Y > rect.max.Y) rect.max.Y = corners[1].Y;
	if (corners[2].X < rect.min.X) rect.min.X = corners[2].X;
	else if (corners[2].X > rect.max.X) rect.max.X = corners[2].X;
	if (corners[2].Y < rect.min.Y) rect.min.Y = corners[2].Y;
	else if (corners[2].Y > rect.max.Y) rect.max.Y = corners[2].Y;
	if (corners[3].X < rect.min.X) rect.min.X = corners[3].X;
	else if (corners[3].X > rect.max.X) rect.max.X = corners[3].X;
	if (corners[3].Y < rect.min.Y) rect.min.Y = corners[3].Y;
	else if (corners[3].Y > rect.max.Y) rect.max.Y = corners[3].Y;
	PlaneClass plane;
	if (camera->Get_Transform()[2][2] < 0.0f) plane.D = 800.0f;
	for (int i = 0; i < 4; ++i) {
		float t;
		if (!plane.Compute_Intersection(corners[i], corners[i + 4], &t)) t = 1.0f;
		Vector3 point;
		Vector3::Lerp(corners[i], corners[i + 4], t, &point);
		rect.Add_Point(Vector2(point.X, point.Y));
	}
	rva00142330(out, rect, margin);
}
