// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2_ascii_native_copy /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Link view first: Vector3 Length/Normalize/ctor and the scalar operator* stay inline without emitting
// /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510, 0x00066382, 0x0007DFB3).
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/W3DScene.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DScene.cpp /////////////////////////////////////////////////////////
//
// Scene manger for display using W3DDispaly.  A scene manager can customize
// the rendering process, culling, material passes ...
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Color.h"
#include "GameClient/View.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "coltest.h" // BFME2 RayCollisionTestClass (reference/shims/bfme2ray): out-of-line ctors as retail calls them
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DStatusCircle.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/camera.h"
#include "WW3D2/dx8renderer.h"
#include "WW3D2/sortingrenderer.h"
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/Light.h"
#include "WW3D2/matpass.h"
#include "WW3D2/shader.h"
#include "WW3D2/DX8Caps.h"
// Retail keeps the size-optimized RGB/HSV definitions in ColorSpaceO1Inlines.
// Declare the shared calls here so this unit cannot supply a different copy.
#include "vector3.h"
void RGB_To_HSV(Vector3 &, const Vector3 &);
void HSV_To_RGB(Vector3 &, const Vector3 &);

#include "WW3D2/shdlib.h"
// Imported-forceinline: this unit inlines RefMultiListClass<RenderObjClass>::Remove
// and must not emit its 48-byte COMDAT copy, which was first in link order and
// differs from retail's 47-byte body (rowed 0x0006EF4E, RefMultiListRenderObjRemove.cpp).
template <> __declspec(dllimport) __forceinline
bool RefMultiListClass<RenderObjClass>::Remove(RenderObjClass *obj)
{
	bool result = Internal_Remove(obj);
	if (result) {
		obj->Release_Ref();
	}
	return result;
}
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////
// DEFINITIONS ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///@todo: Remove these globals since we no longer need W3D to call them for us.
extern void DoTrees(RenderInfoClass & rinfo);
extern void DoShadows(RenderInfoClass & rinfo, Bool stencilPass);
extern void DoParticles(RenderInfoClass & rinfo);

// No texturing, no zbuffer reading/writing, primary gradient, no
// blending, no fogging - mostly for use in solid-colored opaque objects.
#define SC_PLAYER_COLOR ( SHADE_CNST(ShaderClass::PASS_ALWAYS, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, \
	ShaderClass::SRCBLEND_ONE, ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )
static ShaderClass PlayerColorShader(SC_PLAYER_COLOR);

//=============================================================================
// RTS3DScene::RTS3DScene
//=============================================================================
/** */
//=============================================================================
// ?RTS3DScene::RTS3DScene present-unmatched
RTS3DScene::RTS3DScene()
{
	// BFME2's SubsystemInterface::setName (retail 0x0006F3CC, rowed in
	// SubsystemInterfaceSetName.cpp) keeps m_name at +0x08; this Zero Hour
	// view has it at +0x04, so calling it emitted a wrong out-of-line copy
	// that the link kept first. The BFME2 ctor is rowed in RTS3DSceneCtor.cpp.
	m_name = AsciiString("RTS3DScene");
	m_drawTerrainOnly = false;
	m_numGlobalLights=0;
	for (Int i=0; i<LightEnvironmentClass::MAX_LIGHTS; i++)
	{	m_globalLight[i]=NULL;
		m_infantryLight[i]=NEW_REF( LightClass, (LightClass::DIRECTIONAL) );
	}

	m_scratchLight = NEW_REF( LightClass, (LightClass::DIRECTIONAL) );
//	REF_PTR_SET(m_globalLight[lightIndex], pLight);

#if defined(_DEBUG) || defined(_INTERNAL)
	if (TheGlobalData->m_shroudOn)
		m_shroudMaterialPass = NEW_REF(W3DShroudMaterialPassClass,());
	else
		m_shroudMaterialPass = NULL;
#else
	m_shroudMaterialPass = NEW_REF(W3DShroudMaterialPassClass,());
#endif

	m_maskMaterialPass = NEW_REF(W3DMaskMaterialPassClass,());
	m_customPassMode = SCENE_PASS_DEFAULT;

	m_heatVisionMaterialPass = NEW_REF(MaterialPassClass,());
	m_heatVisionOnlyPass = NEW_REF(MaterialPassClass,());
	VertexMaterialClass *heatVisionMtl = NEW_REF(VertexMaterialClass,());
	heatVisionMtl->Set_Lighting(true);
	heatVisionMtl->Set_Ambient(0,0,0);
	heatVisionMtl->Set_Diffuse(0.02f,0.01f,0.00f);
	heatVisionMtl->Set_Emissive(0.5f,0.2f,0.0f);
	m_heatVisionMaterialPass->Set_Material(heatVisionMtl);
	ShaderClass heatVisionShader=ShaderClass::_PresetAdditiveSolidShader;
	heatVisionShader.Set_Depth_Compare(ShaderClass::PASS_EQUAL);
	m_heatVisionMaterialPass->Set_Shader(heatVisionShader);
	heatVisionMtl->Release_Ref();
	heatVisionShader.Set_Depth_Compare(ShaderClass::PASS_LEQUAL);
	heatVisionShader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
	m_heatVisionOnlyPass->Set_Material(heatVisionMtl);
	m_heatVisionOnlyPass->Set_Shader(heatVisionShader);


//	VertexMaterialClass *frenzyMtl = NEW_REF(VertexMaterialClass,());
//	frenzyMtl->Set_Lighting(TRUE);
//	frenzyMtl->Set_Ambient(  0, 0, 0 );
//	frenzyMtl->Set_Diffuse(  1.0f, 0.0f, 0.0f );
//	frenzyMtl->Set_Emissive( 1.0f, 0.0f, 0.0f );
//	m_frenzyMaterialPass = NEW_REF(MaterialPassClass,());
//	m_frenzyMaterialPass->Set_Material(frenzyMtl);
//	frenzyMtl->Release_Ref();
//	ShaderClass frenzyShader=ShaderClass::_PresetMultiplicativeShader;
//	frenzyShader.Set_Depth_Compare(ShaderClass::PASS_EQUAL);
//	frenzyShader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
//	m_frenzyMaterialPass->Set_Shader(frenzyShader);

  
	//Allocate memory to hold queue of visible renderobjects that need to be drawn last
	//because they are forced translucent.
	m_translucentObjectsCount = 0;
	if (TheGlobalData && TheGlobalData->m_maxVisibleTranslucentObjects)
		m_translucentObjectsBuffer = NEW RenderObjClass* [TheGlobalData->m_maxVisibleTranslucentObjects];
	else
		m_translucentObjectsBuffer = NULL;

	m_numPotentialOccluders=0;
	m_numPotentialOccludees=0;
	m_numNonOccluderOrOccludee=0;
	m_occludedObjectsCount=0;

	m_potentialOccluders=NULL;
	m_potentialOccludees=NULL;
	m_nonOccludersOrOccludees=NULL;

	//Modify the shader to make occlusion transparent
	ShaderClass shader = PlayerColorShader;
	shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_SRC_ALPHA);
	shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);

    m_potentialOccluders = NEW RenderObjClass* [TheGlobalData->m_maxVisibleOccluderObjects];
	m_potentialOccludees = NEW RenderObjClass* [TheGlobalData->m_maxVisibleOccludeeObjects];
	m_nonOccludersOrOccludees = NEW RenderObjClass* [TheGlobalData->m_maxVisibleNonOccluderOrOccludeeObjects];

