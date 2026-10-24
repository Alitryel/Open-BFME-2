// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Bind the UV accessor to the separately matched native D1F40 owner.
#define BFME_MESHMATDESC_UV_ARRAY_EXTERNAL
// stlport
//
// ZH donor: GeneralsMD W3DDevice/GameClient/W3DBridgeBuffer.cpp, unchanged
// bodies of W3DBridge::getModelVerticesFixed and W3DBridge::getModelVertices.
// getModelVerticesFixed @0x000DE2AE 573B: the Zero Hour body built
// /O1 /arch:SSE places uniquely in .text, inside W3DBridge's retail range
// (clearBridge 0x000DD816, ~W3DBridge 0x000DDA6E, init 0x000DDB17). Its
// single call is getModelVertices at 0x000DDE13 (Ghidra extent 1179B),
// whose own Zero Hour body does not place. Keeping that definition in this
// unit is what reproduces retail's register allocation for the fixed
// variant; compiled alone the fixed body swaps xmm1/xmm2 and loses 5 bytes.
// That visible definition is written in its BFME 2 form (8000-vertex cap,
// BFME 2 GlobalData light offsets, one model local, UVs and the rotated
// normal stored first) and reads MeshModelClass through the meshgeom shim
// (CurMatDesc at +0x94), so its select-any copy is retail's 0x000DDE13 body
// byte for byte, the one W3DBridgeGetModelVertices.cpp rows.
// BFME 2 changed two callees' signatures that the Zero Hour headers declare:
// MeshGeometryClass::Get_Vertex_Normal_Array(bool) (row 0x0016AB90) and the
// six-argument BaseHeightMapRenderObjClass::doTheLight (row 0x000694A3).
// Declare BFME 2's forms in place of Zero Hour's while the headers are read.
#define Get_Vertex_Normal_Array Get_Vertex_Normal_Array(bool create); const Vector3 *Get_Vertex_Normal_Array_ZeroHour
#define doTheLight doTheLight(VERTEX_FORMAT *vb, Vector3 *light, Vector3 *normal, RefRenderObjListIterator *pLightsIterator, UnsignedByte alpha, Bool skipFirstLight); void doTheLight_ZeroHour
#include "../../../../../reference/shims/meshgeom/meshgeometry.h"
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include "../../../../../reference/shims/dynamesh_color_link/meshmatdesc.h"

#include <stdio.h>
#include <string.h>
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include <texture.h>
#include "common/GlobalData.h"
#include "common/RandomValue.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BodyModule.h"
#include "W3DDevice/GameLogic/W3DTerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Camera.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "WW3D2/Scene.h"
#undef Get_Vertex_Normal_Array
#undef doTheLight

#define NO_USE_BRIDGE_NORMALS

//=============================================================================
// W3DBridge::getModelVerticesFixed
//=============================================================================
/** Gets the vertex values for a section of a fixed bridge.  */
//=============================================================================
Int W3DBridge::getModelVerticesFixed(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, 
																const Matrix3D &mtx, MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL) 
		return(0);

	Vector3 vec = m_end - m_start;
	if (vec.Length2() < 1.0f) {
		vec.Normalize();
	}
	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();
	Real deltaZ = m_end.Z - m_start.Z;
	deltaZ /= vec.Length();
	Real deltaX = sqrt(1.0 - deltaZ*deltaZ);
	Vector3 vecZ(-deltaZ, 0, deltaX);
	vec /= m_length;
	vecNormal *= m_scale;
	vecZ *= m_scale;
	Real xOffset = -m_leftMinX;
	return(getModelVertices(destination_vb, curVertex, xOffset, vec, vecNormal, vecZ, m_start, mtx, pMesh, pLightsIterator));
}

// BFME 2's GlobalData light fields (the Zero Hour header has its own layout).
struct BridgeLightingGlobals
{
	char m_pad000[0x920];
	Coord3D m_terrainLightPos[3];		// +0x920
	char m_pad944[0x988 - 0x944];
	Int m_numGlobalLights;			// +0x988
};
#define TheGlobalLighting ((const BridgeLightingGlobals *)TheWritableGlobalData)

//=============================================================================
// ?W3DBridge::getModelVertices present-unmatched
// W3DBridge::getModelVertices
//=============================================================================
/** Gets the vertex values for a section of a bridge.  */
//=============================================================================
inline Int W3DBridge::getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
																Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset, 
																const Matrix3D &mtx, 
																MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL) 
		return(0);

	Int i;
	MeshModelClass *model = pMesh->Peek_Model();
	Int numVertex = model->Get_Vertex_Count();
	Vector3 *pVert = model->Get_Vertex_Array();
	const Vector3 *pNormal = model->Get_Vertex_Normal_Array(false);

	// If we happen to have too many bridges, stop.
	if (curVertex+numVertex+2>= 8000) {
		return(0);
	}

	Vector3 lightRay[3];
	const Coord3D *lightPos;

	for (Int lightIndex=0; lightIndex < TheGlobalLighting->m_numGlobalLights; lightIndex++)
	{
		lightPos=&TheGlobalLighting->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].Set(-lightPos->x,-lightPos->y,	-lightPos->z);
