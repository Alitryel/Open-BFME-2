// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp); this unit had no counterpart under Code/.
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
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// AssaultTransportAIUpdate.cpp ////////////
// Author: Kris Morness, December 2002
// Desc:   State machine that allows assault transports (troop crawler) to deploy
//         troops, order them to attack, then return. Can do extra things like ordering
//         injured troops to return to the transport for healing purposes.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?reset@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::reset()
{
	for( int i = 0; i < m_currentMembers; i++ )
	{
		m_memberIDs[ i ] = INVALID_ID;
		m_memberHealing[ i ] = FALSE;
		m_newMember[ i ] = FALSE;
	}
	m_currentMembers = 0;
  m_attackMoveGoalPos.zero();
  m_designatedTarget = INVALID_ID;
	m_state = IDLE;
	m_framesRemaining = 0;
	m_isAttackMove = FALSE;
	m_isAttackObject = FALSE;
	m_newOccupantsAreNewMembers = FALSE;
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/AssaultTransportAIUpdateDestructorThunk.cpp
// ??1AssaultTransportAIUpdate@@ present-unmatched
AssaultTransportAIUpdate::~AssaultTransportAIUpdate( void )
{
} 

//-------------------------------------------------------------------------------------------------
// ?aiDoCommand@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::aiDoCommand(const AICommandParms* parms)
{
	//Inspect the command and reset everything when necessary.
	if( parms->m_cmdSource != CMD_FROM_AI )
	{
		//Now the only time we care about anything is if we were ordered to attack something or attack move.
		switch( parms->m_cmd ) 
		{
			case AICMD_ATTACKMOVE_TO_POSITION:
				//Reset because we have been ordered to do something.
				reset();
				m_attackMoveGoalPos = parms->m_pos;
				m_isAttackMove = TRUE;
				break;
			case AICMD_ATTACK_OBJECT:
				//Reset because we have been ordered to do something.
				reset();
				//m_designatedTarget = parms->m_obj ? parms->m_obj->getID() : INVALID_ID;
				m_isAttackObject = TRUE;
				break;
			case AICMD_IDLE:
				m_designatedTarget = INVALID_ID;
				//Order all outside members back inside!
				retrieveMembers();
				reset();
				break;
			default:
				//Reset because we have been ordered to do something we're not handling.
				reset();
				break;
		}
	}

	//Note, in both cases, the transport will fire a dummy DEPLOY weapon that will trigger the 
	//evacuation of the troops.
	AIUpdateInterface::aiDoCommand( parms );
}

//-------------------------------------------------------------------------------------------------
void AssaultTransportAIUpdate::beginAssault( const Object *designatedTarget ) const
{
	//The transport has determined it is in range to begin the assault (via weapon system).
	//Now order the evacuation of healthy troops, and let the update handle moving them.
	if( designatedTarget )
	{
		m_designatedTarget = designatedTarget->getID();
	}
}

//-------------------------------------------------------------------------------------------------
// ?isIdle@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isIdle() const
{
	return AIUpdateInterface::isIdle();
}

//-------------------------------------------------------------------------------------------------
UpdateSleepTime calcSleepTime()
{
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
// The BFME 2 definition is in AssaultTransportAIUpdateUpdate.cpp.

// ?isAttackPointless@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isAttackPointless() const
{
	//If all members are new members (thus can't attack), and the transport itself
	//is still attacking, stop!
	const Object *transport = getObject();
	if( transport->testStatus( OBJECT_STATUS_IS_ATTACKING ) )
	{
		for( int i = 0; i < m_currentMembers; i++ )
		{
			if( !m_newMember[ i ] )
			{
				//We have a non-new member, so attack is valid.
				return FALSE;
			}
		}

		//We are trying to attack, but can't because all our members are new.
		return TRUE;
	}

	//We aren't trying to attack, so everything is good.
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?isMemberWounded@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isMemberWounded( const Object *member ) const
{
	const AssaultTransportAIUpdateModuleData *data = getAssaultTransportAIUpdateModuleData();
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		Real ratio = body->getHealth() / body->getMaxHealth();
		if( ratio < data->m_membersGetHealedAtLifeRatio )
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?isMemberHealthy@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isMemberHealthy( const Object *member ) const
{
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		if( body->getHealth() == body->getMaxHealth() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?retrieveMembers@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::retrieveMembers()
{
	//Order all outside members back inside!
	for( int i = 0; i < m_currentMembers; i++ )
	{
		Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
		AIUpdateInterface *ai = member ? member->getAI() : NULL;
		if( member && ai )
		{
			Bool contained = member->isContained();
			if( !contained )
			{
				//This contained member is healthy so order him to exit to start fighting!
				if (ai->getAIStateType() != AI_ENTER) {
					ai->aiEnter( getObject(), CMD_FROM_AI );
				} 
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?giveFinalOrders@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::giveFinalOrders()
{
	//All members have been ejected outside already -- transfer the original order to the troops
	for( int i = 0; i < m_currentMembers; i++ )
	{
		Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
		AIUpdateInterface *ai = member ? member->getAI() : NULL;
		if( member && ai )
		{
			Object *designatedTarget = TheGameLogic->findObjectByID( m_designatedTarget );

			if( m_isAttackObject && designatedTarget )
			{
				ai->aiAttackObject( designatedTarget, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
			}
			else if( m_isAttackMove )
			{
				ai->aiAttackMoveToPosition( &m_attackMoveGoalPos, NO_MAX_SHOTS_LIMIT, CMD_FROM_PLAYER );
			}

			ai->setAllowedToChase( FALSE );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** CRC */
//-------------------------------------------------------------------------------------------------
// ?crc@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::crc( Xfer *xfer )
{
	// extend base class
	AIUpdateInterface::crc(xfer);
}  // end crc

//-------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdateXfer.cpp

//-------------------------------------------------------------------------------------------------
/** Load post process */
//-------------------------------------------------------------------------------------------------
// ?loadPostProcess@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::loadPostProcess( void )
{
 // extend base class
	AIUpdateInterface::loadPostProcess();
}  // end loadPostProcess

