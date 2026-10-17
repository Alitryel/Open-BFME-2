// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.841 date=2026-10-17
// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.7990908115358819 date=2026-10-13
// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// PointGroup geometry helper, target0x0017A890, full12000B including its12-entry table.
// Identity/ABI: caller PointGroupClass::Render and existing neutral pin; twelve dispatch
// entries and target calls align with ZH pointgr.cpp Update_Arrays geometry subsection.
// Donor revision9cbfb551fe20dae985f91f2319d8997287b6a705. BFME1 still forwards this helper
// to a dump, so ZH is the clean semantic lead. Target proof: view-cache loads transpose
// three rows into a48B Matrix3D, billboard flagbit1, immediate scalar writes/reloads,
// four-point main loops for the variable triangle paths; full RET16+table boundaries.
// The RenderState view offset22C follows target DEE804 minus named render_state DEE5D8.
// Round3: MatrixRotationZ import is now resolved by the normal ledger. Advancing
// input pointers, split ground/billboard paths and ordinary C++ loops recover native
// four-point unrolling. Fixed-size screen mode has three temporary vectors; varying
// size has six. Explicit transposed view assignments preserve target layout.
// Emitted12148B/frameCC vs native12000B/frameB8; all calls resolve, score0.799090812.
// Remaining ground matrix/register allocation and stack homes prevent exact recovery.
// Owner integration preserves43/43 existing rows. Removing its historical optimization
// anchor also preserves those bytes but emits a50B ctor iterator vs retail42B; reverted.
// Round4 (2026-10-17): case7 Matrix4 view via transposed Get_Transform(int,Matrix4&)
// overload (row3 dead-stored as retail), TU-local by-value Matrix3D*Vector3 operator,
// vertex_loc declared before loop_sel, four scaled offsets dx0/dx1/dy0/dy1 computed
// before stores with integer Z copies: now 12000B/frameB8 exact size/frame, score0.841.
// Disproven: ZH i-indexed case7 (vert+=4, point_loc[i]) 12036B score0.823.
// Remaining: case7 keeps two vertex IVs and point_loc in memory (retail: one derived IV
// lea esi,[eax+14h] from invariant base, point_loc in ebp); case0 lost its pre-loop
// xmm6 reload through global register allocation; cases5/6 register choice.
// Banked source is NOT verified recovery.
// cl: /O2 /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "matrix3d.h"
struct RenderStateStruct { unsigned char opaque[0x22C]; Matrix4 view; };
class DX8Wrapper { public:
 static __forceinline void Get_Transform(int,Matrix4& v) {
  if(render_state_changed&(1<<19)) v.Make_Identity();
  else {v[0][0]=render_state.view[0][0];v[0][1]=render_state.view[1][0];v[0][2]=render_state.view[2][0];v[0][3]=render_state.view[3][0];v[1][0]=render_state.view[0][1];v[1][1]=render_state.view[1][1];v[1][2]=render_state.view[2][1];v[1][3]=render_state.view[3][1];v[2][0]=render_state.view[0][2];v[2][1]=render_state.view[1][2];v[2][2]=render_state.view[2][2];v[2][3]=render_state.view[3][2];v[3][0]=render_state.view[0][3];v[3][1]=render_state.view[1][3];v[3][2]=render_state.view[2][3];v[3][3]=render_state.view[3][3];}
 }
 static __forceinline void Get_Transform(int,Matrix3D& v) {
  if(render_state_changed&(1<<19)) v.Make_Identity();
  else {v[0][0]=render_state.view[0][0];v[0][1]=render_state.view[1][0];v[0][2]=render_state.view[2][0];v[0][3]=render_state.view[3][0];v[1][0]=render_state.view[0][1];v[1][1]=render_state.view[1][1];v[1][2]=render_state.view[2][1];v[1][3]=render_state.view[3][1];v[2][0]=render_state.view[0][2];v[2][1]=render_state.view[1][2];v[2][2]=render_state.view[2][2];v[2][3]=render_state.view[3][2];}
 }
private: static RenderStateStruct render_state; static unsigned render_state_changed;
};
#include "ww3d.h"
#include <d3dx8.h>
static __forceinline Vector3 operator * (const Matrix3D &A,const Vector3 &a)
{
	return Vector3
	(
		(A[0][0]*a[0] + A[0][1]*a[1] + A[0][2]*a[2] + A[0][3]),
		(A[1][0]*a[0] + A[1][1]*a[1] + A[1][2]*a[2] + A[1][3]),
		(A[2][0]*a[0] + A[2][1]*a[1] + A[2][2]*a[2] + A[2][3])
	);
}
static Vector3 GroundMultiplierX(1,0,0),GroundMultiplierY(0,1,0);
extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva009148C0(Vector3*,float*,unsigned char*,int);
  enum FlagsType{TRANSFORM,BILLBOARD};
  int Get_Flag(FlagsType f){return (Flags>>f)&1;}

