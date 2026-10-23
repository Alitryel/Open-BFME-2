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


// ResourceGatheringManager::xfer, ported from Zero Hour's GameEngine/Source/
// Common/RTS/ResourceGatheringManager.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "ResourceGatheringManager".
//
// BFME 2 opens with the light-CRC gate and Version1. ZH's xferSTLObjectIDList
// is the free helper 0x0036ABAF (rowed as Rva0036ABAFXfer, over STLport's
// list<int>), applied to the warehouse list (+0x04) and the center list
// (+0x08).

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

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class list
{
	void *m_node;
};
}

Xfer *Rva0036ABAFXfer( Xfer *xfer, _STL::list<int> *values );

class ResourceGatheringManager
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	_STL::list<int> m_supplyWarehouses;																				///< 0x04
	_STL::list<int> m_supplyCenters;																					///< 0x08
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ResourceGatheringManager::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// supply warehouses
	Rva0036ABAFXfer( xfer, &m_supplyWarehouses );

	// supply centers
	Rva0036ABAFXfer( xfer, &m_supplyCenters );

}  // end xfer
