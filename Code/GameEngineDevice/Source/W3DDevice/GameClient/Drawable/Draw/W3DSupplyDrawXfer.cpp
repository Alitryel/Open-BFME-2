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

// W3DSupplyDraw::xfer, ported from Zero Hour's GameEngineDevice/Source/
// W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): slot 3 of the
// vftable whose slot-2 name getter returns W3DSupplyDraw. BFME 2 xfers two
// Ints of its own (+0x2E8, +0x2EC, no ZH counterpart) before the
// W3DScriptedModelDraw base (0x000C5C04).

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

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

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


class W3DScriptedModelDraw
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x2E8 - 0x04 ];
};

typedef int Int;

class W3DSupplyDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_bfmeInt2E8;																													///< 0x2E8
	Int m_bfmeInt2EC;																													///< 0x2EC
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DSupplyDraw::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	*xfer == m_bfmeInt2E8;
	*xfer == m_bfmeInt2EC;

	// extend base class
	W3DScriptedModelDraw::xfer( xfer );

}  // end xfer
