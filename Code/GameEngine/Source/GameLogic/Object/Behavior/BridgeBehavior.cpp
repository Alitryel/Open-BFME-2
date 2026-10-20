// cl: /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp); this unit had no counterpart under Code/.
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
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: BridgeBehavior.cpp ///////////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   Behavior module for bridges
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/Radar.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/InGameUI.h"
#include "GameClient/FXList.h"
#include "GameClient/Line2D.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"

// Retail's shared 8.0f at VA 0x00BC2A10 (RVA 0x007C2A10); name the
// unowned .rdata value so linked code follows it when the image moves.
extern const Real g_00BC2A10 = 8.0f;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorModuleDataCtorThunk.cpp
// BridgeBehaviorModuleData's constructor is rowed at 0x00457FF1 with BFME2's body
// (BridgeBehaviorModuleDataCtor.cpp); the Zero Hour copy was a second definition.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/BridgeBehaviorModuleDataDestructorThunk.cpp
// BridgeBehaviorModuleData::~BridgeBehaviorModuleData is rowed in its home unit; this copy was a duplicate definition.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// BridgeBehaviorModuleData::buildFieldParse is rowed at 0x00458268 with BFME2's
// body (BehaviorModuleDataBuildFieldParse.cpp); the Zero Hour copy was a second definition.

// ------------------------------------------------------------------------------------------------
/** Parse time and location info in the form of:
	* Delay:#### <Bone:BoneName> */
// ------------------------------------------------------------------------------------------------
static void parseTimeAndLocationInfo( INI *ini, void *instance, 
																			TimeAndLocationInfo *timeAndLocationInfo )
{

	// delay label
	const char *token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "Delay" ) != 0 )
	{

		DEBUG_CRASH(( "Expected 'Delay' token, found '%s'\n", token ));
		throw INI_INVALID_DATA;

	}  // end if

	// delay value
	ini->parseDurationUnsignedInt( ini, instance, &timeAndLocationInfo->delay, NULL );

	// get optional bone label
	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if( token )
	{

		// token must be a label for bone location
		if( stricmp( token, "Bone" ) != 0 )
		{

			DEBUG_CRASH(( "Expected 'Bone' token, found '%s'\n", token ));
			throw INI_INVALID_DATA;

		}  // end if

		// read bone name and store
		timeAndLocationInfo->boneName = ini->getNextAsciiString();

	}  // end if

}  // end parseTimeAndLocationInfo

//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
inline /*static*/ void BridgeBehaviorModuleData::parseFX( INI *ini, 
											 														 void *instance, 
																									 void *store, 
																									 const void *userData )
{
	const char *token;

	// create item we will read into and push on list
	BridgeFXInfo item;
	item.fx = NULL;

	// get list to store at
	BridgeFXList *bridgeFXList = (BridgeFXList *)store;

	// fx list label
	token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "FX" ) != 0 )
	{

		DEBUG_CRASH(( "Expected 'FX' token, found '%s'\n", token ));
		throw INI_INVALID_DATA;

	}  // end if

	// fx list name and store as pointer
	FXList *fx;
	ini->parseFXList( ini, instance, &fx, NULL );

	// store fx list to item
	item.fx = fx;

	// parse the timing and location info
	parseTimeAndLocationInfo( ini, instance, &item.timeAndLocationInfo );

	// put on list
	bridgeFXList->push_back( item );

}  // end parseFX

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Retail parseOCL is owned by BridgeBehaviorParseOCL.cpp (RVA 0x00458153).
// Use that byte-verified definition instead of emitting the Zero Hour copy.

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/BridgeBehaviorCtorThunk.cpp
// BridgeBehavior's constructor is rowed with BFME2's body in BridgeBehaviorCtor.cpp;
// the Zero Hour copy was a second definition.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1BridgeBehavior@@ present-unmatched
BridgeBehavior::~BridgeBehavior( void )
{

	//
	// destroy our four towers if they are still present in the world (they wouldn't be if we
	// are resetting the engine, and those towers were earlier in the destruction list than
	// we were)
	//
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{
		Object *tower;

		// get the tower and destroy
		tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
		if( tower )
			TheGameLogic->destroyObject( tower );

	}  // end for i

}  // end ~BridgeBehavior

