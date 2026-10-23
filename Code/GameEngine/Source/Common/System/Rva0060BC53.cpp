// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0060BC53Xfer3@@YAPAVXfer@@PAV1@PAH@Z @0x0060BC53 88B
// Free Xfer helper that checks a uint count of 3 through slot 30 then moves three ints through slot 31.
// Evidence: Xfer.cpp vtable with Ascii slot 27 plus Unicode slot 26 proves reverse order so slot 30 is uint plus slot 31 is int
// plus XferException plus bfmeFormatText plus XferException's throw information from Xfer.cpp plus caller 0x0060BD31 passes 12B stack array
// plus prev XferEnum 0x0060BBD5 plus next PooledString compare 0x0060BCAB both /O1.
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
class Snapshot;
struct XferUnknown11;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};


#include "../../../Include/Common/BfmeXfer.h"

Xfer *__cdecl Rva0060BC53Xfer3(Xfer *xfer, int *data)
{
	unsigned int count = 3;
	xfer->operator==(count);
	if (count != 3)
	{
		throw XferException(0, 0);
	}
	int *p = data;
	int n = 3;
	do
	{
		xfer->operator==(*p++);
	} while (--n != 0);
	return xfer;
}

Xfer *__cdecl Rva0060BD31Xfer(Xfer *xfer)
{
	int tmp[3];
	return Rva0060BC53Xfer3(xfer, tmp);
}