private:
  virtual void abstract_dtor();
  ShareBufferClass<Vector3> *PointLoc;
  ShareBufferClass<Vector4> *PointDiffuse;
  ShareBufferClass<unsigned int> *APT;
  ShareBufferClass<float> *PointSize;
  ShareBufferClass<unsigned char> *PointOrientation, *PointFrame;
  int PointCount;
  unsigned char FrameRowColumnCountLog2;
  void *dword_24;
  unsigned int dword_28;
  PointModeEnum PointMode;
  unsigned int Flags;
  float DefaultPointSize;
  Vector3 DefaultPointColor;
  float DefaultPointAlpha;
  unsigned char DefaultPointOrientation, DefaultPointFrame;
  float VPXMin, VPYMin, VPXMax, VPYMax;
  static Vector3 _TriVertexLocationOrientationTable[256][3];
  static Vector3 _QuadVertexLocationOrientationTable[256][4];
  static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
  static Vector2 *_TriVertexUVFrameTable[5];
  static Vector2 *_QuadVertexUVFrameTable[5];
};

void PointGroupClass::rva009148C0(Vector3*point_loc,float*point_size,unsigned char*point_orientation,int active_points) {
	int i, j;
	Vector3 *vertex_loc = &VertexLoc[0];

	/*
	** Generate the vertex locations from the point locations (note that both are in camera space).
	** Vertex locations depend on the point mode and the points' orientation and size
	*/

	// This defines the loop we run: the LSB indicates whether there is a size override array, the
	// next bit indicates whether there is an orientation override array, and the higher bits
	// indicate the point mode.
	enum LoopSelectionEnum {
		TRIS_NOSIZE_NOORIENT		= ((int)TRIS << 2) + 0,
		TRIS_SIZE_NOORIENT		= ((int)TRIS << 2) + 1,
		TRIS_NOSIZE_ORIENT		= ((int)TRIS << 2) + 2,
		TRIS_SIZE_ORIENT			= ((int)TRIS << 2) + 3,
		QUADS_NOSIZE_NOORIENT	= ((int)QUADS << 2) + 0,
		QUADS_SIZE_NOORIENT		= ((int)QUADS << 2) + 1,
		QUADS_NOSIZE_ORIENT		= ((int)QUADS << 2) + 2,
		QUADS_SIZE_ORIENT			= ((int)QUADS << 2) + 3,
		SCREEN_NOSIZE_NOORIENT	= ((int)SCREENSPACE << 2) + 0,
		SCREEN_SIZE_NOORIENT		= ((int)SCREENSPACE << 2) + 1,
		SCREEN_NOSIZE_ORIENT		= ((int)SCREENSPACE << 2) + 2,
		SCREEN_SIZE_ORIENT		= ((int)SCREENSPACE << 2) + 3,
	};
	LoopSelectionEnum loop_sel = (LoopSelectionEnum)(((int)PointMode << 2) +
		(point_orientation ? 2 : 0) + (point_size ? 1 : 0));

	


	/// @todo lorenzen sez: this switch statement may be done more compactly another way... look into it

	switch (loop_sel) {

		case TRIS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[3];
				scaled_offset[0] = _TriVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _TriVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _TriVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 3) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
					
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i=0;i < active_points;++i,++point_size,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0];
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0];
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0];
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0];
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0];
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0];
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0];
}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i=0;i < active_points;++i,++point_orientation,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize;
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize;
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize;
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize;
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize;
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize;
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize;
}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i=0;i < active_points;++i,++point_size,++point_orientation,++point_loc,vertex_loc+=3) {
					vertex_loc[ 0].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0];