#ifdef USE_NON_STENCIL_OCCLUSION
	for (i=0; i<MAX_PLAYER_COUNT; i++)
	{	m_occludedMaterialPass[i]=NEW_REF(MaterialPassClass,());
		VertexMaterialClass * vmtl = NEW_REF(VertexMaterialClass,());
		vmtl->Set_Lighting(true);
		vmtl->Set_Ambient(0,0,0);	//we're only using emissive so kill all other lights.
		vmtl->Set_Diffuse(0,0,0);
		m_occludedMaterialPass[i]->Set_Material(vmtl);
		m_occludedMaterialPass[i]->Set_Shader(shader);
		vmtl->Release_Ref();	//material pass is holding the pointer so release ref.
	}
#else
	for (i=0; i<MAX_PLAYER_COUNT; i++)
		m_occludedMaterialPass[i]=NULL;
#endif

}  // end RTS3DScene

//=============================================================================
// RTS3DScene::~RTS3DScene
//=============================================================================
// Definition is in RTS3DSceneCtor.cpp, whose private class view matches the
// BFME2 layout rather than Zero Hour's mask and per-player material passes.


// ?RTS3DScene::setGlobalLight present-unmatched
void	RTS3DScene::setGlobalLight(LightClass *pLight, Int lightIndex)
{
	if (m_numGlobalLights < (lightIndex+1))
		m_numGlobalLights=(lightIndex+1);
	REF_PTR_SET(m_globalLight[lightIndex], pLight);
}

/**Find all objects which need to be drawn in a special way because they are occluded by other
objects.
@todo:  Need some kind of scene subdivision or find way to use Partition manger to speed up the ray
intersection tests.  Maybe truncate the ray to terrain length before using it?
*/
// ?RTS3DScene::flagOccludedObjects present-unmatched
void RTS3DScene::flagOccludedObjects(CameraClass * camera)
{
	Vector3 camPosition=camera->Get_Position();

	//Find which objects are actually occluded
	RenderObjClass **occludee=m_potentialOccludees;
	LineSegClass lineseg;
	CastResultStruct result;
	Bool hit=FALSE;
	Vector3 newEndPoint;
	result.ComputeContactPoint=false;
	RayCollisionTestClass raytest(lineseg,&result,COLL_TYPE_ALL,false,false);
	raytest.CollisionType=COLL_TYPE_ALL;

	m_occludedObjectsCount=0;

	for (Int i=0; i<m_numPotentialOccludees; i++,occludee++)
	{	
		raytest.Ray.Set(camPosition,(*occludee)->Get_Position());

		RenderObjClass **occluder=m_potentialOccluders;

		//Check this object against all other possible blocking objects
		for (Int j=0; j<m_numPotentialOccluders; j++,occluder++)
		{
			// Do a quick ray-sphere test (Graphics Gems I,  p388)
			RenderObjClass *robj=*occluder;

			const SphereClass *sphere = &robj->Get_Bounding_Sphere();

			// make a vector from the ray origin to the sphere center
			Vector3 sphere_vector(sphere->Center - raytest.Ray.Get_P0());
			
			// get the dot product between the sphere_vector and the ray vector
			Real Alpha = Vector3::Dot_Product(sphere_vector, raytest.Ray.Get_Dir());

			Real Beta = sphere->Radius * sphere->Radius - (Vector3::Dot_Product(sphere_vector, sphere_vector) - Alpha * Alpha);

			if(Beta < 0.0f)
				continue;	//no intersection
				
			//Do a more accurate test against object geometry
			if (robj->Cast_Ray(raytest))
			{
				//Found an object closer than last closest object
				//Adjust our results and refine search
				raytest.CollidedRenderObj = robj;
				hit=TRUE;
				//reset the result space for next test
				result.StartBad = false; result.Fraction = 1.0f;
				break;
			}
		}
		if (hit)
		{	//ocludee was blocked by something so flag it for custom rendering
			DrawableInfo *drawInfo=(DrawableInfo *)(*occludee)->Get_User_Data();
			drawInfo->m_flags |= DrawableInfo::ERF_IS_OCCLUDED;
			m_potentialOccludees[m_occludedObjectsCount++] = *occludee;
		}
	}
}

//=============================================================================
// RTS3DScene::castRay
//=============================================================================
/** Does a ray intersection test against objects in our scene.
	By default, it only tests objects determined to be visible to the user.
	Setting testAll forces it to test all objects in the scene.
	CollisionType is used as a mask to ignore certain types of objects.
 */
//=============================================================================
// ?RTS3DScene::castRay present-unmatched
Bool RTS3DScene::castRay(RayCollisionTestClass & raytest, Bool testAll, Int collisionType)
{
// this shouldn't be necessary here, and would be an undesirable performance hit.
// if you ever add or modify code here, it MIGHT become necessary... so do so with caution. (srj)
//#ifdef DIRTY_CONDITION_FLAGS
//	StDrawableDirtyStuffLocker lockDirtyStuff;
//#endif

	//temporary results for each object tested
	CastResultStruct result;
	RayCollisionTestClass tempRayTest(raytest.Ray,&result);
	Vector3 newEndPoint;
	Bool hit=FALSE;

	tempRayTest.CollisionType = COLL_TYPE_ALL;
	//check if a mesh is translucent before colliding with it. Skips headlights, etc.
	tempRayTest.CheckTranslucent = true;

	RefRenderObjListIterator it(&RenderList);

	// select the first object
	it.First();

	while (!it.Is_Done())
	{
		// get the render object
		RenderObjClass * robj = it.Peek_Obj();
		it.Next();

		// only intersect if it was visible or if we must test all
		if(robj->Get_Collision_Type() & collisionType && (testAll || robj->Is_Really_Visible()))
		{
			// Do a quick ray-sphere test (Graphics Gems I,  p388)
			const SphereClass *sphere = &robj->Get_Bounding_Sphere();

			// make a vector from the ray origin to the sphere center
			Vector3 sphere_vector(sphere->Center - tempRayTest.Ray.Get_P0());
		
			// get the dot product between the sphere_vector and the ray vector
			Real Alpha = Vector3::Dot_Product(sphere_vector, tempRayTest.Ray.Get_Dir());

			Real Beta = sphere->Radius * sphere->Radius - (Vector3::Dot_Product(sphere_vector, sphere_vector) - Alpha * Alpha);

			if(Beta < 0.0f)
				continue;	//no intersection
			
			//Do a more accurate test against object geometry
			if (robj->Cast_Ray(tempRayTest))
			{
				//Found an object closer than last closest object
				//Adjust our results and refine search
				raytest.CollidedRenderObj = robj;
				hit=TRUE;
				//Refine search by making ray shorter
				tempRayTest.Ray.Compute_Point(tempRayTest.Result->Fraction,&newEndPoint);
				tempRayTest.Ray.Set(raytest.Ray.Get_P0(),newEndPoint);
				//intersection point is at the end of shortened ray, so adjust fraction to 1.0
				tempRayTest.Result->Fraction=1.0f;
			}
		}
	}

	//Store results of ray intersection test including a clipped ray that ends on object.
	raytest.Ray=tempRayTest.Ray;
	return hit;
}

