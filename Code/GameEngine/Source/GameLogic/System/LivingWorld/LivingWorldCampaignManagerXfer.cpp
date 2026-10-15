// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
//
// ?rva003B8F76@Rva003B8F76@@QAEXPAVXfer@@@Z, retail 0x003B8F76..0x003B9051 (213
// bytes, EH, thiscall RET 4): the Xfer method of the secondary interface that the
// LivingWorldCampaignManager carries at +0xC (its primary receiver is this - 0xC;
// the primary lookup 0x003B8E2B is rowed in LivingWorldCampaignManager.cpp). Unless
// the stream is a light CRC: transfer a version 1, then the name of the current
// campaign entry (loading: read the name, resolve it through the rowed lookup and
// store the index; saving: copy the entry's name from +4) and let the entry
// transfer itself (its virtual slot +0xC), then transfer the flag at +0x20.
// Evidence (target): native bytes, Xfer slots +0x04 IsLoading / +0x10 IsLightCRC /
// +0x28 xferVersion / +0x6C xferAsciiString / +0x90 xferBool (the views of
// LivingWorldBattleResultsXfer.cpp and LivingWorldLogicXferStateRva002BB2B7.cpp);
// the member names are address-derived. No WorldBuilder twin matches this build
// (WB 0x010325A0 only supports the shape).
#include "ascii_string.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};
class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(Bool *value);
};

class Rva003B8F76;
class LivingWorldCampaignManager
{
	friend class Rva003B8F76;
	__declspec(nothrow) int rva003B8E2B(const AsciiString &);
};

class Rva003B8F76Entry
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	AsciiString m_name;
};

class Rva003B8F76
{
public:
	virtual void slot00();
	void rva003B8F76(Xfer *xfer);
private:
	int m_index;
	Rva003B8F76Entry **m_entries;
	char m_pad0c[0x14];
	Bool m_flag20;
};

void Rva003B8F76::rva003B8F76(Xfer *xfer)
{
	if (!xfer->IsLightCRC()) {
		XferVersion version;
		version.m_fields.m_version = 1;
		version.m_fields.m_currentVersion = 1;
		xfer->xferVersion(&version);
		if (xfer->IsLoading()) {
			AsciiString name;
			xfer->xferAsciiString(&name);
			m_index = ((LivingWorldCampaignManager *)((char *)this - 0xC))->rva003B8E2B(name);
			m_entries[m_index]->xfer(xfer);
		} else {
			Rva003B8F76Entry **entries = m_entries;
			int i = m_index;
			AsciiString name(entries[i]->m_name);
			xfer->xferAsciiString(&name);
			{ Rva003B8F76Entry **v = m_entries; v[m_index]->xfer(xfer); }
		}
		xfer->xferBool(&m_flag20);
	}
}
