// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp); this unit had no counterpart under Code/.
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

// FILE: W3DGhostObject.cpp /////////////////////////////////////////////////////
//
// Placeholder for objects that have been deleted but need to be maintained because
// a player can see them fogged.
//
// Author: Mark Wilczynski, August 2002
///////////////////////////////////////////////////////////////////////////////

#include "rendobj.h"	// bfmerendobj shim wins RENDOBJ_H: retail ObjectScale@0x48 (ZH has no pre-Transform pad, reads +0x4C)
#include "Common/Debug.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameLogic/W3DGhostObject.h"
#include "WW3D2/rendobj.h"
#include "WW3D2/hlod.h"
#include "WW3D2/Scene.h"
#include "WW3D2/matinfo.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

/**This class will hold all information about a W3D RenderObject needed to
reconstruct it if necessary*/
class W3DRenderObjectSnapshot : public Snapshot
{
	friend W3DGhostObject;

	W3DRenderObjectSnapshot(RenderObjClass *m_parentRobj, DrawableInfo *drawInfo, Bool cloneParentRobj = TRUE);
	~W3DRenderObjectSnapshot() {REF_PTR_RELEASE(m_robj);}
	inline void update(RenderObjClass *robj, DrawableInfo *drawInfo, Bool cloneParentRobj=TRUE);	///<refresh the current snapshot with latest state
	inline void addToScene(void);	///< add this fogged renderobject to the scene.
protected:

	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

#ifdef DEBUG_FOG_MEMORY
	const char *m_robjName;		///<debug pointer so we know what this is a snapshot of.
#endif
	RenderObjClass *m_robj;		///<render object representing state at time of snapshot
	W3DRenderObjectSnapshot *m_next;	///<snapshot of next render object belonging to same drawable
};

//Dummy material override which we assign to all ghost objects to disable their
//texture animation.
static RenderObjClass::Material_Override animationDisableOverride;