//=============================================================================
// RTS3DScene::Visibility_Check
//=============================================================================
/** Custom visibility check method for the RTS3DScene, we can put optimized
  * culling methods in here */
//=============================================================================
// ?RTS3DScene::Visibility_Check present-unmatched
void RTS3DScene::Visibility_Check(CameraClass * camera)
{
#ifdef DIRTY_CONDITION_FLAGS
	StDrawableDirtyStuffLocker lockDirtyStuff;
#endif

	RefRenderObjListIterator it(&RenderList);
	DrawableInfo *drawInfo = NULL;
	Drawable	*draw = NULL;
	RenderObjClass * robj;

	m_numPotentialOccluders=0;
	m_numPotentialOccludees=0;
	m_translucentObjectsCount=0;
	m_numNonOccluderOrOccludee=0;

	Int currentFrame=0;
	if (TheGameLogic) currentFrame = TheGameLogic->getFrame();
	if (currentFrame <= TheGlobalData->m_defaultOcclusionDelay)
		currentFrame = TheGlobalData->m_defaultOcclusionDelay+1;	//make sure occlusion is enabled when game starts (frame 0).


	if (ShaderClass::Is_Backface_Culling_Inverted()) 
	{	//we are rendering reflections
		///@todo: Have better flag to detect reflection pass

		// Loop over all top-level RenderObjects in this scene. If the bounding sphere is not in front
		// of all the frustum planes, it is invisible.
		for (it.First(); !it.Is_Done(); it.Next()) {

			robj = it.Peek_Obj();

			draw=NULL;
			drawInfo = (DrawableInfo *)robj->Get_User_Data();
			if (drawInfo)
				draw=drawInfo->m_drawable;

			if( draw )
			{
				if (robj->Is_Force_Visible()) {
					robj->Set_Visible(true);
				} else {
					robj->Set_Visible(draw->getDrawsInMirror() && !camera->Cull_Sphere(robj->Get_Bounding_Sphere()));
				}
			}
			else
			{	//perform normal culling on non-drawables
				if (robj->Is_Force_Visible()) {
					robj->Set_Visible(true);
				} else {
					robj->Set_Visible(!camera->Cull_Sphere(robj->Get_Bounding_Sphere()));
				}
			}
		}
	}
	else
	{

		// Loop over all top-level RenderObjects in this scene. If the bounding sphere is not in front
		// of all the frustum planes, it is invisible.
		for (it.First(); !it.Is_Done(); it.Next()) {

			robj = it.Peek_Obj();

			if (robj->Is_Force_Visible()) {
				robj->Set_Visible(true);
			} else if (robj->Is_Hidden()) {
				robj->Set_Visible(false);
			} else {

				bool isVisible=!camera->Cull_Sphere(robj->Get_Bounding_Sphere());

				if (isVisible)
				{	//need to keep track of occluders and ocludees for subsequent code.
					drawInfo = (DrawableInfo *)robj->Get_User_Data();
					if (drawInfo && (draw=drawInfo->m_drawable) != NULL)
					{
						if (draw->isDrawableEffectivelyHidden() || draw->getFullyObscuredByShroud())
						{	
							isVisible = FALSE;
						  robj->Set_Visible(isVisible);
            }
						//assume normal rendering.
						drawInfo->m_flags = DrawableInfo::ERF_IS_NORMAL;	//clear any rendering flags that may be in effect.

            if ( ! isVisible )
              continue;

						if (draw->getEffectiveOpacity() != 1.0f && m_translucentObjectsCount < TheGlobalData->m_maxVisibleTranslucentObjects)
						{	drawInfo->m_flags |= DrawableInfo::ERF_IS_TRANSLUCENT;	//object is translucent
							m_translucentObjectsBuffer[m_translucentObjectsCount++] = robj;
						}
						if (TheGlobalData->m_enableBehindBuildingMarkers && TheGameLogic->getShowBehindBuildingMarkers())
						{
							//visible drawable. Check if it's either an occluder or occludee
							if (draw->isKindOf(KINDOF_STRUCTURE) && m_numPotentialOccluders < TheGlobalData->m_maxVisibleOccluderObjects)
							{	//object which could occlude other objects that need to be visible.
								//Make sure this object is not translucent so it's not rendered twice (from m_potentialOccluders and m_translucentObjectsBuffer)
								if (drawInfo->m_flags ^ DrawableInfo::ERF_IS_TRANSLUCENT)
									m_potentialOccluders[m_numPotentialOccluders++]=robj;
								drawInfo->m_flags |= DrawableInfo::ERF_POTENTIAL_OCCLUDER;
							}
							else
							if (draw->getObject() &&
									(draw->isKindOf(KINDOF_SCORE) || draw->isKindOf(KINDOF_SCORE_CREATE) || draw->isKindOf(KINDOF_SCORE_DESTROY) || draw->isKindOf(KINDOF_MP_COUNT_FOR_VICTORY)) &&
									(draw->getObject()->getSafeOcclusionFrame()) <= currentFrame && m_numPotentialOccludees < TheGlobalData->m_maxVisibleOccludeeObjects)
							{	//object which could be occluded but still needs to be visible.
								//We process transucent units twice (also in m_translucentObjectsBuffer) because we need to see them when occluded.
								m_potentialOccludees[m_numPotentialOccludees++]=robj;
								drawInfo->m_flags |= DrawableInfo::ERF_POTENTIAL_OCCLUDEE;
							}
							else
							if (drawInfo->m_flags == DrawableInfo::ERF_IS_NORMAL && m_numNonOccluderOrOccludee < TheGlobalData->m_maxVisibleNonOccluderOrOccludeeObjects)
							{	//regular object with no custom effects but still needs to be delayed to get the occlusion feature to work correctly.
								//Make sure this object is not translucent so it's not rendered twice (from m_potentialOccluders and m_translucentObjectsBuffer)
								if (drawInfo->m_flags ^ DrawableInfo::ERF_IS_TRANSLUCENT)	//make sure not translucent
									m_nonOccludersOrOccludees[m_numNonOccluderOrOccludee++]=robj;
								drawInfo->m_flags |= DrawableInfo::ERF_IS_NON_OCCLUDER_OR_OCCLUDEE;
							}
						}
					}
				}

				robj->Set_Visible(isVisible);
			}

			///@todo: We're not using LOD yet so I disabled this code. MW
			// Also, should check how multiple passes (reflections) get along
			// with the LOD manager - we're rendering double the load it thinks we are.
			// Prepare visible objects for LOD:
			//	if (robj->Is_Really_Visible()) {
			//			robj->Prepare_LOD(*camera);
			//		}
		}
	}

   Visibility_Checked = true;
}

