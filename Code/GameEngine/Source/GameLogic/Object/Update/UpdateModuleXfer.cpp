// cl: /DNDEBUG /MD /GX
// stlport
//
// ?xfer@UpdateModule@@QAEXPAVXfer@@@Z retail 0x0044DF9F
// 62 bytes. UpdateModule base xfer used by every behavior-side xfer in the
// file-unit vein (DynamicShroudClearingRangeUpdate::xfer rowed over its pin;
// row supersedes that pin here).
//
// Shape from retail plus the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/UpdateModule.cpp):
// Version1, BehaviorModule base xfer (pinned), light-CRC early-out, one
// unsigned run over the next-call frame/phase slot, and a load-gated
// all-ones store to the logic-index slot. The Xfer declaration is the
// SkirmishGameInfoXfer proven spelling (IsLoading slot 1, IsLightCRC
// slot 4, Version1 direct row, == uint at 0x78).

// The shared headers declare these members with the access/virtual spelling
// retail's vftables reference; the ledger row keeps the spelling this TU
// compiled to. Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:?xfer@UpdateModule@@MAEXPAVXfer@@@Z=?xfer@UpdateModule@@QAEXPAVXfer@@@Z")
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

class BehaviorModule
{
public:
	void xfer(Xfer *xfer);
};

class UpdateModule : public BehaviorModule
{
public:
	void xfer(Xfer *xfer);

private:
	char m_unreconstructed_00[0x14];
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
};

// ?xfer@UpdateModule@@QAEXPAVXfer@@@Z @0x0044DF9F
void UpdateModule::xfer(Xfer *xfer)
{
	xfer->Version1();

	BehaviorModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	*xfer == m_nextCallFrameAndPhase;

	if (xfer->IsLoading())
		m_indexInLogic |= -1;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?xfer@UpdateModule@@UAEXPAVXfer@@@Z=?xfer@UpdateModule@@QAEXPAVXfer@@@Z")
