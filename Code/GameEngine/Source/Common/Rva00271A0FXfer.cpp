// cl: /Ireference/shims/bfme2_ascii /O1 /Ireference/shims/moduledata

// ?rva00271A0F@Rva00271A0F@@QAEXPAVXfer@@@Z, RVA 0x00271A0F, 113B.
// Chain lane: calls Rva0030612AXfer 0x0030612A (3-float helper, rowed).
// Light-CRC guard via slot 0x10, Version1, four triples at +0x04/+0x10/
// +0x1C/+0x28, int at +0x34 via slot 0x78, bool at +0x39 via slot 0x90,
// unsigned char at +0x38 via slot 0x8c. Xfer declaration is
// Rva000E5725Xfer.cpp's model verbatim so the operator== slots match.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

#include "../../../Libraries/Include/Lib/ICoord3D.h"

#include "../../../Libraries/Include/Lib/Region3D.h"

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

#include "../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../Libraries/Include/Lib/Region2D.h"

#include "../../../Libraries/Include/Lib/IRegion2D.h"

struct RealRange
{
	float lo;
	float hi;
};

#include "../../../Libraries/Include/Lib/RGBColor.h"

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct RGBAColorInt
{
	int red;
	int green;
	int blue;
	int alpha;
};

#include "ascii_string.h"

#include "Common/Snapshot.h"

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

void Rva0030612AXfer(Xfer *xfer, float *vals);

class Rva00271A0F
{
public:
	void rva00271A0F(Xfer *xfer);

private:
	char m_pad[0x04];
	float m_04[12];
	UnsignedInt m_34;
	char m_38;
	Bool m_39;
};

void Rva00271A0F::rva00271A0F(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	Rva0030612AXfer(xfer, m_04);
	Rva0030612AXfer(xfer, m_04 + 3);
	Rva0030612AXfer(xfer, m_04 + 6);
	Rva0030612AXfer(xfer, m_04 + 9);
	*xfer == m_34;
	*xfer == m_39;
	*xfer == m_38;
}
