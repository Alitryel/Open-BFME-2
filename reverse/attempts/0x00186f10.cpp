// ?Calculate_Texture_Matrix@GridWSEnvMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.9897084048027445 date=2026-10-19
// ?Calculate_Texture_Matrix@GridWSEnvMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.542 date=2026-10-17
// ?Calculate_Texture_Matrix@GridWSEnvMapperClass@@UAEXAAVMatrix4@@@Z
// partial score=0.5463121784 date=2026-09-27
// cl: /Ireference/shims/bfmestages /G7 /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Banked partial: GridWSEnvMapperClass::Calculate_Texture_Matrix, RVA 0x186F10.
// Boundary discovery batch 6 proves 1166 bytes. Matched GridWSEnv constructors
// install table 0x7D5860 with this entry at +0x24; the class identity is inherited
// from those existing donor matches. Axis +0x34 comes from the constructors.
// Reference: EA GeneralsMD WW3D2/mapper.cpp, with BFME2 already verified temporal
// and UV helper implementations inlined. The 16-scalar initializations are
// expanded for the BFME1 Matrix4 interface. Emits 1166 bytes but differs from
// +3 onward in SSE registers/stack temporaries; no unresolved calls.


#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>


inline void GridTextureMapperClass::update_temporal_state()
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta = now - LastUsedSyncTime;
	Remainder += delta;
	LastUsedSyncTime = now;

	int new_frame = (int)CurrentFrame + ((int)(Remainder / MSPerFrame) * Sign);
	new_frame = (int)((unsigned)new_frame % LastFrame);

	if (new_frame < 0)
		CurrentFrame = LastFrame + new_frame;
	else
		CurrentFrame = (unsigned int)new_frame;
	Remainder = Remainder % MSPerFrame;
}

inline void GridTextureMapperClass::calculate_uv_offset(float * u_offset, float * v_offset)
{
	unsigned int row_mask = ~(0xFFFFFFFF << GridWidthLog2);
	unsigned int col_mask = row_mask << GridWidthLog2;
	unsigned int x = CurrentFrame & row_mask;
	unsigned int y = (CurrentFrame & col_mask) >> GridWidthLog2;
	*u_offset = x * OOGridWidth;
	*v_offset = y * OOGridWidth;
}
void GridWSEnvMapperClass::Calculate_Texture_Matrix(Matrix4x4 &tex_matrix)
{
	// multiply by inverse of view transform	
	Matrix4x4 mat;	
	DX8Wrapper::Get_Transform(D3DTS_VIEW,mat);		
	Matrix4x4 mv(
        Vector4(mat[0].X, mat[1].X, mat[2].X, 0.0f),
        Vector4(mat[0].Y, mat[1].Y, mat[2].Y, 0.0f),
        Vector4(mat[0].Z, mat[1].Z, mat[2].Z, 0.0f),
        Vector4(0.0f, 0.0f, 0.0f, 1.0f));

	update_temporal_state();

	float u_offset, v_offset;
	calculate_uv_offset(&u_offset, &v_offset);

	float del = 0.5f * OOGridWidth;
	// Set up the offset matrix		
	Matrix4x4 md;	

	switch (Axis) {
		case AXISTYPE_X:
			md[0].X = 0.0f;
			md[0].Y = del;
			md[0].Z = 0.0f;
			md[0].W = u_offset + del;
			md[1].X = 0.0f;
			md[1].Y = 0.0f;
			md[1].Z = del;
			md[1].W = v_offset + del;
			md[2].X = 0.0f;
			md[2].Y = 0.0f;
			md[2].Z = 1.0f;
			md[2].W = 0.0f;
			md[3].X = 0.0f;
			md[3].Y = 0.0f;
			md[3].Z = 0.0f;
			md[3].W = 1.0f;
			break;
		case AXISTYPE_Y:
			md[0].Y = 0.0f;
			md[0].X = del;
			md[0].Z = 0.0f;
			md[0].W = u_offset + del;
			md[1].X = 0.0f;
			md[1].Y = 0.0f;
			md[1].Z = del;
			md[1].W = v_offset + del;
			md[2].X = 0.0f;
			md[2].Y = 0.0f;
			md[2].Z = 1.0f;
			md[2].W = 0.0f;
			md[3].X = 0.0f;
			md[3].Y = 0.0f;
			md[3].Z = 0.0f;
			md[3].W = 1.0f;
			break;
		case AXISTYPE_Z:
		default:
			md[0].Y = 0.0f;
			md[0].X = del;
			md[0].Z = 0.0f;
			md[0].W = u_offset + del;
			md[1].X = 0.0f;
			md[1].Y = del;
			md[1].Z = 0.0f;
			md[1].W = v_offset + del;
			md[2].X = 0.0f;
			md[2].Y = 0.0f;
			md[2].Z = 1.0f;
			md[2].W = 0.0f;
			md[3].X = 0.0f;
			md[3].Y = 0.0f;
			md[3].Z = 0.0f;
			md[3].W = 1.0f;
			break;
	}	
	// multiply by inverse of view transform, then
	// change the world space reflection vector to a UV coordinate
	// then offset by the grid coordinate

	tex_matrix = md * mv;
}

// Resume: scalar-Init and product-temporary variants did not match. Use
// bfmestages first: verified render-state has 16 textures and view at +22C.

// Resume 2026-10-19: native Vector4 inverse-view rows remove the farm levers.
// Only the shared Y/default copy/store order differs; see the accompanying handoff.
