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

// StealthDetectorUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/StealthDetectorUpdate.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose
// slot-2 name getter returns StealthDetectorUpdate. BFME 2 is at version 3
// and has dropped ZH's m_enabled: saves older than version 3 still carry
// the flag, so it is read into a local and discarded.

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


class UpdateModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x20 - 0x04 ];
};

class StealthDetectorUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 3: BFME 2, enabled flag removed */
// ------------------------------------------------------------------------------------------------
void StealthDetectorUpdate::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 3 );
	*xfer == version;

	// extend base class
	UpdateModule::xfer( xfer );

	// enabled (obsolete)
	if( version.m_minimum < 3 )
	{
		Bool enabled = false;
		*xfer == enabled;
	}

}  // end xfer
