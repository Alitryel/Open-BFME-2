// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/InGameUI.cpp); this unit had no counterpart under Code/.
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

// InGameUI.cpp ///////////////////////////////////////////////////////////////////////////////////
// Implementation of in-game user interface singleton inteface
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

// Retail spells _Rb_tree::insert_unique(const value_type&)'s leftmost fast path
// as `if (__comp && __j == begin())` with `_M_insert(__y, __y, __v)`; the
// vendored STLport carries that spelling behind this switch.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#define DEFINE_SHADOW_NAMES

#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GameType.h"
#include "Common/MessageStream.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/BuildAssistant.h"
#include "Common/Recorder.h"
#include "Common/BuildAssistant.h"
#include "Common/SpecialPower.h"

#include "GameClient/Anim2D.h"
#include "GameClient/ControlBar.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Diplomacy.h"
#include "GameClient/Eva.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowID.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/VideoPlayer.h"
#include "GameClient/Mouse.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/View.h"
#include "GameClient/TerrainVisual.h"	
#include "GameClient/ControlBar.h"
#include "GameClient/Display.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/Shadow.h"
#include "GameClient/GlobalLanguage.h"

#include "GameLogic/AIGuard.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/MobMemberSlavedUpdate.h"//ML

#include "Common/UnitTimings.h" //Contains the DO_UNIT_TIMINGS define jba.		 

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// ------------------------------------------------------------------------------------------------
static const Real placementOpacity = 0.45f;
static const RGBColor illegalBuildColor = { 1.0, 0.0, 0.0 };

//-------------------------------------------------------------------------------------------------
/// The InGameUI singleton instance.
InGameUI *TheInGameUI = NULL;

GameWindow *m_replayWindow = NULL;

// LINK: TU-local view of CommandButton::m_command at +0x14 (retail truth:
// matched witnesses isReady 0x0035B069, evaluateSkirmish 0x003E73E7 and
// rowed 0x003C10D8 all read +0x14). The two call sites below read through
// this instead of odr-using the ZH inline, whose +0x10 copy sorts ahead of
// the retail copy in link order (getCommandType L row). Same treatment as
// AIUpdate.cpp's privateCommandButtonObject.
struct InGameUICommandButtonView { unsigned char m_pad[0x14]; Int m_command; };
static Int InGameUIGetCommandType(const CommandButton *button)
{
	return reinterpret_cast<const InGameUICommandButtonView *>(button)->m_command;
}

// ------------------------------------------------------------------------------------------------
struct KindOfSelectionData
{
	KindOfMaskType m_mustbeSet;
	KindOfMaskType m_mustbeClear;