vertex_loc[ 0].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0];
vertex_loc[ 0].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0];
					vertex_loc[ 1].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0];
vertex_loc[ 1].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0];
vertex_loc[ 1].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0];
					vertex_loc[ 2].X = point_loc[0].X + _TriVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0];
vertex_loc[ 2].Y = point_loc[0].Y + _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0];
vertex_loc[ 2].Z = point_loc[0].Z + _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0];
}
			}
			break;

		case QUADS_NOSIZE_NOORIENT:
			{
				// Setup constant vertex offsets (since size and orientation are invariants)
				Vector3 scaled_offset[4];
				scaled_offset[0] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				scaled_offset[3] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * DefaultPointSize;

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + scaled_offset[0].X;
vertex_loc[ 0].Y = point_loc[0].Y + scaled_offset[0].Y;
vertex_loc[ 0].Z = point_loc[0].Z + scaled_offset[0].Z;
					vertex_loc[ 1].X = point_loc[0].X + scaled_offset[1].X;
vertex_loc[ 1].Y = point_loc[0].Y + scaled_offset[1].Y;
vertex_loc[ 1].Z = point_loc[0].Z + scaled_offset[1].Z;
					vertex_loc[ 2].X = point_loc[0].X + scaled_offset[2].X;
vertex_loc[ 2].Y = point_loc[0].Y + scaled_offset[2].Y;
vertex_loc[ 2].Z = point_loc[0].Z + scaled_offset[2].Z;
					vertex_loc[ 3].X = point_loc[0].X + scaled_offset[3].X;
vertex_loc[ 3].Y = point_loc[0].Y + scaled_offset[3].Y;
vertex_loc[ 3].Z = point_loc[0].Z + scaled_offset[3].Z;
					
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_size++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0];
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0];
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0];
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0];
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0];
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0];
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0];
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0];
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0];
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X * point_size[0];
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y * point_size[0];
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z * point_size[0];
					
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				// Scale vertex offsets and add them to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_orientation++, point_loc++, vertex_loc += 4) {
					vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize;
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize;
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize;
					vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize;
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize;
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize;
					vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize;
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize;
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize;
					vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * DefaultPointSize;
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * DefaultPointSize;
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * DefaultPointSize;
					
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
{
Matrix4 view; Vector4 result;
if (!Get_Flag(BILLBOARD)) {
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
for (i = 0; i < active_points; i++, point_size++, point_orientation++, point_loc++, vertex_loc += 4) {
						// If we're not billboarding, then the coordinate we have is in screen space.
						Matrix4 rotMat;
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[0] / 255.0f * 2 * D3DX_PI));
						
						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;

						float dx0 = (orientedVecX.X + orientedVecY.X) * point_size[0];
						float dx1 = (orientedVecX.X - orientedVecY.X) * point_size[0];
						float dy0 = (orientedVecX.Y + orientedVecY.Y) * point_size[0];
						float dy1 = (orientedVecX.Y - orientedVecY.Y) * point_size[0];

						vertex_loc[ 0].X = point_loc[0].X + dx0;
						vertex_loc[ 0].Y = point_loc[0].Y + dy0;
						vertex_loc[ 0].Z = point_loc[0].Z;

						vertex_loc[ 1].X = point_loc[0].X + dx1;
						vertex_loc[ 1].Y = point_loc[0].Y + dy1;
						vertex_loc[ 1].Z = point_loc[0].Z;

						vertex_loc[ 2].X = point_loc[0].X - dx0;
						vertex_loc[ 2].Y = point_loc[0].Y - dy0;
						vertex_loc[ 2].Z = point_loc[0].Z;

						vertex_loc[ 3].X = point_loc[0].X - dx1;
						vertex_loc[ 3].Y = point_loc[0].Y - dy1;
						vertex_loc[ 3].Z = point_loc[0].Z;

						// now apply the view transform so that this data is in the format expected
						// upon the functions return.
						result = view*vertex_loc[0];
						vertex_loc[ 0].X = result.X;
						vertex_loc[ 0].Y = result.Y;
						vertex_loc[ 0].Z = result.Z;

						result = view*vertex_loc[1];
						vertex_loc[ 1].X = result.X;
						vertex_loc[ 1].Y = result.Y;
						vertex_loc[ 1].Z = result.Z;

						result = view*vertex_loc[2];
						vertex_loc[ 2].X = result.X;
						vertex_loc[ 2].Y = result.Y;
						vertex_loc[ 2].Z = result.Z;

						result = view*vertex_loc[3];
						vertex_loc[ 3].X = result.X;
						vertex_loc[ 3].Y = result.Y;
						vertex_loc[ 3].Z = result.Z;
					}
}else{
for (i = 0; i < active_points; i++, point_size++, point_orientation++, point_loc++, vertex_loc += 4) {

						vertex_loc[ 0].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0];
vertex_loc[ 0].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0];
vertex_loc[ 0].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0];
						vertex_loc[ 1].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0];