//============================================================================
// RTS3DScene::renderSingleDrawable
//=============================================================================
/** Renders a single drawable entity. */
//=============================================================================
// ?RTS3DScene::renderSpecificDrawables present-unmatched
void RTS3DScene::renderSpecificDrawables(RenderInfoClass &rinfo, Int numDrawable, Drawable **theDrawables)
{
#ifdef DIRTY_CONDITION_FLAGS
	StDrawableDirtyStuffLocker lockDirtyStuff;
#endif
	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
	RefRenderObjListIterator it(&UpdateList);	
	// loop through all render objects in the list:
	for (it.First(&RenderList); !it.Is_Done();) 
	{
		RenderObjClass *robj;
		// get the render object
		robj = it.Peek_Obj();

		it.Next();	//advance to next object in case this one gets deleted during renderOneObject().

		DrawableInfo *drawInfo = (DrawableInfo *)robj->Get_User_Data();
		Drawable *draw=NULL;
		if (drawInfo)
			draw = drawInfo->m_drawable;
		if (!draw) continue;
		Bool match = false;
		for (Int i = 0; i<numDrawable; i++) {
			if (theDrawables[i] == draw) {
				match = true;
				break;
			}
		}
		if (match) {
			renderOneObject(rinfo, robj, localPlayerIndex);
		}
	}
}

//============================================================================
// RTS3DScene::renderOneObject
//=============================================================================
/** Renders a single drawable entity. */
//=============================================================================
// Unit-local view with the header's Set_Output_Ambient body: the inlined call left an
// unreferenced Zero Hour-layout (+0x160) Set_Output_Ambient COMDAT that the link kept
// ahead of retail's 0x0006E136; this by-product gets a name of its own.
struct W3DSceneLightEnv : public LightEnvironmentClass
{
	void setOutputAmbient(Vector3 &oa) { OutputAmbient = oa; }
};