	DrawableList newlySelectedDrawables;
};
// ------------------------------------------------------------------------------------------------
static Bool kindOfUnitSelection( Drawable *test, void *userData )
{
	KindOfSelectionData *data = (KindOfSelectionData *) userData;

	if( test )
	{
		const Object *object = test->getObject();
		// Only things with objects can be selected, and the code below isn't 
		// safe unless you've verified that there is a valid object.
		if (!object)
			return FALSE;

		Bool isKindOfMatch = object->isKindOfMulti(data->m_mustbeSet, data->m_mustbeClear);

		// only select objects if not already selected
		if( object && isKindOfMatch 
					&& object->isLocallyControlled() 
					&& !object->isContained() 
					&& !object->getDrawable()->isSelected() 
					&& !object->isEffectivelyDead()
					&& object->isMassSelectable()
					&& !object->isOffMap()
				)
		{
			// enforce optional unit cap
			if (TheInGameUI->getMaxSelectCount() > 0 && TheInGameUI->getSelectCount() >= TheInGameUI->getMaxSelectCount())
			{
				if ( !TheInGameUI->getDisplayedMaxWarning() )
				{
					TheInGameUI->setDisplayedMaxWarning( TRUE );
					UnicodeString msg;
					msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
					TheInGameUI->message(msg);
				}
			}
			else
			{
				TheInGameUI->selectDrawable( test );
				TheInGameUI->setDisplayedMaxWarning( FALSE );
				data->newlySelectedDrawables.push_back(test);
				return TRUE;
			}	
		}
	}
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
struct MatchingUnitSelectionData
{
	const ThingTemplate *templateToSelect;
	DrawableList newlySelectedDrawables;
	Bool isCarBomb;
};
// ------------------------------------------------------------------------------------------------
static Bool similarUnitSelection( Drawable *test, void *userData )
{
	MatchingUnitSelectionData *data = (MatchingUnitSelectionData *) userData;
	const ThingTemplate *selectedType = data->templateToSelect;

	if( test )
	{
		const Object *object = test->getObject();
		// Only things with objects can be selected, and the code below isn't 
		// safe unless you've verified that there is a valid object.
		if (!object)
			return FALSE;

		Bool isEquivalent = object->getTemplate()->isEquivalentTo( selectedType );
		if( data->isCarBomb && !isEquivalent && object->testStatus( OBJECT_STATUS_IS_CARBOMB ) )
		{
			isEquivalent = TRUE;
		}

		// only select objects if not already selected
		if( object && isEquivalent 
			  && object->isLocallyControlled() 
				&& !object->isContained()
				&& !( object->getDrawable()->isSelected() ) 
				&& object->isMassSelectable() // And only if they can be multiply selected. (otherwise the drawable will be, but the object will not be)
				&& !object->isOffMap()
				)
		{
			// enforce optional unit cap
			if (TheInGameUI->getMaxSelectCount() > 0 && TheInGameUI->getSelectCount() >= TheInGameUI->getMaxSelectCount())
			{
				if ( !TheInGameUI->getDisplayedMaxWarning() )
				{
					TheInGameUI->setDisplayedMaxWarning( TRUE );
					UnicodeString msg;
					msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
					TheInGameUI->message(msg);
				}
			}
			else
			{
				TheInGameUI->selectDrawable( test );
				TheInGameUI->setDisplayedMaxWarning( FALSE );
				data->newlySelectedDrawables.push_back(test);
				return TRUE;
			}	
		}
	}
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// showReplayControls: defined in ReplayControls.cpp (its row's unit).
void showReplayControls( void );

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// hideReplayControls: defined in ReplayControls.cpp (its row's unit).
void hideReplayControls( void );

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// toggleReplayControls: defined in ReplayControls.cpp (its row's unit).
void toggleReplayControls( void );

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?SuperweaponInfo::SuperweaponInfo present-unmatched
SuperweaponInfo::SuperweaponInfo(
	ObjectID id,
	UnsignedInt timestamp,
	Bool hiddenByScript,
	Bool hiddenByScience,
	Bool ready,
  Bool evaReadyPlayed,
	const AsciiString& superweaponNormalFont, 
	Int superweaponNormalPointSize, 
	Bool superweaponNormalBold,
	Color c, 
	const SpecialPowerTemplate* spt
) :
	m_id(id),
	m_timestamp(timestamp),
	m_hiddenByScript(hiddenByScript),
	m_hiddenByScience(hiddenByScience),
	m_ready(ready),
  m_evaReadyPlayed( evaReadyPlayed ),
	m_forceUpdateText(false),
	m_nameDisplayString(NULL),
	m_timeDisplayString(NULL),
	m_color(c),
	m_powerTemplate(spt)
{
	m_nameDisplayString = TheDisplayStringManager->newDisplayString();
	m_nameDisplayString->reset();
	m_nameDisplayString->setText( UnicodeString::TheEmptyString );

	m_timeDisplayString = TheDisplayStringManager->newDisplayString();
	m_timeDisplayString->reset();
	m_timeDisplayString->setText( UnicodeString::TheEmptyString );

	setFont( superweaponNormalFont, superweaponNormalPointSize, superweaponNormalBold );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?SuperweaponInfo::~SuperweaponInfo present-unmatched
inline SuperweaponInfo::~SuperweaponInfo()
{
	if (m_nameDisplayString)
		TheDisplayStringManager->freeDisplayString( m_nameDisplayString );
	m_nameDisplayString = NULL;

	if (m_timeDisplayString)
		TheDisplayStringManager->freeDisplayString( m_timeDisplayString );
	m_timeDisplayString = NULL;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// SuperweaponInfo::setFont: defined in SuperweaponInfo.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// SuperweaponInfo::setText: defined in SuperweaponInfoSetText.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// SuperweaponInfo::drawName: defined in SuperweaponInfo.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// SuperweaponInfo::drawTime: defined in SuperweaponInfo.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// SuperweaponInfo::getHeight: defined in SuperweaponInfo.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?InGameUI::crc present-unmatched
void InGameUI::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 2: Save NamedTimers, but not specifically their Info structs.  We'll recreate them.
  * 3: Added m_evaReadyPlayed boolean to transfer
*/
// ------------------------------------------------------------------------------------------------
// InGameUI::xfer: defined in InGameUIXfer.cpp (its row's unit). The superweapon map
// node construction its load reached (0x006896F0) keeps this unit's flags and row.
template void _STL::_Construct( SuperweaponMap::value_type *, const SuperweaponMap::value_type & );

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// InGameUI::loadPostProcess: defined in InGameUIXfer.cpp (its row's unit).

// InGameUI::setMouseCursor: defined in InGameUIInputModes.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::findSWInfo: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::addSuperweapon: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::removeSuperweapon: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::objectChangedTeam: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::hideObjectSuperweaponDisplayByScript: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::showObjectSuperweaponDisplayByScript: defined in InGameUISuperweapons.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::setSuperweaponDisplayEnabledByScript present-unmatched
void InGameUI::setSuperweaponDisplayEnabledByScript(Bool enable)
{
	m_superweaponHiddenByScript = !enable;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::getSuperweaponDisplayEnabledByScript present-unmatched
Bool InGameUI::getSuperweaponDisplayEnabledByScript(void) const
{
	return m_superweaponHiddenByScript;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::addNamedTimer: defined in InGameUIXfer.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::removeNamedTimer present-unmatched
void InGameUI::removeNamedTimer( const AsciiString& timerName )
{
	NamedTimerMapIt mapIt = m_namedTimers.find(timerName);
	if (mapIt != m_namedTimers.end())
	{
		TheDisplayStringManager->freeDisplayString( mapIt->second->displayString );
		mapIt->second->deleteInstance();
		m_namedTimers.erase(mapIt);
		return;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::showNamedTimerDisplay present-unmatched
void InGameUI::showNamedTimerDisplay( Bool show )
{
	m_showNamedTimers = show;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const FieldParse InGameUI::s_fieldParseTable[] = 
{
	{ "MaxSelectionSize",								INI::parseInt,					NULL,		offsetof( InGameUI, m_maxSelectCount ) },

	{ "MessageColor1",									INI::parseColorInt,			NULL,		offsetof( InGameUI, m_messageColor1 ) },
	{ "MessageColor2",									INI::parseColorInt,			NULL,		offsetof( InGameUI, m_messageColor2 ) },
	{ "MessagePosition",								INI::parseICoord2D,			NULL,		offsetof( InGameUI, m_messagePosition ) },
	{ "MessageFont",										INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_messageFont ) },
	{ "MessagePointSize",								INI::parseInt,					NULL,		offsetof( InGameUI, m_messagePointSize ) },
	{ "MessageBold",										INI::parseBool,					NULL,		offsetof( InGameUI, m_messageBold ) },
	{ "MessageDelayMS",									INI::parseInt,					NULL,		offsetof( InGameUI, m_messageDelayMS ) },

	{ "MilitaryCaptionColor",						INI::parseRGBAColorInt,	NULL,		offsetof( InGameUI, m_militaryCaptionColor ) },
	{ "MilitaryCaptionPosition",				INI::parseICoord2D,			NULL,		offsetof( InGameUI, m_militaryCaptionPosition ) },

	{ "MilitaryCaptionTitleFont",				INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_militaryCaptionTitleFont ) },
	{ "MilitaryCaptionTitlePointSize",	INI::parseInt,					NULL,		offsetof( InGameUI, m_militaryCaptionTitlePointSize ) },
	{ "MilitaryCaptionTitleBold",				INI::parseBool,					NULL,		offsetof( InGameUI, m_militaryCaptionTitleBold ) },

	{ "MilitaryCaptionFont",						INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_militaryCaptionFont ) },
	{ "MilitaryCaptionPointSize",				INI::parseInt,					NULL,		offsetof( InGameUI, m_militaryCaptionPointSize ) },
	{ "MilitaryCaptionBold",						INI::parseBool,					NULL,		offsetof( InGameUI, m_militaryCaptionBold ) },

	{ "MilitaryCaptionRandomizeTyping",	INI::parseBool,					NULL,		offsetof( InGameUI, m_militaryCaptionRandomizeTyping ) },
	{ "MilitaryCaptionSpeed",						INI::parseInt,					NULL,		offsetof( InGameUI, m_militaryCaptionSpeed ) },

	{ "MilitaryCaptionPosition",				INI::parseICoord2D,			NULL,		offsetof( InGameUI, m_militaryCaptionPosition ) },

	{ "SuperweaponCountdownPosition",					INI::parseCoord2D,			NULL,		offsetof( InGameUI, m_superweaponPosition ) },
	{ "SuperweaponCountdownFlashDuration",		INI::parseDurationReal,	NULL,		offsetof( InGameUI, m_superweaponFlashDuration ) },
	{ "SuperweaponCountdownFlashColor",				INI::parseColorInt,			NULL,		offsetof( InGameUI, m_superweaponFlashColor ) },

	{ "SuperweaponCountdownNormalFont",				INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_superweaponNormalFont ) },
	{ "SuperweaponCountdownNormalPointSize",	INI::parseInt,					NULL,		offsetof( InGameUI, m_superweaponNormalPointSize ) },
	{ "SuperweaponCountdownNormalBold",				INI::parseBool,					NULL,		offsetof( InGameUI, m_superweaponNormalBold ) },

	{ "SuperweaponCountdownReadyFont",				INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_superweaponReadyFont ) },
	{ "SuperweaponCountdownReadyPointSize",		INI::parseInt,					NULL,		offsetof( InGameUI, m_superweaponReadyPointSize ) },
	{ "SuperweaponCountdownReadyBold",				INI::parseBool,					NULL,		offsetof( InGameUI, m_superweaponReadyBold ) },

	{ "NamedTimerCountdownPosition",					INI::parseCoord2D,			NULL,		offsetof( InGameUI, m_namedTimerPosition ) },
	{ "NamedTimerCountdownFlashDuration",			INI::parseDurationReal,	NULL,		offsetof( InGameUI, m_namedTimerFlashDuration ) },
	{ "NamedTimerCountdownFlashColor",				INI::parseColorInt,			NULL,		offsetof( InGameUI, m_namedTimerFlashColor ) },

	{ "NamedTimerCountdownNormalFont",				INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_namedTimerNormalFont ) },
	{ "NamedTimerCountdownNormalPointSize",		INI::parseInt,					NULL,		offsetof( InGameUI, m_namedTimerNormalPointSize ) },
	{ "NamedTimerCountdownNormalBold",				INI::parseBool,					NULL,		offsetof( InGameUI, m_namedTimerNormalBold ) },
	{ "NamedTimerCountdownNormalColor",				INI::parseColorInt,			NULL,		offsetof( InGameUI, m_namedTimerNormalColor ) },

	{ "NamedTimerCountdownReadyFont",					INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_namedTimerReadyFont ) },
	{ "NamedTimerCountdownReadyPointSize",		INI::parseInt,					NULL,		offsetof( InGameUI, m_namedTimerReadyPointSize ) },
	{ "NamedTimerCountdownReadyBold",					INI::parseBool,					NULL,		offsetof( InGameUI, m_namedTimerReadyBold ) },
	{ "NamedTimerCountdownReadyColor",				INI::parseColorInt,			NULL,		offsetof( InGameUI, m_namedTimerReadyColor ) },

	{ "FloatingTextTimeOut",									INI::parseDurationUnsignedInt,		NULL,		offsetof( InGameUI, m_floatingTextTimeOut ) },
	{ "FloatingTextMoveUpSpeed",							INI::parseVelocityReal,	NULL,		offsetof( InGameUI, m_floatingTextMoveUpSpeed ) },
	{ "FloatingTextVanishRate",								INI::parseVelocityReal,	NULL,		offsetof( InGameUI, m_floatingTextMoveVanishRate ) },

	{ "PopupMessageColor",								INI::parseColorInt,					NULL,		offsetof( InGameUI, m_popupMessageColor ) },
	
	{ "DrawableCaptionFont",									INI::parseAsciiString,	NULL,		offsetof( InGameUI, m_drawableCaptionFont ) },
	{ "DrawableCaptionPointSize",							INI::parseInt,					NULL,		offsetof( InGameUI, m_drawableCaptionPointSize ) },
	{ "DrawableCaptionBold",									INI::parseBool,					NULL,		offsetof( InGameUI, m_drawableCaptionBold ) },
	{ "DrawableCaptionColor",									INI::parseColorInt,			NULL,		offsetof( InGameUI, m_drawableCaptionColor ) },

	{ "DrawRMBScrollAnchor",									INI::parseBool,					NULL,		offsetof( InGameUI, m_drawRMBScrollAnchor ) },
	{ "MoveRMBScrollAnchor",									INI::parseBool,					NULL,		offsetof( InGameUI, m_moveRMBScrollAnchor ) },

	{ "AttackDamageAreaRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_ATTACK_DAMAGE_AREA] ) },
	{ "AttackScatterAreaRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_ATTACK_SCATTER_AREA] ) },
	{ "AttackContinueAreaRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_ATTACK_CONTINUE_AREA] ) },
	{ "FriendlySpecialPowerRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_FRIENDLY_SPECIALPOWER] ) },
	{ "OffensiveSpecialPowerRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_OFFENSIVE_SPECIALPOWER] ) },
	{ "SuperweaponScatterAreaRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_SUPERWEAPON_SCATTER_AREA] ) },

	{ "GuardAreaRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_GUARD_AREA] ) },
	{ "EmergencyRepairRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[RADIUSCURSOR_EMERGENCY_REPAIR] ) },

	{ "ParticleCannonRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_PARTICLECANNON] ) },
	{ "A10StrikeRadiusCursor",			RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_A10STRIKE] ) },
	{ "CarpetBombRadiusCursor",			RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_CARPETBOMB] ) },
	{ "DaisyCutterRadiusCursor",		RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_DAISYCUTTER] ) },
	{ "ParadropRadiusCursor",				RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_PARADROP] ) },
	{ "SpySatelliteRadiusCursor",		RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_SPYSATELLITE] ) },
	{ "SpectreGunshipRadiusCursor",	RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_SPECTREGUNSHIP] ) },
	{ "HelixNapalmBombRadiusCursor",RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_HELIX_NAPALM_BOMB] ) },
	
	{ "NuclearMissileRadiusCursor", RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_NUCLEARMISSILE] ) }, 
	{ "EMPPulseRadiusCursor",		  	RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_EMPPULSE] ) },
	{ "ArtilleryRadiusCursor",		  RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_ARTILLERYBARRAGE] ) },
	{ "FrenzyRadiusCursor",				  RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_FRENZY] ) },
	{ "NapalmStrikeRadiusCursor",		RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_NAPALMSTRIKE] ) },
	{ "ClusterMinesRadiusCursor",		RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_CLUSTERMINES] ) },
	
	{ "ScudStormRadiusCursor",			RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_SCUDSTORM] ) }, 
	{ "AnthraxBombRadiusCursor",		RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_ANTHRAXBOMB] ) },
	{ "AmbushRadiusCursor",					RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_AMBUSH] ) }, 
	{ "RadarRadiusCursor",					RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[	RADIUSCURSOR_RADAR] ) },
	{ "SpyDroneRadiusCursor",				RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[ RADIUSCURSOR_SPYDRONE] ) },

	{ "ClearMinesRadiusCursor",			RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[ RADIUSCURSOR_CLEARMINES] ) },
	{ "AmbulanceRadiusCursor",			RadiusDecalTemplate::parseRadiusDecalTemplate, NULL, offsetof( InGameUI, m_radiusCursors[ RADIUSCURSOR_AMBULANCE] ) },

	{ NULL,													NULL,										NULL,		0 }  // keep this last
};