vertex_loc[ 1].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0];
vertex_loc[ 1].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0];
						vertex_loc[ 2].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0];
vertex_loc[ 2].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0];
vertex_loc[ 2].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0];
						vertex_loc[ 3].X = point_loc[0].X + _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * point_size[0];
vertex_loc[ 3].Y = point_loc[0].Y + _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * point_size[0];
vertex_loc[ 3].Z = point_loc[0].Z + _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * point_size[0];
					}
}
}
break;

		// Orientations are ignored for screensize pointgroups
		case SCREEN_NOSIZE_NOORIENT:
		case SCREEN_NOSIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
   
   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;
   
				int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;
Vector3 scaled_locs[3];
scaled_locs[0].X = _ScreenspaceVertexLocationSizeTable[size_idx][0].X * x_scale;
scaled_locs[0].Y = _ScreenspaceVertexLocationSizeTable[size_idx][0].Y * y_scale;
scaled_locs[0].Z = _ScreenspaceVertexLocationSizeTable[size_idx][0].Z;
scaled_locs[1].X = _ScreenspaceVertexLocationSizeTable[size_idx][1].X * x_scale;
scaled_locs[1].Y = _ScreenspaceVertexLocationSizeTable[size_idx][1].Y * y_scale;
scaled_locs[1].Z = _ScreenspaceVertexLocationSizeTable[size_idx][1].Z;
scaled_locs[2].X = _ScreenspaceVertexLocationSizeTable[size_idx][2].X * x_scale;
scaled_locs[2].Y = _ScreenspaceVertexLocationSizeTable[size_idx][2].Y * y_scale;
scaled_locs[2].Z = _ScreenspaceVertexLocationSizeTable[size_idx][2].Z;
// Add vertex offsets to point locations to get vertex locations
				
				for (i = 0; i < active_points; i++) {
					vertex_loc[0].X = point_loc[0].X + scaled_locs[0].X;
vertex_loc[0].Y = point_loc[0].Y + scaled_locs[0].Y;
vertex_loc[0].Z = point_loc[0].Z + scaled_locs[0].Z;
					vertex_loc[1].X = point_loc[0].X + scaled_locs[1].X;
vertex_loc[1].Y = point_loc[0].Y + scaled_locs[1].Y;
vertex_loc[1].Z = point_loc[0].Z + scaled_locs[1].Z;
					vertex_loc[2].X = point_loc[0].X + scaled_locs[2].X;
vertex_loc[2].Y = point_loc[0].Y + scaled_locs[2].Y;
vertex_loc[2].Z = point_loc[0].Z + scaled_locs[2].Z;
					vertex_loc += 3; ++point_loc;
				}
			}
			break;
			
		case SCREEN_SIZE_NOORIENT:
		case SCREEN_SIZE_ORIENT:
			{
				// Offsets need to be scaled to the current screen resolution

   			// First find x and y scale factors (sizes in pixels need to be
   			// normalized to 2D cam viewplane of -1,-1 to 1,1)
   			int xres, yres, bitdepth;
   			bool windowed;
   			WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
   
   			float x_scale = (VPXMax - VPXMin) / xres;
   			float y_scale = (VPYMax - VPYMin) / yres;
   
				Vector3 scaled_locs[2][3];
				scaled_locs[0][0].X = _ScreenspaceVertexLocationSizeTable[0][0].X * x_scale;
scaled_locs[0][0].Y = _ScreenspaceVertexLocationSizeTable[0][0].Y * y_scale;
scaled_locs[0][0].Z = _ScreenspaceVertexLocationSizeTable[0][0].Z;
scaled_locs[0][1].X = _ScreenspaceVertexLocationSizeTable[0][1].X * x_scale;
scaled_locs[0][1].Y = _ScreenspaceVertexLocationSizeTable[0][1].Y * y_scale;
scaled_locs[0][1].Z = _ScreenspaceVertexLocationSizeTable[0][1].Z;
scaled_locs[0][2].X = _ScreenspaceVertexLocationSizeTable[0][2].X * x_scale;
scaled_locs[0][2].Y = _ScreenspaceVertexLocationSizeTable[0][2].Y * y_scale;
scaled_locs[0][2].Z = _ScreenspaceVertexLocationSizeTable[0][2].Z;
scaled_locs[1][0].X = _ScreenspaceVertexLocationSizeTable[1][0].X * x_scale;
scaled_locs[1][0].Y = _ScreenspaceVertexLocationSizeTable[1][0].Y * y_scale;
scaled_locs[1][0].Z = _ScreenspaceVertexLocationSizeTable[1][0].Z;
scaled_locs[1][1].X = _ScreenspaceVertexLocationSizeTable[1][1].X * x_scale;
scaled_locs[1][1].Y = _ScreenspaceVertexLocationSizeTable[1][1].Y * y_scale;
scaled_locs[1][1].Z = _ScreenspaceVertexLocationSizeTable[1][1].Z;
scaled_locs[1][2].X = _ScreenspaceVertexLocationSizeTable[1][2].X * x_scale;
scaled_locs[1][2].Y = _ScreenspaceVertexLocationSizeTable[1][2].Y * y_scale;
scaled_locs[1][2].Z = _ScreenspaceVertexLocationSizeTable[1][2].Z;

				// Add vertex offsets to point locations to get vertex locations
				for (i = 0; i < active_points; i++, point_size++) {
					int size_idx = (point_size[0] <= 1.0f) ? 0 : 1;
					vertex_loc[0].X = point_loc[0].X + scaled_locs[size_idx][0].X;
vertex_loc[0].Y = point_loc[0].Y + scaled_locs[size_idx][0].Y;
vertex_loc[0].Z = point_loc[0].Z + scaled_locs[size_idx][0].Z;
					vertex_loc[1].X = point_loc[0].X + scaled_locs[size_idx][1].X;
vertex_loc[1].Y = point_loc[0].Y + scaled_locs[size_idx][1].Y;
vertex_loc[1].Z = point_loc[0].Z + scaled_locs[size_idx][1].Z;
					vertex_loc[2].X = point_loc[0].X + scaled_locs[size_idx][2].X;
vertex_loc[2].Y = point_loc[0].Y + scaled_locs[size_idx][2].Y;
vertex_loc[2].Z = point_loc[0].Z + scaled_locs[size_idx][2].Z;
					vertex_loc += 3; ++point_loc;
				}
			}
			break;

		default:
			WWASSERT(0);
			break;

	}

}
