// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /EHsc
// stlport
// cl: /O1 /DNDEBUG /MD /GX
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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


// Squad::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// Squad.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "Squad".
//
// BFME 2 opens with the light-CRC gate and Version1, then follows ZH's body.
// ZH's throw SC_INVALID_DATA becomes XferException tag 5 (constructor
// 0x0060C36E). The vector push_back is the out-of-line, ICF-shared 4-byte
// body 0x002E01C6.

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

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

typedef unsigned short UnsignedShort;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Object;

typedef _STL::vector<ObjectID> VecObjectID;
typedef VecObjectID::iterator VecObjectIDIt;

class Squad
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	VecObjectID m_objectIDs;																									///< 0x04
	_STL::vector<Object *> m_objectsCached;																		///< 0x10
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// bfme link decl-only begin
namespace _STL { template <> ObjectID * allocator<ObjectID>::allocate(unsigned int,void const *) const; }
// bfme link decl-only end
void Squad::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// length of object ID list
	UnsignedShort objectCount = m_objectIDs.size();
	*xfer == objectCount;

	// object id elements
	ObjectID objectID;
	if( xfer->IsStoring() )
	{

		// save each object id
		VecObjectIDIt it;
		for( it = m_objectIDs.begin(); it != m_objectIDs.end(); ++it )
		{

			// save object ID
			objectID = *it;
			XferObjectID( xfer, &objectID );

		}  // end for, it

	}  // end if, save
	else
	{

		// the cached objects list should be empty
		if( m_objectsCached.size() != 0 )
			throw XferException( 5, 0 );

		// read all items
		for( UnsignedShort i = 0; i < objectCount; ++i )
		{

			// read id
			XferObjectID( xfer, &objectID );

			// put on list
			m_objectIDs.push_back( objectID );

		}  // end for, i

	}  // end else, load

}  // end xfer
