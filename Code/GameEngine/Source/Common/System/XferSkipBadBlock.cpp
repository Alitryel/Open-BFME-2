// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 Xfer::SkipBadBlock is an intentional no-op; BFME2 retains the same
// virtual hook and emits only the thiscall epilogue.

class Snapshot;

class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

void Xfer::SkipBadBlock(Snapshot &, unsigned int)
{
}