//		__asm {int 3}; //see if it really needs normalization!!
		lightRay[lightIndex].Normalize();
	}

	const Vector2*uvs=pMesh->Peek_Model()->Get_UV_Array_By_Index(0);
	VertexFormatXYZNDUV1 *curVb = destination_vb+curVertex;

	for (i=0; i<numVertex; i++) {
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;

		Vector3 vLoc;
		Vector3 vertex;
		Matrix3D::Transform_Vector(mtx, pVert[i], &vertex);
		vLoc = (vertex.X+xOffset) * vec + vertex.Y*vecNormal + vertex.Z*vecZ;

		vLoc.X += m_start.X;
		vLoc.Y += m_start.Y;
		vLoc.Z += m_start.Z; 

		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;
		
		VERTEX_FORMAT vb;
		vb.x = vLoc.X;
		vb.y = vLoc.Y;
		vb.z = vLoc.Z;

		Vector3 normal;
		Matrix3D::Rotate_Vector(mtx, pNormal[i], &normal);
		Real nx = normal.X;
		Real ny = normal.Y;
		Real nz = normal.Z;
		curVb->nx = nx;
		curVb->ny = ny;
		curVb->nz = nz;
		curVb->diffuse = 0xFF000000;
		normal = (normal.X) * vec + normal.Y*vecNormal + normal.Z*vecZ;
		normal.Normalize();	
		TheTerrainRenderObject->doTheLight(&vb, lightRay, &normal, NULL, 1, true);
		curVb->diffuse = vb.diffuse | 0xFF000000;
		curVb++;
	}
	return(numVertex);
}

//=============================================================================

// ?getIndicesNVertices@W3DBridge@@QAEXPAGPAUVertexFormatXYZNDUV1@@PAH2PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z @0x000DF11E
// Zero Hour's body less its vertex/index overflow returns. BFME 2 floors the
// span count with the CRT floor and an x87 round (retail calls floor and
// fistp) where Zero Hour's REAL_TO_INT_FLOOR uses its bit trick.
#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor(x)))
void W3DBridge::getIndicesNVertices(UnsignedShort *destination_ib, VertexFormatXYZNDUV1 *destination_vb, 
																		Int *curIndexP, Int *curVertexP, RefRenderObjListIterator *pLightsIterator)
{
	Int numI;
	Int numV;
	m_firstVertex = *curVertexP;
	m_firstIndex = *curIndexP;
	m_numVertex = 0;
	m_numPolygons = 0;
	if (m_sectionMesh == NULL) {
		numV = getModelVerticesFixed(destination_vb, *curVertexP, m_leftMtx, m_leftMesh, pLightsIterator);
		numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_leftMesh);
		*curIndexP += numI;
		*curVertexP += numV;
		m_numVertex += numV;
		m_numPolygons += numI/3;
		return;
	}

	Vector3 vec = m_end - m_start;
	if (vec.Length2() < 1.0f) {
		vec.Normalize();
	}

	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();
	vecNormal *= m_scale;

	Real deltaZ = m_end.Z - m_start.Z;
	Real desiredLength = vec.Length();
	deltaZ /= desiredLength;
	Real deltaX = sqrt(1.0 - deltaZ*deltaZ);
	Vector3 vecZ(-deltaZ, 0, deltaX);
	vecZ *= m_scale;

	Real spanLength = m_rightMinX - m_leftMaxX; 
	Int numSpans = 1;
	if (m_bridgeType != FIXED_BRIDGE) {
		Real spannable = desiredLength - (m_length-spanLength);
		numSpans = REAL_TO_INT_FLOOR( (spannable + spanLength/2)/spanLength);
		if (numSpans<0) numSpans = 0;
	}

	Real bridgeLength = m_length + (numSpans-1)*spanLength;
	Real xOffset = -m_leftMinX;

	vec /= bridgeLength;
	numV = getModelVertices(destination_vb, *curVertexP, xOffset, vec, vecNormal, vecZ, m_start, 
		m_leftMtx, m_leftMesh, pLightsIterator);
	numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_leftMesh);
	*curIndexP += numI;
	*curVertexP += numV;
	m_numVertex += numV;
	m_numPolygons += numI/3;

	Int i;
	for (i=0; i<numSpans; i++) {
		numV = getModelVertices(destination_vb, *curVertexP, xOffset+i*spanLength, vec, vecNormal, vecZ, m_start, 
			m_sectionMtx, m_sectionMesh, pLightsIterator);
		numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_sectionMesh);
		*curIndexP += numI;
		*curVertexP += numV;
		m_numVertex += numV;
		m_numPolygons += numI/3;
	}
	numV = getModelVertices(destination_vb, *curVertexP, xOffset+(numSpans-1)*spanLength, vec, vecNormal, vecZ, m_start, 
		m_rightMtx, m_rightMesh, pLightsIterator);
	numI = getModelIndices( destination_ib, *curIndexP, *curVertexP, m_rightMesh);
	*curIndexP += numI;
	*curVertexP += numV;
	m_numVertex += numV;
	m_numPolygons += numI/3;
}
