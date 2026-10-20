// cl: /Ireference/shims/bfme2_get_transform /Ireference/shims/bfme2_matrix4_init16 /Ireference/shims/bfmestages /G7 /Ireference/shims/bfmerendobj /Ireference/shims/bfmemapper /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// GridWSEnvMapperClass::Calculate_Texture_Matrix, retail RVA 0x00186F10, 1166 bytes.
// Identity (target): matched constructors 0x00186DA0/0x00186E00 install vftable
// 0x007D5860 (and the derived tables) whose slot +0x24 is this body; Axis at +0x34.
// Source (donor): EA GeneralsMD WW3D2/mapper.cpp, verbatim. The WorldBuilder twin
// (WB 0x00A38240) confirms the shape: 16-float Matrix4 ctor -> Init(16), md.Init per
// case, operator* then operator=.
// Headers (target): Matrix4's sixteen-float constructor and Init (WB 0x00A363A0,
// 0x00A35C50; BFME 1's matrix4.h lacks them) and BFME 2's DX8Wrapper::Get_Transform
// (WB 0x009C1560: WORLD, VIEW, PROJECTION = DeviceProjectionMatrix.Transpose(),
// default Make_Identity; matched out-of-line copy 0x000768FE) come from TU-scoped
// shims. The dead PROJECTION/default cases of the inlined Get_Transform feed the
// register allocator: with ZH's D3D GetTransform fallback del lands in xmm6.
// update_temporal_state (0x00182590) and calculate_uv_offset (0x001825E0) are the
// BFME 2 bodies already matched elsewhere, visible inline as in retail.

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
	Matrix4x4 mv (	mat[0].X, mat[1].X, mat[2].X, 0.0f,
						mat[0].Y, mat[1].Y, mat[2].Y, 0.0f,
						mat[0].Z, mat[1].Z, mat[2].Z, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );	

	update_temporal_state();

	float u_offset, v_offset;
	calculate_uv_offset(&u_offset, &v_offset);

	float del=0.5f * OOGridWidth;	
	// Set up the offset matrix		
	Matrix4x4 md;	

	switch (Axis) {
		case AXISTYPE_X:
			md.Init(				0.0f, del, 0.0f, u_offset + del,
									0.0f, 0.0f, del, v_offset + del,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f );
			break;
		case AXISTYPE_Y:
			md.Init(				del, 0.0f, 0.0f, u_offset + del,
									0.0f, 0.0f, del, v_offset + del,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f );
			break;
		case AXISTYPE_Z:
		default:
			md.Init(				del, 0.0f, 0.0f, u_offset + del,
									0.0f, del, 0.0f, v_offset + del,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f );			
			break;
	}	
	// multiply by inverse of view transform, then
	// change the world space reflection vector to a UV coordinate
	// then offset by the grid coordinate

	tex_matrix = md * mv;
}
