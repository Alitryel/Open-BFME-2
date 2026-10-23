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

// HeightDieUpdate::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/HeightDieUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose slot-2
// name getter returns HeightDieUpdate. BFME 2 runs UpdateModule's xfer and the
// light-CRC early-out before the version, then ZH's fields with no version
// gate: m_hasDied +0x20, m_particlesDestroyed +0x21, m_lastPosition +0x24
// and m_earliestDeathFrame +0x30.

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

typedef unsigned int UnsignedInt;

class HeightDieUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_hasDied;																														///< 0x20
	Bool m_particlesDestroyed;																								///< 0x21
	char m_unrecovered22[ 0x24 - 0x22 ];
	Coord3DBase m_lastPosition;																								///< 0x24
	UnsignedInt m_earliestDeathFrame;																					///< 0x30
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void HeightDieUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// has died
	*xfer == m_hasDied;

	// particles destroyed
	*xfer == m_particlesDestroyed;

	// last position
	*xfer == m_lastPosition;

	// earliest death frame
	*xfer == m_earliestDeathFrame;

}  // end xfer
