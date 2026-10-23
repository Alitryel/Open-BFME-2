// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// Substantial BFME1-guided reconstruction (not a byte-cp: BFME1 addresses,
// pools and string globals differ).
// Reference: reference/open-bfme-1/Code/GameEngine/Source/GameClient/RadiusDecalTemplate_ctor.cpp
// (carved donor for the BFME1 twin at 0x00458830 with the same layout).
//
// ??0RadiusDecalTemplate@@QAE@XZ, retail 0x00330E5D, 131 bytes.
// RadiusDecalTemplate ctor: two AsciiStrings at +0x00/+0x04 copy-constructed
// from the empty string via 0x365F0, shadow style 0x20 at +0x08, 1.0f for each
// of the two opacities at +0x0C/+0x10, 1000.0f throb time at +0x14, no colour
// at +0x18, visible-to-owning-player at +0x1C, and float zeros at
// +0x20/+0x24/+0x2C/+0x30 with an int zero at +0x28. Table evidence lives in
// the DynamicShroud/Tornado member uses (RadiusDecalTemplate member at +8 via
// this pin). Shard (not a graft into RadiusDecal_ctor.cpp) so that TU's
// frameless /EHsc-off shape stays green.

#include "ascii_string.h"

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
#include "../../Include/Common/BfmeXfer.h"

void XferShadowType(Xfer *xfer, int *value);

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	void xferRadiusDecalTemplate(Xfer *xfer);

private:
	AsciiString m_name; // +0x00
	AsciiString m_secondName; // +0x04
	int m_shadowType; // +0x08
	float m_minOpacity; // +0x0C
	float m_maxOpacity; // +0x10
	float m_opacityThrobTime; // +0x14
	int m_color; // +0x18
	bool m_onlyVisibleToOwningPlayer; // +0x1C
	float m_unmodelled20; // +0x20
	float m_unmodelled24; // +0x24
	unsigned int m_unmodelled28; // +0x28
	float m_unmodelled2C; // +0x2C
	float m_unmodelled30; // +0x30
};

// ??0RadiusDecalTemplate@@QAE@XZ @0x00330E5D
RadiusDecalTemplate::RadiusDecalTemplate()
	: m_name(AsciiString::TheEmptyString),
	  m_secondName(AsciiString::TheEmptyString),
	  m_shadowType(0x20),
	  m_minOpacity(1.0f),
	  m_maxOpacity(1.0f),
	  m_opacityThrobTime(1000.0f),
	  m_color(0),
	  m_onlyVisibleToOwningPlayer(true),
	  m_unmodelled20(0.0f),
	  m_unmodelled24(0.0f),
	  m_unmodelled28(0),
	  m_unmodelled2C(0.0f),
	  m_unmodelled30(0.0f)
{
}

// Native Ghidra RET4 boundary 0x00330EE0..0x00330F7D, 157 bytes.
// Donor: GeneralsMD/Code/GameEngine/Source/GameClient/RadiusDecal.cpp,
// via BFME1 reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20.
// ZH RadiusDecalTemplate::xferRadiusDecalTemplate supplies the transfer
// purpose; the existing target constructor/assignment prove this layout.
// BFME2 has a second string, float throb time, five extra tail fields and
// no local version. The original target method name is not established.
void RadiusDecalTemplate::xferRadiusDecalTemplate(Xfer *xfer)
{
    *xfer == m_name;
    *xfer == m_secondName;
    XferShadowType(xfer, &m_shadowType);
    *xfer == m_minOpacity;
    *xfer == m_maxOpacity;
    *xfer == m_opacityThrobTime;
    *xfer == m_color;
    *xfer == m_onlyVisibleToOwningPlayer;
    *xfer == m_unmodelled24;
    *xfer == m_unmodelled20;
    *xfer == m_unmodelled28;
    *xfer == m_unmodelled2C;
    *xfer == m_unmodelled30;
}
