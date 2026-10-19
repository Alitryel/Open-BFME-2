// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Shell
// stlport
// Both constructors used to live in ShellMenuSchemeCtor.cpp purely for the
// STLport link mode: retail calls __new_alloc::allocate directly and without
// /D_STLP_USE_STATIC_LIB the header declares it dllimport, so the node
// allocation comes out as `call [__imp_...]` instead of `call`. Adding the
// define here re-verified all 24 rows this file already had, which is what the
// split was avoiding.
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

// FILE: ShellMenuScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	ShellMenuScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"
#include "GameClient/Shell.h"
#include "GameClient/Display.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
// Body is MASM exact-byte dump (game/masm_dumps/INI_parseShellMenuSchemeDefinition_581790.asm).
// Retail @ 0x581790; C++ blocked on AsciiString::set vs StringBase::set(s,len) shape.
// ??1ShellMenuSchemeLine@@QAE@XZ present-unmatched

// ??1ShellMenuSchemeImage@@QAE@XZ present-unmatched
ShellMenuSchemeImage::~ShellMenuSchemeImage( void )
{
	m_image = NULL;
}

ShellMenuScheme::ShellMenuScheme( void )
{
	
}

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeDestructor.cpp
// ??1ShellMenuScheme@@QAE@XZ present-unmatched

// ?addLine@ShellMenuScheme@@QAEXPAVShellMenuSchemeLine@@@Z present-unmatched



// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_parseImagePart_Thunk.cpp
// ?parseImagePart@ShellMenuSchemeManager@@ present-unmatched

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_parseLinePart_Thunk.cpp
// ?parseLinePart@ShellMenuSchemeManager@@ present-unmatched

// byte-exact reconstruction: game/GameEngine/Source/Common/ShellMenuSchemeManager_newShellMenuScheme_Thunk.cpp
// ?newShellMenuScheme@ShellMenuSchemeManager@@QAEPAVShellMenuScheme@@VAsciiString@@@Z present-unmatched

// byte-exact reconstruction: game/GameEngine/Source/GameClient/ShellMenuScheme_set.cpp
// ?setShellMenuScheme@ShellMenuSchemeManager@@QAEXVAsciiString@@@Z present-unmatched
//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
