// cl: /MD
// ?xfer@Rva00340461@@MAEXPAVXfer@@@Z, retail 0x00340461, 42 bytes.
// Chain xfer: Version1 via 0x000053EE, bool at +0x54 via Xfer slot 0x90,
// then base Rva00340123 xfer via 0x00340123. Evidence: callees rowed,
// base size 0x54 from Rva00340123Xfer.cpp, no callers.
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

class Rva0033FF2B : public Rva0049B47C
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

class Rva00340123 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_4C;
	bool m_50;
};

class Rva00340461 : public Rva00340123
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_54;
};

class Rva00340411 : public Rva00340123
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva00340461::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_54;
	Rva00340123::xfer(xfer);
}

void Rva00340411::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00340123::xfer(xfer);
}