//-------------------------------------------------------------------------------------------------
/** Parse MouseCursor entry */
//-------------------------------------------------------------------------------------------------
// INI::parseInGameUIDefinition: defined in InGameUIMessages.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// InGameUI::InGameUI: defined in InGameUICtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// InGameUI::~InGameUI: defined in InGameUIDtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Initialize the in game user interface */
//-------------------------------------------------------------------------------------------------
// InGameUI::init: defined in InGameUIMessages.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?InGameUI::setRadiusCursor present-unmatched
void InGameUI::setRadiusCursor(RadiusCursorType cursorType, const SpecialPowerTemplate* specPowTempl, WeaponSlotType weaponSlot)
{
	if (cursorType == m_curRcType)
		return;

	m_curRadiusCursor.clear();
	m_curRcType = RADIUSCURSOR_NONE;

	if (cursorType == RADIUSCURSOR_NONE)
		return;

	Object* obj = NULL;
	if( m_pendingGUICommand && InGameUIGetCommandType(m_pendingGUICommand) == GUI_COMMAND_SPECIAL_POWER_FROM_SHORTCUT )
	{
		if( ThePlayerList && ThePlayerList->getLocalPlayer() && specPowTempl != NULL )
		{
			obj = ThePlayerList->getLocalPlayer()->findMostReadyShortcutSpecialPowerOfType( specPowTempl->getSpecialPowerType() );
		}
	}
	else
	{
		if (getSelectCount() == 0)
			return;

		Drawable *draw = getFirstSelectedDrawable();
		if (draw == NULL)
			return;

		obj = draw->getObject();
	}

	if (obj == NULL)
		return;
	
	Player* controller = obj->getControllingPlayer();
	if (controller == NULL)
		return;

	Real radius = 0.0f;
	const Weapon* w = NULL;
	switch (cursorType)
	{
		// already handled
		//case RADIUSCURSOR_NONE:
		//	return;
		case RADIUSCURSOR_ATTACK_DAMAGE_AREA:
			w = obj->getWeaponInWeaponSlot(weaponSlot);
			radius = w ? w->getPrimaryDamageRadius(obj) : 0.0f;
			break;
		case RADIUSCURSOR_ATTACK_SCATTER_AREA:
			w = obj->getWeaponInWeaponSlot(weaponSlot);
			radius = w ? (w->getScatterRadius() + w->getScatterTargetScalar()) : 0.0f;
			break;
		case RADIUSCURSOR_ATTACK_CONTINUE_AREA:
		case RADIUSCURSOR_CLEARMINES:
			w = obj->getWeaponInWeaponSlot(weaponSlot);
			radius = w ? w->getContinueAttackRange() : 0.0f;
			break;
		case RADIUSCURSOR_GUARD_AREA:
			radius = AIGuardMachine::getStdGuardRange(obj);
			break;
		case RADIUSCURSOR_FRIENDLY_SPECIALPOWER:
		case RADIUSCURSOR_OFFENSIVE_SPECIALPOWER:
		case RADIUSCURSOR_SUPERWEAPON_SCATTER_AREA:
		case RADIUSCURSOR_EMERGENCY_REPAIR:
		case RADIUSCURSOR_PARTICLECANNON: 
		case RADIUSCURSOR_A10STRIKE:
		case RADIUSCURSOR_SPECTREGUNSHIP:
    case RADIUSCURSOR_HELIX_NAPALM_BOMB:
		case RADIUSCURSOR_DAISYCUTTER:
		case RADIUSCURSOR_CARPETBOMB:
		case RADIUSCURSOR_PARADROP:
		case RADIUSCURSOR_SPYSATELLITE: 
		case RADIUSCURSOR_NUCLEARMISSILE: 
		case RADIUSCURSOR_EMPPULSE:
		case RADIUSCURSOR_ARTILLERYBARRAGE:
		case RADIUSCURSOR_FRENZY:
		case RADIUSCURSOR_NAPALMSTRIKE:
		case RADIUSCURSOR_CLUSTERMINES:
		case RADIUSCURSOR_SCUDSTORM: 
		case RADIUSCURSOR_ANTHRAXBOMB:
		case RADIUSCURSOR_AMBUSH: 
		case RADIUSCURSOR_RADAR:
		case RADIUSCURSOR_SPYDRONE:
		case RADIUSCURSOR_AMBULANCE:
			radius = specPowTempl ? specPowTempl->getRadiusCursorRadius() : 0.0f;
			break;

	}

	if (radius <= 0.0f)
		return;

	Coord3D pos = { 0, 0, 0 };	// will be updated right away
	m_radiusCursors[cursorType].createRadiusDecal(pos, radius, controller, m_curRadiusCursor);
	m_curRcType = cursorType;

	handleRadiusCursor();
}

//-------------------------------------------------------------------------------------------------
/** handle updating of "radius cursors" that follow the mouse pos */
//-------------------------------------------------------------------------------------------------
// InGameUI::handleRadiusCursor: defined in InGameUI_handleRadiusCursor.cpp (its row's unit).


// ?InGameUI::triggerDoubleClickAttackMoveGuardHint present-unmatched
void InGameUI::triggerDoubleClickAttackMoveGuardHint( void ) 
{
  m_duringDoubleClickAttackMoveGuardHintTimer = 11; 
	const MouseIO* mouseIO = TheMouse->getMouseStatus();
	TheTacticalView->screenToTerrain( &mouseIO->pos, &m_duringDoubleClickAttackMoveGuardHintStashedPosition );
}


//-------------------------------------------------------------------------------------------------
/** Handle the placement "icons" that appear at the cursor when we're putting down a 
	* structure to build.  Note that this has additional logic to also show a line
	* of objects because when we build "walls" we want to draw a line of repeating
	* wall pieces on the map where we want to put all of them */
//-------------------------------------------------------------------------------------------------


// Native evaluateSoloNexus is recovered in InGameUISelectDrawable.cpp.



//-------------------------------------------------------------------------------------------------
/** Pre-draw phase of the in game ui */
//-------------------------------------------------------------------------------------------------
void InGameUI::preDraw( void )
{

	// handle any "icons" for the act of building things and placing them in the world
	handleBuildPlacements();

	// handle radius-cursors, if any
	handleRadiusCursor();

	// draw the floating text first;
	drawFloatingText();

	// draw world animations
	updateAndDrawWorldAnimations();

}  // end preDraw

//-------------------------------------------------------------------------------------------------
/** Update the in game user interface */
//-------------------------------------------------------------------------------------------------
//DECLARE_PERF_TIMER(InGameUI_update)
// InGameUI::update (0x002A1582) is recovered in InGameUIUpdate.cpp; the Zero Hour
// body that stood here differs from retail and would duplicate that definition.
  // end update

//-------------------------------------------------------------------------------------------------
// ?InGameUI::registerWindowLayout present-unmatched
void InGameUI::registerWindowLayout( WindowLayout *layout )
{
	unregisterWindowLayout(layout); // sanity
	m_windowLayouts.push_back(layout);
}