// ?RTS3DScene::renderOneObject present-unmatched
void RTS3DScene::renderOneObject(RenderInfoClass &rinfo, RenderObjClass *robj, Int localPlayerIndex)
{

	Drawable *draw = NULL;
	DrawableInfo *drawInfo = NULL;
	Bool drawableHidden=FALSE;
	Object* obj = NULL;
	ObjectShroudStatus ss=OBJECTSHROUD_INVALID;
	Bool doExtraMaterialPop=FALSE;
	Bool doExtraFlagsPop=FALSE;
	LightClass **sceneLights=m_globalLight;



	if (robj->Class_ID() == RenderObjClass::CLASSID_IMAGE3D	)
	{	robj->Render(rinfo);	//notify decals system that this track is visible
		return;	//decals are not lit by this system yet so skip rest of lighting
	}

	LightEnvironmentClass lightEnv;
	SphereClass sph = robj->Get_Bounding_Sphere();
	drawInfo = (DrawableInfo *)robj->Get_User_Data();
	if (drawInfo)
	{	draw = drawInfo->m_drawable;
		//If we have a drawInfo but not drawable, we must be dealing with
		//a ghost object which is always fogged.
		if (!draw)
			ss = OBJECTSHROUD_FOGGED;
	}

	// all this ambient business no longer handles the tinting and flashing stuff,
	// but it does still light the drawable explicitly, and can be fudged like this
	// infantry test does, here...
	// the tint has been delegated to the getTint() stuff, below... MLorenzen
	Vector3 ambient = Get_Ambient_Light();
	if (draw && (drawableHidden=draw->isDrawableEffectivelyHidden()) != TRUE)
	{
#ifdef NOT_IN_USE
		const Vector3* drawAmbient = draw->getAmbientLight();
		if (drawAmbient)
			ambient.Add(ambient, *drawAmbient, &ambient);
#endif
		obj = draw->getObject();
		if (obj) {
			ss = obj->getShroudedStatus(localPlayerIndex);
			// For objects like planes, that pop out of the shroud, fire, then head back, 
			// we keep drawing them for 2 seconds after they return to the fogged area, 
			// so the player can see them and missiles chasing them.  jba.
			if (ss == OBJECTSHROUD_CLEAR) {
				draw->setShroudClearFrame(TheGameLogic->getFrame());
			}	else if (ss >= OBJECTSHROUD_FOGGED && draw->getShroudClearFrame()!=0) {
				UnsignedInt limit = 2*LOGICFRAMES_PER_SECOND;
				if (obj->isEffectivelyDead()) {
					limit += 3*LOGICFRAMES_PER_SECOND;
				}
				if (TheGameLogic->getFrame() < limit + draw->getShroudClearFrame()) {
					// It's been less than 2 seconds since we could see them clear, so keep showing them.
					ss = OBJECTSHROUD_PARTIAL_CLEAR;
				}
			}
 			if (!robj->Peek_Scene())
 				return;	//this object was removed by the getShroudedStatus() call.
		}
		else
		{	//drawable with no object so no way to know if it's shrouded.
			ss = OBJECTSHROUD_CLEAR;	//assume not shrouded/fogged.
			//Check to see if there is another unrelated object which controls the shroud status
			//(Hack for prison camps which contain enemy prisoner drawables)
			if (drawInfo->m_shroudStatusObjectID != INVALID_ID)
			{	Object *shroudObject=TheGameLogic->findObjectByID(drawInfo->m_shroudStatusObjectID);
				if (shroudObject && shroudObject->getShroudedStatus(localPlayerIndex) >= OBJECTSHROUD_FOGGED)
					ss = OBJECTSHROUD_SHROUDED;	//we will assume that drawables without objects are 'particle' like and therefore don't need drawing if fogged/shrouded.
			}
		}

		if (draw->isKindOf(KINDOF_INFANTRY))
		{	//ambient = m_infantryAmbient;  //has no effect - see comment on m_infantryAmbient
			sceneLights = m_infantryLight;
		}

		lightEnv.Reset(sph.Center, ambient);


		// HANDLE THE SPECIAL DRAWABLE-LEVEL COLORING SETTINGS FIRST

		const Vector3 *tintColor = NULL;
		const Vector3 *selectionColor = NULL;

		tintColor			 = draw->getTintColor();
		selectionColor = draw->getSelectionColor();

		if ( tintColor || selectionColor )
		{
			Vector3 sumTint, temp, restore;
			
			sumTint.Set(0,0,0); 
			
			if (tintColor)
				Vector3::Add(sumTint, *tintColor, &sumTint);
			if (selectionColor)
				Vector3::Add(sumTint, *selectionColor, &sumTint);

			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
			{
				sceneLights[globalLightIndex]->Get_Diffuse( &temp );
				restore = temp;

				Vector3::Add(temp, sumTint, &temp);

				sceneLights[globalLightIndex]->Set_Diffuse( temp );
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
				sceneLights[globalLightIndex]->Set_Diffuse( restore );

			} // next light
			
			temp = lightEnv.Get_Equivalent_Ambient();
			Vector3::Add(sumTint, temp, &temp );

			static_cast<W3DSceneLightEnv &>(lightEnv).setOutputAmbient( temp );

		}
		else // no funny coloring going on, so just add the lights normally
		{
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
			{
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
			}
		}

		//Apply custom render pass for any drawables with heatvision enabled
		if (draw->getSecondMaterialPassOpacity() != 0 ) 
		{
			rinfo.materialPassEmissiveOverride = draw->getSecondMaterialPassOpacity();

      //if ( draw->testTintStatus( TINT_STATUS_FRENZY ) )
      //{
			//	rinfo.Push_Material_Pass(m_heatVisionMaterialPass);
      //}
			//else 
      if (draw->getStealthLook() == STEALTHLOOK_VISIBLE_DETECTED )
			{
			  rinfo.materialPassEmissiveOverride = draw->getSecondMaterialPassOpacity();
				// THIS WILL EXPLICITLY SKIP THE FIRST PASS SO THAT HEATVISION ONLY WILL RENDER
				rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);
				rinfo.Push_Material_Pass(m_heatVisionOnlyPass);
        doExtraFlagsPop = TRUE;
			}
			else
			{
				//THIS CALLS FOR THE HEATVISION TO RENDER
			  rinfo.materialPassEmissiveOverride = draw->getSecondMaterialPassOpacity();
				rinfo.Push_Material_Pass(m_heatVisionMaterialPass);
			}

			doExtraMaterialPop = TRUE;
		}
	}
	else
	{	//either no drawable or it is hidden
		if (drawableHidden)
			return;	//don't bother with anything else

		//Render object without a drawable.  Must be either some fluff/debug object or a ghostObject.
		if (ss == OBJECTSHROUD_FOGGED)
		{	//Must be ghost object because we don't fog normal things.  Fogged objects always have a predefined
			//lighting environment applied which emulates the look of fog.
			rinfo.light_environment = &m_foggedLightEnv;
			robj->Render(rinfo);
			rinfo.light_environment = NULL;
			return;
		}
		else
		{	lightEnv.Reset(sph.Center, ambient);
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				lightEnv.Add_Light(*m_globalLight[globalLightIndex]);
		}
	}

	if (!drawableHidden)
	{
		//standard scene lights
		RefRenderObjListIterator it2(&LightList);	
		for (it2.First(); !it2.Is_Done(); it2.Next())
		{	
			LightClass *pLight = (LightClass*)it2.Peek_Obj();
			SphereClass lSph = pLight->Get_Bounding_Sphere();
			Bool cull = (pLight->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph));
			if (!cull) {
				lightEnv.Add_Light(*pLight);
			}
		}

    if( draw && draw->getReceivesDynamicLights() )
    {
		  // dynamic lights
		  RefRenderObjListIterator dynaLightIt(&m_dynamicLightList);	
		  for (dynaLightIt.First(); !dynaLightIt.Is_Done(); dynaLightIt.Next())
		  {	
			  W3DDynamicLight* pDyna = (W3DDynamicLight*)dynaLightIt.Peek_Obj();
			  if (!pDyna->isEnabled()) {
				  continue;
			  }
			  SphereClass lSph = pDyna->Get_Bounding_Sphere();
			  if (pDyna->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph)) {
				  continue;
			  }
			  lightEnv.Add_Light(*(LightClass*)dynaLightIt.Peek_Obj());
		  }
    }
		
		lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		rinfo.light_environment = &lightEnv;

		if (drawInfo)
		{
#if defined(_DEBUG) || defined(_INTERNAL)
			if (!TheGlobalData->m_shroudOn)
				ss = OBJECTSHROUD_CLEAR;
#endif
			
			if (m_customPassMode == SCENE_PASS_DEFAULT)	
			{
				if (ss <= OBJECTSHROUD_CLEAR)
					robj->Render(rinfo);
				else
				{	
						rinfo.Push_Material_Pass(m_shroudMaterialPass);
						robj->Render(rinfo);
						rinfo.Pop_Material_Pass();
				}
			}
			else
			if (m_maskMaterialPass)
			{	rinfo.Push_Material_Pass(m_maskMaterialPass);
				rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);
				robj->Render(rinfo);
				rinfo.Pop_Override_Flags();
				rinfo.Pop_Material_Pass();
			}
		}//drawInfo exists so rendering a drawable.
		else
		{
			robj->Render(rinfo);
		}
	}//drawable or robj is not hidden

	rinfo.light_environment = NULL;
	if (doExtraMaterialPop)	//check if there is an extra material on the stack from the add'l material effect.
		rinfo.Pop_Material_Pass();
	if (doExtraFlagsPop)
		rinfo.Pop_Override_Flags();	//flags used to disable base pass and only render custom heat vision pass.
}

//DECLARE_PERF_TIMER(translucentRender)

/**Draw everything that was submitted from this scene*/

/**Generate a predefined light environment(s) that will be applied to many objects.  Useful for things like totally fogged
objects and most generaic map objects that are not lit by dynamic lights.*/
// RTS3DScene::updateFixedLightEnvironments (retail 0x0006E716) lives in
// W3DSceneUpdateFixedLightEnvironments.cpp: BFME 2 builds it at /O1, unlike
// this unit's /O2 rows, and it differs from the Zero Hour body.

