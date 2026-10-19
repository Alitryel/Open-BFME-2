#include "../../GameClient/BuffManager.h"
// BF1 donor BuffTransfer0040A260.cpp at 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Donor carries control flow and snapshot semantics; target independently proves
// version5 and TBUFF block plus the fields at04..30 and its template name at64.
// BuffManager::xfer362702 iterates nine44B entries and publishes g_Va00E01E74;
// target3628D3 is BuffInstance transfer: native table C17068 slot2 names the
// class and slot3 points at this whole body. Existing rowed lookup2D06CA and BuffLogic::addBuff30682A
// resolve the target providers. The Xfer slot view follows SnapshotXfersBfme.
// Full482B body and EH exact with BFME2's canonical AsciiString header.
// cl: /MD /O1 /Oy- /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	__declspec(dllimport) __forceinline Version() {}
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException {public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
struct BlockView003628D3 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
 virtual void begin(const char*); virtual void end(); virtual void skip(const char*);
};
struct Snapshot003628D3 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void transfer(Xfer*);
};
class ThingTemplate;
// Callable view of the rowed template lookup; its argument is a string pointer.
class ThingFactory;
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &name);};
extern ThingFactory *TheThingFactory;
class BuffLogic {public:void *addBuff(void*,void*);};
extern BuffLogic *TheBuffLogic;
extern void *g_Va00E01E74;
#include "../../../../Libraries/Include/Lib/RGBColor.h"

struct VersionStorage { Xfer::Version value; unsigned short padding; };
void BuffInstance::DoXfer(Xfer *xfer) {
 { VersionStorage storage; Xfer::Version &version=storage.value; version.m_current=1; version.m_minimum=5;
 *xfer == version;
 if(xfer->IsCRC()) return;
 if(version.m_minimum<5) throw XferException(2,0); }
 *xfer == m_active;
 xfer->XferRawBytes(&m_type,4);
 xfer->XferRawBytes(&m_subType,4);
 *xfer == m_duration; *xfer == reinterpret_cast<int &>(m_frameLimit);
 bool hasTemplate=m_thing!=0;
 *xfer == hasTemplate;
 AsciiString name;
 if(xfer->IsLoading()) {
  if(hasTemplate) {
   *xfer == name;
   m_thing=TheThingFactory->findTemplate(name);
   if(!m_thing) throw XferException(4,0);
  } else m_thing=0;
 } else if(hasTemplate) {
  name=*(const AsciiString*)((const char*)m_thing+0x64);
  *xfer == name;
 }
 bool hasEffect=m_glow!=0;
 *xfer == hasEffect;
 if(xfer->IsLoading()) {
  if(hasEffect) {
   if(m_thing && g_Va00E01E74) {
    m_glow=(Rva00419BA5*)TheBuffLogic->addBuff((void*)m_thing,g_Va00E01E74);
    ((BlockView003628D3*)xfer)->begin("TBUFF");
    ((Snapshot003628D3*)m_glow)->transfer(xfer);
    ((BlockView003628D3*)xfer)->end();
   } else ((BlockView003628D3*)xfer)->skip("TBUFF");
  } else m_glow=0;
 } else if(hasEffect) {
  ((BlockView003628D3*)xfer)->begin("TBUFF");
    ((Snapshot003628D3*)m_glow)->transfer(xfer);
    ((BlockView003628D3*)xfer)->end();
 }

 *xfer == m_color;
 *xfer == m_intensity;
 m_material.DoXfer(xfer);
}
