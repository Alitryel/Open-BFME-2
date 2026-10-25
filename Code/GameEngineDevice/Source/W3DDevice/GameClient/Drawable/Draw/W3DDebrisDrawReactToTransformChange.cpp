// cl: /Ireference/shims/bfme2_ascii /DBFME_MODULE_NO_MPO /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// ?reactToTransformChange@W3DDebrisDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z,
// retail 0x000B1A14, 35 bytes: W3DDebrisDraw vtable VA 0xBC97A8 (stored at +0
// by the rowed ctor 0xB1C41) slot 38. Shard of W3DDebrisDraw.cpp: retail
// uses the merged one-vptr Module base: m_renderObject is at +0x24 and
// the drawable at +0x08. The shared debris view retains these accesses;
// RenderObjClass::Set_Transform is vtable +0x54 in bfme2renderobj.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "rendobj.h"
#include "BfmeDebrisDrawView.h"

// ?reactToTransformChange@W3DDebrisDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z @0x000B1A14
void W3DDebrisDraw::reactToTransformChange( const Matrix3D *oldMtx, 
																						const Coord3D *oldPos, 
																						float oldAngle )
{

	if( m_renderObject )
		m_renderObject->Set_Transform( *getDrawable()->getTransformMatrix() );

}