//-------------------------------------------------------------------------------------------------
// ?InGameUI::unregisterWindowLayout present-unmatched
void InGameUI::unregisterWindowLayout( WindowLayout *layout )
{
	for (std::list<WindowLayout *>::iterator it = m_windowLayouts.begin(); it != m_windowLayouts.end(); ++it)
	{
		if (*it == layout)
		{
			m_windowLayouts.erase(it);
			return;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** Reset the in game user interface */
//-------------------------------------------------------------------------------------------------
// InGameUI::reset: defined in InGameUIReset.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Free any resources we used for our messages */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::freeMessageResources present-unmatched
void InGameUI::freeMessageResources( void )
{
	Int i;

	// release display strings and set text to empty
	for( i = 0; i < MAX_UI_MESSAGES; i++ )
	{

		// emtpy text
		m_uiMessages[ i ].fullText.clear();

		// free display string
		if( m_uiMessages[ i ].displayString )
			TheDisplayStringManager->freeDisplayString( m_uiMessages[ i ].displayString );
		m_uiMessages[ i ].displayString = NULL;

		// set timestamp to zero
		m_uiMessages[ i ].timestamp = 0;

	}  // end for i

}  // end freeMessageResources

//-------------------------------------------------------------------------------------------------
/** Same as the unicode message method, but this takes an ascii string which is assumed
	* to me a string manager label */
//-------------------------------------------------------------------------------------------------
// srj sez: passing as const-ref screws up varargs for some reason. dunno why. just pass by value.
// InGameUI::message (AsciiString label): defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** Interface for display text messages to the user */
//-------------------------------------------------------------------------------------------------
// srj sez: passing as const-ref screws up varargs for some reason. dunno why. just pass by value.
// InGameUI::message (UnicodeString format): defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** Interface for display text messages to the user */
//-------------------------------------------------------------------------------------------------
// srj sez: passing as const-ref screws up varargs for some reason. dunno why. just pass by value.
// InGameUI::messageColor: defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// InGameUI::addMessageText: defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** Remove the message on screen at index i */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::removeMessageAtIndex present-unmatched
void InGameUI::removeMessageAtIndex( Int i )
{

	m_uiMessages[ i ].fullText.clear();
	if( m_uiMessages[ i ].displayString )
		TheDisplayStringManager->freeDisplayString( m_uiMessages[ i ].displayString );
	m_uiMessages[ i ].displayString = NULL;
	m_uiMessages[ i ].timestamp = 0;

}  // end removeMessageAtIndex

// InGameUI::beginAreaSelectHint: defined in InGameUIInputModes.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** An area selection has occurred, finish graphical "hint". */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::endAreaSelectHint present-unmatched
void InGameUI::endAreaSelectHint( const GameMessage *msg )
{
	m_isDragSelecting = false;
}

//-------------------------------------------------------------------------------------------------
/** A move command has occurred, start graphical "hint". */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::createMoveHint present-unmatched
void InGameUI::createMoveHint( const GameMessage *msg )
{
	Int i;

	// first, remove any existing move hint for this source if present
	for( i = 0; i < MAX_MOVE_HINTS; i++ )
		if( m_moveHint[ i ].sourceID == msg->getArgument( 0 )->objectID &&
				m_moveHint[ i ].frame != 0 )
			expireHint( MOVE_HINT, i );

		
	if( getSelectCount() == 1 )
	{
		Drawable *draw = getFirstSelectedDrawable();
		Object *obj = draw ? draw->getObject() : NULL;
		if( obj && obj->isKindOf( KINDOF_IMMOBILE ) )
		{
			//Don't allow move hints to be created if our selected object can't move!
			return;
		}
	}

	m_moveHint[ m_nextMoveHint ].frame = TheGameClient->getFrame();
	m_moveHint[ m_nextMoveHint ].pos = msg->getArgument( 0 )->location;
		
	m_nextMoveHint++;

	// wrap around
	if (m_nextMoveHint == InGameUI::MAX_MOVE_HINTS)
		m_nextMoveHint = 0;
}

//-------------------------------------------------------------------------------------------------
/** An attack command has occurred, start graphical "hint". */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::createAttackHint present-unmatched
void InGameUI::createAttackHint( const GameMessage *msg )
{

}

//-------------------------------------------------------------------------------------------------
/** A force attack command has occurred, start graphical "hint". */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::createForceAttackHint present-unmatched
void InGameUI::createForceAttackHint( const GameMessage *msg )
{

}

// InGameUI::createGarrisonHint: defined in InGameUIInputModes.cpp (its row's unit).

#if defined(_DEBUG) || defined(_INTERNAL)
#define AI_DEBUG_TOOLTIPS		1

#ifdef AI_DEBUG_TOOLTIPS
#include "Common/StateMachine.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/AIPathfind.h"
#endif // AI_DEBUG_TOOLTIPS

#endif // defined(_DEBUG) || defined(_INTERNAL)

//-------------------------------------------------------------------------------------------------
/** Details of what is mouse hovered over right now are in this message.  Terrain might result
	* in just a tooltip.  An object might get a tooltip and show its hit points.
 */
//-------------------------------------------------------------------------------------------------
// InGameUI::createMouseoverHint: defined in InGameUICreateMouseoverHint.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** A command would be given if a click were to happen, so give a preview hint of what it would be.
	* Changing the mouse cursor is an example
	*/
// ?InGameUI::createCommandHint present-unmatched
void InGameUI::createCommandHint( const GameMessage *msg )
{
	if (m_isScrolling || m_isSelecting || TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
		return;

	const Drawable *draw = TheGameClient->findDrawableByID(m_mousedOverDrawableID);
	GameMessage::Type t = msg->getType();
//#ifdef DO_SHROUD_PROJECTION
	if( draw && (t == GameMessage::MSG_DO_ATTACK_OBJECT_HINT || t == GameMessage::MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT) )
	{
		const Object* obj = draw->getObject();
		Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
#if defined(_DEBUG) || defined(_INTERNAL)
		ObjectShroudStatus ss = (!obj || !TheGlobalData->m_shroudOn) ? OBJECTSHROUD_CLEAR : obj->getShroudedStatus(localPlayerIndex);
#else
		ObjectShroudStatus ss = (!obj) ? OBJECTSHROUD_CLEAR : obj->getShroudedStatus(localPlayerIndex);
#endif
		if (ss == OBJECTSHROUD_SHROUDED)
		{
			t = GameMessage::MSG_DO_MOVETO_HINT;	// if the object is hidden, switch to something innocuous
		}
	}
//#endif


	setRadiusCursorNone();
  if ( TheGlobalData->m_doubleClickAttackMove )
  {
    if ( --m_duringDoubleClickAttackMoveGuardHintTimer > 0 )
    {
      setMouseCursor(Mouse::FORCE_ATTACK_GROUND);
		  setRadiusCursor(RADIUSCURSOR_GUARD_AREA, 
										  NULL,
										  PRIMARY_WEAPON);
      return;
    }
  }





	// set cursor to normal if there is a window under the cursor
	GameWindow *window = NULL;
	const MouseIO *io = TheMouse->getMouseStatus();
	Bool underWindow = false;
	if (io && TheWindowManager)
		window = TheWindowManager->getWindowUnderCursor(io->pos.x, io->pos.y);


	while (window)
	{
		if (window->winGetInputFunc() == LeftHUDInput) {
			underWindow = false;
			break;
		}
		
		// check to see if it or any of its parents are opaque.  If so, we can't select anything.
		if (!BitTest( window->winGetStatus(), WIN_STATUS_SEE_THRU ))
		{
			underWindow = true;
			break;
		}

		window = window->winGetParent();
	}

	//Add basic logic to determine if we can select a unit (or hint)
	const Object *obj = draw ? draw->getObject() : NULL;
	Bool drawSelectable = CanSelectDrawable(draw, FALSE);
	if( !obj )
	{
		drawSelectable = false;
	}

	// Note: These are only non-NULL if there is exactly one thing selected.
	const Drawable *srcDraw = NULL;
	const Object *srcObj = NULL;
	if (getSelectCount() == 1) {
		srcDraw = getAllSelectedDrawables()->front();
		srcObj = (srcDraw ? srcDraw->getObject() : NULL);
	}

	switch (m_mouseMode)
	{
		case MOUSEMODE_DEFAULT:
			{ 
				// This section of code only gets called when there is no specific cursor mode happening.
				if (underWindow || (srcObj && !srcObj->isLocallyControlled()))
				{
					setMouseCursor(Mouse::ARROW);
					return;
				}
				switch (t)
				{
					case GameMessage::MSG_DO_MOVETO_HINT:
					{
						if( !drawSelectable && srcObj && srcObj->isLocallyControlled() && srcObj->isKindOf(KINDOF_STRUCTURE))
							setMouseCursor( Mouse::GENERIC_INVALID );
						else if( drawSelectable && obj->isLocallyControlled() && !obj->isKindOf(KINDOF_MINE))
							setMouseCursor( Mouse::SELECTING );
						else if( TheRadar->isRadarWindow( window ) &&
										 TheRadar->isRadarForced() == FALSE &&
										 (TheRadar->isRadarHidden() || 
										 ThePlayerList->getLocalPlayer()->hasRadar() == FALSE) )
							setMouseCursor( Mouse::ARROW );
						else 
							setMouseCursor( Mouse::MOVETO );
						break;
					}
					case GameMessage::MSG_DO_ATTACKMOVETO_HINT:
						if( drawSelectable && obj->isLocallyControlled()  )
							setMouseCursor( Mouse::SELECTING );
						else
							setMouseCursor( Mouse::ATTACKMOVETO );
						break;
					case GameMessage::MSG_ADD_WAYPOINT_HINT:
						setMouseCursor( Mouse::WAYPOINT );
						break;
					case GameMessage::MSG_DO_ATTACK_OBJECT_HINT:
						setMouseCursor( Mouse::ATTACK_OBJECT );
						break;
					case GameMessage::MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT:
						setMouseCursor( Mouse::OUTRANGE );
						break;
					case GameMessage::MSG_DO_FORCE_ATTACK_OBJECT_HINT:
						setMouseCursor( Mouse::FORCE_ATTACK_OBJECT );
						break;
					case GameMessage::MSG_DO_FORCE_ATTACK_GROUND_HINT:
						setMouseCursor( Mouse::FORCE_ATTACK_GROUND );
						break;
					case GameMessage::MSG_GET_REPAIRED_HINT:
						setMouseCursor( Mouse::GET_REPAIRED );
						break;
					case GameMessage::MSG_DOCK_HINT:
						setMouseCursor( Mouse::DOCK );
						break;
					case GameMessage::MSG_GET_HEALED_HINT:
						setMouseCursor( Mouse::GET_HEALED );
						break;
					case GameMessage::MSG_DO_REPAIR_HINT:
						setMouseCursor( Mouse::DO_REPAIR );
						break;
					case GameMessage::MSG_RESUME_CONSTRUCTION_HINT:
						setMouseCursor( Mouse::RESUME_CONSTRUCTION );
						break;				
					case GameMessage::MSG_ENTER_HINT:
						setMouseCursor( Mouse::ENTER_FRIENDLY );
						break;
					case GameMessage::MSG_CONVERT_TO_CARBOMB_HINT:
					case GameMessage::MSG_HIJACK_HINT:
					case GameMessage::MSG_SABOTAGE_HINT:
						setMouseCursor( Mouse::ENTER_AGGRESSIVELY );
						break;
					case GameMessage::MSG_DEFECTOR_HINT:
						setMouseCursor( Mouse::DEFECTOR );
						break;
#ifdef ALLOW_SURRENDER
					case GameMessage::MSG_PICK_UP_PRISONER_HINT:
						setMouseCursor( Mouse::PICK_UP_PRISONER );
						break;
#endif
					case GameMessage::MSG_CAPTUREBUILDING_HINT:
						setMouseCursor( Mouse::CAPTUREBUILDING );
						break;
					case GameMessage::MSG_HACK_HINT:
						setMouseCursor( Mouse::HACK );
						break;
					case GameMessage::MSG_IMPOSSIBLE_ATTACK_HINT:
						setMouseCursor( Mouse::GENERIC_INVALID );
						break;
					case GameMessage::MSG_SET_RALLY_POINT_HINT:
						if ( !drawSelectable )
							setMouseCursor( Mouse::SET_RALLY_POINT );
						else
							setMouseCursor( Mouse::SELECTING );
						break;
					case GameMessage::MSG_DO_SPECIAL_POWER_OVERRIDE_DESTINATION_HINT:
						setMouseCursor( Mouse::PARTICLE_UPLINK_CANNON );
						break;
					case GameMessage::MSG_DO_SALVAGE_HINT:
						setMouseCursor( Mouse::MOVETO );
						break;
					case GameMessage::MSG_DO_INVALID_HINT:
						setMouseCursor( Mouse::GENERIC_INVALID );
						break;
				}
			}
			break;
		case MOUSEMODE_BUILD_PLACE:
			{
				if (underWindow)
				{
					setMouseCursor(Mouse::ARROW);
					return;
				}
				switch (t)
				{
					case GameMessage::MSG_DO_MOVETO_HINT:
					case GameMessage::MSG_DO_ATTACKMOVETO_HINT:
					case GameMessage::MSG_ADD_WAYPOINT:
						setMouseCursor(Mouse::BUILD_PLACEMENT);
						break;
					case GameMessage::MSG_DO_ATTACK_OBJECT_HINT:
					case GameMessage::MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT:
						setMouseCursor(Mouse::INVALID_BUILD_PLACEMENT);
						break;
				}
			}
			break;
		case MOUSEMODE_GUI_COMMAND:
			{
				if (underWindow)
				{
					setMouseCursor(Mouse::ARROW);
					return;
				}
				// set the mouse cursor for commands that need a targeting or to normal with no command
				if( m_pendingGUICommand )
				{
					if( m_pendingGUICommand->isContextCommand() || 
							InGameUIGetCommandType(m_pendingGUICommand) == GUI_COMMAND_SPECIAL_POWER ||
							InGameUIGetCommandType(m_pendingGUICommand) == GUI_COMMAND_SPECIAL_POWER_FROM_SHORTCUT )
					{
						//Here is the hook for when we are in a context sensitive command mode. We can
						//either do the specified command mode command or nothing! Whether or not the 
						//command is valid or not was determined in evaluateContextCommand which is
						//called first, and posts the appropriate message.
						AsciiString cursorName;	// empty by default
						switch( t )
						{
							case GameMessage::MSG_VALID_GUICOMMAND_HINT:
								cursorName = m_pendingGUICommand->getCursorName();
								break;
							case GameMessage::MSG_INVALID_GUICOMMAND_HINT:
							default:
								cursorName = m_pendingGUICommand->getInvalidCursorName();
								break;
						}

						Int index = TheMouse->getCursorIndex(cursorName);
						if( index != Mouse::INVALID_MOUSE_CURSOR )
						{
							setMouseCursor( (Mouse::MouseCursor)index );
						}
						else
						{
							setMouseCursor( Mouse::CROSS );
						}
						setRadiusCursor(m_pendingGUICommand->getRadiusCursorType(), //*****************************************************************
														m_pendingGUICommand->getSpecialPowerTemplate(),
														m_pendingGUICommand->getWeaponSlot());
					}
					else if( BitTest( m_pendingGUICommand->getOptions(), COMMAND_OPTION_NEED_TARGET ) )
					{
						Int index = TheMouse->getCursorIndex(m_pendingGUICommand->getCursorName());
						if (index != Mouse::INVALID_MOUSE_CURSOR)
							setMouseCursor( (Mouse::MouseCursor)index );
						else
							setMouseCursor( Mouse::CROSS );
						setRadiusCursor(m_pendingGUICommand->getRadiusCursorType(), //*****************************************************************
														m_pendingGUICommand->getSpecialPowerTemplate(),
														m_pendingGUICommand->getWeaponSlot());
					}
					else
					{
						setRadiusCursorNone();
					}
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------------------------
/// Get drawable ID under cursor
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getMousedOverDrawableID present-unmatched
DrawableID InGameUI::getMousedOverDrawableID( void ) const
{

	return m_mousedOverDrawableID;

}

// InGameUI::setScrolling: defined in InGameUIInputModes.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/// are we scrolling?
//-------------------------------------------------------------------------------------------------
// ?InGameUI::isScrolling present-unmatched
// Select-any: the rowed BFME2 body in InGameUIInputModes.cpp comes first in
// link order, so this differing ZH-donor spelling folds without being kept.
inline __declspec(noinline) Bool InGameUI::isScrolling( void )
{
	return m_isScrolling;
}

//-------------------------------------------------------------------------------------------------
/// set drag select mode
//-------------------------------------------------------------------------------------------------
// ?InGameUI::setSelecting present-unmatched
// Select-any, as isScrolling above.
inline __declspec(noinline) void InGameUI::setSelecting( Bool isSelecting )
{
	if (m_isSelecting == isSelecting)
	{
		return;
	}

	//setMouseCursor( Mouse::SELECTING );
	m_isSelecting = isSelecting;
}

//-------------------------------------------------------------------------------------------------
/// are we selecting?
//-------------------------------------------------------------------------------------------------
// ?InGameUI::isSelecting present-unmatched
// Select-any, as isScrolling above.
inline __declspec(noinline) Bool InGameUI::isSelecting( void )
{
	return m_isSelecting;
}

//-------------------------------------------------------------------------------------------------
/// get scroll amount
//-------------------------------------------------------------------------------------------------
// ?InGameUI::setScrollAmount present-unmatched
void InGameUI::setScrollAmount( Coord2D amt )
{
	m_scrollAmt = amt;
}

//-------------------------------------------------------------------------------------------------
/// get scroll amount
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getScrollAmount present-unmatched
Coord2D InGameUI::getScrollAmount( void )
{
	return m_scrollAmt;
}

// InGameUI::setGUICommand: defined in InGameUIInputModes.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Get the pending gui command */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getGUICommand present-unmatched
const CommandButton *InGameUI::getGUICommand( void ) const
{

	return m_pendingGUICommand;

} 

//-------------------------------------------------------------------------------------------------
/** Destroy any drawables we have in our placement icon array and set to NULL */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::destroyPlacementIcons present-unmatched
void InGameUI::destroyPlacementIcons( void )
{
	Int i;

	for( i = 0; i < TheGlobalData->m_maxLineBuildObjects; ++i )
	{

		if( m_placeIcon[ i ] ) 
		{
			TheTerrainVisual->removeFactionBibDrawable(m_placeIcon[ i ]);
			TheGameClient->destroyDrawable( m_placeIcon[ i ] );
		}
		m_placeIcon[ i ] = NULL;

	}  // end for i
	TheTerrainVisual->removeAllBibs();

}  // end destroyPlacementIcons

//-------------------------------------------------------------------------------------------------
/** User has clicked on a built item that requires placement in the world.  We will 
	* record what that thing is so that the we can catch the next click in the world
	* and try to place the object there */
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** Return the thing we're attempting to place */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getPendingPlaceType present-unmatched
const ThingTemplate *InGameUI::getPendingPlaceType( void )
{
	return m_pendingPlaceType;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getPendingPlaceSourceObjectID present-unmatched
const ObjectID InGameUI::getPendingPlaceSourceObjectID( void )
{

	return m_pendingPlaceSourceObjectID;

}  // end getPendingPlaceSourceObjectID

//-------------------------------------------------------------------------------------------------
/** Start the angle selection interface for selecting building angles when placing them */
//-------------------------------------------------------------------------------------------------
// InGameUI::setPlacementStart: defined in InGameUIPlacement.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Set the end anchor for the angle build interface */
//-------------------------------------------------------------------------------------------------
// InGameUI::setPlacementEnd: defined in InGameUIPlacement.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Is the angle selection interface for placing building at angles up? */
//-------------------------------------------------------------------------------------------------
// InGameUI::isPlacementAnchored: defined in InGameUIPlacement.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Get the start and end anchor points for the building angle selection interface */
//-------------------------------------------------------------------------------------------------
// InGameUI::getPlacementPoints: defined in InGameUIPlacement.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Return the angle of the drawable at the cursor if any */
//-------------------------------------------------------------------------------------------------
// InGameUI::getPlacementAngle: defined in InGameUIPlacement.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Mark given Drawable as "selected". */
//-------------------------------------------------------------------------------------------------
// Native selection is recovered in InGameUISelectDrawable.cpp.

//-------------------------------------------------------------------------------------------------
/** Clear "selected" status of Drawable. */
//-------------------------------------------------------------------------------------------------
// InGameUI::deselectDrawable: defined in Common/InGameUIDeselectDrawable.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// InGameUI::deselectAllDrawables: defined in InGameUISelection.cpp (its row's unit).



//-------------------------------------------------------------------------------------------------
/** Return the list of all the currently selected Drawable pointers. */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getAllSelectedDrawables present-unmatched
const DrawableList *InGameUI::getAllSelectedDrawables( void ) const
{
	return &m_selectedDrawables;
}

//-------------------------------------------------------------------------------------------------
/** Return the list of all the currently selected Drawable pointers. */
//-------------------------------------------------------------------------------------------------
// InGameUI::getAllSelectedLocalDrawables: defined in InGameUIGetAllSelectedLocalDrawables.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** Return poiner to the first selected drawable, if any */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::getFirstSelectedDrawable present-unmatched
Drawable *InGameUI::getFirstSelectedDrawable( void )
{

	// sanity
	if( m_selectedDrawables.empty() )
		return NULL;  // this is valid, nothing is selected

	return m_selectedDrawables.front();

}  // end getFirstSelectedDrawable

//-------------------------------------------------------------------------------------------------
/** Return true if the selected ID is in the drawable list */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::isDrawableSelected present-unmatched
Bool InGameUI::isDrawableSelected( DrawableID idToCheck ) const
{

	for( DrawableListCIt it = m_selectedDrawables.begin(); it != m_selectedDrawables.end(); ++it ) 
	{

		if( (*it)->getID() == idToCheck )
			return TRUE;

	}  // end for

	return FALSE;

}  // end isDrawableSelected

// InGameUI::isAnySelectedKindOf: defined in InGameUISelection.cpp (its row's unit).
// InGameUI::isAllSelectedKindOf: defined in InGameUISelection.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Set the input enabled/disabled */
//-------------------------------------------------------------------------------------------------
void InGameUI::setInputEnabled( Bool enable )
{
	if(!enable)
		setSelecting( FALSE );
	
	Bool wasEnabled = m_inputEnabled;

	m_inputEnabled = enable;
	
	if (wasEnabled && !enable)
	{
		/*
			when input is disabled, clear out all the special "modes" we can be in, since we can miss
			the "exit mode" message during the cinematic. e.g., hold down the ctrl key when a cinematic
			begins, then release it during the cinematic... since input is disabled, we never see the keyup
			and thus think we're still in forceattack when its done, until you jiggle that key again.
			(admittedly, this code will actually do the wrong thing if you were to hold down the ctrl
			key thru the whole cinematic, but that's even more unlikely...)
		*/
		setForceAttackMode( false );			// CTRL
		setForceMoveMode( false );				// apparently unmapped in current CommandMap.ini
		setWaypointMode( false );					// ALT
		setPreferSelectionMode( false );	// SHIFT
		setCameraRotateLeft( false );			// KP4
		setCameraRotateRight( false );		// KP6
		setCameraZoomIn( false );					// KP8
		setCameraZoomOut( false );				// KP2
	}
}

//-------------------------------------------------------------------------------------------------
/** Drawable is being destroyed, clean up any UI elements associated with it. */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::disregardDrawable present-unmatched
void InGameUI::disregardDrawable( Drawable *draw )
{

	// make sure drawable is no longer selected
	deselectDrawable( draw );		

}

//-------------------------------------------------------------------------------------------------
/** This is called after the UI has been drawn. */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::postDraw present-unmatched
void InGameUI::postDraw( void )
{

	// render our display strings for the messages if on
	if( m_messagesOn )
	{
		Int i, x, y;
		Color dropColor;
		UnsignedByte r, g, b, a;

		x = m_messagePosition.x;
		y = m_messagePosition.y;
		for( i = MAX_UI_MESSAGES - 1; i >= 0; i-- )
		{

			if( m_uiMessages[ i ].displayString )
			{

				// make drop color black, but use the alpha setting of the fill color specified (for fading)
				GameGetColorComponents( m_uiMessages[ i ].color, &r, &g, &b, &a );
				dropColor = GameMakeColor( 0, 0, 0, a );

				// draw the text
				m_uiMessages[ i ].displayString->draw( x, y, m_uiMessages[ i ].color, dropColor );

				// increment text spot to next location
				GameFont *font = m_uiMessages[ i ].displayString->getFont();
				y += font->height;

			}  //end if

		}  // end for i

	}  // end if

	if( m_militarySubtitle )
	{
		ICoord2D pos;
		pos.x = m_militarySubtitle->position.x;
		pos.y = m_militarySubtitle->position.y;
		Color dropColor;
		UnsignedByte r, g, b, a;
		GameGetColorComponents( m_militarySubtitle->color, &r, &g, &b, &a );
		dropColor = GameMakeColor( 0, 0, 0, a );
		for(Int i = 0; i <= m_militarySubtitle->currentDisplayString; i++)
		{
			m_militarySubtitle->displayStrings[i]->draw(pos.x,pos.y, m_militarySubtitle->color,dropColor );
			Int height;
			m_militarySubtitle->displayStrings[i]->getSize(NULL, &height);
			pos.y += height;
		}
		if( m_militarySubtitle->blockDrawn )
		{
			ICoord2D size;
			size.y = m_militarySubtitle->displayStrings[m_militarySubtitle->currentDisplayString]->getFont()->height;
			size.x = size.y * 0.8f;
			TheDisplay->drawFillRect(m_militarySubtitle->blockPos.x, m_militarySubtitle->blockPos.y, size.x, size.y, m_militarySubtitle->color);
		}

	}

	// draw superweapon timers
  // Also responsible for Eva saying "Superweapon is ready for launch"
  //  IMPORTANT: Don't bail out of this block early just because you don't 
  //  want to display the timers -- Eva still needs to be checked
	if (TheGameLogic->getFrame() > 0 )
	{
//	Int superweaponCount = 0;
		Int startX = (Int)(m_superweaponPosition.x * TheDisplay->getWidth());
		Int startY = (Int)(m_superweaponPosition.y * TheDisplay->getHeight());
		
		Int bottomMargin = (Int)( (Real)TheTacticalView->getHeight() * 0.82f ); 
			


		Bool marginExceeded = FALSE;

		for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
		{
			Color bgColor = GameMakeColor( 0, 0, 0, 255 );
			for (SuperweaponMap::iterator mapIt = m_superweapons[i].begin(); mapIt != m_superweapons[i].end(); ++mapIt)
			{
				AsciiString templateName = mapIt->first;
				for (SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt)
				{
					SuperweaponInfo *info = *listIt;
					DEBUG_ASSERTCRASH(info, ("No superweapon info!"));
					if (info && !info->m_hiddenByScript && !info->m_hiddenByScience)
					{
						//enforce bottom margin of tactical view
						if ( startY >= bottomMargin)
						{
							UnicodeString ellipsis;
							ellipsis.format(L"...");
							info->setText( ellipsis, ellipsis );
							info->setFont( m_superweaponReadyFont, m_superweaponNormalPointSize, m_superweaponNormalBold );
							info->drawTime( startX,	startY, m_superweaponFlashColor, bgColor );
							
							marginExceeded = TRUE;
						}

						Object * owningObject = TheGameLogic->findObjectByID(info->m_id);
						if (owningObject)
						{
							
							// We don't draw our timers until we are finished with construction.
							// It is important that let the SpecialPowerUpdate is add its timer in its contructor,,
							// since the science for it could be added before construction is finished,
							// And thus the timer set to READY before the timer is first drawn, here
							if ( owningObject->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ))
								continue;

							SpecialPowerModuleInterface *module = owningObject->getSpecialPowerModule(info->getSpecialPowerTemplate());
							if (module)
							{
								// found one - draw it
 								Bool isReady = module->isReady();
 								Int readySecs;
 
								// IsReady includes disabledness, so if you have a 0 timer disabled super, you don't want 
 								// the UnsignedInt to wrap around to hundreds of millions of seconds.
 								if( module->getReadyFrame() < TheGameLogic->getFrame() )
									readySecs = 0;
 								else 
 									readySecs = (module->getReadyFrame() - TheGameLogic->getFrame()) / LOGICFRAMES_PER_SECOND;
								// Yes, integer math.  We can't have float imprecision display 4:01 on a disabled superweapon.
 
                // Only if we actually changed the ready status do we want to play an Eva event.
                if ( isReady && !info->m_evaReadyPlayed )
                {
                  if ( TheGameLogic->getFrame() > 0 )
                  {
                    SpecialPowerType type = module->getSpecialPowerTemplate()->getSpecialPowerType();
                  
                    Player *localPlayer = ThePlayerList->getLocalPlayer();
                  
                    if( type == SPECIAL_PARTICLE_UPLINK_CANNON || type == SUPW_SPECIAL_PARTICLE_UPLINK_CANNON || type == LAZR_SPECIAL_PARTICLE_UPLINK_CANNON )
                    {
                      if ( localPlayer == owningObject->getControllingPlayer() )
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Own_ParticleCannon);
                      }
                      else if ( localPlayer->getRelationship(owningObject->getTeam()) != ENEMIES )
                      {
                        // Note: counting relationship NEUTRAL as ally. Not sure if this makes a difference???
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Ally_ParticleCannon);
                      }
                      else
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Enemy_ParticleCannon);
                      }
                    }
                    else if( type == SPECIAL_NEUTRON_MISSILE || type == NUKE_SPECIAL_NEUTRON_MISSILE || type == SUPW_SPECIAL_NEUTRON_MISSILE )
                    {
                      if ( localPlayer == owningObject->getControllingPlayer() )
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Own_Nuke);
                      }
                      else if ( localPlayer->getRelationship(owningObject->getTeam()) != ENEMIES )
                      {
                        // Note: counting relationship NEUTRAL as ally. Not sure if this makes a difference???
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Ally_Nuke);
                      }
                      else
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Enemy_Nuke);
                      }
                    }
                    else if (type == SPECIAL_SCUD_STORM)
                    {
                      if ( localPlayer == owningObject->getControllingPlayer() )
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Own_ScudStorm);
                      }
                      else if ( localPlayer->getRelationship(owningObject->getTeam()) != ENEMIES )
                      {
                        // Note: counting relationship NEUTRAL as ally. Not sure if this makes a difference???
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Ally_ScudStorm);
                      }
                      else
                      {
                        TheEva->setShouldPlay(EVA_SuperweaponReady_Enemy_ScudStorm);
                      }
                    }
                  }
                  info->m_evaReadyPlayed = true;
                }
                else
                {
                  if ( !isReady )
                    info->m_evaReadyPlayed = false; // Reset Eva for next time
                }
              
                // draw the text
                if ( !m_superweaponHiddenByScript && !marginExceeded )
                {
                  // Similarly, only checking timers is not truly indicitive of readyness.
 								  Bool changeBolding = (readySecs != info->m_timestamp) || (isReady != info->m_ready) || info->m_forceUpdateText;
 								  if (changeBolding)
 								  {
 									  if (isReady)
									  {
										  // go bold - we're good to go
										  info->setFont( m_superweaponReadyFont, m_superweaponReadyPointSize, m_superweaponReadyBold );
									  }
									  else
									  {
										  // if we were at 0, we've just fired - kill the bold
										  if (info->m_timestamp == 0)
										  {
											  info->setFont( m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold );
										  }
									  }
                  
									  
									  info->m_forceUpdateText = false;
 									  info->m_ready = isReady;
									  info->m_timestamp = readySecs;
                    Int min = readySecs/60;
                    Int sec = readySecs - min*60;
                    AsciiString strIndex;
                    strIndex.format("GUI:%s", templateName.str());
                    UnicodeString name, time;
                    name.format(L"%ls: ", TheGameText->fetch(strIndex.str()).str());
                    time.format(L"%d:%2.2d", min, sec);
                    info->setText(name, time);
                  }

                  if (isReady)
								  {
									  if ( m_superweaponFlashDuration != 0.0f )
									  {
										  if ( TheGameLogic->getFrame() >= m_superweaponLastFlashFrame + (Int)(m_superweaponFlashDuration) )
										  {
											  m_superweaponUsedFlashColor = !m_superweaponUsedFlashColor;
											  m_superweaponLastFlashFrame = TheGameLogic->getFrame();
										  }
										  info->drawName( startX,
											  startY, (m_superweaponUsedFlashColor)?0:m_superweaponFlashColor, bgColor );
										  info->drawTime( startX,
											  startY, (m_superweaponUsedFlashColor)?0:m_superweaponFlashColor, bgColor );
									  }
									  else
									  {
										  info->drawName( startX, startY, 0, bgColor );
										  info->drawTime( startX, startY, 0, bgColor );
									  }
								  }
								  else
								  {
									  info->drawName( startX,	startY, 0, bgColor );
									  info->drawTime( startX, startY, 0, bgColor );
								  }

								  // increment text spot to next location
								  startY += info->getHeight();

                }
                if (info->getSpecialPowerTemplate()->isSharedNSync())
                  break; // Wow, it is almost too easy!
                // This prevents redundant timers for shared powers/superweapons
                // No matter how many specialpowermodules register their timers with me,
                // I will only draw the timer of the first valid one in my list,
                // since they all have the same template, ans they all
                // use the Player::getReadyFrame() functions to stay in sync.
              }
						}
					}
				}
			}
		}
	}

	// draw named timers
	if (TheGameLogic->getFrame() > 0 && m_showNamedTimers)
	{
//		Int namedTimerCount = 0;
		Bool reverseXDir = (m_namedTimerPosition.x >= 0.5f);
		Int startX = (Int)(m_namedTimerPosition.x * TheDisplay->getWidth());
		Int startY = (Int)(m_namedTimerPosition.y * TheDisplay->getHeight());
		Color bgColor = GameMakeColor( 0, 0, 0, 255 );
		for (NamedTimerMapIt mapIt = m_namedTimers.begin(); mapIt != m_namedTimers.end(); ++mapIt)
		{
			AsciiString timerName = mapIt->first;
			NamedTimerInfo *info = mapIt->second;
			DEBUG_ASSERTCRASH(info, ("No namedTimer info!"));
			if (info)
			{
				// found one - draw it
				UnicodeString line;
				Int framesLeft = TheScriptEngine->getCounter(timerName)->value;
				UnsignedInt readyFrame = TheGameLogic->getFrame();
				if (framesLeft > 0)
					readyFrame += framesLeft;
				Int readySecs = (Int)(SECONDS_PER_LOGICFRAME_REAL * (readyFrame - TheGameLogic->getFrame()));
				if ( (info->isCountdown && readySecs != info->timestamp) || (!info->isCountdown && framesLeft != info->timestamp) )
				{
					if (!readySecs && info->isCountdown)
					{
						// go bold - we're good to go
						info->displayString->setFont( TheFontLibrary->getFont( m_namedTimerReadyFont, 
							TheGlobalLanguageData->adjustFontSize(m_namedTimerReadyPointSize), m_namedTimerReadyBold ) );
					}
					else
					{
						// if we were at 0, we've just fired - kill the bold
						if (info->timestamp == 0 || info->isCountdown)
						{
							info->displayString->setFont( TheFontLibrary->getFont( m_namedTimerNormalFont, 
								TheGlobalLanguageData->adjustFontSize(m_namedTimerNormalPointSize), m_namedTimerNormalBold ) );
						}
					}

					info->timestamp = readySecs;
					Int min = readySecs/60;
					Int sec = readySecs - min*60;
					
					if (!info->isCountdown)
						line.format(L"%s %d", info->timerText.str(), framesLeft);
					else
					{
						if (sec >= 10)
							line.format(L"%s %d:%d", info->timerText.str(), min, sec);
						else
							line.format(L"%s %d:0%d", info->timerText.str(), min, sec);
					}
					info->displayString->setText(line);
				}

				// draw the text
				Int drawX = startX;
				if (reverseXDir)
					drawX -= info->displayString->getWidth();
				if (!readySecs && info->isCountdown)
				{
					if ( m_namedTimerFlashDuration != 0.0f )
					{
						if ( TheGameLogic->getFrame() >= m_namedTimerLastFlashFrame + (Int)(m_namedTimerFlashDuration) )
						{
							m_namedTimerUsedFlashColor = !m_namedTimerUsedFlashColor;
							m_namedTimerLastFlashFrame = TheGameLogic->getFrame();
						}
						info->displayString->draw( drawX, startY, (m_namedTimerUsedFlashColor)?info->color:m_namedTimerFlashColor, bgColor );
					}
					else
					{
						info->displayString->draw( drawX, startY, info->color, bgColor );
					}
				}
				else
				{
					info->displayString->draw( drawX, startY, info->color, bgColor );
				}

				// increment text spot to next location
				startY -= info->displayString->getFont()->height;
			}
		}
	}
	
	// draw RMB scroll anchor
	if (TheLookAtTranslator && m_drawRMBScrollAnchor)
	{
		const ICoord2D* anchor = TheLookAtTranslator->getRMBScrollAnchor();
		if (anchor)
		{
			static const Int w = 2;
			static const Int h = 2;
			static const Int r = 4; // ratio
			static const Color mainColor = GameMakeColor(0, 255, 0, 255);
			static const Color dropColor = GameMakeColor(0, 0, 0, 255);
			TheDisplay->drawFillRect( anchor->x-w*r-1, anchor->y-h-1, w*2*r+3, h*2+3, dropColor );
			TheDisplay->drawFillRect( anchor->x-w-1, anchor->y-h*r-1, w*2+3, h*2*r+3, dropColor );
			TheDisplay->drawFillRect( anchor->x-w*r, anchor->y-h, w*2*r+1, h*2+1, mainColor );
			TheDisplay->drawFillRect( anchor->x-w, anchor->y-h*r, w*2+1, h*2*r+1, mainColor );
		}
	}

	//draw superweapon ready multipliers
	TheControlBar->drawSpecialPowerShortcutMultiplierText();

}  // end postDraw

