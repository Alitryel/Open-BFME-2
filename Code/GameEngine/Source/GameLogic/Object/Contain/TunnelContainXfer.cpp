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

// TunnelContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/TunnelContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Slot 3 of ??_7TunnelContain
// 0x00C47740. BFME 2 derives TunnelContain from HordeGarrisonContain
// (constructor 0x0047DBF7), whose xfer (slot 3 of its vftable 0x00C46570,
// 0x00479D28) runs first. Then, in the BFME 2 Xfer spelling: the light-CRC
// early-out, the version, and ZH's two bools at +0x9E4/+0x9E5.

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

#include "../../../../Include/Common/BfmeXfer.h"

typedef bool Bool;

class HordeGarrisonContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x9E4 - 0x04 ];
};

class TunnelContain : public HordeGarrisonContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_needToRunOnBuildComplete;																					///< 0x9E4
	Bool m_isCurrentlyRegistered;																							///< 0x9E5
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TunnelContain::xfer( Xfer *xfer )
{

	// extend base class
	HordeGarrisonContain::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// need to run on build complete
	*xfer == m_needToRunOnBuildComplete;

	// Currently registered with a Tunnel Tracker?
	*xfer == m_isCurrentlyRegistered;

}  // end xfer
