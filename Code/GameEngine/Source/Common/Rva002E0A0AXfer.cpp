// WotR player member ownership, 2026-10-12. Target table C04948 and its
// LWPlayerDef literal establish Snapshot identity independently of the bank.
// Default2E0EF7/copy2E0A0A/dtor2E0F1E and xfer52BA0A establish the 0x28-byte
// physical contract: wide handle04, narrow08/0C/10/14, ints18/1C/20, flag24.
// Legacy address-named views retain existing callers while emitting the same
// complete four-slot table. Every added fold has whole-body/relocation proof;
// no unique-byte credit for member aliases. See attempt_evidence/player-owners.
// cl: /O1 /G7 /arch:SSE /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /MD
// ?xfer@Rva002E0A0A@@MAEXPAVXfer@@@Z @0x0052BA0A 161B slot 3 xfer via Version plus IsLightCRC plus strings plus ints.
// Evidence: vslot slot 3 of 0x00804948; donor CopyCtor 0x002E0A0A same members; callers vtable.
#include "ascii_string.h"
#include "unicode_string.h"
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
class Xfer::Version
{
public:
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002E0A0A : public Snapshot
{
public:virtual ~Rva002E0A0A();
protected:virtual void loadPostProcess();virtual const char*GetSnapshotName()const;
	virtual void xfer(Xfer *xfer);
private:
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	int m_20;
	bool m_24;
};
void Rva002E0A0A::xfer(Xfer *xfer)
{
	Xfer::Version v(1, 2);
	*xfer == v;
	if (!xfer->IsCRC())
		*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_14;
	*xfer == m_1c;
	*xfer == m_10;
	*xfer == m_18;
	*xfer == m_24;
	if (v.m_minor >= 2)
		*xfer == m_20;
	else
		m_20 = 0;
}
