// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/GameWindowGlobal.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// GameWindowManager::winGetTextSize 0x00314C9F (34B),
// GameWindowManager::winMakeColor 0x00314C1D (33B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
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

// FILE: GameWindowGlobal.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: GameWindowGlobal.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      These are some global functions that every game using this
//						window system must implement for their current technology
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// These two bodies need only the string ABI and callable declarations below.
// BFME 2's rowed names preserve virtual winMakeColor and nonvirtual
// winGetTextSize. No complete GameWindowManager layout or slot is asserted.
#include "unicode_string.h"

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;
class GameFont;

class GameWindowManager
{
public:
    virtual Color winMakeColor(UnsignedByte red, UnsignedByte green,
        UnsignedByte blue, UnsignedByte alpha);
    void winGetTextSize(GameFont *font, UnicodeString text,
        Int *width, Int *height, Int maxWidth);
};

// Same inline expression as the donor's GameClient/Color.h; the native
// 33-byte body verifies the packed component order.
inline Color GameMakeColor(UnsignedByte red, UnsignedByte green,
    UnsignedByte blue, UnsignedByte alpha)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

  // end WinFindImage

// GameWindowManager::winMakeColor ============================================
/** Given RGBA, make a color, you can change color representation for your
	* individual project needs */
//=============================================================================
Color GameWindowManager::winMakeColor( UnsignedByte red, 
																			 UnsignedByte green, 
																			 UnsignedByte blue, 
																			 UnsignedByte alpha ) 
{ 

	return GameMakeColor( red, green, blue, alpha );

}
  // end WinFormatText

// GameWindowManager::winGetTextSize ==========================================
/** get the extent size of text */
//=============================================================================
void GameWindowManager::winGetTextSize( GameFont *font, UnicodeString text, 
																				Int *width, Int *height, Int maxWidth )
{

	/// @todo make display string size stuff go through here

	if( width )
		*width = 0;

	if( height )
		*height = 0;

}


  // end WinIsAlNum
