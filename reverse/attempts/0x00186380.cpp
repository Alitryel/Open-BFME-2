// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.937 date=2026-10-17
// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.68 date=2026-10-15
// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.9 date=2026-10-14
// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.88 date=2026-10-13
// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.88 date=2026-10-12
// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

// DX8Wrapper's device projection copy at VA 0x00DEDBF0 (bfmecamera shim:
// DX8Wrapper::DeviceProjectionMatrix), defined under this name in
// TextureMapperApply.cpp. BFME2 answers Get_Transform(D3DTS_PROJECTION) from
// it rather than from the device.
extern Matrix4x4 g_mapperProjectionUpload_009EDBF0;

void ScreenMapperClass::Calculate_Texture_Matrix(Matrix4 &tex_matrix)
{
	unsigned int delta = (1 ? (WW3D::Get_Sync_Time() - LastUsedSyncTime) : (WW3D::Get_Sync_Time() - LastUsedSyncTime));
	float del = (float)delta;
	float offset_u = CurrentUVOffset.X + UVOffsetDeltaPerMS.X * del;
	float offset_v = CurrentUVOffset.Y + UVOffsetDeltaPerMS.Y * del;

	// We need to clamp these texture coordinates to a reasonable range so the hardware doesn't
	// choke on them. We do this in one of two ways:
	// If ClampFix is not TRUE we use the fractional part of the offset, restricting it between
	// 0 and 1 with wraparound. This works well for tiled textures.
	// If ClampFix is TRUE we clamp the offsets between -Scale and +Scale with no wraparound.
	// This works well for clamped textures.
	if (!ClampFix) {
		offset_u = offset_u - WWMath::Floor(offset_u);
		offset_v = offset_v - WWMath::Floor(offset_v);
	} else {
		offset_u = WWMath::Clamp(offset_u, -Scale.X, Scale.X);
		offset_v = WWMath::Clamp(offset_v, -Scale.Y, Scale.Y);
	}

	// multiply by projection matrix
	// followed by scale and translation
	tex_matrix = (1 ? (g_mapperProjectionUpload_009EDBF0.Transpose()) : (g_mapperProjectionUpload_009EDBF0.Transpose()));
	tex_matrix[0] *= Scale.X; // entire row since we're pre-multiplying
	float ky = Scale.Y;
	tex_matrix[3].X = ky * tex_matrix[3].X;
	tex_matrix[3].Y = ky * tex_matrix[3].Y;
	tex_matrix[3].Z = ky * tex_matrix[3].Z;
	tex_matrix[3].W = ky * tex_matrix[3].W;
	Vector4 last;
	{
		Vector4 row3_for_u(tex_matrix[3]);
		row3_for_u *= offset_u;
		last = row3_for_u;
	}
	float row0_y = *(volatile float*)&tex_matrix[0].Y;
	tex_matrix[0].Y = last.Y + row0_y;
	tex_matrix[0].Z = last.Z + tex_matrix[0].Z;
	tex_matrix[0].W = last.W + tex_matrix[0].W;
	tex_matrix[0].X = last.X + tex_matrix[0].X;
	Vector4 scaled_row3(tex_matrix[3]);
	scaled_row3 *= offset_v;
	tex_matrix[1].X = scaled_row3.X + *(volatile float*)&tex_matrix[1].X;
	tex_matrix[1].Y = scaled_row3.Y + tex_matrix[1].Y;
	tex_matrix[1].Z = scaled_row3.Z + tex_matrix[1].Z;
	tex_matrix[1].W = scaled_row3.W + tex_matrix[1].W;

	// Update state
	CurrentUVOffset.X = offset_u;
	CurrentUVOffset.Y = offset_v;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}