// ------------------------------------------------------------------------------------------------
/** Get bridge behavior interface */
// ------------------------------------------------------------------------------------------------
// getBridgeBehaviorInterfaceFromObject lives in
// BridgeBehaviorGetInterfaceFromObject.cpp (rowed 0x00456556); no local copy
// is emitted, so the rowed copy is the sole definition at link time.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onDelete@BridgeBehavior@@UAEXXZ present-unmatched
void BridgeBehavior::onDelete( void )
{

	// clear the list of scaffold objects
	m_scaffoldObjectIDList.clear();

}  // end onDelete

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?resolveFX@BridgeBehavior@@IAEXXZ

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
void BridgeBehavior::setTower( BridgeTowerType towerType, Object *tower )
{

	// sanity
	if( towerType < 0 || towerType >= BRIDGE_MAX_TOWERS )
	{

		DEBUG_CRASH(( "BridgeBehavior::setTower - Invalid tower type index '%d'\n", towerType ));
		return;

	}  // end if

	// store it
	if( tower )
		m_towerID[ towerType ] = tower->getID();
	else
		m_towerID[ towerType ] = INVALID_ID;

}  // end setTower
#pragma optimize("", on)

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
ObjectID BridgeBehavior::getTowerID( BridgeTowerType towerType )
{

	// sanity
	if( towerType < 0 || towerType >= BRIDGE_MAX_TOWERS )
	{

		DEBUG_CRASH(( "BridgeBehavior::setTower - Invalid tower type index '%d'\n", towerType ));
		return INVALID_ID;

	}  // end if

	// return the stored ID
	return m_towerID[ towerType ];

}  // end getTowerID
#pragma optimize("", on)

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp

// ------------------------------------------------------------------------------------------------
/** Pick a random surface spot on the bridge surface */
// ------------------------------------------------------------------------------------------------
// BridgeBehavior::getRandomSurfacePosition and BridgeBehavior::doAreaEffects are defined with their
// retail-matched /O1 bodies in Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorAreaEffects.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/BridgeBehavior_updateMethodThunk.cpp
// BridgeBehavior::update is defined with its retail-matched /O1 body in
// Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorAreaEffects.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp
// ?onDie@BridgeBehavior@@UAEXPBVDamageInfo@@@Z present-unmatched
void BridgeBehavior::onDie( const DamageInfo *damageInfo )
{

	// kill the towers associated with us
	Object *tower;
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{

		tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
		if( tower )
			tower->kill();

	}  // end for, i

	// we need to handle anything that was on top of us now that we've been destroyed
	handleObjectsOnBridgeOnDie();

	// we have now died, record the death frame
	m_deathFrame = TheGameLogic->getFrame();
			
}  // end onDie

//-----------------------------------------------------------------------------
// Note: a ZH-derived BridgeBehavior::handleObjectsOnBridgeOnDie body stood
// here. The census proves our copy is not retail's (kept definition differs)
// while 0x00457577 is rowed from
// BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp, so this unit no longer
// defines it and the link keeps the rowed copy.


// ------------------------------------------------------------------------------------------------
/** Set all the position, angle, and speed data we need to for a single scaffold object */
// ------------------------------------------------------------------------------------------------
// Implemented in BridgeBehaviorSetScaffoldData.cpp so Coord3D::length remains
// an out-of-line call, as in the retail body.

// ------------------------------------------------------------------------------------------------
/** Start the bridge repair scaffolding.  If we already have scaffolding this call
	* is ignored */
// ------------------------------------------------------------------------------------------------
// Implemented with BFME2 layouts in BridgeBehaviorCreateScaffolding.cpp.
// The old ZH body here competed with that byte-verified retail definition.

// ------------------------------------------------------------------------------------------------
/** Remove the bridge scaffolding.  If we don't have any then this call is ignored */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp

// ------------------------------------------------------------------------------------------------
/** Is any of the scaffolding in motion */
// ------------------------------------------------------------------------------------------------
// Retail-specific layout is isolated in BridgeBehaviorIsScaffoldInMotion.cpp:
// the ZH donor's list at +0x400 is at +0xE0 in this game's body.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BridgeBehavior@@MAEXPAVXfer@@@Z present-unmatched
void BridgeBehavior::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp
// Matched body: BridgeBehaviorXfer.cpp @ 0x457E72 (BFME 2 order). This ZH copy
// stays because it emits the Bridge::setBridgeObjectID/setTowerObjectID rows.
// BridgeBehavior::xfer is rowed with BFME2's body in BridgeBehaviorXfer.cpp; the
// Zero Hour copy here was a second, non-retail definition.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BridgeBehavior@@MAEXXZ present-unmatched
void BridgeBehavior::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
