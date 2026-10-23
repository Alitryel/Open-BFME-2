// cl: /MD
// ?rva005622A6@Rva005622A6@@QAEXPAVXfer@@@Z @0x005622A6 164B: Rva0056224F
// xfer (Version1 plus twelve floats +0x4..+0x30 via slot 0x70 plus rotation
// enum at +0x34 via rowed XferRotationType). Mirrors Rva0056224FCtor layout.

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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../../../Include/Common/BfmeXfer.h"

void XferRotationType(Xfer *xfer, int *value);

class Rva005622A6
{
public:
	void rva005622A6(Xfer *xfer);
	virtual ~Rva005622A6();

private:
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	int m_34;
};

void Rva005622A6::rva005622A6(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0C;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == m_18;
	*xfer == m_1C;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_2C;
	*xfer == m_30;
	XferRotationType(xfer, &m_34);
}
