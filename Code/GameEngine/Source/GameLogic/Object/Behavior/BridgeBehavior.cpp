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
/*static*/ void BridgeBehaviorModuleData::parseFX( INI *ini, 
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
/*static*/ void BridgeBehaviorModuleData::parseOCL( INI *ini, 
																										void *instance,
																										void *store, 
																										const void *userData )
{
	const char *token;

	// create item we will read into and push on list
	BridgeOCLInfo item;
	item.ocl = NULL;

	// get list to store at
	BridgeOCLList *bridgeOCLList = (BridgeOCLList *)store;

	// fx list label
	token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "OCL" ) != 0 )
	{

		DEBUG_CRASH(( "Expected 'OCL' token, found '%s'\n", token ));
		throw INI_INVALID_DATA;

	}  // end if

	// fx list name and store as pointer
	ObjectCreationList *ocl;
	ini->parseObjectCreationList( ini, instance, &ocl, NULL );

	// store ocl list to item
	item.ocl = ocl;

	// parse the timing and location info
	parseTimeAndLocationInfo( ini, instance, &item.timeAndLocationInfo );

	// put on list
	bridgeOCLList->push_back( item );

}  // end parseOCL

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
// ?createScaffolding@BridgeBehavior@@ present-unmatched
void BridgeBehavior::createScaffolding( void )
{

	// if we have scaffolding up already do nothing
	if( m_scaffoldPresent == TRUE )
		return;

	// get the bridge world object
	Object *us = getObject();
	const Coord3D *center = us->getPosition();

	// get our bridge object
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// get the bridge template
	AsciiString bridgeTemplateName = bridge->getBridgeTemplateName();
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );
	DEBUG_ASSERTCRASH( bridgeTemplate, ("Unable to find bridge template to create scaffolding\n") );

	// get the thing template for the scaffold object we're going to use
	AsciiString scaffoldObjectName = bridgeTemplate->getScaffoldObjectName();
	const ThingTemplate *scaffoldTemplate = TheThingFactory->findTemplate( scaffoldObjectName );
	if( scaffoldTemplate == NULL )
	{

		DEBUG_CRASH(( "Unable to find bridge scaffold template\n" ));
		return;

	}  // end if

	// get thing template for scaffold support object
	AsciiString scaffoldSupportObjectName = bridgeTemplate->getScaffoldSupportObjectName();
	const ThingTemplate *scaffoldSupportTemplate = TheThingFactory->findTemplate( scaffoldSupportObjectName );
	if( scaffoldSupportTemplate == NULL )
	{

		DEBUG_CRASH(( "Unable to find bridge support scaffold template\n" ));
		return;

	}  // end if

	// how much space is going to be between each of the scaffold objects at their final positions
	Real spacing = scaffoldTemplate->getTemplateGeometryInfo().getMajorRadius() * 2.0f;

	// how tall are the scaffold objects
	Real scaffoldHeight = scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
												scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();
	Real scaffoldSupportHeight = scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
															 scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();

	// get the bridge info
	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo( &bridgeInfo );

	//
	// given the area of the bridge, figure out what the start and end points are to create
	// all the scaffold objects at (just in the 2D bridge plane, not thinking about
	// rising the objects up through the ground yet)
	//
	Coord3D leftStart;
	leftStart.x = ((bridgeInfo.fromLeft.x - bridgeInfo.fromRight.x) / 2.0f) + bridgeInfo.fromRight.x;
	leftStart.y = ((bridgeInfo.fromLeft.y - bridgeInfo.fromRight.y) / 2.0f) + bridgeInfo.fromRight.y;
	leftStart.z = ((bridgeInfo.fromLeft.z - bridgeInfo.fromRight.z) / 2.0f) + bridgeInfo.fromRight.z;

	Coord3D rightStart;
	rightStart.x = ((bridgeInfo.toLeft.x - bridgeInfo.toRight.x) / 2.0f) + bridgeInfo.toRight.x;
	rightStart.y = ((bridgeInfo.toLeft.y - bridgeInfo.toRight.y) / 2.0f) + bridgeInfo.toRight.y;
	rightStart.z = ((bridgeInfo.toLeft.z - bridgeInfo.toRight.z) / 2.0f) + bridgeInfo.toRight.z;

	//
	// now that we have the left and right start points, we will compute two angles to
	// use for all the objects that we will create ... objects on the left side of the
	// bridge will be given a 'leftAngle' pointing from 'leftStart' to 'rightStart' and
	// the opposite will be given to objects on the right side of the bridge
	//
	Coord2D angleV;
	angleV.x = rightStart.x - leftStart.x;
	angleV.y = rightStart.y - leftStart.y;
	Real leftAngle = angleV.toAngle();
	Real rightAngle = leftAngle + TWO_PI;

	// compute vector from left to right across bridge and the reverse
	Coord3D leftVector;
	leftVector.x = rightStart.x - leftStart.x;
	leftVector.y = rightStart.y - leftStart.y;
	leftVector.z = rightStart.z - leftStart.z;
	Coord3D rightVector;
	rightVector.x = leftStart.x - rightStart.x;
	rightVector.y = leftStart.y - rightStart.y;
	rightVector.z = leftStart.z - rightStart.z;

	//
	// how many of these scaffold objects will take to tile from each of the endpoints 
	// to the center area of the bridge
	//
	Real tileDistance = leftVector.length();
	Int numObjects = REAL_TO_INT_CEIL( tileDistance / spacing ) + 1;

	//
	// given the number of objects that we need to tile across the whole bridge, we will
	// go through the creation loop ceil( numObjects / 2.0f ) times, and each
	// time through the loop we'll create an object to move from each side of the
	// bridge, except the last object if the number of objects is odd is dead in the
	// center
	//
	Int numIterations = REAL_TO_INT_CEIL( INT_TO_REAL( numObjects ) / 2.0f );

	//
	// normalize left and right vectors as it is a vector that goes from our left start 
	// position to the destination right start position ... we will multiply this vector by a
	// spacing amount and add to the left start position to find a destination position
	// for a particular scaffold object along the bridge surface
	//
	leftVector.normalize();
	rightVector.normalize();

	// create the scaffold objects for now
	Int scaffoldObjectsCreated = 0;
	Coord3D destinationPos, *riseToPos;
	Real *angle;
	Object *obj;
	for( Int i = 0; i < numIterations; ++i )
	{

		// sanity
		DEBUG_ASSERTCRASH( scaffoldObjectsCreated < numObjects, 
											 ("Creating too many scaffold objects\n") );

		// create object
		obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam() );

		// this object is from the "left" side of the bridge
		riseToPos = &leftStart;
		angle = &leftAngle;

		//
		// compute position for object moving from the left side, we're adding 0.1 here
		// so that all scaffold objects *have* to move some distance ... that way we
		// can just assign the speeds so they line up perfectly and not have to worry
		// about any object reaching a destination before any other object
		//
		destinationPos.x = leftVector.x * (spacing * i) + riseToPos->x + 0.1f;
		destinationPos.y = leftVector.y * (spacing * i) + riseToPos->y;
		destinationPos.z = leftVector.z * (spacing * i) + riseToPos->z;

		//
		// now that they key positions are calculated, set the rest of the position data
		// and movement speeds for the object
		//
		setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

		// keeping track of objects created
		scaffoldObjectsCreated++;
		m_scaffoldObjectIDList.push_back( obj->getID() );

		//
		// create support object layers under the scaffold object, this object mirrors the scaffold
		// object except is on a lower layer
		//
		Real offset = riseToPos->z;
		Coord3D supportRiseToPos = *riseToPos;
		Coord3D supportDestinationPos = destinationPos;
		Coord3D supportBridgeCenter = *center;
		while( offset >= 0.0f )
		{

			supportRiseToPos.z -= scaffoldSupportHeight;
			supportDestinationPos.z -= scaffoldSupportHeight;
			supportBridgeCenter.z -= scaffoldSupportHeight;
			obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam() );
			setScaffoldData( obj, 
											 angle, 
											 &scaffoldSupportHeight,
											 &supportRiseToPos, 
											 &supportDestinationPos, 
											 &supportBridgeCenter );
			m_scaffoldObjectIDList.push_back( obj->getID() );


			// off to the next layer
			offset -= scaffoldSupportHeight;

		}  // end while

		//
		// now create the object from the "right" side of the bridge ... but note that
		// we don't do this on the last iteration through this loop when we have an odd
		// number of objects we're tiling because all the space is already perfectly used up)
		//
		if( scaffoldObjectsCreated < numObjects )
		{

			// sanity
			DEBUG_ASSERTCRASH( scaffoldObjectsCreated < numObjects, 
												 ("Creating too many scaffold objects\n") );

			// create new object
			obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam() );

			// this object is on the "right" side of the bridge
			riseToPos = &rightStart;
			angle = &rightAngle;

			//
			// compute position for object moving from the left side, we're adding 0.1 here
			// so that all scaffold objects *have* to move some distance ... that way we
			// can just assign the speeds so they line up perfectly and not have to worry
			// about any object reaching a destination before any other object
			//
			destinationPos.x = rightVector.x * (spacing * i) + riseToPos->x + 0.1f;
			destinationPos.y = rightVector.y * (spacing * i) + riseToPos->y;
			destinationPos.z = rightVector.z * (spacing * i) + riseToPos->z;

			// set the rest scaffold data again
			setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );

			// keeping track of objects created
			scaffoldObjectsCreated++;
			m_scaffoldObjectIDList.push_back( obj->getID() );

			//
			// create support object layers under the scaffold object, this object mirrors the scaffold
			// object except is on a lower layer
			//
			Real offset = riseToPos->z;
			Coord3D supportRiseToPos = *riseToPos;
			Coord3D supportDestinationPos = destinationPos;
			Coord3D supportBridgeCenter = *center;
			while( offset >= 0.0f )
			{

				supportRiseToPos.z -= scaffoldSupportHeight;
				supportDestinationPos.z -= scaffoldSupportHeight;
				supportBridgeCenter.z -= scaffoldSupportHeight;
				obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam() );
				setScaffoldData( obj, 
												 angle, 
												 &scaffoldSupportHeight,
												 &supportRiseToPos, 
												 &supportDestinationPos, 
												 &supportBridgeCenter );
				m_scaffoldObjectIDList.push_back( obj->getID() );


				// off to the next layer
				offset -= scaffoldSupportHeight;

			}  // end while

		}  // end if

	}  // end for i	

	// scaffolding is now present
	m_scaffoldPresent = TRUE;

	// when scaffolding is present, a bridge cannot be used
	TheAI->pathfinder()->changeBridgeState( bridge->getLayer(), FALSE );

}  // end createScaffolding

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
