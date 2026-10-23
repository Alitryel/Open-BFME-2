// cl: /MD
// ?xfer@Rva0055B367@@QAEXPAVXfer@@@Z @0x0055B367 53B
// Unlock FX xfer loop 8x via Version1 plus Xfer slots 0x70/0x78.
// Evidence: thiscall 1 Xfer arg ret 4; push 8 pop ebx countdown plus add edi 8;
// lea [edi-4] push plus push edi for Region2D/RealRange; Version1 row 0x53EE;
// callers 0x0055B3EC in 0x0055B3D9; neighbours parse/ctor same subsystem;
// unblocks 0x0055B3D9. Xfer decl verbatim order from PoisonedBehaviorXfer.
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

struct Rva0055B367Pair
{
	float f;
	unsigned int u;
};

class Rva0055B367
{
public:
	void xfer(Xfer *xfer);
private:
	char m_pad[4];
	Rva0055B367Pair m_pairs[8];
};

void Rva0055B367::xfer(Xfer *xfer)
{
	xfer->Version1();
	unsigned int *pu = (unsigned int *)((char *)this + 8);
	for (int n = 8; n > 0; --n)
	{
		xfer->operator==(*(float *)(pu - 1));
		xfer->operator==(*pu);
		pu += 2;
	}
}
