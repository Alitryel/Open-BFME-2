// cl: /MD
//
// ?xfer@Rva00340123@@MAEXPAVXfer@@@Z retail 0x00340123 53B slot 3.
// Evidence: Version1 via rowed 0x000053EE; base AIInternalMoveToState xfer via rowed
// 0x0033FF76; int at +0x4C via Xfer slot 0x7C; bool at +0x50 via slot 0x90;
// callers at 0x00340423 0x00340481.
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

#include "../../Include/Common/BfmeXfer.h"

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
private:
	char m_pad04[8];
};

class AIInternalMoveToState : public Rva0049B47C
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad0C[0x20 - 0x0C];
	float m_20[3];
	float m_2C;
	int m_30;
	float m_34[3];
	unsigned int m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva00340123 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_4C;
	bool m_50;
};

void Rva00340123::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	*xfer == m_4C;
	*xfer == m_50;
}
