// cl: /Ireference/shims/bfme2_get_transform /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ScreenMapperClass::Calculate_Texture_Matrix 0x00186380 823B: vftable 0x007D32D0 slot +0x24, WB twin 0x00A374A0.
// Donor: EA GeneralsMD WW3D2/mapper.cpp verbatim, in its own TU so mapper.cpp keeps its flags.
// BFME 2's inline DX8Wrapper::Get_Transform (WB 0x009C1560) comes from the bfme2_get_transform shim.

// Use the established /O1 iterator copy without changing the array calls here.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// math.h's inline floorf gets internal linkage, and the link view keeps Vector4(x,y,z,w) inline, so neither
// emits a copy that loses to retail's owners (0x0004D649, 0x006D8A30).
extern "C" { static float __cdecl floorf(float); }
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

// Preserve the inline floorf operation without emitting another public Floor copy.
static inline float screenMapperFloor(float value) { return floorf(value); }

void ScreenMapperClass::Calculate_Texture_Matrix(Matrix4x4 &tex_matrix)
{
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
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
		offset_u = offset_u - screenMapperFloor(offset_u);
		offset_v = offset_v - screenMapperFloor(offset_v);
	} else {
		offset_u = WWMath::Clamp(offset_u, -Scale.X, Scale.X);
		offset_v = WWMath::Clamp(offset_v, -Scale.Y, Scale.Y);
	}

	// multiply by projection matrix
	// followed by scale and translation
	DX8Wrapper::Get_Transform(D3DTS_PROJECTION, tex_matrix);
	tex_matrix[0] *= Scale.X; // entire row since we're pre-multiplying
	tex_matrix[1] *= Scale.Y;
	Vector4 last(tex_matrix[3]); // this gets the w
	last *= offset_u; // multiply by w because the projected flag will divide by w
	tex_matrix[0] += last;
	last = tex_matrix[3];
	last *= offset_v;
	tex_matrix[1] += last;

	// Update state
	CurrentUVOffset.X = offset_u;
	CurrentUVOffset.Y = offset_v;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}
