// cl: /DNDEBUG /MD
// cl: /O1 /DNDEBUG /MD /GX
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


// AISkirmishPlayer::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/AI/AISkirmishPlayer.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "AISkirmishPlayer".
//
// BFME 2 order: the AIPlayer base (0x004F0DDE, slot 3 of vftable 0x00C62DC8,
// whose name getter 0x004F05BA returns "AIPlayer") first, then the light-CRC
// gate and Version1, then ZH's fields unchanged at +0x78..+0x94.

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

typedef float Real;

class AIPlayer
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x78 - 0x04 ];
};

class AISkirmishPlayer : public AIPlayer
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_curFrontBaseDefense;																								///< 0x78
	Int m_curFlankBaseDefense;																								///< 0x7C
	Real m_curFrontLeftDefenseAngle;																					///< 0x80
	Real m_curFrontRightDefenseAngle;																					///< 0x84
	Real m_curLeftFlankLeftDefenseAngle;																			///< 0x88
	Real m_curLeftFlankRightDefenseAngle;																			///< 0x8C
	Real m_curRightFlankLeftDefenseAngle;																			///< 0x90
	Real m_curRightFlankRightDefenseAngle;																		///< 0x94
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AISkirmishPlayer::xfer( Xfer *xfer )
{

	// xfer base class info
	AIPlayer::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// front base defense
	*xfer == m_curFrontBaseDefense;

	// flank base defense
	*xfer == m_curFlankBaseDefense;

	// front left defense angle
	*xfer == m_curFrontLeftDefenseAngle;

	// front right defense angle
	*xfer == m_curFrontRightDefenseAngle;

	// left flank left defense angle
	*xfer == m_curLeftFlankLeftDefenseAngle;

	// left flank right defense angle
	*xfer == m_curLeftFlankRightDefenseAngle;

	// right flank left defense angle
	*xfer == m_curRightFlankLeftDefenseAngle;

	// right flank right defense angle
	*xfer == m_curRightFlankRightDefenseAngle;

}  // end xfer
