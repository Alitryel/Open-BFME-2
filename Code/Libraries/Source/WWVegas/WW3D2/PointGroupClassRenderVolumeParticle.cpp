extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?RenderVolumeParticle@PointGroupClass@@QAEXAAVRenderInfoClass@@IPAX@Z
// partial score=0.9887 date=2026-10-10
// cl: /O2 /G7 /arch:SSE /Ireference/shims/bfmestages /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
// PointGroupClass volume layers, native0x0017F6E0..0x0017FADF (1023B).
// WB0x00A290C0 names this method in pointgr.cpp. The neighboring BFME1
// PointGroupClassRender donor10af19f44a supplies the class/setup/helper model;
// the volume-loop control flow and matrix order are independently retail-measured.
// Keep the final payload opaque: caller55C81E passes system+0x88 as a pointer.
// The helper below remains visible for its proven non-escaping output arguments.
#define Matrix4x4 Matrix4

// PointGroupClass::Render(RenderInfoClass &, int) at retail 0x00917B70 and the
// APT compression helper it calls at 0x00917920.
//
// BFME split the Zero Hour Render/Update_Arrays pair into helpers: shader prep
// (0x00912E60), APT compression (0x00917920), the vertex location, UV and
// diffuse fills (0x009148C0, 0x00916CD0, 0x00912880) and the vertex-buffer
// submit (0x00913AF0). The view transform loop and the Update_Arrays sizing
// prologue (out of line at 0x00914860) stay inline in Render.
//
// The helper at 0x00917920 is defined here, before Render, as it was in the
// retail pointgr.cpp: VC7.1 sees that it does not keep the addresses of
// Render's five out pointers, so Render loads them lazily, keeps the location
// base in a register through the transform loop and reads the diffuse pointer
// once. With only a declaration every one of those loads is repeated
// (docs/shape_levers.md, "Compiler-private ABI: compile the static helper with
// its caller"). The other helpers are not visible here, so Render copies
// PointCount into a local that retail kept live across those calls.

#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
// Native transform references share render_state at DEE5D8 with the
// DX8Wrapper setters; the BFME stage layout keeps the sixteen texture slots.
#include "dx8wrapper.h"
#include "vp.h"
// bfme link decl-only begin
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
// bfme link decl-only end

// Retail Vector2/Vector4 resize bodies belong to Vector2Resize.cpp.
// Declare their specializations so this consumer references those owners.
template <> bool VectorClass<Vector2>::Resize(int newsize, Vector2 const *array);
template <> bool VectorClass<Vector4>::Resize(int newsize, Vector4 const *array);

class CameraClass;
class RenderObjClass
{
public:
	Vector3 Get_Position(void) const;
};
class RenderInfoClass
{
public:
	CameraClass &Camera;
};

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector4> VertexDiffuse;
extern VectorClass<Vector2> VertexUV;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
// pointgr.h does not declare the BFME helpers, so this TU carries a shim.
// +0x24 and +0x28 are not read here and have no layout witness.
class PointGroupClass
{
public:
	enum PointModeEnum {
		TRIS,
		QUADS,
		SCREENSPACE
	};
	enum FlagsType {
		TRANSFORM,
		BILLBOARD,
	};

	// Same body as the matched out-of-line Get_Flag at 0x009120D0.
	int Get_Flag(FlagsType flag) { return (Flags >> flag) & 0x1; }

	void Render(RenderInfoClass &rinfo, int unknown);
	void RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth, void *unknown);

	void prepare_shader(void);
	void rva00917920(Vector3 **point_loc, Vector4 **point_diffuse, float **point_size,
		unsigned char **point_orientation, unsigned char **point_frame);
	void rva009148C0(Vector3 *point_loc, float *point_size, unsigned char *point_orientation,
		int active_points);
	void rva00916CD0(unsigned char *point_frame, int active_points, int unknown);
	void rva00912880(Vector4 *point_diffuse, int active_points);
	void rva00913AF0(int vnum, bool no_diffuse);

	// Update_Arrays sizing prologue; retail keeps an out-of-line copy at
	// 0x00914860 and inlines this one.
	void rva00914860(int active_points, int total_points, int *vnum)
	{
		int verts_per_point = (PointMode == QUADS) ? 4 : 3;
		int total_vnum = verts_per_point * total_points;
		*vnum = verts_per_point * active_points;
		if (VertexLoc.Length() < total_vnum) {
			VertexLoc.Resize(total_vnum * 2, false);
			VertexUV.Resize(total_vnum * 2, false);
			VertexDiffuse.Resize(total_vnum * 2, false);
		}
	}

private:
	virtual void abstract_dtor(void);
	ShareBufferClass<Vector3> *PointLoc;
	ShareBufferClass<Vector4> *PointDiffuse;
	ShareBufferClass<unsigned int> *APT;
	ShareBufferClass<float> *PointSize;
	ShareBufferClass<unsigned char> *PointOrientation;
	ShareBufferClass<unsigned char> *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	void *dword_24;
	unsigned int dword_28;
	PointModeEnum PointMode;
	unsigned int Flags;

	static VectorClass<Vector3> compressed_loc;
	static VectorClass<Vector4> compressed_diffuse;
	static VectorClass<float> compressed_size;
	static VectorClass<unsigned char> compressed_orient;
	static VectorClass<unsigned char> compressed_frame;
	static VectorClass<Vector3> transformed_loc;
};

