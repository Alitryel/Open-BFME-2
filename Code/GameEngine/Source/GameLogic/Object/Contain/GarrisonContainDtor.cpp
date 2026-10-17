// cl: /DNDEBUG /MD /EHsc
//
// ??1GarrisonContain@@UAE@XZ retail 0x00478067 128 bytes.
// GarrisonContain virtual destructor over pinned OpenContain base 0x00464692.
// Restores nine vtable slots at +0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// then destroys 120 Coord3D at +0x424 via eh vector destructor iterator
// through folded dtor at 0x000B3FD0 then calls base dtor.
// Donor BFME1 GarrisonContainDestructor Coord3D 3x40 at 0x3FC moved to 0x424 in BFME2.
// Identity via deleting wrapper 0x0047860D slot0 vtable 0x00C461F8
// and pool key 0x0047801C with GarrisonContain string.
// Layout from ctor 0x00477F06 array 0x424 count 0x78 size 0x0C and factory news 0x9E0.
// Shape follows CaveContainDtor ten-vptr plus FlightDeck RunwayInfo Coord3D array precedent.

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();
private:
	unsigned char m_padFC424[0x424 - 0xFC];
	Coord3D m_garrisonPoint[120];
	unsigned char m_tail[0x9E0 - 0x9C4];
};

GarrisonContain::~GarrisonContain()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b1@B1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b6@B6@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?b0@B0@@UAEXXZ=??_GOpenContain@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?b2@B2@@UAEXXZ=?rva004640BE@Rva004640BE@@QAEHXZ")
#pragma comment(linker, "/alternatename:?b3@B3@@UAEXXZ=?rva0046261B@SlaughterHordeContain@@UAEX_N@Z")
#pragma comment(linker, "/alternatename:?b4@B4@@UAEXXZ=?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z")
#pragma comment(linker, "/alternatename:?b5@B5@@UAEXXZ=?onDie@OpenContain@@UAEXPBVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?b7@B7@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?b8@B8@@UAEXXZ=??1Region2D@@QAE@XZ")