/**Generate custom rendering passes for each potential player color.  This is currently only used
to render occluded objects using the color of the player*/
// ?RTS3DScene::updatePlayerColorPasses present-unmatched
void RTS3DScene::updatePlayerColorPasses(void)
{
#ifdef USE_NON_STENCIL_OCCLUSION
	Vector3 hsv,rgb;

	if (TheGlobalData->m_enableBehindBuildingMarkers && TheGameLogic->getShowBehindBuildingMarkers())
	{
		Int numPlayers=ThePlayerList->getPlayerCount();

		for (Int i=0; i<numPlayers; i++)
		{	Player *player=ThePlayerList->getNthPlayer(i);
			Int playerIndex=player->getPlayerIndex();
			Real red,green,blue,alpha;
			GameGetColorComponentsReal(player->getPlayerColor(),&red,&green,&blue,&alpha);
			RGB_To_HSV(hsv,Vector3(red,green,blue));
			hsv.Z*=TheGlobalData->m_occludedLuminanceScale;
			HSV_To_RGB(rgb,hsv);
			VertexMaterialClass *vmat=m_occludedMaterialPass[playerIndex]->Peek_Material();
			vmat->Set_Emissive(rgb);
		}
	}
#endif
}

#define ZBias 0.0001f

//DECLARE_PERF_TIMER(NonTerrainRender)

//=============================================================================
// RTS3DScene::Customized_Renderer
//=============================================================================
/** Custom render method for the RTS3DScene, custom render properties for our
  * particular game go here */
//=============================================================================
// ?RTS3DScene::Customized_Render present-unmatched
void RTS3DScene::Customized_Render( RenderInfoClass &rinfo )
{
#ifdef DIRTY_CONDITION_FLAGS
	StDrawableDirtyStuffLocker lockDirtyStuff;
#endif

	RenderObjClass *terrainObject=NULL,*robj;
	m_translucentObjectsCount = 0;	//start of new frame so no translucent objects
	m_occludedObjectsCount = 0;

	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

#define USE_LIGHT_ENV 1

   if (!Visibility_Checked) {
      // set the visibility bit in all render objects in all layers.
	   Visibility_Check(&rinfo.Camera);
#ifdef USE_NON_STENCIL_OCCLUSION
	   flagOccludedObjects(&rinfo.Camera);
#endif
   }
   Visibility_Checked = false;	
	

	RefRenderObjListIterator it(&UpdateList);	
	// allow all objects in the update list to do their "every frame" processing
	for (it.First(); !it.Is_Done(); it.Next()) {
		RenderObjClass * robj = it.Peek_Obj();
		if (robj->Class_ID() == RenderObjClass::CLASSID_TILEMAP)
			terrainObject=robj;	//found terrain object, store for later.
		if (!ShaderClass::Is_Backface_Culling_Inverted()) {
			// If we are doing water mirror, we draw with backface culling inverted.  In this case, 
			// we only want to call On_Frame_Update if we aren't drawing water, as otherwise
			// we get 2 frame updates per frame, and it screws up the particle emitters.
			it.Peek_Obj()->On_Frame_Update();
		}
	}

	//terrain needs to be rendered first
	if (terrainObject)	// Don't check visibility - terrain is always visible. jba.
	{		
		robj=terrainObject;
		rinfo.light_environment = NULL;		// Terrain is self lit.
		rinfo.Camera.Set_User_Data(this);	//pass the scene to terrain via user data.
		if (m_customPassMode == SCENE_PASS_DEFAULT && m_shroudMaterialPass)
		{
			rinfo.Push_Material_Pass(m_shroudMaterialPass);
			robj->Render(rinfo);
			rinfo.Pop_Material_Pass();
		}
		else
		if (m_customPassMode == SCENE_PASS_ALPHA_MASK && m_maskMaterialPass)
		{
			rinfo.Push_Material_Pass(m_maskMaterialPass);
			robj->Render(rinfo);
			rinfo.Pop_Material_Pass();
		}
		else
		robj->Render(rinfo);
	}

	if (m_drawTerrainOnly) {
		return;
	}
#ifdef EXTENDED_STATS
	if (DX8Wrapper::stats.m_disableObjects) { 
		return;
	}
#endif

	// loop through all render objects in the list:
	for (it.First(&RenderList); !it.Is_Done();) 
	{

		// get the render object
		robj = it.Peek_Obj();
 		it.Next();	//advance to next object in case this one gets deleted during renderOneObject().

		if (robj->Class_ID() == RenderObjClass::CLASSID_TILEMAP)
			continue;	//we already rendered terrain

		if (robj->Is_Really_Visible()) {
			DrawableInfo *drawInfo = (DrawableInfo *)robj->Get_User_Data();
			Drawable *draw=NULL;
			if (drawInfo)
				draw = drawInfo->m_drawable;
#ifdef USE_NON_STENCIL_OCCLUSION
			if (!(draw && drawInfo->m_flags & DrawableInfo::ERF_DELAYED_RENDER))	//model rendering is delayed for some reason until end of normal scene
#else
			if (!(draw && drawInfo->m_flags & (DrawableInfo::ERF_DELAYED_RENDER|DrawableInfo::ERF_POTENTIAL_OCCLUDER|DrawableInfo::ERF_IS_NON_OCCLUDER_OR_OCCLUDEE)))	//in this mode we delay almost all objects in order to do correct sorting with stencil.
#endif
				renderOneObject(rinfo, robj, localPlayerIndex);
		}
	}

#ifdef	INCLUDE_GRANNY_IN_BUILD
	if (TheGrannyRenderObjSystem)
	{	//we only want to update granny animations once per frame, so only queue
		//them up if this is not a mirror pass.
		if (!ShaderClass::Is_Backface_Culling_Inverted())
			TheGrannyRenderObjSystem->queueUpdate();
		TheGrannyRenderObjSystem->Flush();
	}
#endif
	
	//Tell shadow manager to render shadows at the end of this frame
	//Don't draw shadows if there is no terrain present.
	if (TheW3DShadowManager && terrainObject && !ShaderClass::Is_Backface_Culling_Inverted() &&
		Get_Extra_Pass_Polygon_Mode() == EXTRA_PASS_DISABLE)
		TheW3DShadowManager->queueShadows(TRUE);

	// only render particles once per frame
	if (terrainObject != NULL && TheParticleSystemManager != NULL &&
		Get_Extra_Pass_Polygon_Mode() == EXTRA_PASS_DISABLE)
	{	TheParticleSystemManager->queueParticleRender();
	}

}  // end Customized_Renderer

