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

// SupplyTruckAIUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). It is slot 3 of the
// SupplyTruckAIUpdate table in BFME 2's Xfer spelling: AIUpdateInterface::xfer
// (slot 3 of AIUpdateInterface's vftable 0x00BFA480, 0x00267EDD), the
// light-CRC early-out, Version1, then the state-machine snapshot (+0x3E8)
// and preferred dock (+0x3EC) as in ZH. BFME 2 inserts a Coord3D (+0x3F0)
// and a Bool (+0x3FC) before ZH's box count (+0x400) and force-pending flag
// (+0x404), and adds a final Bool (+0x405). The inserted fields have no ZH
// counterpart and keep offset names.

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

#include "../../../../../Include/Common/BfmeXfer.h"

typedef bool Bool;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered004[ 0x3E8 - 0x004 ];
};

class SupplyTruckAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Snapshot *m_supplyTruckStateMachine;																			///< 0x3E8
	ObjectID m_preferredDock;																									///< 0x3EC
	Coord3DBase m_bfmeCoord3F0;																								///< 0x3F0
	Bool m_bfmeFlag3FC;																												///< 0x3FC
	Int m_numberBoxes;																												///< 0x400
	Bool m_forcePending;																											///< 0x404
	Bool m_bfmeFlag405;																												///< 0x405
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void SupplyTruckAIUpdate::xfer( Xfer *xfer )
{

	// extend base class
	AIUpdateInterface::xfer(xfer);

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	*xfer == *m_supplyTruckStateMachine;
	XferObjectID( xfer, &m_preferredDock );
	*xfer == m_bfmeCoord3F0;
	*xfer == m_bfmeFlag3FC;
	*xfer == m_numberBoxes;
	*xfer == m_forcePending;
	*xfer == m_bfmeFlag405;

}  // end xfer
