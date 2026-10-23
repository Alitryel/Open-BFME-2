// cl: /DNDEBUG /MD /GX
// ?xfer@HordeTransportContain@@MAEXPAVXfer@@@Z, retail 0x0047714A, 59 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00845EB8 (class of
// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// HordeTransportContainCtor.cpp). Version1 via rowed 0x000053EE then
// rowed TransportContain::xfer 0x00466DBC then int at +0x120 via Xfer
// slot 0x7c and bool at +0x124 via Xfer slot 0x90 (same slots as
// TransportContain::xfer uses for int at +0x100 and bool at +0x10C).
// Layout from HordeTransportContainCtor (int -1000 at +0x120 and zero
// byte at +0x124); Xfer declaration copied verbatim from
// TransportContainXfer.cpp per xfer recipe.
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

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class OpenContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x100 - 0x04 ];
};

class TransportContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_extraSlotsInUse;
	UnsignedInt m_frameExitNotBusy;
	char m_unrecovered108[ 0x10C - 0x108 ];
	Bool m_payloadCreated;
};

class HordeTransportContain : public TransportContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_pad110[ 0x120 - 0x110 ];
	Int m_int120;
	Bool m_bool124;
};

void HordeTransportContain::xfer( Xfer *xfer )
{
	xfer->Version1();
	TransportContain::xfer( xfer );
	*xfer == m_int120;
	*xfer == m_bool124;
}
