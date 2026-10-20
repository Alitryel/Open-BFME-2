// cl: /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// HLodClass::Update_Obj_Space_Bounding_Volumes: retail 0x0019DB50..0x0019E514, 2501 bytes, ZH donor body.
// Identity: HLod definition constructor call 0x0019FF2F, table 0x007D6780 slot +0x114, WB 0xA57C60.
// Bone matrices are built as WB does: pivot accessor, then the transform's expansion (WB 0x009FAF30).
#define Matrix4x4 Matrix4
#include <sweep/winbase_shim.h>
#include <string.h>
// Retail binds the donor's stricmp to msvcr71!_strcmpi (import slot 0x00BBA518).
#define stricmp _strcmpi
#define _CRTIMP
#include "rendobj.h"
#include "winbase_shim.h"
#include "hlod.h"
#include "assetmgr.h"
#include "hmdldef.h"
#include "w3derr.h"
#include "chunkio.h"
#include "predlod.h"
class CameraClass;
#include "rinfo.h"
#include "sphere.h"
#include "boxrobj.h"

// BFME2 pivots hold a rotation quaternion and a translation at +0x30/+0x40 with stride 0x58
// (HTreePivotClass.cpp); the expansion's arithmetic is the verified Add_Lod_Model one.
struct HlodTransformView
{
    __forceinline void Get_Matrix3D(Matrix3D &m) const
    {
        const float xx = X * X * 2.0f;
        const float xy = X * Y * 2.0f;
        const float xz = Z * X * 2.0f;
        const float wx = W * X * 2.0f;
        const float yy = Y * Y * 2.0f;
        const float yz = Z * Y * 2.0f;
        const float wy = W * Y * 2.0f;
        const float zz = Z * Z * 2.0f;
        const float wz = W * Z * 2.0f;
        m[0][0] = 1.0f - yy - zz;
        m[0][1] = xy - wz;
        m[0][2] = xz + wy;
        m[1][0] = xy + wz;
        m[1][1] = 1.0f - zz - xx;
        m[1][2] = yz - wx;
        m[2][0] = xz - wy;
        m[2][1] = yz + wx;
        m[2][2] = 1.0f - yy - xx;
        m[0][3] = Position.X;
        m[1][3] = Position.Y;
        m[2][3] = Position.Z;
    }
    float X, Y, Z, W;
    Vector3 Position;
};
struct HlodPivotView
{
    unsigned char unaccessed[0x30];
    HlodTransformView Transform;
    int Index;
    bool IsVisible;
    unsigned char tail[7];
};
typedef char HlodPivotStride[(sizeof(HlodPivotView) == 0x58) ? 1 : -1];
// The retail accessor's out-of-line copy is rowed at 0x0014D3BB.
struct HlodTreeView
{
    __forceinline const HlodTransformView &Get_Transform(int pivot) const { return Pivot[pivot].Transform; }
    char Name[16];
    int NumPivots; // +0x10
    HlodPivotView *Pivot; // +0x14
};

/***********************************************************************************************
 * HLodClass::Update_Obj_Space_Bounding_Volumes -- update object-space bounding volumes        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/26/00    gth : Created.                                                                 *
 *=============================================================================================*/
void HLodClass::Update_Obj_Space_Bounding_Volumes(void)
{
	//
	//	Do we still have a valid bounding box index?
	//
	ModelArrayClass &high_lod = Lod[LodCount - 1];
	int count = high_lod.Count ();
	if (	BoundingBoxIndex < 0 ||
			BoundingBoxIndex >= count ||
			high_lod[BoundingBoxIndex].Model->Class_ID () != RenderObjClass::CLASSID_OBBOX)
	{
		BoundingBoxIndex = -1;
	}

	//
	//	Attempt to find an OBBox mesh inside the heirarchy
	//
	int index = high_lod.Count ();
	while (index -- && BoundingBoxIndex == -1) {
		RenderObjClass *model = high_lod[index].Model;

		//
		//	Is this an OBBox mesh?
		//
		if (model->Class_ID () == RenderObjClass::CLASSID_OBBOX)
		{
			const char *name = model->Get_Name ();
			const char *name_seg = ::strchr (name, '.');
			if (name_seg != NULL) {
				name = name_seg + 1;
			}

			//
			//	Does the name match the designator we are looking for?
			//
			if (::stricmp (name, "BOUNDINGBOX") == 0) {
				BoundingBoxIndex = index;
			}
		}
	}


	int i;
	RenderObjClass * robj = NULL;

	// if we don't have any sub objects, just set default bounds
	if (Get_Num_Sub_Objects() <= 0) {
		ObjSphere.Init(Vector3(0,0,0),0);
		ObjBox.Center.Set(0,0,0);
		ObjBox.Extent.Set(0,0,0);
		return;
	}

	// loop through all sub-objects, combining their object-space bounding spheres and boxes.
	// Put our HTree in its base pose at the origin.
	SphereClass sphere;
	AABoxClass obj_aabox;
	MinMaxAABoxClass box;

	HTree->Base_Update(Matrix3D(1));

	robj = Get_Sub_Object(0);
	WWASSERT(robj);

	Matrix3D bonetm;
	reinterpret_cast<const HlodTreeView *>(HTree)->Get_Transform(Get_Sub_Object_Bone_Index(robj)).Get_Matrix3D(bonetm);
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	sphere.Transform(bonetm);
	robj->Get_Obj_Space_Bounding_Box(obj_aabox);

	box.Init(obj_aabox);
	box.Transform(bonetm);

	robj->Release_Ref();

	for (i=1; i<Get_Num_Sub_Objects(); i++) {
		robj = Get_Sub_Object(i);
		WWASSERT(robj);

		Matrix3D bonetm;
		reinterpret_cast<const HlodTreeView *>(HTree)->Get_Transform(Get_Sub_Object_Bone_Index(robj)).Get_Matrix3D(bonetm);

		SphereClass tmpsphere;
		robj->Get_Obj_Space_Bounding_Sphere(tmpsphere);
		tmpsphere.Transform(bonetm);
		sphere.Add_Sphere(tmpsphere);

		AABoxClass tmpbox;
		robj->Get_Obj_Space_Bounding_Box(tmpbox);
		tmpbox.Transform(bonetm);
		box.Add_Box(tmpbox);

		robj->Release_Ref();
	}

	ObjSphere = sphere;
	ObjBox = box;

   Invalidate_Cached_Bounding_Volumes();
	Set_Hierarchy_Valid(false);

   // Now update the object space bounding volumes of this object's container:
   RenderObjClass *container = Get_Container();
   if (container) container->Update_Obj_Space_Bounding_Volumes();
}