// One APT compression step of 0x00917920. The buffer is a reference, so the
// Resize call stays virtual as in retail.
template <class T, class S>
static inline T *rva00917920_compress(VectorClass<T> &buffer, S *source, unsigned int *apt, int count)
{
	if (source) {
		if (buffer.Length() < count) {
			buffer.Resize(count * 2);
		}
		VectorProcessorClass::CopyIndexed(&buffer[0], source->Get_Array(), apt, count);
		return &buffer[0];
	}
	return NULL;
}

inline __declspec(noinline) void PointGroupClass::rva00917920(Vector3 **point_loc, Vector4 **point_diffuse, float **point_size,
	unsigned char **point_orientation, unsigned char **point_frame)
{
	if (APT) {
		unsigned int *apt = APT->Get_Array();
		*point_loc = rva00917920_compress(compressed_loc, PointLoc, apt, PointCount);
		*point_diffuse = rva00917920_compress(compressed_diffuse, PointDiffuse, apt, PointCount);
		*point_size = rva00917920_compress(compressed_size, PointSize, apt, PointCount);
		*point_orientation = rva00917920_compress(compressed_orient, PointOrientation, apt, PointCount);
		*point_frame = rva00917920_compress(compressed_frame, PointFrame, apt, PointCount);
	} else {
		*point_loc = PointLoc->Get_Array();
		if (PointDiffuse) {
			*point_diffuse = PointDiffuse->Get_Array();
		}
		if (PointSize) {
			*point_size = PointSize->Get_Array();
		}
		if (PointOrientation) {
			*point_orientation = PointOrientation->Get_Array();
		}
		if (PointFrame) {
			*point_frame = PointFrame->Get_Array();
		}
	}
}

// Retail matrix associations preserve all three native product schedules.
void PointGroupClass::RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth, void *unknown)
{
	if (depth <= 1 || !Get_Flag(TRANSFORM) || !Get_Flag(BILLBOARD)) {
		Render(rinfo, (int)unknown);
		return;
	}

	if (depth > 16)
		depth = 16;

	if (PointCount == 0)
		return;

	prepare_shader();

	Vector3 *current_loc = NULL;
	Vector4 *current_diffuse = NULL;
	float *current_size = NULL;
	unsigned char *current_orient = NULL;
	unsigned char *current_frame = NULL;
	rva00917920(&current_loc, &current_diffuse, &current_size, &current_orient, &current_frame);

	Vector3 *source_loc = current_loc;
	int vnum;
	rva00914860(PointCount, PointLoc->Get_Count(), &vnum);
	rva00912880(current_diffuse, PointCount);
	rva00916CD0(current_frame, PointCount, (int)unknown);

	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	if (transformed_loc.Length() < PointCount) {
		transformed_loc.Resize(PointCount * 2);
	}

	for (int t = 0; t < (int)depth; ++t) {
		float shiftInc = (float)t * 0.1f / (float)depth;
		Vector3 cameraPosition = ((RenderObjClass &)rinfo.Camera).Get_Position();
		for (int i = 0; i < PointCount; i++) {
			Vector3 cameraToPointDelta;
			Vector3::Subtract(cameraPosition, source_loc[i], &cameraToPointDelta);
			float len = cameraToPointDelta.Length();
			float scale = current_size[i] * shiftInc;
			scale /= len;
			cameraToPointDelta.X *= scale;
			cameraToPointDelta.Y *= scale;
			cameraToPointDelta.Z *= scale;
			Vector3 temp;
			temp.X = source_loc[i].X + cameraToPointDelta.X;
			temp.Y = source_loc[i].Y + cameraToPointDelta.Y;
			temp.Z = source_loc[i].Z + cameraToPointDelta.Z;
			Vector4 result;
			result = Vector4(
                ((view[0][2] * temp.Z) + (view[0][1] * temp.Y)) + (view[0][0] * temp.X) + view[0][3],
                (view[1][0] * temp.X) + ((view[1][1] * temp.Y) + (view[1][2] * temp.Z)) + view[1][3],
                (view[2][0] * temp.X) + ((view[2][1] * temp.Y) + (view[2][2] * temp.Z)) + view[2][3],
                0.0f);
			transformed_loc[i][0] = result[0];
			transformed_loc[i][1] = result[1];
			transformed_loc[i][2] = result[2];
		}
		// Separate the two actual pointer captures to retain native EBX/EDI reload order.
        float *sizes = current_size;
        _ReadWriteBarrier();
        unsigned char *orient = current_orient;
        current_loc = &transformed_loc[0];
        rva009148C0(current_loc, sizes, orient, PointCount);
		rva00913AF0(vnum, current_diffuse == NULL);
	}
}
