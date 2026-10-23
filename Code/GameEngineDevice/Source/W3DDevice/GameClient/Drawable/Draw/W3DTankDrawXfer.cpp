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

// W3DTankDraw::xfer, ported from Zero Hour's GameEngineDevice/Source/W3DDevice/
// GameClient/Drawable/Draw/W3DTankDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of ??_7W3DTankDraw
// 0x00BCCBE8: the version, then the base model draw's xfer. In BFME 2 that
// base is W3DScriptedModelDraw (slot 3 of its vftable 0x00BCA090,
// 0x000C5C04). As in ZH, there is no data of its own.

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

class W3DScriptedModelDraw
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class W3DTankDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTankDraw::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	// extend base class
	W3DScriptedModelDraw::xfer( xfer );

	// John A and Mark W say there is no data to save here

}  // end xfer