//-------------------------------------------------------------------------------------------------
/** Expire a hint of the specified type with the corresponding hint index */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::expireHint present-unmatched
void InGameUI::expireHint( HintType type, UnsignedInt hintIndex )
{

	if( type == MOVE_HINT )
	{

		// sanity
		if( hintIndex < 0 || hintIndex >= MAX_MOVE_HINTS )
			return;

		m_moveHint[ hintIndex ].sourceID = 0;
		m_moveHint[ hintIndex ].frame = 0;

	}  // end if
	else
	{

		// undefined hint type
		DEBUG_CRASH(("undefined hint type"));
		return;

	}  // end else

}  // end expireHint

//-------------------------------------------------------------------------------------------------
/** Create the control user interface GUI */
//-------------------------------------------------------------------------------------------------
// InGameUI::createControlBar: defined in InGameUIMessages.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Create the replay control GUI */
//-------------------------------------------------------------------------------------------------
// InGameUI::createReplayControl: defined in InGameUIMessages.cpp (its row's unit).

// ------------------------------------------------------------------------------------------------
// InGameUI::playMovie
// ------------------------------------------------------------------------------------------------
// ?InGameUI::playMovie present-unmatched
void InGameUI::playMovie( const AsciiString& movieName )
{

	stopMovie();

	m_videoStream = TheVideoPlayer->open( movieName );

	if ( m_videoStream == NULL )
	{
		return;
	}

	m_currentlyPlayingMovie = movieName;
	m_videoBuffer = TheDisplay->createVideoBuffer();

	if (	m_videoBuffer == NULL || 
				!m_videoBuffer->allocate(	m_videoStream->width(), 
													m_videoStream->height())
		)
	{
		stopMovie();
		return;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::stopMovie present-unmatched
void InGameUI::stopMovie( void )
{
	delete m_videoBuffer;
	m_videoBuffer = NULL;

	if ( m_videoStream )
	{
		m_videoStream->close();
		m_videoStream = NULL;
	}

	if (!m_currentlyPlayingMovie.isEmpty()) {
		//TheScriptEngine->notifyOfCompletedVideo(m_currentlyPlayingMovie); // removing sync error source -MDC
		m_currentlyPlayingMovie = AsciiString::TheEmptyString;
	}
}

// ------------------------------------------------------------------------------------------------
// InGameUI::videoBuffer
// ------------------------------------------------------------------------------------------------
// ?InGameUI::videoBuffer present-unmatched
VideoBuffer* InGameUI::videoBuffer( void )
{
	return m_videoBuffer;
}

// ------------------------------------------------------------------------------------------------
// InGameUI::playMovie
// ------------------------------------------------------------------------------------------------
// The playCameoMovie body lives under InGameUIPlayCameoMovie.cpp (retail row); deleted here so the kept copy links.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?InGameUI::stopCameoMovie present-unmatched
void InGameUI::stopCameoMovie( void )
{
//RightHUD
	//GameWindow *window = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( AsciiString("ControlBar.wnd:CameoMovieWindow") ));
	GameWindow *window = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( AsciiString("ControlBar.wnd:RightHUD") ));
//	window->winHide(FALSE);
	WinInstanceData *winData = window->winGetInstanceData();
	winData->setVideoBuffer(NULL);
	
	delete m_cameoVideoBuffer;
	m_cameoVideoBuffer = NULL;

	if ( m_cameoVideoStream )
	{
		m_cameoVideoStream->close();
		m_cameoVideoStream = NULL;
	}
	
}

// ------------------------------------------------------------------------------------------------
// InGameUI::videoBuffer
// ------------------------------------------------------------------------------------------------
// ?InGameUI::cameoVideoBuffer present-unmatched
VideoBuffer* InGameUI::cameoVideoBuffer( void )
{
	return m_cameoVideoBuffer;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The displayCantBuildMessage body lives under InGameUIDisplayCantBuild.cpp (retail row); deleted here so the kept copy links.

// ------------------------------------------------------------------------------------------------
// InGameUI::militarySubtitle
// ------------------------------------------------------------------------------------------------
// InGameUI::militarySubtitle: defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// ------------------------------------------------------------------------------------------------
// InGameUI::removeMilitarySubtitle
// ------------------------------------------------------------------------------------------------
// InGameUI::removeMilitarySubtitle: defined in InGameUIMessages.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// InGameUI::areSelectedObjectsControllable: defined in Rva0029C752Check.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//------------------------------------------------------------------------------
//Resets the camera to default zoom and orientation.
//------------------------------------------------------------------------------
// InGameUI::resetCamera: defined in Rva0029B4F9Init.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

//------------------------------------------------------------------------------
//Checks to see if an object can interact with an object in a non-hostile manner. This is currently used by the selection 
//translator to determine whether to do something to an object or select it instead based on the context of what is currently
//selected.
//------------------------------------------------------------------------------
// ?InGameUI::canSelectedObjectsNonAttackInteractWithObject present-unmatched
Bool InGameUI::canSelectedObjectsNonAttackInteractWithObject( const Object *objectToInteractWith, SelectionRules rule ) const
{
	for( int i = 1; i < NUM_ACTIONTYPES; i++ )
	{
		if( i != ACTIONTYPE_ATTACK_OBJECT )
		{
			if( canSelectedObjectsDoAction( (ActionType)i, objectToInteractWith, rule ) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

// getCanSelectedObjectsAttack is recovered in InGameUICanSelectedObjectsDoAction.cpp.

//------------------------------------------------------------------------------
//Wrapper function that checks a specific action.
//------------------------------------------------------------------------------
// canSelectedObjectsDoAction is recovered in InGameUICanSelectedObjectsDoAction.cpp.

//------------------------------------------------------------------------------
// canSelectedObjectsDoSpecialPower is recovered in InGameUICanSelectedObjectsDoSpecialPower.cpp.

//------------------------------------------------------------------------------
// canSelectedObjectsOverrideSpecialPowerDestination is recovered in
// InGameUI_selectMatchingAcrossScreen.cpp with target-proven virtual/Drawable access.

//------------------------------------------------------------------------------
// InGameUI::canSelectedObjectsEffectivelyUseWeapon: native body in InGameUICanSelectedObjectsDoAction.cpp.


// ------------------------------------------------------------------------------------------------
// ?InGameUI::selectAllUnitsByTypeAcrossRegion present-unmatched
Int InGameUI::selectAllUnitsByTypeAcrossRegion( IRegion2D *region, KindOfMaskType mustBeSet, KindOfMaskType mustBeClear )
{
	KindOfSelectionData data;
	Int newSelectionCount = 0;
	Int oldSelectionCount = getAllSelectedDrawables()->size();

	data.m_mustbeSet = mustBeSet;
	data.m_mustbeClear = mustBeClear;

	if (region)
	{
		TheTacticalView->iterateDrawablesInRegion(region, kindOfUnitSelection, (void *)&data);
		newSelectionCount += data.newlySelectedDrawables.size();
	}
	else
	{
		// loop over the map
		Drawable *temp = TheGameClient->firstDrawable();
		while( temp )
		{
			if( kindOfUnitSelection( temp, (void *)&data) )
			{
				newSelectionCount ++;
			}

			temp = temp->getNextDrawable();
		}
	}
	setDisplayedMaxWarning( FALSE );

	if (newSelectionCount > 0)
	{
		// create selected message
		GameMessage *teamMsg = TheMessageStream->appendMessage( GameMessage::MSG_CREATE_SELECTED_GROUP );

		teamMsg->appendBooleanArgument( (oldSelectionCount == 0) ? TRUE : FALSE );

		const Drawable *draw;

		//Loop through each drawable add append it's objectID to the event.
		for( DrawableListCIt it = data.newlySelectedDrawables.begin(); it != data.newlySelectedDrawables.end(); ++it )
		{
			draw = *it;
			if( draw && draw->getObject() )
			{
				teamMsg->appendObjectIDArgument( draw->getObject()->getID() );
			}
		}
	}

	return newSelectionCount;
}

// ------------------------------------------------------------------------------------------------
/** Selects maching units on the screen */
// ------------------------------------------------------------------------------------------------
// InGameUI::selectMatchingAcrossRegion: defined in InGameUI_selectMatchingAcrossRegion.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// ------------------------------------------------------------------------------------------------
// ?InGameUI::selectAllUnitsByTypeAcrossScreen present-unmatched
Int InGameUI::selectAllUnitsByTypeAcrossScreen(KindOfMaskType mustBeSet, KindOfMaskType mustBeClear)
{
	/// When implementing this, obey TheInGameUI->getMaxSelectCount() if it is > 0
			
	IRegion2D region;
	ICoord2D origin;
	ICoord2D size;
 
	TheTacticalView->getOrigin( &origin.x, &origin.y );
	size.x = TheTacticalView->getWidth();
	size.y = TheTacticalView->getHeight();
 
	buildRegion( &origin, &size, &region );

	Int numSelected = selectAllUnitsByTypeAcrossRegion(&region, mustBeSet, mustBeClear);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch( "GUI:NothingSelected" );
		TheInGameUI->message( message );
	}
	else if (numSelected == 0)
	{
	}
	else
	{
		UnicodeString message = TheGameText->fetch( "GUI:SelectedAcrossScreen" );
		TheInGameUI->message( message );
	}
	return numSelected;
}

// ------------------------------------------------------------------------------------------------
/** Selects maching units on the screen */
// ------------------------------------------------------------------------------------------------
// InGameUI::selectMatchingAcrossScreen: defined in InGameUI_selectMatchingAcrossScreen.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// ?InGameUI::selectAllUnitsByTypeAcrossMap present-unmatched
Int InGameUI::selectAllUnitsByTypeAcrossMap(KindOfMaskType mustBeSet, KindOfMaskType mustBeClear)
{
	/// When implementing this, obey TheInGameUI->getMaxSelectCount() if it is > 0
	Int numSelected = selectAllUnitsByTypeAcrossRegion(NULL, mustBeSet, mustBeClear);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch( "GUI:NothingSelected" );
		TheInGameUI->message( message );
	}
	else if (numSelected == 0)
	{
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if( !draw || !draw->getObject() || !draw->getObject()->isKindOf( KINDOF_STRUCTURE ) )
		{
			UnicodeString message = TheGameText->fetch( "GUI:SelectedAcrossMap" );
			TheInGameUI->message( message );
		}
	}
	else
	{
		UnicodeString message = TheGameText->fetch( "GUI:SelectedAcrossMap" );
		TheInGameUI->message( message );
	}
	return numSelected;
}

//-------------------------------------------------------------------------------------------------
/** Selects matching units across map */
//-------------------------------------------------------------------------------------------------
// InGameUI::selectMatchingAcrossMap: defined in InGameUI_selectMatchingAcrossMap.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// ?InGameUI::selectAllUnitsByType present-unmatched
Int InGameUI::selectAllUnitsByType(KindOfMaskType mustBeSet, KindOfMaskType mustBeClear)
{
	/// When implementing this, obey TheInGameUI->getMaxSelectCount() if it is > 0
	Int numSelected = selectAllUnitsByTypeAcrossScreen(mustBeSet, mustBeClear);
	if (numSelected == -1)
	{
		return numSelected;
	}

	if (numSelected == 0)
	{
		Int numSelectedAcrossMap = selectAllUnitsByTypeAcrossMap(mustBeSet, mustBeClear);
		return numSelectedAcrossMap;
	}
	return numSelected;
}

//-------------------------------------------------------------------------------------------------
/** Selects matching units, either on screen or across map.  When called by pressing 'T',
    their is not a way to tell if the game is supposed to select across the screen, or
    across the map.  For mouse clicks, i.e. Alt + click or double click, we can directly call
    selectMatchingAcrossScreen or selectMatchingAcrossMap */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::selectUnitsMatchingCurrentSelection present-unmatched
Int InGameUI::selectUnitsMatchingCurrentSelection()
{
	/// When implementing this, obey TheInGameUI->getMaxSelectCount() if it is > 0
	Int numSelected = selectMatchingAcrossScreen();
	if (numSelected == -1)
		return numSelected;
	if (numSelected == 0)
	{
		Int numSelectedAcrossMap = selectMatchingAcrossMap();
		//if (numSelectedAcrossMap < 1)
		//{
			//UnicodeString message = TheGameText->fetch( "GUI:NothingSelected" );
			//TheInGameUI->message( message );
		//}
		return numSelectedAcrossMap;
	}
	return numSelected;

}

//-----------------------------------------------------------------------------
/**
 * Given an "anchor" point and the current mouse position (dest),
 * construct a valid 2D bounding region.
 */
//-----------------------------------------------------------------------------------
// ?InGameUI::buildRegion present-unmatched
void InGameUI::buildRegion( const ICoord2D *anchor, const ICoord2D *dest, IRegion2D *region )
{
	// build rectangular region defined by the drag selection
	if (anchor->x < dest->x)
	{
		region->lo.x = anchor->x;
		region->hi.x = dest->x;
	}
	else
	{
		region->lo.x = dest->x;
		region->hi.x = anchor->x;
	}

	if (anchor->y < dest->y)
	{
		region->lo.y = anchor->y;
		region->hi.y = dest->y;
	}
	else
	{
		region->lo.y = dest->y;
		region->hi.y = anchor->y;
	}
}

//-------------------------------------------------------------------------------------------------
/** Add a new floating text to our list */
//-------------------------------------------------------------------------------------------------
// InGameUI::addFloatingText: defined in InGameUIFloatingText.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#if defined(_DEBUG) || defined(_INTERNAL)
inline Bool isClose(Real a, Real b) { return fabs(a-b) <= 1.0f; }
inline Bool isClose(const Coord3D& a, const Coord3D& b) 
{
		return	isClose(a.x, b.x) && 
			isClose(a.y, b.y) && 
			isClose(a.z, b.z);
}
// ?InGameUI::DEBUG_addFloatingText present-unmatched
void InGameUI::DEBUG_addFloatingText(const AsciiString& text, const Coord3D * pos, Color color)
{
	const Int POINTSIZE = 8;
	const Int LEADING = 0;

	Coord3D posToUse = *pos;

try_again:
	for (FloatingTextListIt it = m_floatingTextList.begin(); it != m_floatingTextList.end(); ++it)
	{
		if (isClose((*it)->m_pos3D, posToUse))
		{
			posToUse.z -= (POINTSIZE + LEADING);
			goto try_again;
		}
	}

	FloatingTextData *newFTD = newInstance( FloatingTextData );
	newFTD->m_color = color;
	newFTD->m_pos3D.x = posToUse.x;
	newFTD->m_pos3D.y = posToUse.y;
	newFTD->m_pos3D.z = posToUse.z;
	UnicodeString translate;
	translate.translate(text);
	newFTD->m_text = translate;
	newFTD->m_dString->setText(translate);
	newFTD->m_dString->setFont(TheWindowManager->winFindFont( AsciiString("Arial"), POINTSIZE, FALSE ));
				
	if(m_floatingTextTimeOut <= 0)
		newFTD->m_frameTimeOut = TheGameLogic->getFrame() +  DEFAULT_FLOATING_TEXT_TIMEOUT;
	else
		newFTD->m_frameTimeOut = TheGameLogic->getFrame() +  m_floatingTextTimeOut; 
	
	m_floatingTextList.push_front( newFTD ); // add to the list

	//DEBUG_LOG(("%s\n",text.str()));
}
#endif

//-------------------------------------------------------------------------------------------------
/** modify the position of our floating text */
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** Itterates through and draws each floating text */
//-------------------------------------------------------------------------------------------------
// InGameUI::drawFloatingText: defined in InGameUI_drawFloatingText.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** ittereate through and clear out the list of floating text */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::clearFloatingText present-unmatched
void InGameUI::clearFloatingText( void )
{
	FloatingTextData *ftd;
	// loop through and draw all the texts
	for(FloatingTextListIt it = m_floatingTextList.begin(); it != m_floatingTextList.end();)
	{
		ftd = *it;
		it = m_floatingTextList.erase(it);
		ftd->deleteInstance();
	}
	
}

//-------------------------------------------------------------------------------------------------
/** If we want to use the default text color, then we call this function */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::popupMessage present-unmatched
void InGameUI::popupMessage( const AsciiString& message, Int x, Int y, Int width, Bool pause, Bool pauseMusic)
{
	popupMessage( message, x, y, width, m_popupMessageColor, pause, pauseMusic);
}

//-------------------------------------------------------------------------------------------------
/** initialize, and popup a message box to the user */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::popupMessage present-unmatched
void InGameUI::popupMessage( const AsciiString& identifier, Int x, Int y, Int width, Color textColor, Bool pause, Bool pauseMusic)
{
	if(m_popupMessageData)
		clearPopupMessageData();

	UpdateDiplomacyBriefingText(identifier, FALSE);

	UnicodeString message = TheGameText->fetch(identifier);

	m_popupMessageData = newInstance( PopupMessageData );	
	m_popupMessageData->message = message;
	// x and why are passed in as a percentage of the screen, convert to screen coords
	if( x > 100 )
		x = 100;
	if( x < 0 )
		x = 0;
	
	if( y > 100 )
		y = 100;
	if( y < 0 )
		y = 0;

	m_popupMessageData->x = TheDisplay->getWidth() * (INT_TO_REAL(x) / 100);
	m_popupMessageData->y = TheDisplay->getHeight() * (INT_TO_REAL(y) / 100);
	// cap the lower limit of the width
	if(width < 50)
		width = 50;
	m_popupMessageData->width = width;
	m_popupMessageData->textColor = textColor;
	m_popupMessageData->pause = pause;
	m_popupMessageData->pauseMusic = pauseMusic;

	if( pause )
		TheGameLogic->setGamePaused(TRUE, pauseMusic);

	m_popupMessageData->layout = TheWindowManager->winCreateLayout(AsciiString("InGamePopupMessage.wnd"));
	m_popupMessageData->layout->runInit();
}

//-------------------------------------------------------------------------------------------------
/** take care of the logic of clearing the popupMessageData */
//-------------------------------------------------------------------------------------------------
// ?InGameUI::clearPopupMessageData present-unmatched
void InGameUI::clearPopupMessageData( void )
{
	if(!m_popupMessageData)
		return;
	if(m_popupMessageData->layout)
	{
		m_popupMessageData->layout->destroyWindows();
		m_popupMessageData->layout->deleteInstance();
		m_popupMessageData->layout = NULL;
	}
	if( m_popupMessageData->pause )
		TheGameLogic->setGamePaused(FALSE, m_popupMessageData->pauseMusic);
	m_popupMessageData->deleteInstance();
	m_popupMessageData = NULL;
	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** Floating Text Constructor */
//-------------------------------------------------------------------------------------------------
// FloatingTextData::FloatingTextData: defined in InGameUIFloatingText.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Floating Text Destructor */
//-------------------------------------------------------------------------------------------------
// ?FloatingTextData::~FloatingTextData present-unmatched
FloatingTextData::~FloatingTextData(void)
{
	if(m_dString)
		TheDisplayStringManager->freeDisplayString( m_dString );
	m_dString = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// WORLD ANIMATION DATA ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorldAnimationData::WorldAnimationData (retail 0x0029AF82) is rowed in
// InGameUIAddWorldAnimation.cpp, whose addWorldAnimation inlines it and
// emits the out-of-line copy; a second, non-inline definition here
// collided with that copy at link.

// NOTE (link lane): InGameUI::addWorldAnimation was defined here as a
// second out-of-line copy, but the rowed home is InGameUIAddWorldAnimation.cpp
// (259B @0x002A0E16, verified). This TU never calls it, so the definition
// is dropped and all references bind the rowed copy. The
// present-unmatched marker went with the definition.

// ------------------------------------------------------------------------------------------------
/** Delete all world animations */
// ------------------------------------------------------------------------------------------------
// ?InGameUI::clearWorldAnimations present-unmatched
void InGameUI::clearWorldAnimations( void )
{
	WorldAnimationData *wad;

	// iterate through all entries and delete the animation data
	for( WorldAnimationListIterator it = m_worldAnimationList.begin();	
			 it != m_worldAnimationList.end(); /*empty*/ )
	{

		wad = *it;
		if( wad )
		{

			// delete the animation instance
			wad->m_anim->deleteInstance();

			// delete the world animation data
			delete wad;

		}  // end if

		it = m_worldAnimationList.erase( it );

	}  // end for
	
}  // end clearWorldAnimations

static const UnsignedInt FRAMES_BEFORE_EXPIRE_TO_FADE = LOGICFRAMES_PER_SECOND * 1;
// ------------------------------------------------------------------------------------------------
/** Update all world animations and draw the visible ones */
// ------------------------------------------------------------------------------------------------



































































































// InGameUI::findIdleWorker: defined in InGameUIIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// InGameUI::addIdleWorker: defined in InGameUIIdleWorker.cpp (its row's unit).

// InGameUI::removeIdleWorker: defined in InGameUIRemoveIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// InGameUI::selectNextIdleWorker: defined in InGameUIIdleWorker.cpp (its row's unit).

// InGameUI::getIdleWorkerCount: defined in InGameUIRemoveIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// InGameUI::showIdleWorkerLayout: defined in InGameUIIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.
// InGameUI::hideIdleWorkerLayout: defined in InGameUIIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// InGameUI::updateIdleWorker: defined in InGameUIIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.

// ?InGameUI::resetIdleWorker present-unmatched
void InGameUI::resetIdleWorker( void )
{
	if(m_idleWorkerWin)
	{
		GadgetButtonSetText(m_idleWorkerWin, UnicodeString::TheEmptyString);
	}
	m_currentIdleWorkerDisplay = -1;
	for(Int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		m_idleWorkers[i].clear();
	}

}

// InGameUI::recreateControlBar: defined in InGameUIMessages.cpp (its row's unit).

// InGameUI::areTooltipsDisabled: defined in InGameUI_Rva0029B04D.cpp (its row's
// unit), beside the disableTooltipsUntil/clearTooltipsDisabled slot bodies rowed
// there under address names.


// IdleWorkerSystem: defined in InGameUIIdleWorker.cpp (its row's unit); the unmatched Zero Hour copy here was a second, non-retail definition.



// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?gen006896F0@@YAXPAUElem28@@PBU1@@Z=??$_Construct@U?$pair@$$CBVAsciiString@@V?$list@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@V?$list@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@@0@ABU10@@Z")
