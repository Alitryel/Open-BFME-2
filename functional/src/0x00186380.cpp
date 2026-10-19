// ?Calculate_Texture_Matrix@ScreenMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.926 date=2026-10-18
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
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
	float del = (float)delta;
	float offset_u = CurrentUVOffset.X + UVOffsetDeltaPerMS.X * del;
	float offset_v = CurrentUVOffset.Y + UVOffsetDeltaPerMS.Y * del;

	if (!ClampFix) {
		offset_u = offset_u - WWMath::Floor(offset_u);
		offset_v = offset_v - WWMath::Floor(offset_v);
	} else {
		offset_u = WWMath::Clamp(offset_u, -Scale.X, Scale.X);
		offset_v = WWMath::Clamp(offset_v, -Scale.Y, Scale.Y);
	}

	tex_matrix = g_mapperProjectionUpload_009EDBF0.Transpose();
	tex_matrix[0] *= Scale.X; // entire row since we're pre-multiplying
	tex_matrix[1] *= Scale.Y;
	// Row 0 differs from Zero Hour: retail adds each product with the row
	// element folded as the addss memory operand, in Y,Z,W,X order (X, at
	// displacement 0, is scheduled last). Writing the four products per element
	// in that order (tex_matrix[0].Y += last.Y * offset_u; ... X last) matches
	// every instruction except colouring: offset_u/offset_v then take xmm5/xmm4
	// instead of retail's xmm1/xmm0 (824 B). This in-place form keeps the
	// colouring but only Z coalesces into the folded add (836 B). Row 1's scale
	// X (retail movaps xmm3,xmm2; mulss xmm3,[row1.X]) is open in every form.
	Vector4 last(tex_matrix[3]); // this gets the w
	last *= offset_u; // multiply by w because the projected flag will divide by w
	tex_matrix[0].Y += last.Y;
	tex_matrix[0].Z += last.Z;
	tex_matrix[0].W += last.W;
	tex_matrix[0].X += last.X;
	last = tex_matrix[3];
	last *= offset_v;
	tex_matrix[1] += last;

	CurrentUVOffset.X = offset_u;
	CurrentUVOffset.Y = offset_v;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}