/**Convert a player index to a color index, we use this because color indices are
assigned in left-right binary flipped fashion so as not to occupy lower bits unless
necessary.  This is used because lower bits are free for use by stencil shadow
rendering*/
#define NUMBER_PLAYER_COLOR_BITS 4	//need 4 bits to encode 8 players because indices start at 1 (not 0).
Int playerIndexToColorIndex(Int playerIndex)
{
	Int tmp=playerIndex;
	Int result=0;
	Int flippedPosition;

	//Player index is stored in 4 bits
	for (Int i=0; i<NUMBER_PLAYER_COLOR_BITS; i++)
	{
		flippedPosition = NUMBER_PLAYER_COLOR_BITS-1-i;	//correct position of bit after it's flipped left/right

		if (flippedPosition > i)
		{	//shifting left
			result |= (tmp & (1<<i))<<(flippedPosition-i);
		}
		else
		{	//shifting right
			result |= (tmp & (1<<i))>>(i-flippedPosition);
		}
	}
	return result;
}

/**Utility function used to render a full screen quad with the specified color and
stencil mask*/
void renderStenciledPlayerColor( UnsignedInt color, UnsignedInt stencilRef, Bool clear=FALSE)
{
	struct _TRANSLITVERTEX {
	    Vector4 p;
		DWORD color;   // diffuse color    
	} v[4];

	Int xpos, ypos, width, height;

	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

    v[0].p.Set(xpos+width, ypos+height, 0.0f, 1.0f );
    v[1].p.Set(xpos+width, 0, 0.0f, 1.0f );
    v[2].p.Set(xpos, ypos+height, 0.0f, 1.0f );
    v[3].p.Set(xpos,  0, 0.0f, 1.0f );
    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

	DX8Wrapper::Set_Shader(PlayerColorShader);
	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);
	DX8Wrapper::Apply_Render_State_Changes();	//force update all renderstates

	LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();

	if (!m_pDev)
		return;	//need device to render anything.

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	m_pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// Set stencil states
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, TRUE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE );
	DWORD	oldColorWriteEnable=0x12345678;
	if (clear)
	{	//we want to clear the stencil buffer to some known value whereever a player index is stored
		Int occludedMask=TheW3DShadowManager->getStencilShadowMask();
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      0x80808080 );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,     occludedMask );	//isolate bits containing occluder|playerIndex
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,  D3DCMP_LESS );	//only draw to pixels that match the reference value
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE );	
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,  D3DSTENCILOP_REPLACE );	//pixels which had occluded player colors, get MSB set.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,  D3DSTENCILOP_ZERO );	//pixels which had no occluded player colors are cleared.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_NEVER  );	//fail all access to the frame buffer to improve memory bandwidth

		//disable writes to color buffer
		if (DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().PrimitiveMiscCaps & D3DPMISCCAPS_COLORWRITEENABLE)
		{	DX8Wrapper::_Get_D3D_Device8()->GetRenderState(D3DRS_COLORWRITEENABLE, &oldColorWriteEnable);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,0);
		}
		else
		{	//device does not support disabling writes to color buffer so fake it through alpha blending
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ZERO );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ONE );
		}
	}
	else
	{	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      stencilRef );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,     0xffffffff );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff );	
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,  D3DCMP_EQUAL );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );

		//Make occluded pixels transparent
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
		m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANSLITVERTEX));

	// turn off the stencil buffer
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, FALSE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);	//restore shader state
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ZERO );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	if (oldColorWriteEnable != 0x12345678)
		DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,oldColorWriteEnable);

}  // end renderStencilShadows

#define MAX_VISIBLE_OCCLUDED_PLAYER_OBJECTS	512 //maximum number of occluded objects permitted per player

/*Version which does not require stencil buffer*/
// ?RTS3DScene::flushOccludedObjects present-unmatched
void RTS3DScene::flushOccludedObjects(RenderInfoClass & rinfo)
{
	RenderObjClass *robj;
	Drawable *draw;

	TheW3DShadowManager->setStencilShadowMask(0);

	if (m_occludedObjectsCount)
	{
		Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

		if (DX8Wrapper::Has_Stencil())	//just in case we have shadows, disable them over occluded pixels.
		{
			//Set all stencil pixels of potentially occluded objects to 128.
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, TRUE );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      128 );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,     0xffffffff );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,  D3DSTENCILOP_REPLACE );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,  D3DCMP_ALWAYS );
		}

		//First draw all the solid colored models
		///@todo: Optimize this so that the extra passes don't actually install the material since it's all the same.
		rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);	//disable textures
		for (Int i=0; i<m_occludedObjectsCount; i++)
		{
			robj=m_potentialOccludees[i];

			draw = ((DrawableInfo *)robj->Get_User_Data())->m_drawable;
			Object *object=draw->getObject();

			Int index=object->getControllingPlayer()->getPlayerIndex();

			rinfo.Push_Material_Pass(m_occludedMaterialPass[index]);
			robj->Render(rinfo);
			rinfo.Pop_Material_Pass();
		}
		rinfo.Pop_Override_Flags();
		TheDX8MeshRenderer.Flush();

		//Now draw the normal models so they cover up the colored models on any pixels that

		//Now draw the normal models so they cover up the colored models on any pixels that
		//Normal models will clear stencil value from 128 back to 0 where the object pixels are
		//not occluded but will leave  128 in stencil where still occluded.
		if (DX8Wrapper::Has_Stencil())
			DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      0 );

		for (i=0; i<m_occludedObjectsCount; i++)
		{
			robj=m_potentialOccludees[i];
			renderOneObject(rinfo, robj, localPlayerIndex);//WW3D::Render(*robj,rinfo);
		}

		//Flush all the submitted translucent objects.
		TheDX8MeshRenderer.Flush();
		m_occludedObjectsCount = 0;
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, FALSE );
		TheW3DShadowManager->setStencilShadowMask(0x80808080);	//upper MSB always contains flag indicating occluded player color.
	}

	//Reset scene ambient because we sometimes mess around with it to make objects
	//glow, etc. when processing drawables.  This is a good place to do it because this
	//function gets called right after we flush regular render objects.
	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENT,DX8Wrapper::Convert_Color(this->Get_Ambient_Light(),0.0f));
}

// ?RTS3DScene::flushTranslucentObjects present-unmatched
void RTS3DScene::flushTranslucentObjects(RenderInfoClass & rinfo)
{
	RenderObjClass *robj;
	Drawable *draw;

	if (m_translucentObjectsCount)
	{
		Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

		for (Int i=0; i<m_translucentObjectsCount; i++)
		{
			robj=m_translucentObjectsBuffer[i];
			draw = ((DrawableInfo *)robj->Get_User_Data())->m_drawable;

			rinfo.alphaOverride = draw->getEffectiveOpacity();

			renderOneObject(rinfo, robj, localPlayerIndex);//WW3D::Render(*robj,rinfo);
		}

		//Flush all the submitted translucent objects.
		TheDX8MeshRenderer.Flush();
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);	//draws things like water
		rinfo.alphaOverride = 1.0f;	//disable forced alpha
		m_translucentObjectsCount = 0;
	}

	//Reset scene ambient because we sometimes mess around with it to make objects
	//glow, etc. when processing drawables.  This is a good place to do it because this
	//function gets called right after we flush regular render objects.
	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENT,DX8Wrapper::Convert_Color(this->Get_Ambient_Light(),0.0f));
}

