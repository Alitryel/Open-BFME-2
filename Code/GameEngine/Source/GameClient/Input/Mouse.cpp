// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
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

// FILE: Mouse.cpp ////////////////////////////////////////////////////////////////////////////////
// Created:   Colin Day, June 2001
// Desc:      Basic mouse interactions
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Debug.h"
#include "Common/MessageStream.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/INI.h"

#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindow.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Keyboard.h"
#include "GameClient/Mouse.h"
#include "GameClient/GlobalLanguage.h"

#include "GameLogic/ScriptEngine.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Retail getCursorIndex compares bounded bytes through the MSVCR71 _memicmp import.
extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
Mouse *TheMouse = NULL;

const char *Mouse::RedrawModeName[RM_MAX] = {
	"Mouse:Windows",
	"Mouse:W3D",
	"Mouse:Poly",
	"Mouse:DX8",
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
static const FieldParse TheMouseCursorFieldParseTable[] = 
{
	{ "CursorText",						INI::parseAsciiString,	NULL, offsetof( CursorInfo, cursorText ) },
	{ "CursorTextColor",			INI::parseRGBAColorInt,	NULL, offsetof( CursorInfo, cursorTextColor ) },
	{ "CursorTextDropColor",	INI::parseRGBAColorInt,	NULL, offsetof( CursorInfo, cursorTextDropColor ) },
	{ "W3DModel",							INI::parseAsciiString,	NULL,	offsetof( CursorInfo, W3DModelName ) },
	{ "W3DAnim",							INI::parseAsciiString,	NULL,	offsetof( CursorInfo, W3DAnimName ) },
	{ "W3DScale",							INI::parseReal,					NULL,	offsetof( CursorInfo, W3DScale ) },
	{ "Loop",									INI::parseBool,					NULL,	offsetof( CursorInfo, loop ) },
	{ "Image",							INI::parseAsciiString,	NULL,	offsetof( CursorInfo, imageName ) },
	{ "Texture",							INI::parseAsciiString,	NULL,	offsetof( CursorInfo, textureName ) },
	{ "HotSpot",							INI::parseICoord2D,	NULL,	offsetof( CursorInfo, hotSpotPosition ) },
	{ "Frames",							INI::parseInt,	NULL,	offsetof( CursorInfo, numFrames ) },
	{ "FPS",							INI::parseReal, NULL, offsetof( CursorInfo, fps)},
	{ "Directions",							INI::parseInt,	NULL,	offsetof( CursorInfo, numDirections ) },
};

static const FieldParse TheMouseFieldParseTable[] = 
{
	{ "TooltipFontName",						INI::parseAsciiString,NULL,			offsetof( Mouse, m_tooltipFontName ) },
	{ "TooltipFontSize",						INI::parseInt,				NULL,			offsetof( Mouse, m_tooltipFontSize ) },
	{ "TooltipFontIsBold",					INI::parseBool,				NULL,			offsetof( Mouse, m_tooltipFontIsBold ) },
	{ "TooltipAnimateBackground",		INI::parseBool,				NULL,			offsetof( Mouse, m_tooltipAnimateBackground ) },
	{ "TooltipFillTime",						INI::parseInt,				NULL,			offsetof( Mouse, m_tooltipFillTime ) },
	{ "TooltipDelayTime",						INI::parseInt,				NULL,			offsetof( Mouse, m_tooltipDelayTime ) },
	{ "TooltipTextColor",						INI::parseRGBAColorInt,	NULL,		offsetof( Mouse, m_tooltipColorText ) },
	{ "TooltipHighlightColor",			INI::parseRGBAColorInt,	NULL,		offsetof( Mouse, m_tooltipColorHighlight ) },
	{ "TooltipShadowColor",					INI::parseRGBAColorInt,	NULL,		offsetof( Mouse, m_tooltipColorShadow ) },
	{ "TooltipBackgroundColor",			INI::parseRGBAColorInt,	NULL,		offsetof( Mouse, m_tooltipColorBackground ) },
	{ "TooltipBorderColor",					INI::parseRGBAColorInt,	NULL,		offsetof( Mouse, m_tooltipColorBorder ) },
	{ "TooltipWidth",								INI::parsePercentToReal,NULL,		offsetof( Mouse, m_tooltipWidth ) },
	{ "CursorMode",									INI::parseInt,					NULL,		offsetof( Mouse, m_currentRedrawMode ) },
	{ "UseTooltipAltTextColor",			INI::parseBool,					NULL,		offsetof( Mouse, m_useTooltipAltTextColor ) },
	{ "UseTooltipAltBackColor",			INI::parseBool,					NULL,		offsetof( Mouse, m_useTooltipAltBackColor ) },
	{ "AdjustTooltipAltColor",			INI::parseBool,					NULL,		offsetof( Mouse, m_adjustTooltipAltColor ) },
	{ "OrthoCamera",								INI::parseBool,					NULL,		offsetof( Mouse, m_orthoCamera ) },
	{ "OrthoZoom",									INI::parseReal,					NULL,		offsetof( Mouse, m_orthoZoom ) },
	{ "DragTolerance",							INI::parseUnsignedInt,	NULL,		offsetof( Mouse, m_dragTolerance) },
	{ "DragTolerance3D",						INI::parseUnsignedInt,	NULL,		offsetof( Mouse, m_dragTolerance3D) },
	{ "DragToleranceMS",						INI::parseUnsignedInt,	NULL,		offsetof( Mouse, m_dragToleranceMS) },

};

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Move the mouse in either relative or absolute coords */
//-------------------------------------------------------------------------------------------------
// BFME 2's Mouse keeps m_currMouse (whose first field is the position) at
// this+0x4F0C: retail setPosition (0x001EDE4C, a Mouse vftable slot that
// DirectInputMouse::setPosition also calls directly) stores x/y there, and
// MouseProcessEvents.cpp places m_currMouse at the same offset.
struct BfmeMouseLayout
{
	UnsignedByte pad0[0x4f0c];
	ICoord2D currPos;									///< retail this+0x4F0C
};

// Mouse::moveMouse is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EDC41).

// Mouse::updateMouseData is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EDCB1).

// Mouse::processMouseEvent is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EE069).

// Mouse::checkForDrag is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EDD1C).


//-------------------------------------------------------------------------------------------------
/** Check for mouse click, using allowed drag forgiveness */
//-------------------------------------------------------------------------------------------------
// ?isClick@Mouse@@ present-unmatched
Bool Mouse::isClick(const ICoord2D *anchor, const ICoord2D *dest, UnsignedInt previousMouseClick, UnsignedInt currentMouseClick)
{
	ICoord2D delta;
	delta.x = anchor->x - dest->x;
	delta.y = anchor->y - dest->y;


	// if the mouse hasn't moved further than the tolerance distance
	// or the click took less than the tolerance duration
	if (	abs(delta.x) > m_dragTolerance
		||	abs(delta.y) > m_dragTolerance
		||	currentMouseClick - previousMouseClick > m_dragToleranceMS)
	{
		return FALSE;
	}
	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CursorInfo::CursorInfo( void )
{
	// Added Sadullah Nader
	// Initializations missing and needed
	
	cursorName.clear();
	cursorText.clear();
	cursorTextColor.red = cursorTextColor.green = cursorTextColor.blue = 0;
	cursorTextDropColor.red = cursorTextDropColor.blue = cursorTextDropColor.green = 0;
	 
	//
	textureName.clear();
	imageName.clear();
	W3DModelName.clear();
	W3DAnimName.clear();
	W3DScale = 1.0f;
	loop = TRUE;
	//Assume hotspot is at the center of a 32x32 image.
	hotSpotPosition.x=16;
	hotSpotPosition.y=16;
	numFrames = 1;	//assume no animation
	fps=20.0f;
	numDirections=1;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Mouse::Mouse (0x001EEC97) and Mouse::~Mouse (0x001EE3DE) are matched in
// Rva001EE3DEDtor.cpp with BFME 2's layout; this unit's ZH-layout copies
// competed with them for ??0Mouse / ??1Mouse at link. Retail's Mouse ctor
// hands ~CursorInfo (0x001EE376, rowed here) to the eh vector constructor
// iterator; this local array construction is the same use, keeping the
// implicit destructor emitted in its home unit.
// ?MouseCursorInfoArrayAnchor absent-from-retail
void MouseCursorInfoArrayAnchor()
{
	CursorInfo cursors[2];
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// Mouse::parseIni is defined with its retail-matched body in FontLibraryInit.cpp (0x001EE483).

//-------------------------------------------------------------------------------------------------
/** Initialize the mouse */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameClient/Input/Mouse_init.cpp
// Mouse::init is the retail-matched body below (0x001EE4DC, subsystem slot 1).

//-------------------------------------------------------------------------------------------------
/** Tell mouse system display resolution changed. */
//-------------------------------------------------------------------------------------------------
// BFME 2's body is empty: its display-mode change calls the shared empty body
// 0x000B3FD0 where Zero Hour calls this (GameClientDisplayModeChange.cpp).
// ?mouseNotifyResolutionChange@Mouse@@ present-unmatched
void Mouse::mouseNotifyResolutionChange( void )
{
}


//-------------------------------------------------------------------------------------------------
/** Reset mouse system */
//-------------------------------------------------------------------------------------------------
// TU-local DisplayStringManager view: retail reaches newDisplayString through
// slot 0x38 (see rowed Rva0029B816Ctor), not the shared header's slot 0x18.
class MouseResetDisplayStringManager
{
public:
	virtual void mrs00(); virtual void mrs01(); virtual void mrs02(); virtual void mrs03();
	virtual void mrs04(); virtual void mrs05(); virtual void mrs06(); virtual void mrs07();
	virtual void mrs08(); virtual void mrs09(); virtual void mrs10(); virtual void mrs11();
	virtual void mrs12(); virtual void mrs13();
	virtual DisplayString *newDisplayString();
};
void Mouse::init( void )
{
	// Retail 0x001EE4DC, 226 bytes: subsystem slot 1 (init), far beyond ZH's
	// cursor-text stub. Target facts: TheGlobalData (0xDFE758) +0x9C6 gate
	// zeroes +0x12DC; StringBase<G> releaseBuffer 0x00036E70 on the wide
	// strings at +0x12FC and +0x1300 (UnicodeString::clear, public inline);
	// flag bytes +0x12F4/5 = 2, +0x12F6/+0x1308 = 0; timeGetTime (winmm IAT
	// 0xBBA918) into +0x4FD8; memset +0x130C/0x3C00, +0x4F0C/0x3C,
	// +0x4F48/0x3C; limit words +0x4F84 = 0, +0x4F88 = 799, +0x4F8C = 0,
	// +0x4F90 = 599 (setMouseLimits precedent); +0x4F94/98/9C/FC = 0,
	// +0x4FA4 = 2; DisplayStringManager slot 0x38 newDisplayString into
	// +0x4FA8 (same expression as init). Raw members below the mouselayout
	// shim's view, punned per setMouseLimits/resetTooltipDelay precedent.
	char *self = reinterpret_cast<char *>(this);
	if (TheGlobalData && *(reinterpret_cast<Bool *>(reinterpret_cast<char *>(const_cast<GlobalData *>(TheGlobalData)) + 0x9C6)))
		*reinterpret_cast<Int *>(self + 0x12DC) = 0;
	UnicodeString *strA = reinterpret_cast<UnicodeString *>(self + 0x12FC);
	*(self + 0x12F4) = 2;
	*(self + 0x12F5) = 2;
	*(self + 0x12F6) = 0;
	*(self + 0x1308) = 0;
	strA->clear();
	reinterpret_cast<UnicodeString *>(self + 0x1300)->clear();
	*reinterpret_cast<UnsignedInt *>(self + 0x4FD8) = timeGetTime();
	memset(self + 0x130C, 0, 0x3C00);
	memset(self + 0x4F0C, 0, 0x3C);
	memset(self + 0x4F48, 0, 0x3C);
	*reinterpret_cast<Int *>(self + 0x4F84) = 0;
	*reinterpret_cast<Int *>(self + 0x4F88) = 799;
	*reinterpret_cast<Int *>(self + 0x4F8C) = 0;
	*reinterpret_cast<Int *>(self + 0x4F90) = 599;
	*reinterpret_cast<Int *>(self + 0x4F94) = 0;
	*reinterpret_cast<Int *>(self + 0x4F98) = 0;
	*(self + 0x4F9C) = 0;
	*reinterpret_cast<Int *>(self + 0x4FFC) = 0;
	*reinterpret_cast<Int *>(self + 0x4FA4) = 2;
	// The shared DisplayStringManager header places newDisplayString at slot
	// 0x18, but retail calls slot 0x38 here (and in rowed Rva0029B816Ctor).
	// TU-local view with the proven 14-stub prefix; same pattern as that TU.
	*reinterpret_cast<DisplayString **>(self + 0x4FA8) =
		reinterpret_cast<MouseResetDisplayStringManager *>(TheDisplayStringManager)->newDisplayString();

}  // end reset

// Mouse::update is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EDE3A).

// Mouse::createStreamMessages is defined with its retail-matched body in MouseProcessEvents.cpp (0x001EE630).

//-------------------------------------------------------------------------------------------------
/** Set the string to display at the cursor for the tooltip */
//-------------------------------------------------------------------------------------------------
// ?setCursorTooltip@Mouse@@ present-unmatched
void Mouse::setCursorTooltip( UnicodeString tooltip, Int delay, const RGBColor *color, Real width )
{

	//DEBUG_LOG(("%d Tooltip: %ls\n", TheGameClient->getFrame(), tooltip.str()));

	m_isTooltipEmpty = tooltip.isEmpty();
  m_tooltipDelay = delay;

	Bool forceRecalc = FALSE;
	if ( !tooltip.isEmpty() && width != m_lastTooltipWidth )
	{
		forceRecalc = TRUE;
		Int widthInPixels = (Int)(TheDisplay->getWidth()*m_tooltipWidth*width);
		if (widthInPixels < 10)
		{
			widthInPixels = 120;
		}
		else if (widthInPixels > TheDisplay->getWidth())
		{
			widthInPixels = TheDisplay->getWidth();
		}
		//DEBUG_LOG(("Setting tooltip width to %d pixels (%g%% of the normal tooltip width)\n", widthInPixels, width*100));
		m_tooltipDisplayString->setWordWrap( widthInPixels );
		m_lastTooltipWidth = width;
	}

	if (forceRecalc || !m_isTooltipEmpty && tooltip.compare(m_tooltipDisplayString->getText()))
	{
		m_tooltipDisplayString->setText(tooltip);
		//DEBUG_LOG(("Tooltip: %ls\n", tooltip.str()));
	}
	if (color)
	{
		if (m_useTooltipAltTextColor)
		{
			if (m_adjustTooltipAltColor)
			{
				m_tooltipTextColor.red   = REAL_TO_INT((color->red + 1.0f)   * 255.0f / 2.0f);
				m_tooltipTextColor.green = REAL_TO_INT((color->green + 1.0f) * 255.0f / 2.0f);
				m_tooltipTextColor.blue  = REAL_TO_INT((color->blue + 1.0f)  * 255.0f / 2.0f);
			}
			else
			{
				m_tooltipTextColor.red   = REAL_TO_INT(color->red   * 255.0f);
				m_tooltipTextColor.green = REAL_TO_INT(color->green * 255.0f);
				m_tooltipTextColor.blue  = REAL_TO_INT(color->blue  * 255.0f);
			}
			m_tooltipTextColor.alpha = m_tooltipColorText.alpha;
		}
		if (m_useTooltipAltBackColor)
		{
			if (m_adjustTooltipAltColor)
			{
				m_tooltipBackColor.red   = REAL_TO_INT(color->red   * 255.0f * 0.5f);
				m_tooltipBackColor.green = REAL_TO_INT(color->green * 255.0f * 0.5f);
				m_tooltipBackColor.blue  = REAL_TO_INT(color->blue  * 255.0f * 0.5f);
			}
			else
			{
				m_tooltipBackColor.red   = REAL_TO_INT(color->red   * 255.0f);
				m_tooltipBackColor.green = REAL_TO_INT(color->green * 255.0f);
				m_tooltipBackColor.blue  = REAL_TO_INT(color->blue  * 255.0f);
			}
			m_tooltipBackColor.alpha = m_tooltipColorBackground.alpha;
		}
	}
	else
	{
		m_tooltipTextColor = m_tooltipColorText;
		m_tooltipBackColor = m_tooltipColorBackground;
	}

}  // end setCursorTooltip

// ------------------------------------------------------------------------------------------------
/** Set the text for the mouse cursor ... note that this is *NOT* the tooltip text we
	* can set to be at the mouse position */
// ------------------------------------------------------------------------------------------------
// Mouse::setMouseText (0x001EEBD5) is defined with its retail body in MouseRva001EEBD5.cpp.

//-------------------------------------------------------------------------------------------------
/** Move the mouse to the position */
//-------------------------------------------------------------------------------------------------
void Mouse::setPosition( Int x, Int y )
{
	BfmeMouseLayout *self = (BfmeMouseLayout *)this;

	self->currPos.x = x;
	self->currPos.y = y;

}  // end setPosition

//-------------------------------------------------------------------------------------------------
/** This default implemtation of SetMouseLimits will just set the limiting	
	* rectangle to be the width and height of the game display with the
	* origin in the upper left at (0,0).  However, if the game is running
	* in a windowed mode then these limits should reflect the SCREEN
	* coords that the mouse is allowed to move in.  Also, if the game is in
	* a window you may want to adjust for any title bar available in
	* the operating system.  For system specific limits and windows etc,
	* just override this function in the device implementation of the mouse */
//-------------------------------------------------------------------------------------------------
class BfmeMouseLimitDisplay
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0c() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1c() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2c() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual Int getWidth() = 0;
	virtual Int getHeight() = 0;
};

void Mouse::setMouseLimits( void )
{
	char *mouse = reinterpret_cast<char *>(this);
	*reinterpret_cast<Int *>(mouse + 0x4f84) = 0;
	*reinterpret_cast<Int *>(mouse + 0x4f8c) = 0;
	if( TheDisplay )
	{
		*reinterpret_cast<Int *>(mouse + 0x4f88) =
			reinterpret_cast<BfmeMouseLimitDisplay *>(TheDisplay)->getWidth();
		*reinterpret_cast<Int *>(mouse + 0x4f90) =
			reinterpret_cast<BfmeMouseLimitDisplay *>(TheDisplay)->getHeight();
	}  // end if

}  // end setMouseLimits

//-------------------------------------------------------------------------------------------------
/** Draw the mouse */
//-------------------------------------------------------------------------------------------------
// ?draw@Mouse@@ present-unmatched
void Mouse::draw( void )
{

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Mouse::resetTooltipDelay is retail 0x001EEC4B, matched in MouseRva001EEC4B_muse-f8cb.cpp.

//-------------------------------------------------------------------------------------------------
/** Draw the mouse tooltip if one is set */
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Draw the cursor text at the mouse position.  Note that this is *NOT* the tooltip text */
// ------------------------------------------------------------------------------------------------
class MouseDrawCursorTextDisplayString
{
public:
	virtual ~MouseDrawCursorTextDisplayString();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColor(Color color, Color dropColor) = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void draw(Int x, Int y, Int xDrop, Int yDrop) = 0;
	virtual void getSize(Int *width, Int *height) = 0;
};

class MouseDrawCursorTextDisplay
{
public:
	virtual ~MouseDrawCursorTextDisplay();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual UnsignedInt getWidth() = 0;
	virtual UnsignedInt getHeight() = 0;
};

void Mouse::drawCursorText( void )
{
	// BFME2 adds 0x554 bytes before the corresponding BFME1 mouse fields.
	Mouse *const retailMouse = reinterpret_cast<Mouse *>(
		reinterpret_cast<char *>(this) + 0x554);

	// sanity
	if( retailMouse->m_cursorTextDisplayString == NULL )
		return;

	// get the colors to draw the text in an acceptable format
	Color color, dropColor;
	color = GameMakeColor( retailMouse->m_cursorTextColor.red,
													 retailMouse->m_cursorTextColor.green,
													 retailMouse->m_cursorTextColor.blue,
													 retailMouse->m_cursorTextColor.alpha );
	dropColor = GameMakeColor( retailMouse->m_cursorTextDropColor.red,
														 retailMouse->m_cursorTextDropColor.green,
														 retailMouse->m_cursorTextDropColor.blue,
														 retailMouse->m_cursorTextDropColor.alpha );

	// get the size of the text to draw
	Int width, height;
	reinterpret_cast<MouseDrawCursorTextDisplayString *>(
		retailMouse->m_cursorTextDisplayString)->getSize( &width, &height );

	// Put the text to the right/below the cursor unless it would cross the
	// retail display edge; then place it to the left/above the cursor.
	Int x, y;
	Int *const retailMousePosition = reinterpret_cast<Int *>(
		reinterpret_cast<char *>(this) + 0x4f0c);
	Int mouseX = retailMousePosition[0];
	if( mouseX + 16 < reinterpret_cast<MouseDrawCursorTextDisplay *>(TheDisplay)->getWidth() - width )
		x = mouseX + 16;
	else
		x = mouseX - width - 16;

	Int mouseY = retailMousePosition[1];
	if( mouseY + 16 < reinterpret_cast<MouseDrawCursorTextDisplay *>(TheDisplay)->getHeight() - height )
		y = mouseY + 16;
	else
		y = mouseY - height - 16;

	reinterpret_cast<MouseDrawCursorTextDisplayString *>(
		retailMouse->m_cursorTextDisplayString)->setColor( color, dropColor );
	reinterpret_cast<MouseDrawCursorTextDisplayString *>(
		retailMouse->m_cursorTextDisplayString)->draw( x, y, 1, 1 );

}  // end drawCursorText


// Mouse::getCursorIndex is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva001EF291Find.cpp (0x001EF291).

// Mouse::setCursor is defined with its retail-matched body in Code/GameEngine/Source/GameClient/MouseSetCursor.cpp (0x001EEFD2).

//-------------------------------------------------------------------------------------------------
/** Parse MouseCursor entry */
//-------------------------------------------------------------------------------------------------
// ?parseMouseCursorDefinition@INI@@SAXPAV1@@Z
// The "MouseCursor" block (INI block table entry 0x001EF2CB). m_cursorInfo
// sits at +0x0C in Mouse with a 0x54 stride, which is how retail addresses the
// element (imul index,0x54 then lea [eax+TheMouse+0x0C]), and the cursor's
// name is the first member at offset 0 -- the field table's lowest entry is
// CursorText at 0x04.
void INI::parseMouseCursorDefinition( INI* ini )
{
	AsciiString name;

	name = ini->getNextToken();

	if( TheMouse )
	{
		Int index = TheMouse->getCursorIndex( name );
		if( index != Mouse::INVALID_MOUSE_CURSOR )
		{
			CursorInfo *cursorInfo = (CursorInfo *)((char *)TheMouse + index * 0x54 + 0x0C);
			cursorInfo->cursorName = name;

			ini->initFromINI( cursorInfo, TheMouseCursorFieldParseTable );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** Parse MouseCursor entry */
//-------------------------------------------------------------------------------------------------
void INI::parseMouseDefinition( INI* ini )
{
	if( TheMouse )
	{
		// parse the ini weapon definition
		ini->initFromINI( TheMouse, TheMouseFieldParseTable );
	}
}
