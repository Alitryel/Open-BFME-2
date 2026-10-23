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

// AIGuardRetaliateMachine::xfer, ported from Zero Hour's AIGuardRetaliate.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference) in
// BFME 2's Xfer spelling: slot 3 of the vftable whose slot-2 name getter
// returns AIGuardRetaliateMachine. The light-CRC early-out and version come
// first, then the StateMachine base (0x004D7744, ZH's version-2 addition),
// the nemesis (+0x48) and the guard position (+0x3C).

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


enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

class StateMachine
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------
class AIGuardRetaliateMachine : public StateMachine
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
	Coord3DBase m_positionToGuard;																						///< 0x3C
	ObjectID m_nemesisToAttack;																								///< 0x48
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGuardRetaliateMachine::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;
	xfer->Version1();
	StateMachine::xfer(xfer);
	XferObjectID( xfer, &m_nemesisToAttack );
	*xfer == m_positionToGuard;
}  // end xfer