//=============================================================================
// RTS3DScene::createLightsIterator
//=============================================================================
/** Returns an iterator of the lights in the scene. */
//=============================================================================
// RTS3DScene::createLightsIterator: defined in RTS3DScene_createLightsIterator.cpp (its row's unit).


//=============================================================================
// RTS3DScene::destroyLightsIterator
//=============================================================================
/** Destroys the iterator returned by createLightsIterator. */
//=============================================================================
// ?RTS3DScene::destroyLightsIterator present-unmatched
void RTS3DScene::destroyLightsIterator(RefRenderObjListIterator * it)
{
	delete it;
}


//=============================================================================
// RTS3DScene::addDynamicLight
//=============================================================================
/** Adds a dynamic light. */
//=============================================================================
// ?RTS3DScene::addDynamicLight present-unmatched
void RTS3DScene::addDynamicLight(W3DDynamicLight * obj)
{
	m_dynamicLightList.Add(obj);
	UpdateList.Add(obj);
}

//=============================================================================
// RTS3DScene::addDynamicLight
//=============================================================================
/** Adds a dynamic light. */
//=============================================================================
// ?RTS3DScene::getADynamicLight present-unmatched
W3DDynamicLight * RTS3DScene::getADynamicLight(void)
{
		RefRenderObjListIterator dynaLightIt(&m_dynamicLightList);
		W3DDynamicLight *pLight;
		for (dynaLightIt.First(); !dynaLightIt.Is_Done(); dynaLightIt.Next())
		{		
			pLight = (W3DDynamicLight*)dynaLightIt.Peek_Obj();
			if (!pLight->isEnabled()) {
				pLight->setEnabled(true);
				return(pLight);
			}
		}
		pLight = NEW_REF(W3DDynamicLight, ());
		addDynamicLight( pLight );
		pLight->Release_Ref();
		pLight->setEnabled(true);
		return(pLight);
}

//=============================================================================
// RTS3DScene::removeDynamicLight
//=============================================================================
/** Removes a dynamic light. */
//=============================================================================
// ?RTS3DScene::removeDynamicLight present-unmatched
void RTS3DScene::removeDynamicLight(W3DDynamicLight * obj)
{
	m_dynamicLightList.Remove(obj);
}

//=============================================================================
// RTS3DScene::doRender
//=============================================================================
/** Render the scene */
//=============================================================================
// RTS3DScene::doRender is rowed at 0x0006ED36 (Rva0006ED36Call.cpp); the Zero Hour copy
// here was a second definition.

//=============================================================================
// RTS3DScene::draw
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================
// ?RTS3DScene::draw present-unmatched
void RTS3DScene::draw( )
{

	if (m_camera == NULL) {
		DEBUG_CRASH(("Null m_camera in RTS3DScene::draw"));
		return;
	}
	WW3D::Render( this, m_camera );


}  // end Customized_Render


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
// RTS2DScene::RTS2DScene
//=============================================================================
/** */
//=============================================================================
// ?RTS2DScene::RTS2DScene present-unmatched
RTS2DScene::RTS2DScene()
{
	// BFME2's SubsystemInterface::setName (retail 0x0006F3CC, rowed in
	// SubsystemInterfaceSetName.cpp) keeps m_name at +0x08; this Zero Hour
	// view has it at +0x04, so calling it emitted a wrong out-of-line copy
	// that the link kept first. The BFME2 ctor is rowed in RTS2DSceneCtor.cpp.
	m_name = AsciiString("RTS2DScene");
	m_status = NEW_REF( W3DStatusCircle, () );
	Add_Render_Object( m_status );
}  // end RTS2DScene

//=============================================================================
// RTS2DScene::~RTS2DScene
//=============================================================================
/** */
//=============================================================================
// ?RTS2DScene::~RTS2DScene present-unmatched
RTS2DScene::~RTS2DScene()
{
	this->Remove_Render_Object(m_status);
	REF_PTR_RELEASE(m_status);
}  // end ~RTS2DScene

//=============================================================================
// RTS2DScene::Custimized_Render
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================
// ?RTS2DScene::Customized_Render present-unmatched
void RTS2DScene::Customized_Render( RenderInfoClass &rinfo )
{

	// call simple scene class renderer
	SimpleSceneClass::Customized_Render( rinfo );

}  // end Customized_Render

//=============================================================================
// RTS2DScene::doRender
//=============================================================================
/** Render the scene */
//=============================================================================
// RTS2DScene::doRender is rowed at 0x0006EE27 (Rva0006ED36Call.cpp); the Zero Hour copy
// here was a second definition.

//=============================================================================
// RTS2DScene::draw
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================
// ?RTS2DScene::draw present-unmatched
void RTS2DScene::draw( )
{

	if (m_camera == NULL) {
		DEBUG_CRASH(("Null m_camera in RTS2DScene::draw"));
		return;
	}
	WW3D::Render( this, m_camera );


}  // end Customized_Render



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
// RTS3DInterfaceScene::RTS3DInterfaceScene
//=============================================================================
/** */
//=============================================================================
// ?RTS3DInterfaceScene::RTS3DInterfaceScene present-unmatched
RTS3DInterfaceScene::RTS3DInterfaceScene()
{
}  // end RTS3DInterfaceScene

//=============================================================================
// RTS3DInterfaceScene::~RTS3DInterfaceScene
//=============================================================================
/** */
//=============================================================================
// ?RTS3DInterfaceScene::~RTS3DInterfaceScene present-unmatched
RTS3DInterfaceScene::~RTS3DInterfaceScene()
{
}  // end ~RTS3DInterfaceScene

//=============================================================================
// RTS3DInterfaceScene::Custimized_Render
//=============================================================================
/** Customized render for the 3d interface scene management */
//=============================================================================
// ?RTS3DInterfaceScene::Customized_Render present-unmatched
void RTS3DInterfaceScene::Customized_Render( RenderInfoClass &rinfo )
{

	// call simple scene class renderer
	SimpleSceneClass::Customized_Render( rinfo );

}  // end Customized_Render



/// The following is an :archive" of a partial attempt at detecting the mapshroud hack
/*
 *
	


 *
 */

