// cl: /DNDEBUG /MD /GX
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

// Energy::xfer, ported from Zero Hour's GameEngine/Source/Common/RTS/Energy.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// slot 3 of the vftable whose slot-2 name getter returns Energy. BFME 2
// starts with the light-CRC early-out and a version, then keeps only ZH's
// owning-player index: written from m_owner (+0x0C, index at Player +0x54)
// when storing, then resolved back through ThePlayerList.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};


typedef int Int;

class Player
{
public:
	// Matched callers use the target player index at +0x54 directly;
	// avoid an out-of-line getter shared with incompatible layouts.
public:
	char m_unrecovered00[ 0x54 ];
	Int m_playerIndex;																												///< 0x54
};

class PlayerList
{
public:
	Player *getNthPlayer( Int i );
};
extern PlayerList *ThePlayerList;

class Energy
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x0C - 0x04 ];
	Player *m_owner;																													///< 0x0C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void Energy::xfer( Xfer *xfer )
{

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// owning player
	Int owningPlayerIndex;
	if( xfer->IsStoring() )
		owningPlayerIndex = m_owner->m_playerIndex;
	*xfer == owningPlayerIndex;
	m_owner = ThePlayerList->getNthPlayer( owningPlayerIndex );

}  // end xfer