//Helper function used to disable all UV mapper animations on a given model.
//Also use this pass to disable muzzle effects.
// ?disableUVAnimations@@YAXPAVRenderObjClass@@@Z is rowed in its own unit; this copy collided with it.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?W3DRenderObjectSnapshot::addToScene present-unmatched
void W3DRenderObjectSnapshot::addToScene(void)
{
	((SimpleSceneClass *)W3DDisplay::m_3DScene)->Add_Render_Object(m_robj);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0W3DRenderObjectSnapshot@@AAE@PAVRenderObjClass@@PAUDrawableInfo@@_N@Z is rowed in its own unit; this copy collided with it.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?W3DRenderObjectSnapshot::crc present-unmatched
void W3DRenderObjectSnapshot::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?W3DRenderObjectSnapshot::xfer present-unmatched
void W3DRenderObjectSnapshot::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// sanity
	DEBUG_ASSERTCRASH( m_robj, ("W3DRenderObjectSnapshot::xfer - invalid m_robj\n") );

	// transform on the main render object
	Matrix3D transform;
	transform = m_robj->Get_Transform();
	xfer->xferUser( &transform, sizeof( Matrix3D ) );
	if( xfer->getXferMode() == XFER_LOAD )
		m_robj->Set_Transform( transform );

	// how many sub objects of data will follow
	Int subObjectCount = m_robj->Get_Num_Sub_Objects();
	xfer->xferInt( &subObjectCount );

	Bool visible;
	RenderObjClass *subObject;
	AsciiString subObjectName;
	for( Int i = 0; i < subObjectCount; ++i )
	{

		//
		// when saving we get sub objects by index and xfer their name, when loading
		// we read the name and find that sub object
		//
		if( xfer->getXferMode() == XFER_SAVE )
		{

			// get sub object
			subObject = m_robj->Get_Sub_Object( i );

			// xfer sub object name which is unique among those in this render object
			subObjectName.set( subObject->Get_Name() );
			xfer->xferAsciiString( &subObjectName );

		}  // end if, save
		else
		{

			// read sub object name
			xfer->xferAsciiString( &subObjectName );

			// find this sub object on the object
			subObject = m_robj->Get_Sub_Object_By_Name( subObjectName.str() );

		}  // end else load

		//
		// NOTE that the remainder of this xfer code works on a sub object only *if*
		// it is present.  It is possible that in future patches we change the artwork
		// for some objects which could remove sub objects for which we have data saved
		// for in the save game file.  If we encounter data in the save file for 
		// sub objects that are no longer in the artwork we just read the data and
		// throw it away
		//

		// visible/hidden status of this sub object
		if( subObject )
			visible = subObject->Is_Not_Hidden_At_All();
		xfer->xferBool( &visible );
		if( subObject && xfer->getXferMode() == XFER_LOAD )
			subObject->Set_Hidden( !visible );

		// transform of this sub object
		if( subObject )
			transform = subObject->Get_Transform();
		xfer->xferUser( &transform, sizeof( Matrix3D ) );
		if( subObject && xfer->getXferMode() == XFER_LOAD )
			subObject->Set_Transform( transform );

		// need to tell W3D that this sub object transforms are ok
		if( subObject )
		{

			// need to cast to HLod if we can to validate the hierarchy
			if( subObject->Class_ID() == RenderObjClass::CLASSID_HLOD )
				((HLodClass *)subObject)->Friend_Set_Hierarchy_Valid( TRUE );

		}  // end if

		// release reference to sub object
		if( subObject )
			REF_PTR_RELEASE( subObject );

	}  // end for, i

	// tell W3D that the transforms for our sub objects are all OK cause we've done them ourselves
	m_robj->Set_Sub_Object_Transforms_Dirty( FALSE );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?W3DRenderObjectSnapshot::loadPostProcess present-unmatched
void W3DRenderObjectSnapshot::loadPostProcess( void )
{

}  // end loadPostProcess

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0W3DGhostObject@@QAE@XZ is rowed in its own unit; this copy collided with it.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1W3DGhostObject@@UAE@XZ is rowed in its own unit; this copy collided with it.

// ------------------------------------------------------------------------------------------------
/** Record the current state of the renderobjects used by this parent object
so we can display cached state when player is looking at fogged object.
Should only be called when object enters the fogged state.*/
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Remove the original object from our 3D scene*/
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
/** Reinsert the original object into our 3D scene*/
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
/** Player has unfogged the object so he no longer needs the snapshot*/
// ------------------------------------------------------------------------------------------------
// W3DGhostObject::freeSnapShot is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp (0x00063A1D).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObject::updateParentObject present-unmatched
void W3DGhostObject::updateParentObject(Object *object, PartitionData *mod)
{
	m_parentObject = object;
	m_partitionData = mod;
}

// ------------------------------------------------------------------------------------------------
/**Remove the dummy render objects from scene that belong to given player*/
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
/**Add the dummy render objects to scene so player sees the correct version within the fog*/
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObject::release present-unmatched
void W3DGhostObject::release(void)
{
	W3DRenderObjectSnapshot *snap,*nextSnap;

	for (Int i=0; i<MAX_PLAYER_COUNT; i++)
	{	snap = m_parentSnapshots[i];
		while (snap)
		{
			nextSnap=snap->m_next;
			delete snap;
			snap=nextSnap;
		}
		m_parentSnapshots[i]=NULL;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObject::crc present-unmatched
void W3DGhostObject::crc( Xfer *xfer )
{

	// extend base class
	GhostObject::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObject::loadPostProcess present-unmatched
void W3DGhostObject::loadPostProcess( void )
{

	// extend base class
	GhostObject::loadPostProcess();

}  // end loadPostProcess

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
W3DGhostObjectManager::W3DGhostObjectManager(void)
{

	m_freeModules = NULL;
	m_usedModules = NULL;
	
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1W3DGhostObjectManager@@UAE@XZ is rowed in its own unit; this copy collided with it.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::removeGhostObject present-unmatched
void W3DGhostObjectManager::removeGhostObject(GhostObject *object)
{
	if (!object)
		return;

	W3DGhostObject *mod = (W3DGhostObject *)object;

	mod->freeAllSnapShots();

	// remove module from used list
	if( mod->m_nextSystem )
		mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
	if( mod->m_prevSystem )
		mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
	else
		m_usedModules = mod->m_nextSystem;

	// add module to free list
	mod->m_prevSystem = NULL;
	mod->m_nextSystem = m_freeModules;
	if( m_freeModules )
		m_freeModules->m_prevSystem = mod;
	m_freeModules = mod;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::addGhostObject present-unmatched
GhostObject *W3DGhostObjectManager::addGhostObject(Object *object, PartitionData *pd)
{

	// we disabled adding new ghost objects - used during map border resizing and loading
	if (m_lockGhostObjects || m_saveLockGhostObjects )
		return NULL;

#ifdef DEBUG_FOG_MEMORY
	// sanity
	if( object != NULL )
	{

		W3DGhostObject *sanity = m_usedModules;
		while( sanity )
		{

			DEBUG_ASSERTCRASH( sanity->m_parentObject != object,	
												 ("W3DGhostObjectManager::addGhostObject - Duplicate ghost object detected\n") );
			sanity = sanity->m_nextSystem;

		}  // end while

	}  // end if
#endif

	W3DGhostObject *mod = m_freeModules;
	if( mod )
	{
		// take module off the free list
		if( mod->m_nextSystem )
			mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
		if( mod->m_prevSystem )
			mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
		else
			m_freeModules = mod->m_nextSystem;
	}
	else
	{
		mod = NEW W3DGhostObject;	// poolify
	}

	mod->m_prevSystem = NULL;
	mod->m_nextSystem = m_usedModules;
	if( m_usedModules )
		m_usedModules->m_prevSystem = mod;
	m_usedModules = mod;

	//Copy settings from parent object
	mod->m_parentObject=object;
	mod->m_drawableInfo.m_drawable=NULL;	//these dummy render objects don't have drawables.
	mod->m_drawableInfo.m_ghostObject = mod;
	mod->m_partitionData=pd;

	return mod;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectScene.cpp

// ------------------------------------------------------------------------------------------------
/** When a game object/drawable dies, it is removed from the rest of the engine.  It leaves behind
a GhostObject in case any players didn't see the death and have a fogged view of the pre-death object.
We need to manually determine if these orphaned GhostObjects ever become visible and are no longer
needed*/
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::updateOrphanedObjects present-unmatched
void W3DGhostObjectManager::updateOrphanedObjects(int *playerIndexList, int numNonLocalPlayers)
{

	W3DGhostObject *mod = m_usedModules, *nextmod;
	int numStoredSnapshots;

	while (mod)
	{
		//updating the shroud status of this ghostobject could remove
		//it from the scene if it becomes visible but parent object is gone.
		nextmod=mod->m_nextSystem;
		if (!mod->m_parentObject)
		{	
			numStoredSnapshots=0;
#ifdef DEBUG_FOG_MEMORY
			for (int i=0; i<numNonLocalPlayers; i++, playerIndexList++)
			{
				if (mod->m_parentSnapshots[*playerIndexList])
					mod->getShroudStatus(*playerIndexList);
				if (mod->m_parentSnapshots[*playerIndexList])
					numStoredSnapshots++;
			}
#endif
			mod->getShroudStatus(m_localPlayer);
			if (mod->m_parentSnapshots[m_localPlayer])
					numStoredSnapshots++;
			if (!numStoredSnapshots)
			{	ThePartitionManager->unRegisterGhostObject(mod);
				mod->m_partitionData=NULL;
				removeGhostObject(mod);
			}
		}

		mod=nextmod;
	}
}

// ------------------------------------------------------------------------------------------------
/*When a map border changes (via script) we reset the partition manager.  Since ghost objects are
stored inside the partition manager, we need to save and restore them.  This function will save
enough data to restore the state of the partition manager.*/
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::releasePartitionData present-unmatched
void W3DGhostObjectManager::releasePartitionData(void)
{
	W3DGhostObject *mod = m_usedModules;
	W3DGhostObject *nextmod;

	while (mod)
	{
		nextmod=mod->m_nextSystem;
		//if module has no parent object, then its holding a ghost object which
		//needs to have it's own partition data.
		if (!mod->m_parentObject)
		{
			ThePartitionManager->unRegisterGhostObject(mod);
			mod->m_partitionData = NULL;
		}
		else
		{	//The parent object will handle unregistering so just tell to break the
			//ghost object link.
			mod->friend_getPartitionData()->friend_setGhostObject(NULL);
			mod->m_partitionData = NULL;
		}
		mod=nextmod;
	}
}

// ------------------------------------------------------------------------------------------------
/*Insert ghost objects back into the partition manager*/
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::restorePartitionData present-unmatched
void W3DGhostObjectManager::restorePartitionData(void)
{
	W3DGhostObject *mod = m_usedModules;
	W3DGhostObject *nextmod;

	while (mod)
	{
		nextmod=mod->m_nextSystem;
		//if module has no parent object, then its holding a ghost object which
		//needs to have it's own partition data.
		if (mod->m_parentObject)
		{
			//restore into parent's partition data
			mod->m_parentObject->friend_getPartitionData()->friend_setGhostObject(mod);
			mod->m_partitionData=mod->m_parentObject->friend_getPartitionData();
		}
		else
		{	
			//restore into our own partition data
			ThePartitionManager->registerGhostObject(mod);
		}

		//set partition data to reflect that we've seen a fogged version
		//of this object if one exists.
		for (Int i=0; i<MAX_PLAYER_COUNT; i++)
		{	if (mod->m_parentSnapshots[i])
				mod->m_partitionData->friend_setShroudednessPrevious(i,OBJECTSHROUD_FOGGED);
		}

		mod=nextmod;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::crc present-unmatched
void W3DGhostObjectManager::crc( Xfer *xfer )
{

	// extend base class
	GhostObjectManager::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?W3DGhostObjectManager::loadPostProcess present-unmatched
void W3DGhostObjectManager::loadPostProcess( void )
{

	// extend base class
	GhostObjectManager::loadPostProcess();

}  // end loadPostProcess
